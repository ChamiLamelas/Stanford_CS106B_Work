// reimplement as BST 

#ifndef LEXICON_H
#define LEXICON_H

#include <set>
#include <string>
using namespace std;

const string DEF_LEX_SRC = "my_lib\\words_alpha.txt";
const char PREFIX_MARKER = '~';

class Lexicon {
    private:
    int numWords;
    bool prefixesEnabled;
    set<string> contents;
    void strToLower(string& str) const;

    public:
    Lexicon(const string& src = DEF_LEX_SRC);
    bool hasWord(const string& word) const;
    bool hasPrefix(const string& prefix) const;
    int size() const;
    void print() const;
};

#endif