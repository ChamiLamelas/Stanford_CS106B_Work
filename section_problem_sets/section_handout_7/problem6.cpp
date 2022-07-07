#include <iostream>
#include "C:\Users\Chami\Stanford_Cpp_Class\organized_materials_and_my_code\my_lib\linked_lists.h"
using namespace std;

void removeDupes(Node<int> * const &head);

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
    removeDupes(head);
    printList(head);
    deallocateList(head);
    return 0;
}

void removeDupes(Node<int> * const &head) {
    // note on stop condition: both curr & curr->next must exist in order to see if there is a pair of duplicates
    // note on iteration step: observe that the loop body gaurantees that curr->next will be the next element to process 
    for (Node<int> *curr = head; curr != nullptr && curr->next != nullptr; curr = curr->next) {
        if (curr->data == curr->next->data) { // neighboring duplicates 
            Node<int> *tmp = curr->next->next; // create tmp. pointer to the data that follows curr->next (done through pointer cpy)
            delete curr->next; // to prevent orphaned data that would occur by just redirecting curr->next to curr->next->next
            curr->next = tmp; // the next element to be processed by the loop should be what used to follow curr->next, which is now in tmp. This also relinks the list properly.
        }
    }
}