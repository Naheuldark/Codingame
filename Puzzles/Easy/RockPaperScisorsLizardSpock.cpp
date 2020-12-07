#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Player {
    int id;
    std::string sign;
    std::vector<int> adv;

    Player(int id, std::string sign) : id(id), sign(sign) {}
};

Player battle(Player& p1, Player& p2) {
    p1.adv.emplace_back(p2.id);
    p2.adv.emplace_back(p1.id);

    if ((p1.sign == "C" && p2.sign == "P") ||
		(p1.sign == "P" && p2.sign == "R") ||
		(p1.sign == "R" && p2.sign == "L") ||
		(p1.sign == "L" && p2.sign == "S") ||
		(p1.sign == "S" && p2.sign == "C") ||
		(p1.sign == "C" && p2.sign == "L") ||
		(p1.sign == "L" && p2.sign == "P") ||
		(p1.sign == "P" && p2.sign == "S") ||
		(p1.sign == "S" && p2.sign == "R") ||
		(p1.sign == "R" && p2.sign == "C") ||
		// They played the same sign
		(p1.sign == p2.sign && p1.id < p2.id)) {
		return p1;
	} else {
		return p2;
	}
}

int main()
{
    int N;
    cin >> N; cin.ignore();
    std::vector<Player> players;
    for (int i = 0; i < N; i++) {
        int NUMPLAYER;
        string SIGNPLAYER;
        cin >> NUMPLAYER >> SIGNPLAYER; cin.ignore();
        players.emplace_back(NUMPLAYER, SIGNPLAYER);
    }

    while (players.size() > 1) {
        // Play a round
		std::vector<Player> nextRoundPlayers;
		for (size_t idx = 0; idx < players.size(); idx += 2) {
			nextRoundPlayers.emplace_back(battle(players[idx], players[idx+1]));
		}
		players = nextRoundPlayers;
    }

    cout << players[0].id << endl;
    for (size_t i = 0; i < players[0].adv.size(); ++i) {
         cout << players[0].adv[i]; 
         if (i < players[0].adv.size()-1) cout << " ";
    }
    cout << endl;
}