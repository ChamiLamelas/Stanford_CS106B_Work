#include <map> 
#include <iostream> 
#include <fstream>
#include <string> 
#include <vector>
#include <cstdlib> 
#include <ctime>  

using namespace std; 

void generateFrequencyMap(ifstream& in, int seedLen, map<string, vector<char> >& freqMap);
void printOutput(const map<string, vector<char> >& freqMap, unsigned int outputCharLength = 2000);

int main() {
    ifstream inFile;
    cout << "Enter input filename: ";
    bool couldReadAndOpen = false;
    while (!couldReadAndOpen) {
        string filename; 
        if (getline(cin, filename)) {
            inFile.open(filename);
            if (inFile.fail()) {
                inFile.clear();
                cerr << "File could not be opened, try again: ";
            }
            else {
                couldReadAndOpen = true;
            }
        }
        else {
            cerr << "Filename could not be read, try again: ";
            cin.clear();
            cin.ignore();
        }
    }

    int seedLen;
    cout << "Enter seed length: ";
    bool readValidSeed = false; 
    while (!readValidSeed) {
        cin >> seedLen;
        if (!cin.fail()) {
            if (seedLen < 1 || seedLen > 10) {
                cerr << "Seed length must be in [1, 10], try again: ";
            }
            else {
                readValidSeed = true;
            }
        }
        else {
            cin.clear();
            cin.ignore();
            cerr << "Seed length must be a positive integer, try again: ";
        }
    }

    map<string, vector<char> > freqMap;
    generateFrequencyMap(inFile, seedLen, freqMap);
    inFile.close();

    printOutput(freqMap);
    return 0;
}

void generateFrequencyMap(ifstream& in, int seedLen, map<string, vector<char> >& freqMap) {
    string currSeed; 
    char nextChar;
    for (unsigned int i = 0; i < seedLen; i++) {
        if (!in.get(nextChar)) {
            if (in.eof()) {
                cerr << "File's character length < seed length." << endl;
            }
            else {
                cerr << "An error occurred while reading the input file." << endl;
            }
            return;
        }
        currSeed += nextChar;
    }
    
    while (in.get(nextChar)) {
        freqMap[currSeed].push_back(nextChar);
        currSeed = currSeed.substr(1) + nextChar;
    }

    if (!in.eof()) {
        cerr << "An error occurred before EOF." << endl;
    }
}

void printOutput(const map<string, vector<char> >& freqMap, unsigned int outputCharLength) {
    string currSeed;
    int highestFreq = 0; 

    for (map<string, vector<char> >::const_iterator itr = freqMap.begin(); itr != freqMap.end(); itr++) {
        // for debug: must use const_iterator from vector because freqMap is const (and can't be edited)
        // cout << "seed=" << itr->first << ", following=";
        // for (vector<char>::const_iterator i = itr->second.begin(); i != itr->second.end(); i++) {
        //     cout << *i;
        // }
        // cout << endl;

        if (itr->second.size() > highestFreq) {
            highestFreq = itr->second.size();
            currSeed = itr->first;
        }
    }
    
    srand(time(0));
    string output = currSeed;

    while (output.length() <= outputCharLength && freqMap.find(currSeed) != freqMap.end()) {
        vector<char> followingChars = freqMap.at(currSeed);
        int randIdx = rand() % followingChars.size();
        output.push_back(followingChars[randIdx]);
        currSeed = currSeed.substr(1) + followingChars[randIdx];
    }

    cout << output << endl;
}