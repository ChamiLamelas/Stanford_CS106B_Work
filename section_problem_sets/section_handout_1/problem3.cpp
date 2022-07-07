#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std; 

void CountLetters(const string& filename);

int main() {
    cout << "Enter a filename: ";
    string filename; 
    getline(cin, filename);
    CountLetters(filename);
}

void CountLetters(const string& filename) {
    ifstream f;
    vector<int> letterCounts(26); // constructs a vector with 26 empty entries 
    f.open(filename.c_str());
    /* Correction from soln. manual: 
    Make sure that f was opened properly as in problem 2. 
     */
    if (f.fail()) {
        cerr << "Error: input file could not be opened." << endl;
        return;
    }

    /* The soln. manual provides a method that reads line by line and then goes through each line again character by character. Instead, I chose to use f.get() to retrieve a
    character at a time. 
    Note: with no error check above, this still works as f.get() returns EOF if no chars can be read (as in the case of f not being created properly) even though f.eof() is
    false. See: http://www.cplusplus.com/reference/istream/istream/get/
     */
    char ch;
    while ((ch = f.get()) != EOF) {
        ch = tolower(ch);
        if (ch >= 'a' && ch <= 'z') { // checks if ch is in the alphabet by using ASCII comparison (char comparison breaks down to int comparison)
            letterCounts[ch-'a']++;
        }
    }
    f.close();
    /* The soln. manual uses an integer to iterate over vector<int>, which is discouraged. However, this may be due to the case that they use their own Vector wrapper. 
     */
    /* vector<int>::iterator is a random access iterator and subtraction between them yields an integer. Thus, the difference between itr and the iterator at the beginning of the 
    vector will show how many indices have been iterated over. That difference + the integer value of 'a' will provide the correct letter the count at the vector entry pointed at
    by itr corresponds to. 
     */
    for (vector<int>::iterator itr = letterCounts.begin(); itr != letterCounts.end(); itr++) {
        cout << char((itr-letterCounts.begin())+'a') << ": " << *itr << endl;
    }
}
