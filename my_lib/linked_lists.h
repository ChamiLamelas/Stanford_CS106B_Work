#ifndef LINKED_LISTS_H
#define LINKED_LISTS_H

#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node* next;
};

// If you wish to execute any of these methods on an empty list, make sure that the head or list parameter is NULL. Do not leave it unitialized


template <typename T> 
void addToHead(Node<T>* &head, Node<T>* newNode) {
    newNode->next = head; 
    head = newNode;
}

template <typename T>
void deallocateList(Node<T> *list) {
    Node<T> *nextToDel = NULL;
    while (list != NULL) {
        nextToDel = list->next;
        delete list;
        list = nextToDel;
    }
}

template <typename T>
void printList(const Node<T> *const list) {
    for (const Node<T>* curr = list; curr != NULL; curr = curr->next) {
        cout << curr->data;
    }
    cout << endl;
}

#endif