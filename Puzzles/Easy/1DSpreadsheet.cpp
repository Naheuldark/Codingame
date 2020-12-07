#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Cell {
    std::string operation;
    int val1;
    int val2;
    struct Cell* dep1 = nullptr;
    struct Cell* dep2 = nullptr;
    bool calculated;
    int result;
};

int calculate(const std::string& operation, int val1, int val2) {
    if (operation == "VALUE") {
        return val1;
    } else if (operation == "ADD" ) {
        return val1 + val2;
    } else if (operation == "SUB") {
        return val1 - val2;
    } else if (operation == "MULT") {
        return val1 * val2;
    }
}

int eval(struct Cell* cell) {
    if (cell->calculated) {
        return cell->result;
    } else {
        if (cell->dep1) {
            cell->val1 = eval(cell->dep1);
        }
        
        if (cell->dep2) {
            cell->val2 = eval(cell->dep2);
        }
        
        cell->result = calculate(cell->operation, cell->val1, cell->val2);
        cell->calculated = true;
        
        return cell->result;
    }
}

int main() {
    int N;
    cin >> N; cin.ignore();
    
    std::vector<struct Cell*> graph(N);
    for (size_t i = 0; i < N; ++i) graph[i] = new Cell();
    
    for (int i = 0; i < N; i++) {
        string operation;
        string arg1;
        string arg2;
        cin >> operation >> arg1 >> arg2; cin.ignore();
        
        std::cerr << operation << " " << arg1 << " " << arg2 << "\n";
        
        graph[i]->operation = operation;
        
        if (arg1[0] == '$') {
            arg1.erase(std::remove(arg1.begin(), arg1.end(), '$'), arg1.end());
            graph[i]->dep1 = graph[atoi(arg1.c_str())];
        } else {
            graph[i]->val1 = atoi(arg1.c_str());
        }
        
        if (arg2[0] == '$') {
            arg2.erase(std::remove(arg2.begin(), arg2.end(), '$'), arg2.end());
            graph[i]->dep2 = graph[atoi(arg2.c_str())];
        } else {
            graph[i]->val2 = atoi(arg2.c_str());
        }
        
        // Calculation
        if (!graph[i]->dep1 && !graph[i]->dep2) {
            graph[i]->result = calculate(graph[i]->operation, graph[i]->val1, graph[i]->val2);
            graph[i]->calculated = true;
        }
    }
    
    for (size_t i = 0; i < N; ++i) {
        cout << eval(graph[i]) << endl;
    }
}