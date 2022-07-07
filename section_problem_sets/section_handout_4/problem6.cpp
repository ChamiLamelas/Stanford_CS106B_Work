#include <iostream>
#include <string> 
using namespace std;
 
struct Node {
    string data; 
    Node* next; 
};

void append(Node* &list1, Node* list2);
void addToHead(Node* &head, Node* newNode);
void deallocateList(Node* list);
void buildList(Node*& list);
void printList(const Node* const n);

int main() {
    Node *list1, *list2;
    cout << "Building List 1.\n----------------------------\n"; 
    buildList(list1);
    cout << "Building List 2.\n----------------------------\n";
    buildList(list2);
    cout << "List 1: ";
    printList(list1);
    cout << "List 2: ";
    printList(list2);
    append(list1, list2);
    cout << "List 1 + 2: ";
    printList(list1);
    cout << "List 2: ";
    printList(list2);

    // all the data is put into list1 now, even though there also pointers to the data in list2 still
    // double deletion would lead to undefined behavior 
    deallocateList(list1); 
    return 0;
}

/* From soln. manual. 

Use a reference variable for the first param. Pass next pointer of 'first' to the recursive call by reference. When this reaches the base case, list2 can be assigned to list1. This 
is because list1 is currently an alias for the next field of the last processed 1st list node. Thus, by setting it to list2 that means the last processed first list's node's next
field is set to list2. This then connects the 2 lists. In the case of list1 being empty, the base case is hit immediately. Since list1 is a reference to some variable in the calling
method, it will be properly updated to hold the contents of list2 (the result of appending a list to a non-empty list). This also covers the case of list2 being empty, because 
regardless of the state of list2, its contents will always be attached to list1. 

While the first list is not being "destroyed" in the sense that the data is being lost, but by using recursion, the list is shortened till the reference parameter was an alias
the next field of the last processed 1st list node. 
 */
void append(Node* &list1, Node* list2) {
    if (list1 == NULL) {
        list1 = list2; 
    }
    else {
        append(list1->next, list2);
    }
}

void addToHead(Node* &head, Node* newNode) {
    newNode->next = head; 
    head = newNode;
}

void deallocateList(Node* list) {
    Node* nextToDel = NULL;
    while (list != NULL) {
        nextToDel = list->next;
        delete list;
        list = nextToDel;
    }
}

void buildList(Node*& list) {
    while (true) {
        cout << "Building list backwards.\nEnter string (RETURN to exit): ";
        string s; 
        if (getline(cin, s)) {
            if (s.empty()) {
                break;
            }
            Node* n = new Node;
            n->data = s;
            addToHead(list, n);
        }
        else {
            cerr << "input error" << endl;
            return;
        }
    }
}

void printList(const Node* const list) {
    for (const Node* curr = list; curr != NULL; curr = curr->next) {
        cout << curr->data << ' ';
    }
    cout << endl;
}