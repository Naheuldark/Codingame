#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <regex>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int N; // Number of elements which make up the association table.
    cin >> N; cin.ignore();
    int Q; // Number Q of file names to be analyzed.
    cin >> Q; cin.ignore();
    
    map<string, string> extensions;
    for (int i = 0; i < N; i++) {
        string EXT; // file extension
        string MT; // MIME type.
        cin >> EXT >> MT; cin.ignore();
        string out;
        transform(EXT.begin(), EXT.end(), back_inserter(out), ::toupper);
        extensions[out] = MT;
    }
    
    regex rgx(".*\\.(\\w+)$");
    smatch match;
    
    for (int i = 0; i < Q; i++) {
        string FNAME; // One file name per line.
        getline(cin, FNAME);
        string out;
        if (std::regex_search(FNAME, match, rgx)) {
            string mat = match[1];
            transform(mat.begin(), mat.end(), back_inserter(out), ::toupper);
            if (extensions[out] != "") {
                cout << extensions[out] << endl;   
            } else {
                cout << "UNKNOWN" << endl;
            }
        } else {
            cout << "UNKNOWN" << endl;
        }
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;


    // For each of the Q filenames, display on a line the corresponding MIME type. If there is no corresponding type, then display UNKNOWN.
}