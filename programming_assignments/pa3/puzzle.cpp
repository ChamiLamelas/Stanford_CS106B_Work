#include <iostream> 
#include <fstream> 
#include <vector>
using namespace std;

bool solvable(int start, vector<int>& squares);
bool solvable(int start, vector<int>& squares, vector<bool>& visited);

int main() {
    ifstream f("puzzle.dat");
    if (f.fail()) { 
        cerr << "couldn't open data file";
        return 1;
    }
    
    vector<int> squares;
    int x;
    while (f >> x) {
        squares.push_back(x);
    }
    if (!f.eof()) {
        cerr << "error interrupt";
        return 2;
    }

    int start;
    while (true) {
        cout << "Enter start: ";
        cin >> start;
        if (cin.fail()) {
            cerr << "error reading int";
            return 3;
        }
        if (start < 0) {
            break;
        }
        cout << "Solvable? " << solvable(start, squares) << endl;
    }
    
    return 0;
}

// assume for n = len(squares), squares[0...n-2] are all > 0 and squares[n-1] = 0
bool solvable(int start, vector<int>& squares) {
    vector<bool> visited(squares.size(), 0);
    visited[start] = 1;
    return solvable(start, squares, visited);
}

bool solvable(int start, vector<int>& squares, vector<bool>& visited) {
    if (squares[start] == 0) {
        return true;
    }

    int move = start - squares[start];
    if (move >= 0 && !visited[move]) {
        visited[move] = 1;
        if (solvable(move, squares, visited)) {
            return true;
        }
        visited[move] = 0;
    }
    move = start + squares[start];
    if (move < squares.size() && !visited[move]) {
        visited[move] = 1;
        if (solvable(move, squares, visited)) {
            return true;
        }
        visited[move] = 0;
    }
    
    return false;
}