#include <iostream>
using namespace std; 

bool isPerfect(unsigned int n); 

int main() {
    for (unsigned int t = 1; t <= 10000; t++) {
        if (isPerfect(t)) {
            cout << t << endl;
        }
    }
    return 0;
}

bool isPerfect(unsigned int n) {
    unsigned int sumOfProperDivisors = 0; 
    // The only possible proper divisors of n - even or odd - are in [1, n/2]. As they are found, add to them their sum which will be compared with n at the end.
    for (unsigned int i = 1; i <= n/2; i++) {
        if (n % i == 0) {
            sumOfProperDivisors += i;
        }
    }
    return sumOfProperDivisors == n;
}

