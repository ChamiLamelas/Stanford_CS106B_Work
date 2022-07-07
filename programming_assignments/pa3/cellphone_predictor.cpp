#include <iostream> 
#include "texting.h"
#include "texting.cpp"
#include <vector>
using namespace std;

void listCompletions(string digitSeq, const Lexicon& l);
void listMnemonicCompletions(string currCompletions, const Lexicon& l);
vector<string> getMnemonics(string digitSeq);
void getMnemonics(string digitSeq, const CellPhone& p, string currMnemonic, vector<string>& mnemonics);

int main() {
    const Lexicon l;

    while (true) {
        cout << "Enter digit sequence (RETURN to exit): ";
        string seq;
        if (getline(cin, seq)) {
            if (seq.empty()) {
                break;
            }
            listCompletions(seq, l);
        }
        else {
            cerr << "error reading string\n";
            return 1;
        }
    }
    return 0;
}

void listCompletions(string digitSeq, const Lexicon& l) {
    vector<string> mnemonics = getMnemonics(digitSeq);
    for (vector<string>::iterator itr = mnemonics.begin(); itr != mnemonics.end(); itr++) {
        if (l.hasPrefix(*itr)) { // skip mnemonics that aren't prefixes in the lexicon
            listMnemonicCompletions(*itr, l);
        }
    }
    cout << endl;
}

vector<string> getMnemonics(string digitSeq) {
    const CellPhone p;
    vector<string> out;
    getMnemonics(digitSeq, p, "", out);
    return out;
}

void listMnemonicCompletions(string currCompletion, const Lexicon& l) {
    if (l.hasWord(currCompletion)) {
        cout << currCompletion << '\n';
    }
    for (alpha_itr i = ALPHABET.begin(); i != ALPHABET.end(); i++) {
        if (l.hasPrefix(currCompletion + *i)) {
            listMnemonicCompletions(currCompletion + *i, l);
        }
    }
}

void getMnemonics(string digitSeq, const CellPhone& p, string currMnemonic, vector<string>& mnemonics) {
    if (digitSeq.empty()) {
        mnemonics.push_back(currMnemonic);
        return;
    }

    digit_set s = p.getDigMappings(digitSeq[0]);
    for (digit_itr i = s.begin(); i != s.end(); i++) {
        getMnemonics(digitSeq.substr(1), p, currMnemonic + *i, mnemonics);
    }
}



