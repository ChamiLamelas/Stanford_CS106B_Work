// tests my answer in problem5.txt

#include <iostream> 
#include <string> 
using namespace std;

struct Cell {
    string value;
    Cell* next;
};

void PopRocks(Cell * & mikey);
void addToHead(Cell* &head, Cell* newNode);
void deallocateList(Cell* list);
void printList(const Cell* const list);

int main() {
    Cell* list = NULL;
    cout << "Building list BACK to FRONT.\n";
    while (true) {
        cout << "Entry (RETURN to exit): ";
        string entry;
        getline(cin, entry);
        if (cin.fail()) {
            cerr << "input error";
            return 1;
        }
        if (entry.empty()) {
            break;
        }
        Cell* c = new Cell;
        c->value = entry;
        addToHead(list, c);
    }
    cout << "Built list: "; 
    printList(list);
    PopRocks(list);
    cout << "Post PopRocks: ";
    printList(list);

    deallocateList(list);
    return 0;
}

void PopRocks(Cell * & mikey)
{
    Cell *ptr;
    for (ptr = mikey; ptr->next != NULL; ptr = ptr->next)
    {
    /* Note: loop body intentionally left empty */
    }
    ptr->next = mikey;
    ptr = ptr->next;
    mikey = mikey->next;
    ptr->next = NULL;
}

void addToHead(Cell* &head, Cell* newNode) {
    newNode->next = head; 
    head = newNode;
}

void deallocateList(Cell* list) {
    Cell* nextToDel = NULL;
    while (list != NULL) {
        nextToDel = list->next;
        delete list;
        list = nextToDel;
    }
}

void printList(const Cell* const list) {
    for (const Cell* curr = list; curr != NULL; curr = curr->next) {
        cout << curr->value << ' ';
    }
    cout << endl;
}