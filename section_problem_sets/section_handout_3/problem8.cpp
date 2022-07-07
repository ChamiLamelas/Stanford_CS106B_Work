#include <map> 
#include <iostream>
#include <string> 
#include <vector> 
using namespace std; 

void ListMnemonics(string str);
void ListMnemonics(string str, string curr, const map<char, vector<char> >& digitsToLetters);

int main() {
    cout << "Enter digits: ";
    string digits; 
    getline(cin, digits);

    ListMnemonics(digits);
    return 0;
}

void ListMnemonics(string str) {
    map<char, vector<char> > digitsToLetters;
    digitsToLetters['0'].push_back('0');
    digitsToLetters['1'].push_back('1');
    digitsToLetters['2'].push_back('A');
    digitsToLetters['2'].push_back('B');
    digitsToLetters['2'].push_back('C');
    digitsToLetters['3'].push_back('D');
    digitsToLetters['3'].push_back('E');
    digitsToLetters['3'].push_back('F');
    digitsToLetters['4'].push_back('G');
    digitsToLetters['4'].push_back('H');
    digitsToLetters['4'].push_back('I');
    digitsToLetters['5'].push_back('J');
    digitsToLetters['5'].push_back('K');
    digitsToLetters['5'].push_back('L');
    digitsToLetters['6'].push_back('M');
    digitsToLetters['6'].push_back('N');
    digitsToLetters['6'].push_back('O');
    digitsToLetters['7'].push_back('P');
    digitsToLetters['7'].push_back('R');
    digitsToLetters['7'].push_back('S');
    digitsToLetters['8'].push_back('T');
    digitsToLetters['8'].push_back('U');
    digitsToLetters['8'].push_back('V');
    digitsToLetters['8'].push_back('W');
    digitsToLetters['8'].push_back('X');
    digitsToLetters['8'].push_back('Y');
    digitsToLetters['*'].push_back('*');
    digitsToLetters['0'].push_back('0');
    digitsToLetters['#'].push_back('#');
    ListMnemonics(str, "", digitsToLetters);
}

void ListMnemonics(string str, string curr, const map<char, vector<char> >& digitsToLetters) {
    if (str.empty()) {
        cout << curr << endl;
        return;
    }
    vector<char> letters = digitsToLetters.at(str[0]);
    for (vector<char>::const_iterator itr = letters.begin(); itr != letters.end(); itr++) {
        ListMnemonics(str.substr(1), curr + *itr, digitsToLetters);
    }
}