#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "C:\Users\Chami\Stanford_Cpp_Class\organized_materials_and_my_code\my_lib\general_utils.h"
using namespace std;

// 1a
template <typename T>
vector<string> keysForMaxVal(map<string, T> m, int (cmpFn)(T &x, T &y) = operatorCmp) {
    vector<string> keys;
    typename map<string, T>::iterator itr = m.begin();
    T maxVal = itr->second;
    keys.push_back(itr->first);
    itr++;
    for (; itr != m.end(); itr++) {
        if (cmpFn(itr->second, maxVal) > 0) { // itr->second > maxVal
            maxVal = itr->second;
            keys.clear();
            // bug! when you find the new max val, make sure you add its key to the set of keys associated with a max val. 
            keys.push_back(itr->first); 
        }
        else if (cmpFn(itr->second, maxVal)==0) { // itr->second == maxVal
            keys.push_back(itr->first);
        }
        // else: cmpFn(itr->second, maxVal) < 0 (i.e. itr->second < maxVal), do nothing
    }
    return keys;
}

int markovComp(vector<char> &v, vector<char> &w) {
    return v.size() - w.size();
}

// 1b
string mostFrequentSeed(map<string, vector<char>> &model) {
    vector<string> mostFreq = keysForMaxVal(model, markovComp);
    if (mostFreq.size()==1) {
        return mostFreq[0];
    }
    else {
        srand(time(nullptr));
        int seedIdx = rand() % mostFreq.size();
        return mostFreq[seedIdx];
    }
}

int main() {
    map<string, int> ages;
    ages["Zinnia"] = 3;
    ages["Rein"] = 5;
    ages["Kalev"] = 2;
    ages["Ian"] = 4; 
    vector<string> maxKeys = keysForMaxVal(ages);
    for (vector<string>::iterator itr = maxKeys.begin(); itr != maxKeys.end(); itr++) {
        cout << *itr << ' ';
    }
    cout << endl;
    return 0;
}
