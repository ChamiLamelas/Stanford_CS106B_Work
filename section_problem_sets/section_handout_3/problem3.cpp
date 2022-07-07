#include <set> 
#include <string>
#include <iostream> 
using namespace std; 

typedef set<string>::const_iterator string_set_itr;

struct pairT {
    string first, second; 
};

struct pairTcomp {
    bool operator() (const pairT& a, const pairT& b) {
        if (a.first == b.first) {
            return a.second < b.second;
        }
        else {
            return a.first < b.first;
        }
    }
};

set<pairT, pairTcomp> cartesianProduct(const set<string>& a, const set<string>& b);
void constructSet(set<string>& set);

int main() {
    set<string> set1, set2; 
    constructSet(set1);
    constructSet(set2);

    set<pairT, pairTcomp> cartProd = cartesianProduct(set1, set2);
    cout << "\n--- Cartesian Product of ---" << endl;

    for (string_set_itr itr = set1.begin(); itr != set1.end(); itr++) {
        cout << *itr << " ";
    }
    cout << endl;
    for (string_set_itr itr = set2.begin(); itr != set2.end(); itr++) {
        cout << *itr << " ";
    }
    cout << "\n" << endl;

    for (set<pairT, pairTcomp>::iterator itr = cartProd.begin(); itr != cartProd.end(); itr++) {
        cout << "(" << itr->first << ", " << itr->second << ") ";
    }
}

set<pairT, pairTcomp> cartesianProduct(const set<string>& a, const set<string>& b) {
    set<pairT, pairTcomp> cartProd; 
    
    for (string_set_itr aItr = a.begin(); aItr != a.end(); aItr++) {
        for (string_set_itr bItr = b.begin(); bItr != b.end(); bItr++) {
            pairT newPair;
            newPair.first = *aItr; 
            newPair.second = *bItr; 
            cartProd.insert(newPair);
        }
    }

    return cartProd; 
}

void constructSet(set<string>& set) {
    cout << "\n--- Constructing New Set ---" << endl;
    string entry; 
    while (true) {
        cout << "Entry (RETURN to exit): ";
        if (!getline(cin, entry)) {
            cerr << "Could not read input." << endl;
        }
        else if (entry.empty()) {
            break;
        }
        else {
            set.insert(entry);
        }
    }
}