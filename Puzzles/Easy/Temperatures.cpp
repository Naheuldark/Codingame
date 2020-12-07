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
    int n; // the number of temperatures to analyse
    cin >> n; cin.ignore();
    
    int min = 5527;
    
    if (n == 0) {
        min = 0;
    } else {
        for (int i = 0; i < n; i++) {
            int t; // a temperature expressed as an integer ranging from -273 to 5526
            cin >> t; cin.ignore();
            cerr << "t: " << t << endl;
            cerr << "min: " << min << endl;
            if (abs(t) <= abs(min)) {
                if (abs(t) == abs(min)) {
                    if (t > 0) {
                        min = t;
                    }
                } else {
                    min = t;
                }
            }
        }
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << min << endl;
}