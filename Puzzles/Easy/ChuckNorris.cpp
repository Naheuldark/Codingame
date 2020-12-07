#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    string MESSAGE;
    getline(cin, MESSAGE);

    const char *str = MESSAGE.c_str();
    string bit_str = "";
    
    for (size_t i = 0; i < MESSAGE.size(); ++i) {
        bitset<7> bits(str[i]);
        bit_str += bits.to_string();
    }
        
    for (size_t i = 0; i < bit_str.size(); ++i) {
        if (bit_str[i] == '0') {
            cout << "00 ";
            while (bit_str[i] == '0') {
                cout << "0";   
                i++;
            }
            if (i != bit_str.size())
                cout << " ";
        }
        if (bit_str[i] == '1') {
            cout << "0 ";
            while (bit_str[i] == '1') {
                cout << "0"; 
                i++;
            }
            if (i != bit_str.size())
                cout << " ";
        }
        i--;
    }
}