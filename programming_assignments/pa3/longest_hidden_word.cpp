#include <iostream>
#include <string>
#include "texting.h" // for lexicon
#include "texting.cpp"
using namespace std; 

string findLongestHidden(string phrase, const Lexicon& l);
void findLongestHidden(string phrase, const Lexicon& l, string& longest, string curr);

int main() {
    Lexicon l;
    while (true) {
        string phrase;
        cout << "Enter phrase (or RETURN to exit): ";
        getline(cin, phrase);
        if (cin.fail()) {
            cin.ignore();
            cin.clear();
        }
        if (phrase.empty()) {
            break;
        }
        cout << "Longest hidden word: " << findLongestHidden(phrase, l) << endl;
    }
    return 0;
}

string findLongestHidden(string phrase, const Lexicon& l) {
    string longest = "";
    string::iterator i = phrase.begin();
    while (i != phrase.end()) {
        *i = tolower(*i);
        if (!isalpha(*i)) {
            i = phrase.erase(i);
        }
        else {
            i++;
        }
    }
    findLongestHidden(phrase, l, longest, "");
    return longest;
}

/* (exhaustive, as expected) Permutations algorithm:

Build up a permutation until the permutation is not a prefix of any word in the lexicon. Along the way, if the permutation progress (i.e. a subset of the set of chars in the
phrase a.k.a. the set of choices) is a word in the lexicon, compare it with the tracked longest word (and update the longest word to it if the progress is longer).

This is similar to the listCompletions algorithm in the cellphone problem. However, the set of characters to choose from to continue permutation progress is limited to the
ones in the phrase. Hence, in the recursive call, making the choice entails removing the chosen char from 'phrase'.

Note: while this deals with subsets, I could not get a soln. to work using the exhaustive subset algorithm.
*/
void findLongestHidden(string phrase, const Lexicon& l, string& longest, string curr) {
    if (l.hasWord(curr)) { // if curr is currently a word, see if its longer than the longest and if so update longest 
        if (longest.length() < curr.length()) {
            longest = curr;
        }
    }
    for (int i = 0; i < phrase.length(); i++) { // set of choices are the chars in the phrase 
        if (l.hasPrefix(curr + phrase[i])) { // only move forward on characters from the phrase that will lead to a word 
            // make choice of phrase[i] 
            findLongestHidden(phrase.substr(0, i) + phrase.substr(i + 1), l, longest, curr + phrase[i]); // will update longest when a word is reached 
            // unmake choice of phrase[i] and move on 
        }
    }
}