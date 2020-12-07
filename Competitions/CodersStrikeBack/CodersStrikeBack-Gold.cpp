#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <memory>
#include <random>
#include <map>

const int kSHIELD = -1;
const int kSHIELD_PROB = 20;


const int kMAX_TURNS = 6;
const int kNB_SOLUTIONS = 5;
const int kMAX_TIME = 150;

std::random_device rd;
std::mt19937 gen(rd());


class Point;
class Unit;
class Pod;
class Checkpoint; 

float eval(const std::vector<std::shared_ptr<Pod>>& pods, const std::vector<std::shared_ptr<Checkpoint>>& checkpoints, int laps);
void play(const std::vector<std::shared_ptr<Pod>>& pods, const std::vector<std::shared_ptr<Checkpoint>>& checkpoints);


// Collision class
class Collision {
public:
    Collision(std::shared_ptr<Unit> a, std::shared_ptr<Unit> b, float t) : _a(a), _b(b), _t(t) {}
    ~Collision() = default;

public:
    std::shared_ptr<Unit> _a;
    std::shared_ptr<Unit> _b;
    float _t;
};

// Move class
class Move {
public:
    Move(float angle, int thrust) : _angle(angle), _thrust(thrust) {}
    ~Move() = default;

    static std::shared_ptr<Move> Randomize() {
    	std::uniform_real_distribution<> disangle(-18.0, 18.0);
    	std::uniform_int_distribution<> disthrust(-1, 100);
    	return std::make_shared<Move>(disangle(gen), disthrust(gen));
    }

    void mutate(float amplitude) {
    	// Mutate angle
    	float ramin = _angle - 36.0 * amplitude;
    	float ramax = _angle + 36.0 * amplitude;
    	
    	if (ramin < -18.0) ramin = -18.0;
    	if (ramax > 18.0) ramax = 18.0;

    	std::uniform_real_distribution<> disangle(ramin, ramax);
    	_angle = disangle(gen);

    	// Mutate shield
    	std::uniform_int_distribution<> disshield(0, 100);
    	if (_thrust != kSHIELD && disshield(gen) < kSHIELD_PROB) {
    		_thrust = kSHIELD;
    	} else {
    		int pmin = _thrust - 100 * amplitude;
    		int pmax = _thrust + 100 * amplitude;

    		if (pmin < 0) pmin = 0;
    		if (pmax > 100) pmax = 100;

    		std::uniform_int_distribution<> disthrust(pmin, pmax);
    		_thrust = disthrust(gen);
    	}
    }

public:
	float _angle; // Between -18.0 and +18.0
	int _thrust; // Between -1 (shield) and 100
};

// Point class
class Point {
public:
    Point(float x, float y) : _x(x), _y(y) {}
    virtual ~Point() = default;

    float distance2(std::shared_ptr<Point> p) const { return (_x - p->_x)*(_x - p->_x) + (_y - p->_y)*(_y - p->_y); }
    float distance(std::shared_ptr<Point> p) const { return sqrt(distance2(p)); }

    std::shared_ptr<Point> closest(std::shared_ptr<Point> a, std::shared_ptr<Point> b) const {
        float da = b->_y - a->_y;
        float db = a->_x - b->_x;
        float c1 = da*a->_x + db*a->_y;
        float c2 = -db*_x + da*_y;
        float det = da*da + db*db;
        float cx = 0.0f;
        float cy = 0.0f;

        if (det != 0.0) {
            cx = (da*c1 - db*c2) / det;
            cy = (da*c2 + db*c1) / det;
        } else {
            // Point already on the collision line
            cx = _x;
            cy = _y;
        }

        return std::make_shared<Point>(cx, cy);
    }

public:
    float _x = 0.0f;
    float _y = 0.0f;
};

// Unit class
class Unit : public Point {
public:
    Unit(int id, float x, float y, float r = 0.0f) : Point(x, y), _id(id), _r(r) {}
    Unit(const Unit& ) = default;

