#include <queue>
#include <stack> 
#include <iostream> 
using namespace std; 

void ReverseQueue(queue<int> &q);

int main() {
    queue<int> q;

    while (true) {
        cout << "Enter a non-negative integer (NEGATIVE to exit): ";
        int x; 
        cin >> x;
        if (cin.fail()) {
            cerr << "Non-integer value entered." << endl;
            return 1;
        }
        if (x < 0) {
            break;
        }
        q.push(x);
    }

    ReverseQueue(q);

    // printing queue by dequeueing
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    return 0;
}

void ReverseQueue(queue<int> &q) {
    stack<int> s;
    while (!q.empty()) {
        s.push(q.front());
        q.pop();
    }
    while (!s.empty()) {
        q.push(s.top());
        s.pop();
    }
}