#include "C:\Users\Chami\Stanford_Cpp_Class\organized_materials_and_my_code\my_lib\lexicon.h"
#include "C:\Users\Chami\Stanford_Cpp_Class\organized_materials_and_my_code\my_lib\lexicon.cpp"
#include <string> 
#include <iostream>
#include <set>
using namespace std;

int permute(string soFar, string rest, const Lexicon &l);

int main() {
    Lexicon l;
    while (true) {
        string word;
        cout << "Enter a word (RETURN to exit): ";
        getline(cin, word);
        if (word.empty()) {
            break;
        }
        cout << word << " has " << permute("", word, l) << " permutation(s)." << endl;
    }

    return 0;
}

// I changed this to the soln. but I think my result was not entirely wrong - it used more space as opposed to more time - however the soln. 
// was more interesting to analyze. 
int permute(string soFar, string rest, const Lexicon &l) {
    if (rest.empty()) {
        return l.hasWord(soFar);
    }
    
    int count = 0;
    // looping over choices in rest. rest[i] is the current choice.
    for (int i = 0; i < rest.length(); i++) {
        /* Suppose i < j and rest[i] = rest[j]. That is, rest.find(rest[i]) != string::npos. Suppose one were to permute with the choice 'rest[i]'
        made at this step and some result is reached. Then, suppose later on in this loop, rest[j] is visited and a permutation is made with that
        choice. Since removing rest[j] from rest leaves the same remaining choices as removing rest[i] from rest, the same result reached by choosing
        rest[i] will eventually be reached in some future recursive call by choosing rest[j].
        To avoid this repeated result (and the recursive calls that lead up to it), skip 'rest[i]' as long as there exists some j > i such that 
        rest[j] = rest[i]. That way, there is no way a permutation path will not be followed more than once. 
        Note: this saves having to maintain an auxilary set to check for duplicate results which would take up O(N) space with the tradeoff
        being for every character in rest, a linear time search must be made of rest to see if it occurs later on. */
        if (rest.find(rest[i], i+1) == string::npos && l.hasPrefix(soFar + rest[i])) {
            count += permute(soFar + rest[i], rest.substr(0, i) + rest.substr(i + 1), l);
        }
    }

    return count;
}