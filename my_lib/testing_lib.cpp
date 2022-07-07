#include "testing_lib.h"
#include <ctime>
#include <iostream> 
using namespace std;

Tester::Tester(bool wait) {
    running = false;
    if (!wait) {
        start();
    }
}

Tester::~Tester() {
    if (running) {
        end();
    }
}

template <typename T> 
void Tester::report(const T& actual, const T& expected, unsigned int lineNum) {
    if (running) {
        numTests++;
        if (actual == expected) {
            return;
        }
        cerr << "[ TEST FAILED ] | Test no. " << numTests;
        if (lineNum != DEFAULT_LINE_NUM) {
            cerr << " | Line no. " << lineNum;
        }
        cerr << " | Actual: " << actual << " | Expected: " << expected << "\n";
    }
}

void Tester::start() {
    if (!running) {
        cerr << "\n---- [[ STARTING TESTS ]] ----\n";
        iTime = time(NULL);
        running = true;
        numTests = 0;
    }
}

void Tester::end() {
    if (running) {
        cerr << "\n---- [[ " << numTests << " TESTS COMPLETED in " << (time(NULL) - iTime) << " seconds. ]] ----\n";
        running = false;
    }
}

bool Tester::isRunning() const {
    return running;
}