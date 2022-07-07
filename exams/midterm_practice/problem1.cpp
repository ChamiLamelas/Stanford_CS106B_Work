#include <string>
#include <iostream>
using namespace std;

void convertMacLineEndsToPC(string &s) {
    for (string::iterator i = s.begin(); i != s.end(); i++) {
        if (*i == '\n') {
            i = s.insert(i, '\r'); // points it to the first inserted character, so moving i up by 1 would only move i back to '\n' again (leading to inf. loop)
            i += 2;
        }
        else {
            i++;
        }
    }
}

int main() {
    string macTxt = "\nI am a \nMac Line\n";
    for (char ch : macTxt) {
        cout << int(ch) << ' ';
    }
    cout << '\n';
    convertMacLineEndsToPC(macTxt);
    for (char ch : macTxt) {
        cout << int(ch) << ' ';
    }
    cout << endl;

    return 0;
}