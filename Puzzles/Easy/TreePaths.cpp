#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

struct Node {
    int index;
    int leftIdx;
    int rightIdx;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int index, int leftIdx, int rightIdx) : index(index), leftIdx(leftIdx), rightIdx(rightIdx) {}
};

using Tree = std::map<int, Node*>;


void printTree(Tree tree) {
    for (auto&& n : tree) {
        std::cerr << n.first << " (" << n.second << "): " 
                  << n.second->leftIdx << " (" << n.second->left << "), "
                  << n.second->rightIdx << " (" << n.second->right << ")"
                  << std::endl;
    }
    std::cerr << std::endl;
}


bool hasPath(Node *node, int idx, std::vector<std::string>& arr, int target) { 
    std::cerr << "Node: " << node << std::endl;

    if (idx == target)     
        return true; 

    if (!node) 
        return false; 
               
    if (hasPath(node->left, node->leftIdx, arr, target)) {
        arr.emplace_back("Left");
        return true;
    } 

    if (hasPath(node->right, node->rightIdx, arr, target)) {
        arr.emplace_back("Right");
        return true; 
    }
      
    return false;             
} 
  
void printPath(Tree tree, int target) { 
    std::vector<std::string> arr; 
    Node* root = tree.begin()->second;

    std::cerr << "Looking for " << target << std::endl;
    std::cerr << "Root: " << root << "\n" << std::endl;

    if (root->index == target) {
        std::cout << "Root" << std::endl;
    } else if (hasPath(root, tree.begin()->first, arr, target)) { 
        for (size_t i = arr.size() - 1; i > 0; --i)
            std::cout << arr[i] << " "; 
        std::cout << arr[0] << std::endl;     
    }
} 


int main() {
    int N;
    std::cin >> N; std::cin.ignore();
    int V;
    std::cin >> V; std::cin.ignore();
    int M;
    std::cin >> M; std::cin.ignore();

    Tree tree;
    for (int i = 0; i < M; i++) {
        int P;
        int L;
        int R;
        std::cin >> P >> L >> R; std::cin.ignore();
        tree.emplace(P, new Node(P, L, R));
    }

    for (auto&& n : tree) {
        for (auto&& o : tree) {
            if (o.first == n.second->leftIdx) {
                n.second->left = o.second;
            } else if (o.first == n.second->rightIdx) {
                n.second->right = o.second;
            }
        }
    }
    printTree(tree);
    printPath(tree, V); 
}