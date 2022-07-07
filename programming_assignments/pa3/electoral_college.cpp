#include <iostream>
#include <fstream> 
#include <vector>
using namespace std;

int countCritVotes(vector<int>& blocks, int tar);
void countCritVotes(vector<int>& blocks, int tar, int idx, int votesA, int votesB, int& critCount);

int main() {
    cout << "loading block data ";
    ifstream f("voting_blocks.dat");
    if (f.fail()) { 
        cerr << "couldn't open";
        return 1; 
    }

    int x; 
    vector<int> blocks;
    while (f >> x) {
        blocks.push_back(x);
        cout << x << ' ';
    }
    cout << endl;
    if (!f.eof()) {
        cerr << "error interrupt";
        return 2;
    }
    f.close();
    while (true) {
        cout << "block of interest (out of bounds input -> exit)=";
        int idx;
        cin >> idx;
        if (cin.fail()) {
            cin.ignore();
            cin.clear();
        }
        else if (idx < 0 || idx >= blocks.size()) {
            break;
        }
        cout << "Critical votes by block " << idx << " (" << blocks.at(idx) << " votes): " << countCritVotes(blocks, idx) << endl;
    }
    
    return 0;
} 

int countCritVotes(vector<int>& blocks, int tar) {
    int count = 0;
    countCritVotes(blocks, tar, 0, 0, 0, count);
    return count;
}

void countCritVotes(vector<int>& blocks, int tar, int idx, int votesA, int votesB, int& critCount) {
    if (idx == tar) {
        idx++;
    }
    if (idx >= blocks.size()) { 
        if ((votesA < votesB && votesA + blocks[tar] > votesB) || (votesB < votesA && votesB + blocks[tar] > votesA)) {
            critCount++;
        }
        return;
    }
    countCritVotes(blocks, tar, idx + 1, votesA + blocks[idx], votesB, critCount);
    countCritVotes(blocks, tar, idx + 1, votesA, votesB + blocks[idx], critCount);
}
