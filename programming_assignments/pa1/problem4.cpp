#include <iostream> 
#include <string> 
using namespace std; 

// use the insert function found here: http://www.cplusplus.com/reference/string/string/insert/ -> under fill(5) signature: void insert (iterator p, size_t n, char c);

string getSoundexCode(const string& surname);
void cleanCode(string &code);

int main() {
    while (true) {
        string surname;
        cout << "Enter surname (RETURN to quit): ";    

        // using getline() to capture an empty string. cin>> will wait for non-whitespace text (which in the case of the user trying to exit with "RETURN" will not happen)
        if (getline(cin, surname)) { 
            if (surname.empty()) {
                break;
            }
            cout << "Soundex code for " << surname << " is " << getSoundexCode(surname) << endl;
        }
        else {
            cerr << "Error: no input could be read." << endl;
        }
    }
    
    return 0;
}

string getSoundexCode(const string& surname) {
    string code;
    code += toupper(surname[0]);
    for (int i = 1; i < surname.length(); i++) {
        char ch = toupper(surname[i]);
        if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U' || ch == 'H' || ch == 'W' || ch == 'Y') {
            code.insert(code.end(), 1, '0');
        }
        else if (ch == 'B' || ch == 'F' || ch == 'P' || ch == 'V') {
            code.insert(code.end(), 1, '1');
        }
        else if (ch == 'C' || ch == 'G' || ch == 'J' || ch == 'K' || ch == 'Q' || ch == 'S' || ch == 'X' || ch == 'Z') {
            code.insert(code.end(), 1, '2');
        }
        else if (ch == 'D' || ch == 'T') {
            code.insert(code.end(), 1, '3');
        }
        else if (ch == 'M' || ch == 'N') {
            code.insert(code.end(), 1, '4');
        }
        else if (ch == 'L') {
            code.insert(code.end(), 1, '5');
        }
        else if (ch == 'R') {
            code.insert(code.end(), 1, '6');
        }
    }
    cleanCode(code);
    return code;
}

void cleanCode(string &code) {
    unsigned int i = 1;
    while (i < code.length()) {
        if (code[i] == '0' || (i < code.length() - 1 && code[i] == code[i + 1])) {
            code.erase(i, 1);
        }
        else {
            i++;
        }
    }
    if (code.length() > 4) {
        code.erase();
    }
    else {
        code.insert(code.end(), (4-code.length()), '0');
    }
}