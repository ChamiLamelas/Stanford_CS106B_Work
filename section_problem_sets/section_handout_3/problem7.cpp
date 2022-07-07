#include <iostream>
#include <vector> 
using namespace std; 

bool isMeasurable(int target, vector<int> &weights); 
bool isMeasurable(int target, vector<int> &weights, int idx); 

int getInt() {
    cout << "Enter an integer >= 0: "; 
    bool gotValidInt = false;
    int val;
    while (!gotValidInt) {
        cin >> val;
        if (cin.fail()) {
            cerr << "Value must be a positive integer, try again: ";
            cin.clear();
            cin.ignore();
        }
        else if (val < 0) {
            cerr << "Value (" << val << ") cannot be < 0, try again: ";
        }
        else {
            gotValidInt = true;
        }
    }
    return val;
}

int main() {
    cout << "--- Getting number of weights ---" << endl;
    int numWeights = getInt();
    cout << "--- Filling Weights ---" << endl;
    vector<int> weights;
    for (int i = 0; i < numWeights; i++) {
        weights.push_back(getInt());
    }
    cout << "--- Getting target ---" << endl;
    int target = getInt();
    cout << "Is measurable? " << isMeasurable(target, weights) << endl;
    return 0;
}

/* Falls under 'subset' recursive problems: 
1. try to see if target is measurable with current weight on the other side of the balance (opposite from target - represented
by subtracting from target)
2. try to see if target is measurable with current weight on neither balance (discarded)
3. try to see if target is measurable with current weight on its side of the balance (add to target)

Soln. manual: Instead of erasing/inserting into vector, 'idx' is used to move over the vector where previously visited entries
are not removed (just ignored). 
 */
bool isMeasurable(int target, vector<int> &weights) {
    if (target == 0) {
        return true;
    }
    if (weights.empty()) {
        return false;
    }
    int curr = weights.front();
    weights.erase(weights.begin());

    if (isMeasurable(target - curr, weights) || isMeasurable(target, weights) || isMeasurable(target + curr, weights)) {
        return true; 
    }

    weights.insert(weights.begin(), curr);
    return false; 
}

