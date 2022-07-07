#include <iostream> 
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

struct Cell {
    Cell* next;
    int value;
};

Cell* convertToList(const vector<int>& vec);
Cell* recConvertToList(const vector<int>& vec);
Cell* recConvertToList(const vector<int>& vec, int i);

int sumList(Cell* list);
int recSumList(Cell* list);

void addToHead(Cell* &head, Cell* newNode);
void deallocateList(Cell* list);
void printList(const Cell* const list);

int main() {
    vector<int> nums;
    srand(time(NULL));

    int numInputs = rand() % 11 + 0; // nos. in [0, 10]
    for (int i = 0; i < numInputs; i++) {
        nums.push_back(rand() % 21 - 10); // nos. in [-10, 10]
    }
    cout << "Input: ";
    for (vector<int>::iterator itr = nums.begin(); itr != nums.end(); itr++) {
        cout << *itr << ' ';
    }

    cout << "\nVector as linked list.\n";
    cout << "Iterative: ";
    Cell* list = convertToList(nums);
    printList(list);
    cout << "Recursive: ";
    Cell* recList = recConvertToList(nums);
    printList(recList);

    cout << "Sum of elements in linked list.\n";
    cout << "Iterative (using iterative result from last test): " << sumList(list) << '\n';
    cout << "Recursive (using recursive result from last test): " << recSumList(recList) << '\n';

    deallocateList(list);
    deallocateList(recList);
    cout << endl;
}


Cell* convertToList(const vector<int>& vec) {
    Cell* list = NULL;
    for (vector<int>::const_reverse_iterator itr = vec.rbegin(); itr != vec.rend(); itr++) {
        Cell* newNode = new Cell;
        newNode->value = *itr;
        addToHead(list, newNode);
    }
    return list;
}

Cell* recConvertToList(const vector<int>& vec) {
    return recConvertToList(vec, 0);
}

Cell* recConvertToList(const vector<int>& vec, int i) {
    if (i >= vec.size()) {
        return NULL;
    }

    Cell* c = new Cell; 
    c->value = vec[i];
    c->next = recConvertToList(vec, i+1);
    return c;
}

int sumList(Cell* list) {
    int sum = 0;
    for (Cell* curr = list; curr != NULL; curr = curr->next) {
        sum += curr->value;
    }
    return sum;
}

int recSumList(Cell* list) {
    if (list == NULL) {
        return 0;
    }
    return list->value + recSumList(list->next);
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

