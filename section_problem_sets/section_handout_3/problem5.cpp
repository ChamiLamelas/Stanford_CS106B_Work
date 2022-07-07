#include <string>
#include <iostream> 
using namespace std; 

/* Pros: could be easier to come up with 
   Cons: uses up more memory 
 */
string reverseStringRecursive(string s) {
    if (s.empty()) {
        return s;
    }
    else {
        return reverseStringRecursive(s.substr(1)) + s[0];
    }
}

/* Pros: uses up less memory 
   Cons: reverse traversal may be at first complicated 
 */
string reverseStringIterative(string s) {
    string rev; 

    /* Use a reverse iterator to go over a string backwards (not a regular one). Do not use size_t because it is unsigned and integer wrap around will cause an infinite loop when
    the size_t for loop counter is supposed to go "below" 0. Ends up becoming some large unsigned integer again.
     */
    for (string::reverse_iterator itr = s.rbegin()-1; itr != s.rend(); itr++) {
        rev.push_back(*itr);
    }
    return rev;
}

int main() {
    while (true) {
        cout << "Enter string (RETURN to exit): ";
        string str; 
        if (!getline(cin, str)) {
            cerr << "Could not read input." << endl;
            cin.ignore();
            cin.clear();
        }
        else if (str.empty()) {
            break;
        }
        else {
            cout << "Reversed (Recursively): " << reverseStringRecursive(str) << endl;
            cout << "Reversed (Iteratively): " << reverseStringIterative(str) << endl;
        }
    }

    return 0;
}