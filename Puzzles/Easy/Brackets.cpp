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
    string expression;
    cin >> expression; cin.ignore();

    int balance = 0;
    for (auto&& c : expression) {
        switch(c) {
            case '(':
                balance += 1;
                break;
            case ')':
                balance -= 1;
                break;
            case '[':
                balance += 2;
                break;
            case ']':
                balance -= 2;
                break;
            case '{':
                balance += 3;
                break;
            case '}':
                balance -= 3;
                break;
        }
        if (balance < 0) {
            std::cout << "false";
            return EXIT_SUCCESS;
        }
    }
    
    std::cout << ((balance == 0) ? "true" : "false"); 
}