    std::shared_ptr<Collision> collision(std::shared_ptr<Unit> u) {
        float dist = distance2(u);
        float sr = (_r + u->_r)*(_r + u->_r);

        // Objects are already one onto another --> Collision!
        if (dist < sr) {
            return std::make_shared<Collision>(std::shared_ptr<Unit>(this), u, 0.0f);
        }

        // Objects have same speed --> No collision
        if (_vx == u->_vx && _vy == u->_vy) {
            return nullptr;
        }

        // Change referential to u
        float x = _x - u->_x;
        float y = _y - u->_y;
        auto&& myp = std::make_shared<Point>(x, y);
        float vx = _vx - u->_vx;
        float vy = _vy - u->_vy;
        auto&& up = std::make_shared<Point>(0, 0);

        // Look for the closest point to u on the line described by the speed vector
        auto&& p = up->closest(myp, std::make_shared<Point>(x + vx, y + vy));
        float pdist = up->distance2(p);
        float mypdist = myp->distance2(p);

        // If distance between u and this line is less than sum of radiuses
        if (pdist < sr) {
            float length = sqrt(vx*vx + vy*vy);

            // Move point on line to find impact point
            float backdist = sqrt(sr - pdist);
            p->_x = p->_x - backdist * (vx / length);
            p->_y = p->_y - backdist * (vy / length);

            // Impact point went further --> No collision
            if (myp->distance2(p) > mypdist) {
                return nullptr;
            }

            // Impact is too far away --> No collision
            pdist = p->distance(myp);
            if (pdist > length) {
                return nullptr;
            }

            // Time until impact
            float t = pdist / length;
            return std::make_shared<Collision>(std::shared_ptr<Unit>(this), u, t);
        }

        return nullptr;
    }

    void bounce(std::shared_ptr<Unit> u) {}

public:
    int _id;
    float _r = 0.0f;
    float _vx = 0.0f;
    float _vy = 0.0f;
};

// Checkpoint class
class Checkpoint : public Unit {
public:
    Checkpoint(int id, float x, float y, float r) : Unit(id, x, y, r) {}

    void bounce(std::shared_ptr<Unit> u) {}
};

// Pod class
class Pod : public Unit {
public:
    Pod(int id, int x, int y, float r, float angle = 0.0f) : Unit(id, x, y, r), _angle(angle) {}

    void activateShield() { _shield = true; _shieldTimeout = 3; }

    // Return the angle to face the given Point p
    float getAngle(std::shared_ptr<Point> p) const {
        float d = distance(p);
        float dx = (p->_x - _x) / d;
        float dy = (p->_y - _y) / d;

        float a = acos(dx) * 180.0 / M_PI;
        if (dy < 0) {
            a = 360.0 - a;
        }

        return a;
    }

    // Returs how much to rotate to face Point p, and in which direction
    float diffAngle(std::shared_ptr<Point> p) const {
        float a = getAngle(p);
        float rightTurn = (_angle <= a) ? (a - _angle) : (360.0 - _angle + a);
        float leftTurn = (_angle >= a) ? (_angle - a) : (_angle + 360.0 - a);

        if (rightTurn < leftTurn) {
            return rightTurn;
        } else {
            return -leftTurn; // Neg for turning left
        }
    }

    // Perform a rotation of the pod
    void rotate(std::shared_ptr<Point> p) { rotate(diffAngle(p)); }
    void rotate(float a) {
        // Maximum angle per turn is 18deg
        if (a > 18.0) {
            a = 18.0;
        } else if (a < -18.0) {
            a = -18.0;
        }

        _angle += a;
        if (_angle >= 360.0) {
            _angle = _angle - 360.0;
        } else if (_angle < 0.0) {
            _angle += 360.0;
        }
    }

    // Apply thrust
    void boost(int thrust) {
        if (_shield || (_shieldTimeout > 0 && _shieldTimeout < 3)) return;

        float ra = _angle * M_PI / 180.0;

        _vx += cos(ra) * thrust;
        _vy += sin(ra) * thrust;
    }

    // Move the pod
    void move(float t) {
        _x += _vx * t;
        _y += _vy * t;
    }

    // Apply friction and round up
    void end() {
        _x = std::round(_x);
        _y = std::round(_y);
        _vx = int(_vx * 0.85);
        _vy = int(_vy * 0.85);

        _timeout--;

        // Shield
        _shield = false;
        if (_shieldTimeout != 0) {
            _shieldTimeout--;
        }
    }


    // Play full turn
    void play(std::shared_ptr<Point> p, int thrust) {
        rotate(p);
        boost(thrust);
        move(1.0);
        end();
    }

