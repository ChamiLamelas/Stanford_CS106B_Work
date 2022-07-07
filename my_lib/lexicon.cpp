#include "lexicon.h"
#include <fstream>
#include <stdexcept>
#include <iostream>
using namespace std;

void Lexicon::strToLower(string& str) const {
    for (string::iterator i = str.begin(); i != str.end(); i++) {
        *i = tolower(*i);
    }
}

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
        strToLower(word);
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
    string wordCpy = word;
    strToLower(wordCpy);
    return contents.find(wordCpy) != contents.end();
}

bool Lexicon::hasPrefix(const string& prefix) const {
    string preCpy = prefix;
    strToLower(preCpy);
    return contents.find(PREFIX_MARKER + preCpy) != contents.end();
}

void Lexicon::print() const {
    for (set<string>::const_iterator itr = contents.begin(); itr != contents.end(); itr++) {
        if ((*itr)[0] != PREFIX_MARKER) {
            cout << *itr << '\n';
        }
    }
    cout << endl;
}