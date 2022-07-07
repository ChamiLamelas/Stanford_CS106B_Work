#include <iostream> 
using namespace std;
 
 // calculates GCD using the Euclidean Algorithm (see proofs bk.)
int gcd(int m, int n) {
    if (m % n == 0) {
        return n;
    }
    else {
        return gcd(n, m%n);
    }
}

int getInt() {
    cout << "Enter an integer > 0: "; 
    bool gotValidInt = false;
    int val;
    while (!gotValidInt) {
        cin >> val;
        if (cin.fail()) {
            cerr << "Value must be a positive integer, try again: ";
            cin.clear();
            cin.ignore();
        }
        else if (val <= 0) {
            cerr << "Value (" << val << ") cannot be <= 0, try again: ";
        }
        else {
            gotValidInt = true;
        }
    }
    return val;
}

int main() {
    int m = getInt(), n = getInt();
    cout << "GCD(" << m << ", " << n << ") = " << gcd(m, n) << endl;
    return 0;
}