    void bounce(std::shared_ptr<Unit> u) {
        // Collision with checkpoint
        if (dynamic_cast<Checkpoint*>(u.get())) {
            _checked++;
            _timeout = 100;
        }
        // Collision with other pod
        else {
            auto&& p = std::shared_ptr<Pod>(dynamic_cast<Pod*>(u.get()));

            // Shield
            float m1 = _shield ? 10.0f : 1.0f;
            float m2 = p->_shield ? 10.0f : 1.0f;
            float mcoeff = (m1 + m2) / (m1 * m2);

            float nx = _x - p->_x;
            float ny = _y - p->_y;
            float nxnysq = nx*nx + ny*ny;

            float dvx = _vx - p->_vx;
            float dvy = _vy - p->_vy;

            // Create impact vector
            float product = nx*dvx + ny*dvy;
            float fx = (nx * product) / (nxnysq * mcoeff);
            float fy = (ny * product) / (nxnysq * mcoeff);

            // Apply it on each pod
            _vx -= fx / m1;
            _vy -= fy / m1;
            p->_vx += fx / m2;
            p->_vy += fy / m2;

            // Trunc norm to 120 for impact vector
            float impulse = sqrt(fx*fx + fy*fy);
            if (impulse < 120.0) {
                fx = fx * 120.0 / impulse;
                fy = fy * 120.0 / impulse;
            }

            // Apply second time
            _vx -= fx / m1;
            _vy -= fy / m1;
            p->_vx += fx / m2;
            p->_vy += fy / m2;

        }
    }

    void output(std::shared_ptr<Move> move) {
    	float a = _angle + move->_angle;
    	if (a >= 360.0) a = a - 360.0;
    	else if (a < 0.0) a += 360.0;

    	a = a * M_PI / 180.0;
    	float px = _x + cos(a) * 10000.0;
    	float py = _y + sin(a) * 10000.0;

    	if (move->_thrust == kSHIELD) {
    		std::cout << std::round(px) << " " << std::round(py) << " SHIELD" << std::endl;
    		activateShield();
    	} else {
    		std::cout << std::round(px) << " " << std::round(py) << " " << move->_thrust << std::endl;
    	}
    }

    float score(std::shared_ptr<Checkpoint> next) const {
        return _checked*50000 - distance(next);
    }

    void apply(std::shared_ptr<Move> move) {
    	rotate(move->_angle);

    	if (move->_thrust == kSHIELD) {
    		activateShield();
    	} else {
    		boost(move->_thrust);
    	}
    }

    std::shared_ptr<Pod> clone() {
        auto&& pod = std::make_shared<Pod>(_id, _x, _y, _r, _angle);
        pod->_nextCheckpointId = _nextCheckpointId;
        pod->_vx = _vx;
        pod->_vy = _vy;
        return pod;
    }

public:
    float _angle = 0.0f;
    bool _shield = false;
    int _shieldTimeout = 3;

    int _nextCheckpointId = 0;
    int _checked = 0;
    int _timeout = 100;
    
    std::shared_ptr<Pod> _partner = nullptr;
};

// Solution class
class Solution {
public:
    Solution() = default;
    Solution(const Solution&) = default;
    ~Solution() = default;

    static std::shared_ptr<Solution> Randomize() {
        auto&& solution = std::make_shared<Solution>();
    	for (size_t i = 0; i < kMAX_TURNS; ++i) {
    		solution->_moves1.emplace_back(Move::Randomize());
    		solution->_moves2.emplace_back(Move::Randomize());
    	}
        return solution;
    }

    std::shared_ptr<Solution> mutate(float amplitude) {
    	for (auto&& m : _moves1) m->mutate(amplitude);
    	for (auto&& m : _moves2) m->mutate(amplitude);
        return std::make_shared<Solution>(*this);
    }

    float score(const std::vector<std::shared_ptr<Pod>>& pods, const std::vector<std::shared_ptr<Checkpoint>>& checkpoints, int laps) {
    	// Clone pods to start fresh
    	std::vector<std::shared_ptr<Pod>> clones;
    	for (auto&& pod : pods) {
    		clones.emplace_back(pod->clone());
    	}

    	// Play turns
    	for (size_t i = 0; i < kMAX_TURNS; ++i) {
    		clones[0]->apply(_moves1[i]);
    		clones[1]->apply(_moves2[i]);

    		play(clones, checkpoints);
    	}

    	// Compute score
    	return eval(clones, checkpoints, laps);
    }

public:
	std::vector<std::shared_ptr<Move>> _moves1; // Possible moves for Pod 1 (max kMAX_TURNS)
	std::vector<std::shared_ptr<Move>> _moves2; // Possible moves for Pod 2 (max kMAX_TURNS)
};


