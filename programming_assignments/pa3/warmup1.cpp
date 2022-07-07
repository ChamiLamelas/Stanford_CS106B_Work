#include <iostream> 
using namespace std; 

void printInBinary(int num);

int main() {
    bool done = false;
    while (!done) {
        int num;
        cout << "Enter a num (-1 to exit): ";
        cin >> num;
        if (cin.fail()) {
            cerr << "Entered non integer!\n";
            return 1;
        }
        if (num == -1) {
            done = true;
        }
        else {
            printInBinary(num);
            cout << endl;
        }
    }
}

void printInBinary(int num) {
    if (num > 1) {
        printInBinary(num/2);
    }
    cout << (num % 2);
}