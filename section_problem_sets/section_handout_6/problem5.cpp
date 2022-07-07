#include <vector>
#include <iostream>
#include <string>
#include "C:\Users\Chami\Stanford_Cpp_Class\organized_materials_and_my_code\my_lib\general_utils.h"
using namespace std;

// 5a)
template <typename T>
void removeDuplicates(vector<T> &v, int (cmpFn)(const T&, const T&) = operatorCmp) {
    for (auto itr = v.begin(); itr != v.end(); itr++) {
        T tmp = *itr;
        /* standard format for deleting some portion of elements from a vector (taken from https://en.cppreference.com/w/cpp/container/vector/erase)
        must update rest to the updated iterator returned by erase because calling erase() invalidates iterators and references at 
        or after the point of the erase, including the end() iterator.  */
        for (auto rest = itr + 1; rest != v.end(); ) {
            if (cmpFn(*rest, tmp) == 0) {
                rest = v.erase(rest);
            }
            else {
                rest++;
            }
        }
    }
}

// tester function
int caseInsensitiveCmp(const string &s1, const string &s2) {
    string lowerS1, lowerS2;
    for (string::const_iterator itr1 = s1.begin(); itr1 != s1.end(); itr1++) {
        lowerS1.push_back(tolower(*itr1));
    }
    for (string::const_iterator itr2 = s2.begin(); itr2 != s2.end(); itr2++) {
        lowerS2.push_back(tolower(*itr2));
    }
    return operatorCmp(lowerS1, lowerS2);
}

// 5b)
// even though its not needed to pass a small primitive like int by const ref, it's needed to satisfy function arg. of removeDuplicates()
int absValCmp(const int &x, const int &y) {
    return operatorCmp(abs(x), abs(y));
}

int main() {
    vector<int> i;
    i.push_back(-1);
    i.push_back(1);
    i.push_back(10);
    i.push_back(-10);
    i.push_back(-10);

    removeDuplicates(i, absValCmp);
    for (auto itr = i.begin(); itr != i.end(); itr++) {
        cout << *itr << ' ';
    }

    vector<string> s;
    s.push_back("daniel");
    s.push_back("cHamI");
    s.push_back("chami");
    s.push_back("Daniel");
    s.push_back("Chami");

    removeDuplicates(s, caseInsensitiveCmp);
    for (auto itr = s.begin(); itr != s.end(); itr++) {
        cout << *itr << ' ';
    }
    return 0;
}