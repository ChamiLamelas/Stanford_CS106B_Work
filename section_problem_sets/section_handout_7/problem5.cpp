#include <iostream>
#include "C:\Users\Chami\Stanford_Cpp_Class\organized_materials_and_my_code\my_lib\linked_lists.h"
using namespace std; 

void Stutter(Node<int> *&head);

int main() {
    Node<int> *head = nullptr; // failure to initialize this will lead to errors in linked_lists.h
    cout << "LL length: ";
    int llLen;
    cin >> llLen;
    int in; 
    for (int i = 0; i < llLen; i++) {
        cout << "Input " << i+1 << ':';
        cin >> in;
        if (!cin.fail()) {
            Node<int> *newNode = new Node<int>;
            newNode->data = in;
            addToHead(head, newNode);
        }
        else {
            cerr << "invalid input";
            return 1;
        }
    }
    printList(head);
    Stutter(head);
    printList(head);
    deallocateList(head);
    return 0;
}

void Stutter(Node<int> *&head) {
    Node<int> *curr = head; 
    while (curr != nullptr) {
        Node<int> *cpy = new Node<int>;
        cpy->data = curr->data; // if whatever the data is performs a shallow copy, this could lead to problems 
        cpy->next = curr->next;
        curr->next = cpy;
        curr = cpy->next;
    }
}