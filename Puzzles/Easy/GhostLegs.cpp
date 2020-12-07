#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <iterator>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int W;
    int H;
    std::cin >> W >> H; std::cin.ignore();
    
    std::vector<std::pair<std::string, std::string>> res;
    
    std::string line;
    std::getline(std::cin, line);
    
    std::istringstream iss(line);
    std::vector<std::string> top{std::istream_iterator<std::string>(iss), {}};
    
    std::vector<std::string> lines;
    for (int i = 1; i < H-1; ++i) {
        std::string l;
        std::getline(std::cin, l);
        lines.push_back(l);
    }
    
    std::getline(std::cin, line);

    std::istringstream iss2(line);
    std::vector<std::string> bottom{std::istream_iterator<std::string>(iss2), {}};
    
    for (int i = 0; i < top.size(); ++i) {
        res.push_back(std::make_pair(top[i], bottom[i]));
    }

    for (int i = 0; i < res.size(); ++i) {
        int col = i * 3;
        for (int j = 0; j < H-2; ++j) {
            std::string row = lines[j];
            if (col != 0 && row[col-1] == '-') {
                res[i].second = bottom[col/3-1];
                col -= 3;
            } else if (col != W-1 && row[col+1] == '-') {
                res[i].second = bottom[col/3+1];
                col += 3;
            }
        }
    }
    
    
    for (auto&& x : res) std::cout << x.first << x.second << std::endl;
}