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
    int r1;
    cin >> r1; cin.ignore();
    
    auto nextRiver = [](long long r) {
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
    
    std::string res("NO");

    for (int k = 0; k <= r1; ++k) {
        if (nextRiver(k) == r1) res = "YES";
    }
    std::cout << res;
}