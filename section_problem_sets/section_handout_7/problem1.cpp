#include <vector>
#include <iostream>
#include <queue>
using namespace std;

// Implementing Stack to test 
template <typename T>
class Stack {
    public: 
        Stack() {}
        ~Stack() {}

        void push(T entry);
        void pop();
        const T& peek() const;
        T& peek();
        bool empty() const;
        void reverse();
    
    private:
        vector<T> buffer;
};

template <typename T>
void Stack<T>::push(T entry) {
    buffer.push_back(entry);
}

template <typename T>
void Stack<T>::pop() {
    if (!empty()) {
        buffer.pop_back();
    }
}

template <typename T>
const T& Stack<T>::peek() const {
    return buffer.back();
}

template <typename T>
T& Stack<T>::peek() {
    return buffer.back();
}

template <typename T>
bool Stack<T>::empty() const {
    return buffer.empty();
}

// Answer to 1a
template <typename T>
void Stack<T>::reverse() {
    for (size_t i = 0; i < buffer.size()/2; i++) {
        T tmp = buffer[i];
        buffer[i] = buffer[buffer.size()-i-1];
        buffer[buffer.size()-i-1] = tmp;
    }
}  

// Answer to 1b
template <typename T>
void reverse(Stack<T> &s) {
    queue<T> q;
    while (!s.empty()) {
        q.push(s.peek());
        s.pop();
    }
    while (!q.empty()) {
        s.push(q.front());
        q.pop();
    }
}

int main() {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.reverse();
    while (!s.empty()) {
        cout << s.peek() << ' ';
        s.pop();
    }
    cout << '\n';
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    reverse(s);
    while (!s.empty()) {
        cout << s.peek() << ' ';
        s.pop();
    }
    return 0;
}