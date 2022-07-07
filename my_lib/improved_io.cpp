#include "improved_io.h"
#include <string> 
#include <vector> 
#include <stdexcept>
using namespace std; 

template <typename T>
void MyTextFileRdr<T>::reportError(string errMsg) {
    const string FLAG = ">> ERROR >> ";
    switch (readErrorType) {
        case WARNINGS:
            cerr << FLAG << errMsg << endl;
            break;
        case EXCEPTIONS:
            throw invalid_argument(FLAG + errMsg);
        default:
            break;
    };
}

template <typename T>
MyTextFileRdr<T>::MyTextFileRdr() {
    currentToken = 0;
    readErrorType = NONE;
    badTokens = 0;
}

template <typename T> 
bool MyTextFileRdr<T>::isOpen() const {
    return f.is_open();
}

// keeps data in buffer until another successful opening is done, can force clearing using 'discardReadData()'
template <typename T> 
void MyTextFileRdr<T>::open(string path) {
    f.open(path);
    if (f.fail()) {
        f.clear();
        throw invalid_argument("Could not open " + path + ". Call open() again to try again.");
    }
    else {
        filepath = path;
        buf.clear();
    }
}

template <typename T> 
void MyTextFileRdr<T>::read() {
    if (!isOpen()) {
        reportError("No open file found. Last stored path: " + filepath + ".");
    }
    if (atEOF()) {
        throw invalid_argument("End of file " + filepath + " reached."); 
    }
    T input;
    f >> input;
    currentToken++;
    if (f.fail()) {
        f.clear();
        f.ignore();
        badTokens++;
        reportError("Token " + to_string(currentToken) + " in " + filepath + " was formatted incorrectly.");
    }
    else {
        buf.push_back(input);
    }
}

template <typename T>
bool MyTextFileRdr<T>::atEOF() const {
    return f.eof();
}

template <typename T> 
void MyTextFileRdr<T>::close() {
    if (isOpen()) {
        f.close();
    }
}

template <typename T> 
void MyTextFileRdr<T>::setReadErrInfoType(ReadErrInfoT type) {
    readErrorType = type;
}

template <typename T>
ReadErrInfoT MyTextFileRdr<T>::getCurrReadErrInfo() const {
    return readErrorType;
}

template <typename T>
string MyTextFileRdr<T>::getFilePath() const {
    return filepath;
}

template <typename T>
vector<T> MyTextFileRdr<T>::getReadData() const {
    if (badTokens > 0) {
        reportError(to_string(badTokens) + " tokens were invalid. Output data not complete.");
    }
    return buf;
}

template <typename T>
bool MyTextFileRdr<T>::hasReadData() const {
    return !buf.empty();
}

template <typename T>
void MyTextFileRdr<T>::discardReadData() {
    buf.clear();
}