#include <map>
#include <fstream>
#include <iostream> 
using namespace std; 

char MostFrequentCharacter(ifstream &f, int &numOccurrences);

int main() {
    ifstream f;
    f.open("sample.txt");
    int numOcc = 0;
    char c = MostFrequentCharacter(f, numOcc);
    cout << "Most frequent character: " << c << endl;
    f.close();
    return 0;
}

char MostFrequentCharacter(ifstream &f, int &numOccurrences) { 
    if (f.fail()) {
        cerr << "Cannot perform operations on file input stream already in a fail state." << endl;
        return 0;
    }
    else {
        map<char, int> occurrenceCounts; 
        char ch;
        while (f.get(ch)) {
            occurrenceCounts[ch]++;
        }
        if (!f.eof()) {
            cerr << "Error reading input file." << endl;
        }
        map<char, int>::iterator itr = occurrenceCounts.begin();
        char mostFreq = itr->first; // choose first character key has most occurrences 
        // go through rest of loop starting from the next entry reached by iterator to see if there is any char key with more occurrences
        for (itr++; itr != occurrenceCounts.end(); itr++) { 
            if (itr->second > occurrenceCounts[mostFreq]) {
                mostFreq = itr->first;      
            }
        }
        return mostFreq;
    }
}