#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    string op;
    getline(cin, op);
    
    int N;
    cin >> N; cin.ignore();
    
    std::vector<std::string> rotors;
    for (int i = 0; i < 3; i++) {
        string rotor;
        getline(cin, rotor);
        rotors.emplace_back(rotor);
    }
    
    string msg;
    getline(cin, msg);
    
    auto toIndex = [](char c) {
        return ((int)c - (int)'A') % 26;
    };
    
    auto toChar = [](char c) {
        return char(c + (int)'A');
    };
    
    auto indexOf = [](const std::string& r, char c) {
        for (int i = 0; i < r.size(); ++i) {
            if (r[i] == c) return i;
        }
    };

    if (op == "ENCODE") {
        std::vector<int> encode;
        for (int i = 0; i < msg.length(); ++i) {
            encode.push_back(toIndex(int(msg[i]) + N + i % 26));
        }
        
        for (auto&& r : rotors) {
            for (int i = 0; i < encode.size(); ++i) {
                encode[i] = toIndex(r[encode[i]]);
            }
        }
        
        for (auto&& x : encode) std::cout << toChar(x);
    } else {
        for (int i = 0; i < msg.length(); ++i) {
            msg[i] = toChar(indexOf(rotors[2], msg[i]));
        }
        
        for (int i = 0; i < msg.length(); ++i) {
            msg[i] = toChar(indexOf(rotors[1], msg[i]));
        }
        
        for (int i = 0; i < msg.length(); ++i) {
            msg[i] = toChar(indexOf(rotors[0], msg[i]));
        }
        
        for (int i = 0; i < msg.length(); ++i) {
            int idx = (toIndex(msg[i]) - N - i) % 26;
            std::cout << toChar(toIndex(toChar(idx > 0 ? idx : 26 + idx)));
        }
    }
}