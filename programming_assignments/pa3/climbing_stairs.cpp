#include <iostream>
using namespace std;

int countWays(int stairs);
void countWays(int stairs, int& count);

int main() {
    while (true) {
        cout << "# stairs = ";
        int stairs; 
        cin >> stairs; 
        if (cin.fail()) {
            cerr << "bad in";
            return 1;
        }
        if (stairs<0) {
            break;
        }
        cout << countWays(stairs) << endl;
    }
    return 0;
}

int countWays(int stairs) {
    int count = 0;
    countWays(stairs, count);
    return count;
}

// O(2^n) rec. soln. b/c the output turns out to the be the same as that of the fibonacci seq. Thus, iteratively, like fibonacci, this could be solved in O(n) time and O(1) space.
void countWays(int stairs, int& count) {
    if (stairs == 0) {
        count++;
    }
    else if (stairs < 0) {
        return;
    }

    countWays(stairs-1, count);
    countWays(stairs-2, count);
}