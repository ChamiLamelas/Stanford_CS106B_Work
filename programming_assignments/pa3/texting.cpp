#include "texting.h"
#include <fstream>
#include <stdexcept>
#include <iostream>
using namespace std;

Lexicon::Lexicon(const string& src) {
    numWords = 0;

    cerr << "Setting up lexicon...";
    ifstream f;
    f.open(src);

    if (f.fail()) {
        throw invalid_argument("source file could not be opened.");
    }

    string word;
    while (f >> word) {
        numWords++;
        contents.insert(word);
        for (int i = 1; i < word.length() + 1; i++) {
            contents.insert(PREFIX_MARKER + word.substr(0, i));
        }
    }
    if (!f.eof()) {
        throw invalid_argument("an error occurred while reading the source file.");
    }
    f.close();
    cerr << "DONE.\n";
}

int Lexicon::size() const {
    return numWords;
}

bool Lexicon::hasWord(const string& word) const {
    return contents.find(word) != contents.end();
}

bool Lexicon::hasPrefix(const string& prefix) const {
    return contents.find(PREFIX_MARKER + prefix) != contents.end();
}

void Lexicon::print() const {
    for (set<string>::const_iterator itr = contents.begin(); itr != contents.end(); itr++) {
        if ((*itr)[0] != PREFIX_MARKER) {
            cout << *itr << '\n';
        }
    }
    cout << endl;
}

CellPhone::CellPhone() {
    digMappings['1'].push_back('1');
    digMappings['2'].push_back('a');
    digMappings['2'].push_back('b');
    digMappings['2'].push_back('c');
    digMappings['3'].push_back('d');
    digMappings['3'].push_back('e');
    digMappings['3'].push_back('f');
    digMappings['4'].push_back('g');
    digMappings['4'].push_back('h');
    digMappings['4'].push_back('i');
    digMappings['5'].push_back('j');
    digMappings['5'].push_back('k');
    digMappings['5'].push_back('l');
    digMappings['6'].push_back('m');
    digMappings['6'].push_back('n');
    digMappings['6'].push_back('o');
    digMappings['7'].push_back('p');
    digMappings['7'].push_back('q');
    digMappings['7'].push_back('r');
    digMappings['7'].push_back('s');
    digMappings['8'].push_back('t');
    digMappings['8'].push_back('u');
    digMappings['8'].push_back('v');
    digMappings['9'].push_back('w');
    digMappings['9'].push_back('x');
    digMappings['9'].push_back('y');
    digMappings['9'].push_back('z');
    digMappings['*'].push_back('*');
    digMappings['0'].push_back('0');
    digMappings['#'].push_back('#');
}

const vector<char>& CellPhone::getDigMappings(char dig) const {
    dig = tolower(dig);
    if (digMappings.find(dig) == digMappings.end()) {
        throw invalid_argument("provided digit not in cellphone.");
    } 
    return digMappings.at(dig);
} 