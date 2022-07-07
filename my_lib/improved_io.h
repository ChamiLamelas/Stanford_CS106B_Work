#ifndef IMPROVED_IO_H
#define IMPROVED_IO_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

bool defaultExtraCondFn(int x) {
    return true;
}

int getInt(string msg = "Enter an integer: ", bool (*extraCondFn)(int) = defaultExtraCondFn, string extraConditionMsg = "") {
    int anInt;
    bool gotValidInt = false;
    while (!gotValidInt) {
        cout << msg;
        cin >> anInt;
        if (cin.fail()) {
            cerr << "Failed to read an integer. Try again.\n";
            cin.ignore(); // extract and discard whatever non-integer data was read into the stream
            cin.clear(); // reset bit state so integer read can be tried again
        }
        else if (!extraCondFn(anInt)) {
            cerr << extraConditionMsg << endl;
        }
        else {
            gotValidInt = true;
        }
    }
    return anInt;
}

// document below ... TODO: add a delimeter specifier / think about extending ifstream

enum ReadErrInfoT {
    WARNINGS, EXCEPTIONS, NONE
};

template <typename T>
class MyTextFileRdr {
    string filepath;
    int currentToken;
    int badTokens;
    ifstream f;
    vector<T> buf;
    ReadErrInfoT readErrorType; 
    void reportError(string errMsg);

    public:
    MyTextFileRdr<T>();
    bool isOpen() const;
    void open(string path);
    void read();
    bool atEOF() const;
    void close();
    void setReadErrInfoType(ReadErrInfoT type);
    ReadErrInfoT getCurrReadErrInfo() const;
    string getFilePath() const;
    vector<T> getReadData() const;
    bool hasReadData() const; 
    void discardReadData();
};

#endif