#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 * ---
 * Hint: You can use the debug stream to print initialTX and initialTY, if Thor seems not follow your orders.
 **/
int main()
{
    int lightX; // the X position of the light of power
    int lightY; // the Y position of the light of power
    int initialTX; // Thor's starting X position
    int initialTY; // Thor's starting Y position
    cin >> lightX >> lightY >> initialTX >> initialTY; cin.ignore();

    // game loop
    while (1) {
        int remainingTurns; // The remaining amount of turns Thor can move. Do not remove this line.
        cin >> remainingTurns; cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        
        int dX = lightX - initialTX;
        int dY = lightY - initialTY;
        
        cerr << dX << " " << dY << endl;
        
        if (dX == 0) {
            if (dY > 0) { 
                cout << "S" << endl;
                initialTY++;
            }
            if (dY < 0) {
                cout << "N" << endl;
                initialTY--;
            }
        } else if (dY == 0) {
            if (dX > 0) {
                cout << "E" << endl;
                initialTX++;
            }
            if (dX < 0) {
                cout << "W" << endl;
                initialTX--;
            }
        } else if (dY < 0) {
            initialTY--;
            if (dX > 0) {
                cout << "NE" << endl;
                initialTX++;
            }
            if (dX < 0) {
                cout << "NW" << endl;
                initialTX--;
            }
        } else if (dY > 0) {
            initialTY++;
            if (dX > 0) {
                cout << "SE" << endl;
                initialTX++;
            }
            if (dX < 0) {
                cout << "SW" << endl;
                initialTX--;
            }
        } 
    }
}