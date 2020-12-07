#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>


/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    std::string opBowls;
    getline(std::cin, opBowls);
    std::istringstream iss(opBowls);
    std::vector<std::string> ops{std::istream_iterator<std::string>(iss), {}};
    std::vector<int> op;
    for (auto&& o : ops) op.push_back(std::atoi(o.c_str()));
    
    std::string myBowls;
    getline(std::cin, myBowls);
    std::istringstream iss2(myBowls);
    std::vector<std::string> mys{std::istream_iterator<std::string>(iss2), {}};
    std::vector<int> my;
    for (auto&& o : mys) my.push_back(std::atoi(o.c_str()));
    
    int i;
    std::cin >> i; std::cin.ignore();
    
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    
    int N = my[i];
    size_t size = my.size();
    
    for (my[i++] = 0; N-- > 0; i = i % (2*size-1)) {
        i < size ? my[i++]++ : op[i++ - size]++;
    }
    
    auto print = [](auto&& arr){
        for (size_t i = 0; i < arr.size()-1; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << "[" << arr[arr.size()-1] << "]" << std::endl;
    };
    
    print(op);
    print(my);
    
    if (i == my.size()) std::cout << "REPLAY" << std::endl;
}