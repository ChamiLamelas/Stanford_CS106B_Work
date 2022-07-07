#ifndef TEXTING_H
#define TEXTING_H

#include <string>
#include <set>
#include <map>
#include <vector>
using namespace std;

const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";
const string DEF_LEX_SRC = "words_alpha.txt";
const char PREFIX_MARKER = '~';

typedef vector<char> digit_set;
typedef vector<char>::const_iterator digit_itr;
typedef string::const_iterator alpha_itr;

class Lexicon {
    private:
    int numWords;
    set<string> contents;

    public:
    Lexicon(const string& src = DEF_LEX_SRC);
    bool hasWord(const string& word) const;
    bool hasPrefix(const string& prefix) const;
    int size() const;
    void print() const;
};

class CellPhone {
    private:
    map<char, vector<char>> digMappings;

    public:
    CellPhone();
    const vector<char>& getDigMappings(char dig) const;
};

#endif