// Get heuristic for the turn
float eval(const std::vector<std::shared_ptr<Pod>>& pods, const std::vector<std::shared_ptr<Checkpoint>>& checkpoints, int laps) {
    auto&& p1 = pods[0]; float s1 = p1->score(checkpoints[p1->_nextCheckpointId]);
    auto&& p2 = pods[1]; float s2 = p2->score(checkpoints[p2->_nextCheckpointId]);
    auto&& a1 = pods[2]; float sa1 = a1->score(checkpoints[a1->_nextCheckpointId]);
    auto&& a2 = pods[3]; float sa2 = a2->score(checkpoints[a2->_nextCheckpointId]);

    int totalCheckpoints = laps*checkpoints.size();

    // If I lose --> worst score
    if (a1->_checked == totalCheckpoints || a2->_checked == totalCheckpoints) {
        return -INFINITY;
    }

    // If I win --> best score
    if (p1->_checked == totalCheckpoints || p2->_checked == totalCheckpoints) {
        return INFINITY;
    }

    // Determine runner (ahead = better score) vs chaser
    std::shared_ptr<Pod> runner, chaser, advrunner;
    if (s1 < s2) {
        chaser = p1;
        runner = p2;
    } else {
        chaser = p2;
        runner = p1;
    }
    if (sa1 < sa2) {
        advrunner = a2;
    } else {
        advrunner = a1;
    }
    
    float score = 0.0f;

    // If I am ahead --> better score
    score += 50.0 * (runner->score(checkpoints[runner->_nextCheckpointId]) - advrunner->score(checkpoints[advrunner->_nextCheckpointId]));

    // If my chaser is close from adv runner's next checkpoint --> better score
    score += chaser->distance(checkpoints[advrunner->_nextCheckpointId]);

    // If my chaser is not targetting the adv runner --> lesser score
    score -= chaser->diffAngle(advrunner);

    return score;
}

// Simulate complete turn for all pods
void play(const std::vector<std::shared_ptr<Pod>>& pods, const std::vector<std::shared_ptr<Checkpoint>>& checkpoints) {
    float t = 0.0f;

    while (t < 1.0) {
        std::shared_ptr<Collision> firstCollision = nullptr;

        // Look for all collisions 
        for (size_t i = 0; i < pods.size(); ++i) {
            // Collision with pods?
            for (size_t j = i+1; j < pods.size(); ++j) {
                auto&& col = pods[i]->collision(pods[j]);
                if (col && (col->_t + t < 1.0) && (!firstCollision || col->_t < firstCollision->_t)) {
                    firstCollision = col;
                }
            }

            // Collision with chekpoint?
            auto&& col = pods[i]->collision(checkpoints[pods[i]->_nextCheckpointId]);
            if (col && (col->_t + t < 1.0) && (!firstCollision || col->_t < firstCollision->_t)) {
                firstCollision = col;
            }
        }

        // No collision for this turn --> Just move pods
        if (!firstCollision) {
            for (auto&& pod : pods) {
                pod->move(1.0 - t);
            }

            // End of turn
            t = 1.0f;
        }
        // Move pods until collision time and play collision
        else {
            for (auto&& pod : pods) {
                pod->move(firstCollision->_t);
            }
            firstCollision->_a->bounce(firstCollision->_b);

            t += firstCollision->_t;
        }
    }

    // Call end for all pods
    for (auto&& pod : pods) {
        pod->end();
    }
}

std::map<float, std::shared_ptr<Solution>> generatePopulation(const std::vector<std::shared_ptr<Pod>>& pods, const std::vector<std::shared_ptr<Checkpoint>>& checkpoints, int laps) {
	std::map<float, std::shared_ptr<Solution>> solutions;
	for (size_t i = 0; i < kNB_SOLUTIONS; ++i) {
		auto&& solution = Solution::Randomize();
		solutions[solution->score(pods, checkpoints, laps)] = solution;
	}
	return solutions;
}

