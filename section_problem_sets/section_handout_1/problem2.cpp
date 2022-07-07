#include <fstream> 
#include <string>
#include <iostream>
using namespace std; 

struct exam {
    int min; 
    int max; 
    double avg;
};

exam getExamData(const string& filename);

int main() {
    cout << "Enter filename with score data: ";
    string scoreDatFile; 
    getline(cin, scoreDatFile);
    exam examFromFile = getExamData(scoreDatFile);
    cout << "\nExam Information\n-----------------\nMin: " << examFromFile.min << "\nMax: " << examFromFile.max << "\nAvg: " << examFromFile.avg << endl;
    return 0;
}

/* Given a filename that holds score data for a given exam, returns an exam struct that holds calculated info. 
   @param filename - the path to the input file 
   @return an exam struct containing member variables that have been updated with data from the input file (assuming reading was done successfully)
 */
exam getExamData(const string& filename) {
    /* Correction from soln. manual: 
    Since we know the data range of ex.min and ex.max, instead of using this bool, we can set ex.min and ex.max to appropriate numbers outside the data range. Specifically,
    since ex.min and ex.max will both be in [0, 100], ex.min could be initialized to 101 and ex.max could be initialized to -1. The use of 'setMinMax' will be ignored.
     */
    // bool setMinMax = false;
    exam ex; 
    ex.min = 101;
    ex.max = -1;
    ex.avg = -1.0; // Not in soln. manual, but should be added to prevent undefined behavior in the case of 'ex' returning but an error occuring in the file reading below.
    ifstream f;
    f.open(filename.c_str());
    /* Correction from soln. manual: 
    Add check here to make sure file could actually be opened: 
     */
    if (f.fail()) {
        cerr << "Error: input file could not be read." << endl;
    }
    int count = 0, sum = 0;
    int score;
    // Note on reading text files: https://stackoverflow.com/questions/5605125/why-is-iostreameof-inside-a-loop-condition-i-e-while-stream-eof-cons
    while (f >> score && (score >= 0 || score <= 100)) {
        // if (!setMinMax) {
        //     ex.min = score;
        //     ex.max = score;
        //     setMinMax = true;
        // }
        // else {
        if (score < ex.min) {
            ex.min = score; 
        }
        /*
        Correction from solb. manual: 
        Make this if not else-if so in the case of 1 score, it will become the max and the min
         */
        if (score > ex.max) {
            ex.max = score; 
        }
        // }
        sum += score;
        count++;
    }
    if (!f.eof()) { // if file was closed before the end, report error. http://www.cplusplus.com/reference/ios/ios/eof/
        cerr << "Error in input file. Disregard returned data. Score values must be integers in [0, 100]." << endl;
    }
    f.close();
    if (count > 0) {
        ex.avg = double(sum)/count;
    }
    return ex;
}
