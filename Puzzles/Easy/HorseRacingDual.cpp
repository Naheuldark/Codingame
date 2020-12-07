#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int N;
    cin >> N; cin.ignore();
    list<int> horses;
    for (int i = 0; i < N; i++) {
        int Pi;
        cin >> Pi; cin.ignore();
        horses.push_back(Pi);
    }
    
    horses.sort();
        
    int min = 10000000; 

    int prev = horses.front();
    horses.pop_front();
    int curr = 0;
    while (!horses.empty()) {
        curr = horses.front();
        horses.pop_front();
        if (curr-prev < min)
            min = curr-prev;
        prev = curr;
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << min << endl;
}