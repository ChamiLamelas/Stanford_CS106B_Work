#include <deque> // could use vector, but that would be less efficient 
#include <stack>
#include <iostream>
using namespace std;

void roll(stack<char> &s, int n, int p);

int main() {
    stack<char> stack;

    cout << "Pushing Characters onto Stack\n";
    while (true) {
        cout << "Enter char (0 to exit): ";
        char ch;
        cin >> ch;
        if (ch == '0') {
            break;
        }
        else {
            stack.push(ch);
        }
    }
    cout << "n? ";
    int n;
    cin >> n;
    cout << "p? ";
    int p;
    cin >> p;

    roll(stack, n, p);
    cout << "Resulting Stack: ";
    while (!stack.empty()) {
        cout << stack.top() << ' ';
        stack.pop();
    }
    cout << endl;

    return 0;
}

void roll(stack<char> &s, int n, int p) {
    deque<char> d;
    // for the first 2 loops, d is essentially acting like a queue (FIFO)
    for (int i = 0; i < n; i++) {
        d.push_back(s.top());
        s.pop();
    }
    for (int i = 0; i < p; i++) {
        d.push_back(d.front());
        d.pop_front();
    }
    // here is where a deque is needed to push back into the stack. simply popping out of a queue would cause the reverse of the desired output
    // consider the simple case where p = 0. Pushing from a stack into a queue and then popping from the queue into the stack would simply reverse 
    // the stack (this is a common app. of queue). For the non-simple cases where a rotation is actually performed and stored correctly in the queue
    // as it should appear in the stack, the stack will put these elements in backwards. One would have to reverse the queue first before being put
    // into the stack (which would req. a 2nd stack to do this reversal). Think of it as a double reversal to get back to the desired forward order.
    while (!d.empty()) {
        s.push(d.back());
        d.pop_back();
    }
}