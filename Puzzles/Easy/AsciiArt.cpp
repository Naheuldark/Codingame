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
    int L;
    cin >> L; cin.ignore();
    int H;
    cin >> H; cin.ignore();
    string T;
    getline(cin, T);
    
    const int A = (int) 'A';
    const int Z = (int) 'Z';
    
    std::transform(T.begin(), T.end(),T.begin(), ::toupper);
    
    for (int i = 0; i < H; ++i) {
        string ROW;
        getline(cin, ROW);
        
        string ret = "";
        
        for (auto s : T) {
            auto c = (int) s;
            
            if (c < A || c > Z)
                ret += ROW.substr(L * (Z - A + 1), L);
            else
                ret += ROW.substr(L * (c - A), L);
        }
        std::cout << ret << std::endl;
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

}