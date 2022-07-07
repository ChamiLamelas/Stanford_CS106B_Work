#include <iostream>
#include "texting.h"
#include "texting.cpp"
#include <string>
#include <set>
using namespace std;

void printSuggestions(string word, const Lexicon& l, int numEdits);

int main() {
    Lexicon l;
    int numEdits;
    cout << "Enter no. of allowed edits: ";
    cin >> numEdits;
    if (cin.fail()) {
        cerr << "Could not get # of edits.";
        return 1;
    }
    cin.ignore();
    while (true) {
        cout << "Enter a word: ";
        string word;
        if (getline(cin, word)) {
            if (word.empty()) {
                break;
            }
            printSuggestions(word, l, numEdits);
        }
        else {
            cin.ignore();
            cin.clear();
        }
    }
    return 0;
}

// set is to store suggestions that could have been reached by an ulternate "edit". e.g. correcting caj with at most 2 edits could be corrected to cat by:
// swapping 'j' with 't' (i.e. 1 edit) or by first deleting 'j' and then adding 't'
void printSuggestions(string word, const Lexicon& l, int numEdits, set<string>& suggested) {
    if (l.hasWord(word) && suggested.find(word) == suggested.end()) {
        cout << word << endl;
        suggested.insert(word);
    }

    if (numEdits > 0) {
        for (int i = 0; i < word.length(); i++) {
            printSuggestions(word.substr(0, i) + word.substr(i + 1), l, numEdits-1, suggested); // edit: delete char 
            for (alpha_itr aitr = ALPHABET.begin(); aitr != ALPHABET.end(); aitr++) {
                printSuggestions(word.substr(0, i) + *aitr + word.substr(i + 1), l, numEdits-1, suggested); // edit: replace char with new char 
                printSuggestions(word.substr(0, i + 1) + *aitr + word.substr(i + 1), l, numEdits-1, suggested); // edit: insert new char
            }
        }
    }
}

void printSuggestions(string word, const Lexicon& l, int numEdits) {
    set<string> suggested;
    printSuggestions(word, l, numEdits, suggested);
}