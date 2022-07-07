#include <vector>
#include <string>
#include <iostream>
#include <map>
using namespace std;

// 2a
double similarity(const vector<char> &v, const vector<char> &w);
// 2b 
bool markovMatch(const map<string, vector<char>> &m1, const map<string, vector<char>> &m2);

int main() {
    while (true) {
        string phrase1, phrase2;
        cout << "Enter phrase 1 (RETURN to exit): ";
        getline(cin, phrase1);
        if (phrase1.empty()) {
            break;
        }
        cout << "Enter phrase 2 (RETURN to exit): ";
        getline(cin, phrase2);
        if (phrase2.empty()) {
            break;
        }
        vector<char> v, w;
        for (char ch : phrase1) {
            v.push_back(ch);
        }
        for (char ch : phrase2) {
            w.push_back(ch);
        }
        cout << "Similarity between " << phrase1 << " and " << phrase2 << " is " << similarity(v, w) << '.' << endl;
    }
    return 0;
}

double similarity(const vector<char> &v, const vector<char> &w) {
    int numSameChars = 0;
    vector<char>::const_iterator vItr = v.begin(), wItr = w.begin();

    while (vItr != v.end() && wItr != w.end()) {
        if (*vItr < *wItr) {
            vItr++;
        }
        else if (*wItr < *vItr) {
            wItr++;
        }
        else { // *wItr == *vItr
            vItr++;
            wItr++;
            numSameChars++;
        }
    }

    return (double)numSameChars/(0.5 * (v.size() + w.size()));
}

bool markovMatch(const map<string, vector<char>> &m1, const map<string, vector<char>> &m2) {
    for (map<string, vector<char>>::const_iterator m1Itr = m1.begin(); m1Itr != m1.end(); m1Itr++) {
        if (m2.find(m1Itr->first) != m2.end() && similarity(m2.at(m1Itr->first), m1Itr->second) < 0.7) {
            return false;
        }
    }
    return true;
}