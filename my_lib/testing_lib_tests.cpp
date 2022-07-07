#include "testing_lib.h"
#include "testing_lib.cpp"
#include <iostream>
using namespace std;

int main() {
    Tester t(true);
    cerr << t.isRunning() << "\n";
}