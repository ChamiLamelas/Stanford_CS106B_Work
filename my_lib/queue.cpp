#include "queue.h"
#include <stdexcept>
#include <iostream> // debugging
#include <string>
using namespace std;

void checkEmpty(bool emptyState, const string &opName) {
    if (emptyState) {
        throw invalid_argument("Cannot perform " + opName + " on empty Queue.");
    }
}

template <typename T>
Queue<T>::Queue() {
    head = nullptr;
    tail = nullptr;
    numElements = 0;
}

template <typename T>
Queue<T>::~Queue() {
    while (head != nullptr) {
        Node *tmp = head->next;
        delete head;
        head = tmp;
    }
}

template <typename T>
unsigned int Queue<T>::size() const {
    return numElements;
}

template <typename T>
bool Queue<T>::empty() const {
    return head == nullptr;
}

template <typename T>
void Queue<T>::enqueue(const T &entry) {
    Node *newNode = new Node;
    newNode->data = entry;
    newNode->next = nullptr;
    if (empty()) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
    numElements++;
}

template <typename T>
void Queue<T>::dequeue() {
    checkEmpty(empty(), "dequeue");
    //cerr << head << " v.s " << tail << '\n';
    Node *tmp = head->next;
    delete head;
    head = tmp;
    numElements--;
    /* if now there are no elements, and head had been pointing to the same address as tail, now tail is pointing to a deleted memory
    To see that tail still points to what head & tail used to point to, uncomment the line above tmp declaration, and the one
    following this comment
    even though the user can't access tail, it goes against the idea of objects never being in some undefined state for tail
    to be pointing to some unknown data. TO see this, uncomment the following: */
    //cerr << head << " v.s " << tail << '\n';
    if (empty()) { 
        tail = nullptr;
    }
}

template <typename T>
const T& Queue<T>::front() const {
    checkEmpty(empty(), " get front of ");
    return head->data;
}

template <typename T>
T& Queue<T>::front() {
    checkEmpty(empty(), " get front of ");
    return head->data;
}

template <typename T>
void Queue<T>::clear() {
    while (head != nullptr) {
        Node *tmp = head->next;
        delete head;
        head = tmp;
    }
    head = nullptr;
    tail = nullptr;
    numElements = 0;
}

void SortedChunkListMaxPriorityQueue::split(Node *&node) {
    Node *split = new Node;
    for (unsigned int i = MAX_ELEMS_PER_BLOCK/2; i < MAX_ELEMS_PER_BLOCK; i++) {
        split->block[i - MAX_ELEMS_PER_BLOCK/2] = node->block[i];
    }   
    node->used = MAX_ELEMS_PER_BLOCK/2;
    split->used = MAX_ELEMS_PER_BLOCK - node->used;
    split->next = node->next;
    node->next = split;
}

SortedChunkListMaxPriorityQueue::SortedChunkListMaxPriorityQueue() {
    head = nullptr;
    numEntries = 0;
}

SortedChunkListMaxPriorityQueue::~SortedChunkListMaxPriorityQueue() {
    clear();
}

