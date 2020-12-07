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
    long long r1;
    cin >> r1; cin.ignore();
    long long r2;
    cin >> r2; cin.ignore();
    
    auto updateRiver = [](long long r) {
        std::vector<int> digits;
        long long number = r;
        while (number > 0) {
            digits.push_back(number % 10);
            number /= 10;
        }
        
        long long sum = 0;
        for (auto&& d : digits) sum += d;
        
        return r + sum;
    };
    
    while (r1 != r2) {
        while (r1 < r2) {
            r1 = updateRiver(r1);
            if (r1 == r2) { std::cout << r1; return EXIT_SUCCESS; }
        }
        while (r1 > r2) {
            r2 = updateRiver(r2);
            if (r1 == r2) { std::cout << r1; return EXIT_SUCCESS; }
        }
    }
    
    std::cout << r1;
}