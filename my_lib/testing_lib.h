#ifndef TESTING_LIB_H
#define TESTING_LIB_H

#include <ctime>
#include <iostream> 
#include <string>
using namespace std;

const unsigned int DEFAULT_LINE_NUM = 0;

class Tester {
    unsigned int numTests; 
    time_t iTime;
    bool running;
    public:
    Tester(bool wait = false);
    ~Tester();
    template <typename T>
    void report(const T& actual, const T& expected, unsigned int lineNum = DEFAULT_LINE_NUM);
    void start();
    void end();
    bool isRunning() const;
};

#endif 