void SortedChunkListMaxPriorityQueue::enqueue(int entry) {
    if (empty()) { // empty pq 
        head = new Node;
        head->block[0] = entry;
        head->used = 1;
        head->next = nullptr;
    }
    else if (entry > head->block[0]) { // entry is larger than the max. entry in the pq 
        if (head->used == MAX_ELEMS_PER_BLOCK) {
            split(head);
        }
        for (int j = head->used; j > 0; j--) {
            head->block[j] = head->block[j-1];
        }
        head->block[0] = entry;
        head->used++;
    }
    else { // entry is smaller than the max. element in the pq 
        Node *curr;
        for (curr =head; curr->next != nullptr && entry < curr->next->block[0]; curr = curr->next) {}
        bool mustSplit = curr->used == MAX_ELEMS_PER_BLOCK;
        if (mustSplit) {
            split(curr);
        }

        if (mustSplit && entry < curr->next->block[0]) {
            /* If curr was split, there is the possibility that entry should belong in the splitoff block. This is because in the advancement loop above, entry is only compared to
            the tops of each node. Now, there is a new node made up of the splitoff block. Thus, entry must be compared with it. In the case of it being smaller than this new node's
            top block element it should be put into it. 
            
            Observe: we have to go no further because the advancement loop would have processed whatever node comes after the new node (
            because it would have been whatever followed curr).

            Note: If a split occurred, then curr->next->used = MAX_ELEMS_PER_BLOCK - curr->used = MAX_ELEMS_PER_BLOCK - MAX_ELEMS_PER_BLOCK/2 <= MAX_ELEMS_PER_BLOCK-1. Thus, it is
            safe to loop i=curr->next->used...2. 
            */
           unsigned int i;
           for (i = curr->next->used; i > 1 && curr->next->block[i - 1] < entry; i--) {
               curr->next->block[i] = curr->next->block[i - 1];
           }
           // Note: i can be at least 1 and this follows because we know already that entry < curr->next->block[0]. This also keeps duplicate elements in the order they were put in.
           curr->next->block[i] = entry;
           curr->next->used++;
           
        }
        else {
            /* In all other cases, entry should be put into curr->block. This will be explained by first negating the if statement using De Morgan's Law:
            !(mustSplit && entry < curr->next->block[0]) = !mustSplit or !(entry < curr->next->block[0]) = !mustSplit or entry >= curr->next->block[0]              (1)
            From (1), let:
            P = !mustSplit  
            Q = entry >= curr->next->block[0]

            Using a truth table, i-iii will represent the cases in which P or Q is true (i.e. when this else condition is executed). 
            P       Q       P or Q 
            T       T       T           (i)
            T       F       T           (ii)
            F       T       T           (iii)
            F       F       F
            
            Case i: If no splitting occurred, and entry >= curr->next->block[0], entry should be placed in curr->block. This is redundant to the 1st stop condition of the 
            advancement loop and hence follows its logic.
            Case ii: If no splitting occurred, and entry < curr->next->block[0]. This part of the else isn't entirely following the truth table and is more using an 'or' trick
            from the C++ (and other) languages. That is, if the first condition in an or statement is true, the 2nd is not even processed. Note that it is impossible for no split
            to occur and entry to be less than curr->next->block[0] because that would violate the advancement loop's 2nd stop condition. That is the loop hasn't been edited at all
            but suddenly violates a previous condition. Instead case ii is meant to really take account of the advancement loop's 1st stop condition. That is, curr is the last element
            in the list and wasn't split and is therefore pointing next to NULL. In this case, as with the 1st advancement loop, entry must be put into the last node b/c it has space.
            Case iii: Following from the comment below the if statement above, when a split has been made, entry must be compared with the top of the split node's block. In this case,
            entry turns out to be larger than what used to be the middle of curr's block and is now the top of curr->next's block. Thus, entry should be put into curr. Another way
            to explain why entry should be put into curr would be to imagine if curr's next had already existed as a node in the list before entering this method. The advancement
            loop would have stopped before curr's next because entry would no longer have been smaller than curr->next->block[0] (see advancement loop's 2nd stop condition). 
            */
            unsigned int i; 
            for (i = curr->used; i > 1 && entry > curr->block[i-1]; i--) { 
                curr->block[i] = curr->block[i-1];
            }
            curr->block[i] = entry;
            curr->used++;
        }
    }
    numEntries++;
}

void SortedChunkListMaxPriorityQueue::dequeue() {
    checkEmpty(empty(), "dequeue");
    if (head->used == 1) {
        Node *tmp = head->next;
        delete head; 
        head = tmp;
    }
    else {
        head->used--;
        for (unsigned int i = 0; i < head->used; i++) {
            head->block[i] = head->block[i+1];
        }
    }
    numEntries--;
}

