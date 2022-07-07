#include <iostream> 
#include <fstream> 
#include <vector>
using namespace std;

void createHistogram(const string& filename, vector<int> &histogram);
void printHistogram(const vector<int> &histogram);

int main() {
    string filename;
    cout << "Enter an input score file: ";
    if (getline(cin, filename)) {
        /* Histogram will be represented as an integer vector with 10 entries. Here is how it will be indexed: 
        The 0th entry will hold the no. of scores in [0, 9]
        The 1st entry will hold the no. of scores in [10, 19]
        .
        .
        .
        The 9th entry will hold the no. of scores in [90, 99]
        In general: Let h[i] be the ith entry in the histogram. h[i] will store the number of scores in [i*10, i*10+9].
         */
        vector<int> histogram(10); 
        createHistogram(filename, histogram);
        printHistogram(histogram);
    }
    else {
        cerr << "Could not read input file name.\n";
    }
    return 0;
}

void createHistogram(const string& filename, vector<int> &histogram) {
    ifstream f; 
    f.open(filename.c_str());
    if (f.fail()) {
        cerr << "Could not open input file.\n";
        return;
    }
    int score;
    // Note on reading text files: https://stackoverflow.com/questions/5605125/why-is-iostreameof-inside-a-loop-condition-i-e-while-stream-eof-cons
    while (f >> score && (score >= 0 && score <= 99)) { 
        /* Since it is known that score is in [0, 99], using integer division the score can be indexed quickly. Observe: 
        any no. in [0, 9] divided by 10 is 0
        any no. in [10, 19] divided by 10 is 1 
        .
        .
        .
        any no. in [90, 99] divided by 10 is 9
        Hence, they will be indexed/stored properly in the histogram.
         */
        histogram[score/10]++;
    }
    if (!f.eof()) { // if error occurred not due to the file reaching the end, report error. http://www.cplusplus.com/reference/ios/ios/eof/
        cerr << "Error reading input file: encountered invalid score value. Score values must be integers in [0, 99]. Histogram data incomplete!\n";
    }
    f.close();
}

void printHistogram(const vector<int> &histogram) {
    /* Since this function takes a const reference, to iterate, a const_iterator must be used. Constant iterators are iterators that do not fulfill the requirements of an 
    output iterator; Dereferencing them yields a reference to a constant element (such as const T&).

    Since random access iterators are quite similar to pointers and support the difference operator- 
    Thus, the index from the start can be calculated as itr-histogram.begin(). Using the general formula provided in the comment in main(), it can print the range appropriate
    for this index. That is, if we are at index i, it can print the range: (i*10)-(i*10+9)

    Lastly, "X" is printed next to the range the number of times appropriate according to the count in histogram.
     */
    for (vector<int>::const_iterator itr = histogram.begin(); itr != histogram.end(); itr++) {
        cout << ((itr-histogram.begin())*10) << "-" << ((itr-histogram.begin())*10+9) << ": ";
        for (int i = 0; i < *itr; i++) {
            cout << "X";
        }
        cout << endl;
    }
}