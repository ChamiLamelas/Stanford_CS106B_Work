#include <iostream>
#include <vector>
#include <fstream>
using namespace std; 

int cutStock(vector<int>& reqs, int len);
void cutStock(vector<int>& reqs, int len, int curr, int count, int& minCount);

int main() {
    ifstream f("stock.dat");
    if (f.fail()) { 
        cerr << "couldn't open data file";
        return 1;
    }
    
    vector<int> reqs;
    int x;
    while (f >> x) {
        reqs.push_back(x);
    }
    if (!f.eof()) {
        cerr << "error interrupt";
        return 2;
    }

    int len;
    while (true) {
        cout << "Enter length: ";
        cin >> len;
        if (cin.fail()) {
            cerr << "error reading int";
            return 3;
        }
        if (len <= 0) {
            break;
        }
        cout << "Min boards: " << cutStock(reqs, len) << endl;
    }

    return 0;
}

// pre-condition: reqs is not empty and contains entries > 0
int cutStock(vector<int>& reqs, int len) {
    int minCount = reqs.size() + 1;
    cutStock(reqs, len, len, 1, minCount); // starting with using 1 board
    return minCount;
}

void cutStock(vector<int>& reqs, int len, int curr, int count, int& minCount) {
    if (reqs.empty()) { // if found places for all reqs - see if the # of boards it took is less than min. count 
        if (len==curr) { // if current board was taken but not actually used, don't count it 
            count--;
        }
        if (count < minCount) {
            minCount = count;
        }
    }

    for (vector<int>::iterator i = reqs.begin(); i != reqs.end(); i++) { // for each of the remaining reqs. 
        int tmp = *i;  // choose 1 and remove it (make choice)
        i = reqs.erase(i);
        /* Place choice 
        In the case of tmp being bigger than len, use up as many boards as needed to reduce tmp to a number less than len. 
        tmp/len will give the number of boards needed to reduce tmp to a number less than len
        tmp%len will give the number that tmp will be reduced to
        Put tmp%len into the current board (also adding 1 to count) and add the # of boards used up (tmp/len) to count
         */
        if (curr - tmp < 0) { 
            cutStock(reqs, len, len - (tmp % len), count + 1 + tmp/len, minCount);
        }
        else {
            cutStock(reqs, len, curr - tmp, count, minCount);
        }
        reqs.insert(i, tmp); // unmake choice
    }
}
