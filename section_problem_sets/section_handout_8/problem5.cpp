#include <string>
using namespace std; 

struct nodeT {
    string key;
    nodeT *left;
    nodeT *right;
};

int treeHeight(nodeT *root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + max(treeHeight(root->left), treeHeight(root->right));
}

bool isBalanced(nodeT *root) {
    if (root == nullptr) {
        return true; 
    }
    if (abs(treeHeight(root->left)-treeHeight(root->right)) > 1) {
        return false;
    }
    return isBalanced(root->left) && isBalanced(root->right);
}