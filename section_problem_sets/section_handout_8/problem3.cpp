#include <queue> 
#include <string>
using namespace std;

struct nodeT {
    string key;
    nodeT *left;
    nodeT *right;
};

bool areEqualIter(const nodeT * const root1, const nodeT * const root2) {
    if (root1 == nullptr && root2 == nullptr) {
        return true;
    }
    else {
        if (root1 == nullptr || root2 == nullptr) {
            return false;
        }
    }

    queue<const nodeT*> q1, q2;
    q1.push(root1);
    q2.push(root2);
    while (!q1.empty() && !q2.empty()) {
        const nodeT *tmp1 = q1.front(), *tmp2 = q2.front();
        q1.pop();
        q2.pop();
        // check data
        if (tmp1->key != tmp2->key) {
            return false;
        }
        // check structure 
        if (tmp1->left != nullptr && tmp2->left != nullptr) {
            q1.push(tmp1->left);
            q2.push(tmp2->left);
        }
        else {
            if (tmp1->left != nullptr || tmp2->left != nullptr) {
                return false;
            }
        }
        if (tmp1->right != nullptr && tmp2->right != nullptr) {
            q1.push(tmp1->right);
            q2.push(tmp2->right);
        }
        else {
            if (tmp1->right != nullptr || tmp2->right != nullptr) {
                return false;
            }
        }
    }

    return q1.empty() && q2.empty();
}

bool areEqualRec(nodeT *root1, nodeT *root2) {
    if (root1 == nullptr && root2 == nullptr) {
        return true;
    }
    else {
        if (root1 == nullptr || root2 == nullptr) {
            return false;
        }
    }

    if (root1->key != root2->key) {
        return false;
    }
    
    return areEqualRec(root1->left, root2->left) && areEqualRec(root1->right, root2->right);
}