#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int N;
    cin >> N; cin.ignore();
    int L;
    cin >> L; cin.ignore();
    
    auto initArray = [&N](std::vector<std::vector<int>>& arr) {
        for (int i = 0; i < N; ++i) {
            std::vector<int> ll;
            for (int j = 0; j < N; ++j) {
                ll.push_back(0);
            }
            arr.emplace_back(ll);
        }
    };
    
    std::vector<std::vector<std::string>> room;
    std::vector<std::vector<int>> light;
    initArray(light);
    
    for (int i = 0; i < N; i++) {
        string line;
        getline(cin, line);
        std::istringstream iss(line);
        room.emplace_back(std::vector<std::string>{std::istream_iterator<std::string>(iss), {}});
    }
    
    auto createLight = [&N, &L](int row, int col) {
        std::vector<std::vector<int>> arr;
        
        for (int i = 0; i < N; ++i) {
            std::vector<int> ll;
            for (int j = 0; j < N; ++j) {
                ll.push_back(std::max(0, L - std::max(std::abs(row-i), std::abs(col-j))));
            }
            arr.emplace_back(ll);
        }
        
        return arr;
    };
    
    auto add = [&light, &N](const std::vector<std::vector<int>> &newLight) {
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) { 
                light[r][c] += newLight[r][c];
            }
        }
    };
    
    for (int i = 0; i < N; ++i) {
        std::vector<std::string> line = room[i];
        for (int j = 0; j < N; ++j) {
            if (line[j] == "C") {
                const auto& newLight = createLight(i, j);
                add(newLight);
            }
        }
    }
    
    int cpt = 0;
    for (auto&& r : light) {
        for (auto&& c : r) {
            if (c == 0) cpt++;
        }
        std::cerr << std::endl;
    }
    
    std::cout << cpt;
}