// Simulate kMAX_TURNS using genetic evolution and kNB_SOLUTIONS
void test(const std::vector<std::shared_ptr<Pod>>& pods, const std::vector<std::shared_ptr<Checkpoint>>& checkpoints, int laps) {
    auto&& solutions = generatePopulation(pods, checkpoints, laps);

    int time = 0;
    while (time < kMAX_TIME) {
    	float amplitude = 1.0 - (9.0 * time) / (kMAX_TIME * 10.0);

		std::uniform_int_distribution<> dissol(0, kNB_SOLUTIONS-1);
    	auto&& solution = solutions[dissol(gen)]->mutate(amplitude);

    	// Add mutated solution to the list
    	solutions[solution->score(pods, checkpoints, laps)] = solution;

    	// Remove solution with worst score aka first element of the map
    	solutions.erase(solutions.begin());

    	time++;
    }
}

int main() {
    int laps;
    std::cin >> laps; std::cin.ignore();
    int checkpointCount;
    std::cin >> checkpointCount; std::cin.ignore();
    std::vector<std::shared_ptr<Checkpoint>> checkpoints;
    for (int i = 0; i < checkpointCount; i++) {
        int checkpointX;
        int checkpointY;
        std::cin >> checkpointX >> checkpointY; std::cin.ignore();
        checkpoints.emplace_back(std::make_shared<Checkpoint>(i+10, checkpointX, checkpointY, 600.0));
    }

    for (auto&& c : checkpoints) {
        std::cerr << "Checkpoint: " << c->_id << " (" << c->_x << ", " << c->_y << ")\n";
    }

    // Boosts
    bool b1 = true;
    bool b2 = true;

    // game loop
    while (true) {
        int x; // x position of your pod
        int y; // y position of your pod
        int vx; // x speed of your pod
        int vy; // y speed of your pod
        int angle; // angle of your pod
        int nextCheckPointId; // next check point id of your pod

        std::vector<std::shared_ptr<Pod>> pods;

		// Pod 1
        std::cin >> x >> y >> vx >> vy >> angle >> nextCheckPointId; std::cin.ignore();
        pods.emplace_back(std::make_shared<Pod>(1, x, y, 400, angle));
        pods[0]->_vx = vx;
        pods[0]->_vy = vy;
        pods[0]->_nextCheckpointId = nextCheckPointId;
        std::cerr << "Pod " << pods[0]->_id << ": (" << pods[0]->_x << ", " << pods[0]->_y << ") - (" << pods[0]->_vx << ", " << pods[0]->_vy << ") - " << pods[0]->_nextCheckpointId << "\n";

        // Pod 2
        std::cin >> x >> y >> vx >> vy >> angle >> nextCheckPointId; std::cin.ignore();
        pods.emplace_back(std::make_shared<Pod>(2, x, y, 400, angle));
        pods[1]->_vx = vx;
        pods[1]->_vy = vy;
        pods[1]->_nextCheckpointId = nextCheckPointId;
        std::cerr << "Pod " << pods[1]->_id << ": (" << pods[1]->_x << ", " << pods[1]->_y << ") - (" << pods[1]->_vx << ", " << pods[1]->_vy << ") - " << pods[1]->_nextCheckpointId << "\n";

        // Adv 1
        std::cin >> x >> y >> vx >> vy >> angle >> nextCheckPointId; std::cin.ignore();
        pods.emplace_back(std::make_shared<Pod>(3, x, y, 400, angle));
        pods[2]->_vx = vx;
        pods[2]->_vy = vy;
        pods[2]->_nextCheckpointId = nextCheckPointId;
        std::cerr << "Pod " << pods[2]->_id << ": (" << pods[2]->_x << ", " << pods[2]->_y << ") - (" << pods[2]->_vx << ", " << pods[2]->_vy << ") - " << pods[2]->_nextCheckpointId << "\n";

        // Adv 2
        std::cin >> x >> y >> vx >> vy >> angle >> nextCheckPointId; std::cin.ignore();
        pods.emplace_back(std::make_shared<Pod>(4, x, y, 400, angle));
        pods[3]->_vx = vx;
        pods[3]->_vy = vy;
        pods[3]->_nextCheckpointId = nextCheckPointId;
        std::cerr << "Pod " << pods[3]->_id << ": (" << pods[3]->_x << ", " << pods[3]->_y << ") - (" << pods[3]->_vx << ", " << pods[3]->_vy << ") - " << pods[3]->_nextCheckpointId << "\n";

        
    }
}