int SortedChunkListMaxPriorityQueue::front() const {
    checkEmpty(empty(), "get front of");
    return head->block[0];
}

bool SortedChunkListMaxPriorityQueue::empty() const {
    return head == nullptr;
}

unsigned int SortedChunkListMaxPriorityQueue::size() const {
    return numEntries;
}

void SortedChunkListMaxPriorityQueue::clear() {
    while (head != nullptr) {
        Node *tmp = head->next;
        delete head; 
        head = tmp;
    }
    numEntries = 0;
    head = nullptr;
}

template <typename T>
void HeapMaxPriorityQueue<T>::exchange(T &x, T &y) {
    T tmp = x;
    x = y;
    y = tmp;
}

template <typename T>
void HeapMaxPriorityQueue<T>::heapifyDown(unsigned int index) {
    bool heapifying = true;
    while (index <= numEntries && heapifying) {
        int largest = index;
        int left = leftChild(index);
        int right = rightChild(index);
        if (left <= numEntries && comparisonFunc(heap[left], heap[largest]) == 1) {
            largest = left;
        }
        if (right <= numEntries && comparisonFunc(heap[right], heap[largest]) == 1) {
            largest = right;
        }
        if (largest != index) {
            exchange(heap[largest], heap[index]);
            index = largest;
        }
        else {
            heapifying = false;
        }
    }
    
}

template <typename T>
void HeapMaxPriorityQueue<T>::heapifyUp(unsigned int index) {
    while (index > 1 && comparisonFunc(heap[parent(index)], heap[index]) == -1) {
        exchange(heap[parent(index)], heap[index]);
        index = parent(index);
    }
}

template <typename T>
void HeapMaxPriorityQueue<T>::increaseCapacity() {
    capacity = HEAP_SIZING_FACTOR*capacity; 
    T *buf = new T[capacity + 1]; // 1-based indexing
    for (unsigned int i = 1; i <= numEntries; i++) {
        buf[i] = heap[i];
    }
    delete[] heap;
    heap = buf;
}

template <typename T>
HeapMaxPriorityQueue<T>::HeapMaxPriorityQueue(int (*cmpFn)(T&, T&)) {
    comparisonFunc = cmpFn;
    capacity = INITIAL_HEAP_CAPACITY; 
    heap = new T[capacity + 1];// 1-based indexing
    numEntries = 0;
}

template <typename T>
HeapMaxPriorityQueue<T>::~HeapMaxPriorityQueue() {
    clear();
}

template <typename T>
void HeapMaxPriorityQueue<T>::enqueue(T entry) {
    if (numEntries == capacity) {
        increaseCapacity();
    }
    heap[++numEntries] = entry;
    heapifyUp(numEntries);
}

template <typename T>
void HeapMaxPriorityQueue<T>::increaseEntry(T entry, T newValue) {
    if (comparisonFunc(entry, newValue) <= 0) {
        for (unsigned int i = 1; i <= numEntries; i++) {
            if (comparisonFunc(heap[i], entry) == 0) {
                heap[i] = newValue;
                heapifyUp(i);
            }
        }
    }
    
    
}

template <typename T>
void HeapMaxPriorityQueue<T>::dequeue() {
    checkEmpty(empty(), "dequeue");
    exchange(heap[1], heap[numEntries--]);
    heapifyDown(1);
}

template <typename T>
const T &HeapMaxPriorityQueue<T>::front() const {
    checkEmpty(empty(), "get front of");
    return heap[1];
}

template <typename T>
bool HeapMaxPriorityQueue<T>::empty() const {
    return numEntries == 0;
}

template <typename T>
unsigned int HeapMaxPriorityQueue<T>::size() const {
    return numEntries;
}

template <typename T>
void HeapMaxPriorityQueue<T>::clear() {
    delete[] heap;
    capacity = INITIAL_HEAP_CAPACITY; // 1-based indexing
    heap = new T[capacity + 1];
    numEntries = 0;
}