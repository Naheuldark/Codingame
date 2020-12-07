#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <math.h>

using namespace std;

/*
 * GLOBAL VARIABLES
 */
static const float distError = 2000;

/*
 * Vec2 class
 */
struct vec2 {

    float x;
    float y;
    
    vec2 (float s = 0.0) : x(s), y(s) {}
    vec2(float xx, float yy) : x(xx), y(yy) {}

    vec2(const vec2& v) { x = v.x;  y = v.y;  }
    
    float& operator [] (int i) { return *(&x + i); }
    const float operator [] (int i) const { return *(&x + i); }

    vec2 operator - () const { return vec2( -x, -y ); }
    vec2 operator + (const vec2& v) const { return vec2( x + v.x, y + v.y ); }
    vec2 operator - (const vec2& v) const { return vec2( x - v.x, y - v.y ); }
    vec2 operator * (const float s) const { return vec2( s*x, s*y ); }
    vec2 operator * (const vec2& v) const { return vec2( x*v.x, y*v.y ); }
    friend vec2 operator * (const float s, const vec2& v) { return v * s; }
    vec2 operator / (const float s) const { return *this * (float(1.0) / s); }

    bool operator == (const vec2& v) const { return ( x == v.x ) && ( y == v.y ); }
    bool operator != (const vec2& v) const { return ( x != v.x ) || ( y != v.y ); }

    vec2& operator += (const vec2& v) { x += v.x; y += v.y; return *this; }
    vec2& operator -= (const vec2& v) { x -= v.x; y -= v.y; return *this; }
    vec2& operator *= (const float s) { x *= s; y *= s; return *this; }
    vec2& operator *= (const vec2& v) { x *= v.x; y *= v.y; return *this; }
    vec2& operator /= (const float s) { *this *= (float(1.0) / s); return *this; }
};


inline float dot(const vec2& u, const vec2& v) { return u.x * v.x + u.y * v.y; }
inline float length(const vec2& v) { return std::sqrt( dot(v,v) ); }
inline vec2 normalize(const vec2& v) { return v / length(v); }

inline vec2 rotate(const vec2& v, float angle) { 
    float radian = angle * M_PI / 180;
    double sinAngle = sin(radian);
    double cosAngle = cos(radian);
    
    return vec2(v.x * cosAngle - v.y * sinAngle, v.y * cosAngle + v.x * sinAngle);
}

/*
 * Race Helper class
 */
class RaceHelper {
public:
    RaceHelper() : _boostAvailable(true), _allCheckpointFound(false), _furthestDist(0.0) {}

    bool boostAvailable() const { return _boostAvailable; }

    bool useBoost(float dist) {
        cerr << "BOOST left:" << _boostAvailable;
        cerr << " is 2nd Lap:" << _allCheckpointFound;
        cerr << " best boost dist:" << _furthestDist;
        cerr << " current dist:" << dist << endl;
        
        if (_boostAvailable && _allCheckpointFound && (dist + distError) > _furthestDist) {
            _boostAvailable = false;
            return true;
        } else {
            return false;
        }
        
    }
    
    void setNextCheckpoint(int x, int y, int dist) {
        if (_allCheckpointFound) { return; }
        
        const vec2 newCheckpoint(x, y);
        
        if (_checkpoints.empty()) {
            _checkpoints.push_back(newCheckpoint);
        } else if (_checkpoints.back() != newCheckpoint) {
            _checkpoints.push_back(newCheckpoint);

            if (_checkpoints.front() == newCheckpoint) {
                _allCheckpointFound = true;  
            }
        }
        
        if (_furthestDist < dist) {
            _furthestDist = dist;
        }
    }
        
private:
    bool _boostAvailable;
    bool _allCheckpointFound;
    float _furthestDist;
    std::vector<vec2> _checkpoints;
};

int main() {
    // Steering Behaviors
    // https://gamedevelopment.tutsplus.com/series/understanding-steering-behaviors--gamedev-12732
    // 1. Seek
    // 2. Boost
    // 3. Slowing Down (straight only)
    
    RaceHelper helper;
    
    const int kAngleToSteer = 1;
    const int kSlowingAngle = 90;
    const float kSlowingRadius = 600 * 4; // check point radius = 600
    
        
    // game loop
    while (1) {
        int x;
        int y;
        int nextCheckpointX; // x position of the next check point
        int nextCheckpointY; // y position of the next check point
        int nextCheckpointDist; // distance to the next checkpoint
        int nextCheckpointAngle; // angle between your pod orientation and the direction of the next checkpoint
        cin >> x >> y >> nextCheckpointX >> nextCheckpointY >> nextCheckpointDist >> nextCheckpointAngle; cin.ignore();
        int opponentX;
        int opponentY;
        cin >> opponentX >> opponentY; cin.ignore();

        helper.setNextCheckpoint(nextCheckpointX, nextCheckpointY, nextCheckpointDist);
        
        cerr << "x:" << x << ", y:" << y << endl;
        cerr << "nextCheckpoint x:" << nextCheckpointX << ", y:" << nextCheckpointY << endl;
        cerr << "nextCheckpoint angle:" << nextCheckpointAngle << endl;
        cerr << "nextCheckpointDist:" << nextCheckpointDist << endl;
        
        int thrust = 100;
        bool useBoost = false;
        
        if (nextCheckpointAngle <= -kAngleToSteer || nextCheckpointAngle >= kAngleToSteer) {
            // 1. Seek
            vec2 desiredDirection(nextCheckpointX - x, nextCheckpointY - y);
            desiredDirection = normalize(desiredDirection);
            
            vec2 currentDirection = rotate(desiredDirection, -nextCheckpointAngle);
            currentDirection = normalize(currentDirection);
            
            vec2 steeringDirection = (desiredDirection - currentDirection);
            steeringDirection = normalize(steeringDirection) * 100;
            
            nextCheckpointX += steeringDirection.x;
            nextCheckpointY += steeringDirection.y;
            
            // 2. Slowing Down (angle)
            if (nextCheckpointAngle <= -kSlowingAngle || nextCheckpointAngle >= kSlowingAngle) {
                thrust = 0;
            } else if (nextCheckpointDist < kSlowingRadius) {
                thrust *= (kSlowingAngle - abs(nextCheckpointAngle)) / (float)kSlowingAngle;
            }
        } else {
            if (helper.useBoost(nextCheckpointDist)) {
                useBoost = true;
            } else if (nextCheckpointDist < kSlowingRadius) {
                // 2. Slowing Down (radius)
                thrust *= nextCheckpointDist / kSlowingRadius;
            }
        }
        
        // Output
        cout << nextCheckpointX << " " << nextCheckpointY << " ";
        if (useBoost) {
            cout << "BOOST" << endl;
        } else {
            cout << thrust << endl;
        }
    }
}