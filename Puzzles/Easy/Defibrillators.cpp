#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cmath>

using namespace std;

template<typename Out>
void split(const string &s, char delim, Out result) {
    stringstream ss(s);
    string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}


int main()
{
    string LON;
    cin >> LON; cin.ignore();
    replace(LON.begin(), LON.end(), ',', '.');
    double lngA = atof(LON.c_str()) * M_PI / 180.0;
    string LAT;
    cin >> LAT; cin.ignore();
    replace(LAT.begin(), LAT.end(), ',', '.');
    double latA = atof(LAT.c_str()) * M_PI / 180.0;
    int N;
    cin >> N; cin.ignore();
    string name;
    double min = 999999999;
    for (int i = 0; i < N; i++) {
        string DEFIB;
        getline(cin, DEFIB);
        
        vector<string> elems;
        split(DEFIB, ';', back_inserter(elems));
        replace(elems[4].begin(), elems[4].end(), ',', '.');
        replace(elems[5].begin(), elems[5].end(), ',', '.');
        
        double lngB = atof(elems[4].c_str()) * M_PI / 180.0;
        double latB = atof(elems[5].c_str()) * M_PI / 180.0;
        
        double x = (lngB - lngA) * cos((latA + latB) / 2.0);
        double y = (latB - latA);
        double d = sqrt(pow(x,2) + pow(y,2)) * 6371.0;
                
        if (d < min) {
            min = d;
            name = elems[1];
        }
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << name << endl;
}