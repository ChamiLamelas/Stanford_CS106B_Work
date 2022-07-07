#include "texting.h"
#include "texting.cpp"
#include <iostream>
using namespace std;

int main() {
    Lexicon l("small_lex.txt");
    cout << "1=" << l.hasPrefix("a") << endl; 
    cout << "1=" << l.hasPrefix("ap") << endl; 
    cout << "1=" << l.hasPrefix("app")<< endl;  
    cout << "1=" << l.hasPrefix("appl")<< endl; 
    cout << "1=" << l.hasPrefix("apple")<< endl; 
    cout << "1=" << l.hasPrefix("b")<< endl;  
    cout << "1=" << l.hasPrefix("bo")<< endl; 
    cout << "1=" << l.hasPrefix("c")<< endl;   
    cout << "1=" << l.hasPrefix("cr")<< endl;  
    cout << "1=" << l.hasWord("apple")<< endl;  
    cout << "1=" << l.hasWord("application")<< endl;  
    cout << "1=" << l.hasWord("boy")<< endl;  
    cout << "1=" << l.hasWord("boat")<< endl;  
    cout << "1=" << l.hasWord("cry")<< endl;  
    cout << "1=" << l.hasWord("crime")<< endl;  
    cout << "0=" << l.hasPrefix("") << endl;
    cout << "0=" << l.hasWord("") << endl;

    CellPhone p;
    char ch[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '#'};
    for (int i = 0; i < 12; i++) {
        cout << ch[i] << ": ";
        digit_set s = p.getDigMappings(ch[i]);
        for (digit_itr i = s.begin(); i != s.end(); i++) {
            cout << *i << ' ';
        }
        cout << endl;
    }
}