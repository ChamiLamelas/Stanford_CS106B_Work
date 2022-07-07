// REDO this problem.. keep cubes in same order no need to swap up ordering of cubes 

#include <vector>
#include <string>
#include <iostream>
#include "C:\Users\Chami\Stanford_Cpp_Class\organized_materials_and_my_code\my_lib\general_utils.h"
using namespace std;

const unsigned int BOARD_SIZE = 4;

string StandardCubes[16]  = 
{"AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS", "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
 "DISTTY", "EEGHNW", "EEINSU", "EHRTVW", "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"};


bool canSpell(const string &word, vector<string> &cubes);
bool canSpell(const string &word, vector<string> &cubes, size_t cube, char (&board)[4][4], int row, int col);

int main() {
    cout << "Fetching cubes...";
    vector<string> cubes;
    for (string s : StandardCubes) {
        cubes.push_back(convertToLower(s));
    }
    cout << "DONE." << endl;

    while (true) {
        cout << "Enter a word (RETURN to exit): ";
        string word;
        getline(cin, word);
        if (word.empty()) {
            break;
        }
        string lcWord = convertToLower(word);
        cout << "Cubes can spell " << lcWord << "? " << canSpell(convertToLower(lcWord), cubes) << endl;
    }

    return 0;
}
