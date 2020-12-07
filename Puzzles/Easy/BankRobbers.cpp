#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int R;
    cin >> R; cin.ignore();
    std::vector<long long> robbersTimes;
    for (int i = 0; i < R; ++i) robbersTimes.emplace_back(0);
    
    int V;
    cin >> V; cin.ignore();
    
    auto indexOf = [&robbersTimes](long long t) {
        for (int i = 0; i < robbersTimes.size(); ++i) {
            if (robbersTimes[i] == t) return i;
        }
    };
    
    auto min = [&robbersTimes]() {
        long long min = robbersTimes[0]; 
        for (auto&& t : robbersTimes) {
            if (t < min) min = t;
        }
        return min;
    };
    
    auto max = [&robbersTimes]() {
        long long max = 0; 
        for (auto&& t : robbersTimes) {
            if (t > max) max = t;
        }
        return max;
    };
    
    auto getCombinationTime = [](int C, int N) {
        return (long long)std::pow(10, N) * (long long)std::pow(5, (C-N));
    };
    
    for (int i = 0; i < V; i++) {
        int C, N;
        cin >> C >> N; cin.ignore();
        
        robbersTimes[indexOf(min())] += getCombinationTime(C, N);
    }
    
    std::cout << max();
}