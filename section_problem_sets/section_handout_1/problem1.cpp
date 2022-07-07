#include <iostream>
#include <string> 
using namespace std;

string CensorString1(const string& text, const string& remove);
void CensorString2(string &text, const string& remove);

int main() {
    const string SENTINEL = "_exit";
    cout << "Use " << SENTINEL << " to exit." << endl;

    while (true) {
        cout << "Enter a string: ";
        string str; 
        getline(cin, str);
        if (str == SENTINEL) break;
        cout << "Enter a string of chars to be removed from " << str << ": ";
        string rmv; 
        getline(cin, rmv); // in case user wants to remove spaces from str 
        cout << "Censored string (function 1): " << CensorString1(str, rmv) << endl;
        CensorString2(str, rmv);
        cout << "Censored string (function 2): " << str << endl;
    }

    return 0;
}

/* This answer goes over 'text' once and 'remove' many times (see remove.find()). The provided soln. goes over 'text' many times and 'remove' once. Furthermore, instead of 
building up a string, it combines substrings around the removed character (which seemed inefficient to make so many - possibly large - copies).
 */
string CensorString1(const string& text, const string& remove) {
    string censoredString;
    for (int i = 0; i < text.length(); i++) {
        if (remove.find(text[i]) == string::npos) { 
            censoredString += text[i];
        }
    }
    return censoredString;
}

/* This answer goes over 'text' once and 'remove' many times (see remove.find()). The provided soln. again does the opposite. For each character to be removed, it goes through 
text and removes it. This also gets around having to worry about incrementing i at the right time (hence the else {} clause below).
 */
void CensorString2(string &text, const string& remove) {
    int i = 0;
    while (i < text.length()) {
        if (remove.find(text[i]) != string::npos) {
            text.erase(i, 1);
        }
        else {
            i++;
        }
    }
}
