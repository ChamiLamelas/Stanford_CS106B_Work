#include "testing_lib.h"
#include "testing_lib.cpp"
#include "stack.h"
#include "stack.cpp"
#include <stdexcept>
#include <iostream>
using namespace std;

int main() {
    
    Tester t; 

    VectorStack<int> vs;
    for (int i = 1; i <= 10000; i*=10) {
        vs.push(i);
        t.report(vs.peek(), i);
    }
    t.report(vs.size(), (unsigned int)5);
    t.report(vs.empty(), false);

    int cmp = 10000;
    while (!vs.empty()) {
        t.report(vs.peek(), cmp);
        vs.pop();
        cmp /= 10;
    }
    cout << '\n';

    t.report(vs.size(), (unsigned int)0);
    t.report(vs.empty(), true);
    try {
        vs.peek();
    }
    catch (invalid_argument i) {
        cout << i.what() << '\n';
    }

    try {
        vs.pop();
    }
    catch (invalid_argument i) {
        cout << i.what() << '\n';
    }

    VectorStack<char> vsc;
    
    vsc.push('a');
    t.report(vsc.peek(), 'a');
    vsc.push('l');
    t.report(vsc.peek(), 'l');
    vsc.push('t');
    t.report(vsc.peek(), 't');
    vsc.push('F');
    t.report(vsc.peek(), 'F');
    vsc.push('4');
    t.report(vsc.peek(), '4');

    t.report(vsc.size(), (unsigned int)5);
    t.report(vsc.empty(), false);
    vsc.clear();
    t.report(vsc.size(), (unsigned int)0);
    t.report(vsc.empty(), true);

    LinkedListStack<string> lls;
    lls.push("users");
    t.report(lls.peek(), string("users"));
    lls.pop();
    t.report(lls.empty(), true);
    t.report(lls.size(), (unsigned int)0);

    try {
        lls.pop();
    }
    catch (invalid_argument i) {
        cout << i.what() << '\n';
    }

    try {
        lls.peek();
    }
    catch (invalid_argument i) {
        cout << i.what() << '\n';
    }

    lls.push("C");
    t.report(lls.peek(), string("C"));
    t.report(lls.empty(), false);
    lls.push("temp");
    t.report(lls.peek(), string("temp"));
    lls.push("System32");
    t.report(lls.peek(), string("System32"));

    t.report(lls.size(), (unsigned int)3);
    lls.clear();
    t.report(lls.empty(), true);
    t.report(lls.size(), (unsigned int)0);

    LinkedListStack<bool> llsb;
    int num = 123;
    cout << num << " in binary is ";
    while (num > 0) {
        llsb.push(num % 2);
        t.report(llsb.peek(), (bool)(num % 2));
        num /= 2;
    }
    
    while (!llsb.empty()) {
        cout << llsb.peek();
        llsb.pop();
    }
    cout << endl;

    llsb.clear();
    return 0;
}