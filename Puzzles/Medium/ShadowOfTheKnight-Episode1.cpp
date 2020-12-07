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
    int W; // width of the building.
    int H; // height of the building.
    cin >> W >> H; cin.ignore();
    int N; // maximum number of turns before game over.
    cin >> N; cin.ignore();
    int x;
    int y;
    cin >> x >> y; cin.ignore();
    
    int x1 = 0;
    int y1 = 0;
    int x2 = W-1;
    int y2 = H-1;

    // game loop
    while (1) {
        string bombDir; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        cin >> bombDir; cin.ignore();
        
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        
        if (bombDir == "U") {
            y2 = y - 1; 
        }
        if (bombDir == "UR") {
            y2 = y - 1; 
            x1 = x + 1;
        }
        if (bombDir == "R") {
            x1 = x + 1;
        }
        if (bombDir == "DR") {
            x1 = x + 1;
            y1 = y + 1;
        }
        if (bombDir == "D") {
            y1 = y + 1;
        }
        if (bombDir == "DL") {
            y1 = y + 1;
            x2 = x - 1;
        }
        if (bombDir == "L") {
            x2 = x - 1;
        }
       if (bombDir == "UL") {
            y2 = y - 1; 
            x2 = x - 1;
        }
        
        x = x1 + (x2 - x1)/2;
        y = y1 + (y2 - y1)/2;

        // the location of the next window Batman should jump to.
        cout << x << " " << y << endl;
    }
}