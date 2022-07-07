#include "stack.h"
#include <stdexcept>
using namespace std;

template <typename T>
void VectorStack<T>::push(const T &entry) {
    buf.add(entry);
}

template <typename T> 
void VectorStack<T>::pop() {
    if (empty()) {
        throw invalid_argument("Cannot pop from empty stack");
    }
    buf.remove(buf.size()-1);
}

template <typename T>
T& VectorStack<T>::peek() {
    if (empty()) {
        throw invalid_argument("Cannot peek empty stack");
    }
    return buf.get(buf.size()-1);
}

template <typename T>
const T& VectorStack<T>::peek() const {
    if (empty()) {
        throw invalid_argument("Cannot peek empty stack");
    }
    return buf.get(buf.size()-1);
}

template <typename T>
unsigned int VectorStack<T>::size() const {
    return buf.size();
}

template <typename T> 
bool VectorStack<T>::empty() const {
    return buf.empty();
}

template <typename T>
void VectorStack<T>::clear() {
    buf.clear();
}

template <typename T>
LinkedListStack<T>::LinkedListStack() {
    head = nullptr;
    numElements = 0;
}

template <typename T>
LinkedListStack<T>::~LinkedListStack() {
    while (head != nullptr) {
        Node<T> *tmp = head->next;
        delete head;
        head = tmp;
    }
}

template <typename T>
void LinkedListStack<T>::push(const T &entry) {
    Node<T> *newNode = new Node<T>;
    newNode->data = entry;
    newNode->next = head;
    head = newNode;
    numElements++;
}

template <typename T>
void LinkedListStack<T>::pop() {
    if (empty()) {
        throw invalid_argument("Cannot pop empty stack");
    }
    Node<T> *tmp = head->next;
    delete head;
    head = tmp;
    numElements--;
}

template <typename T>
const T& LinkedListStack<T>::peek() const {
    if (empty()) {
        throw invalid_argument("Cannot peek empty stack");
    }
    return head->data;
}

template <typename T>
T& LinkedListStack<T>::peek() {
    if (empty()) {
        throw invalid_argument("Cannot peek empty stack");
    }
    return head->data;
}

template <typename T>
bool LinkedListStack<T>::empty() const {
    return head == nullptr;
}

template <typename T>
unsigned int LinkedListStack<T>::size() const {
    return numElements;
}

template <typename T>
void LinkedListStack<T>::clear() {
    while (head != nullptr) {
        Node<T> *temp = head->next;
        delete head;
        head = temp;
    }
    numElements = 0;
}



