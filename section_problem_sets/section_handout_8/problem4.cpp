#include <string>
#include <queue> 
using namespace std;

struct nodeT {
    string key;
    nodeT *left;
    nodeT *right;
};

// this soln. requires further testing but wasn't required by the assignment!
void trimFoliageIter(nodeT *&root) {
    if (root == nullptr) {
        return;
    }
    if (root->left == nullptr && root->right == nullptr) {
        delete root;
        root = nullptr;
        return;
    }

    queue<nodeT*> q;
    q.push(root);
    while (!q.empty()) {
        nodeT *curr = q.front();
        q.pop();
        if (curr->left->left == nullptr && curr->left->right == nullptr) {
            delete curr->left;
            curr->left = nullptr;
        }
        else {
            q.push(curr->left);
        }
        if (curr->right->left == nullptr && curr->right->right == nullptr) {
            delete curr->right;
            curr->right = nullptr;
        }
        else {
            q.push(curr->right);
        }
    }
}

/* If one did not pass the pointer to root by reference, this algorithm would not work. Mainly because the 2nd if statement would not be editing what we wanted it to. If root
was a copy of some other pointer, the delete would work but it would not get updated to nullptr and would remain some other value. The algorithm would most likely have to be
changed (and maybe placed into 2 methods) and would become more complicated (as seen with the iterative implementation of the same procedure).
*/

void trimFoliageRec(nodeT *&root) {
    if (root == nullptr) {
        return; 
    }
    if (root->left == nullptr && root->right == nullptr) {
        delete root;
        root = nullptr;
        return;
    }
    trimFoliageRec(root->left);
    trimFoliageRec(root->right);
}