#include <vector>
#include <string>
#include <stack>
using namespace std;

struct nodeT {
    string data;
    nodeT *left, *right;
};

void fillVector(nodeT *root, vector<nodeT*> &v);
nodeT *buildTree(vector<nodeT*> &v, int startIdx, int stopIdx);

void Rebalance(nodeT *&root) {
    vector<nodeT*> flattenedTree;
    fillVector(root, flattenedTree);
    root = buildTree(flattenedTree, 0, flattenedTree.size()-1);
}

void fillVector(nodeT *root, vector<nodeT*> &v) {
    // top of stack will hold the lowest node that curr is in the left subtree of. Therefore, whenever curr hits null, a subtree has been fully
    // explored so go back to the lowest unprocessed root (which is s.top())
    stack<nodeT*> s; 
    nodeT *curr = root;
    while (curr != nullptr && !s.empty()) {
        if (curr==nullptr) {
            curr = s.top();
            s.pop();
            v.push_back(curr);
            curr = curr->right;
        }
        else {
            s.push(curr);
            curr = curr->left;
        }
    }
}

nodeT *buildTree(vector<nodeT*> &v, int startIdx, int stopIdx) {
    if (startIdx > stopIdx) {
        return nullptr;
    }

    int mid = (startIdx+stopIdx)/2;
    nodeT *root = v[mid];
    root->left = buildTree(v, startIdx, mid-1);
    root->right = buildTree(v, mid + 1, stopIdx);
    return root;
}