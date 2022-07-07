/* TODO 
Add increase-key() option to both Max Priority Queues. 
Create a Max Priority Queue abstract class. 
Add deep copy support to both Max Priority Queues
Implement Min Priority Queues and/or other versions of Max Priority Queue 
*/

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <string> 
#include "C:\Users\Chami\Stanford_Cpp_Class\organized_materials_and_my_code\my_lib\general_utils.h"
using namespace std;

class SortedChunkListMaxPriorityQueue;

typedef SortedChunkListMaxPriorityQueue LSMaxPQ;

/* Holds the maximum number of elements per block in a Node. 
In Runtime analysis, will be referred to as M. */
const unsigned int MAX_ELEMS_PER_BLOCK = 4; 
const unsigned int HEAP_SIZING_FACTOR = 2; 
const unsigned int INITIAL_HEAP_CAPACITY = 10;

// Runtime: O(1)
void checkEmpty(bool emptyState, const string &opName);

/* Represents a Node in the sorted chunk list. In Runtime analysis, the number of them in the list will be referred to as a function of N say K(N). At a given time, all the Nodes
in the list besides the head will stored at least M/2 elements. The head can store as few as 1 element. In the worst case in terms of memory usage, the head will store 1 out of N 
elements, leaving the rest of the Nodes (holding their minimum M/2 elements each) to store the remaining N-1 elements.
Let N-1 = CM for some scalar C
Observe: N-1 = 2C(M/2)
Thus, it would require 2C Nodes to store the remaining N-1 elements. 

Therefore, in the worst case K(N) = 1 + 2C = 1 + 2((N-1)/M). That is, W = 1 + 2((N-1)/M) nodes are required to store N elements in the worst case. 
To traverse each non-head node is O(M) even if they only contain M/2 elements. I will use W as the worst possible number of nodes along with O(M) in the runtime analysis of the
various member functions of SortedChunkListMaxPriorityQueue. */
struct Node {
    Node *next;
    int block[MAX_ELEMS_PER_BLOCK];
    int used;
};

// Runtime: O(M)
void split(Node *&node);

class SortedChunkListMaxPriorityQueue {
    public:
        // Runtime: O(1)
        SortedChunkListMaxPriorityQueue();
        // Runtime: O(W)
        ~SortedChunkListMaxPriorityQueue();

        // Runtime: O(W + M)
        void enqueue(int entry);
        // Runtime: O(M)
        void dequeue();
        // Runtime: O(1)
        int front() const;
        // Runtime: O(1)
        bool empty() const;
        // Runtime: O(1)
        unsigned int size() const;
        // Runtime: O()
        void clear();

    private:
        Node *head;
        unsigned int numEntries; 

        // making copy constructor & assignment operator private to disallow copying
        SortedChunkListMaxPriorityQueue(const SortedChunkListMaxPriorityQueue&); 
        SortedChunkListMaxPriorityQueue& operator= (const SortedChunkListMaxPriorityQueue&);
};

// Runtime: O(1)
inline int parent(int index) { return index/2; }
// Runtime: O(1)
inline int leftChild(int index) { return 2*index; }
// Runtime: O(1)
inline int rightChild(int index) { return 2*index + 1; }
// Runtime: O(1)
template <typename T>
void exchange(T &x, T &y);

/* Note on Runtime Analysis: allocation of an array is considered O(1), regardless of the size.
*/
template <typename T>
class HeapMaxPriorityQueue {
    public:
        // Runtime: O(1)
        HeapMaxPriorityQueue(int (*cmpFn)(T&, T&) = operatorCmp);
        // Runtime: O(1)
        ~HeapMaxPriorityQueue();

        // Runtime: O(n) due to the possibility of capacity increase & copy-over
        void enqueue(T entry);
        // Runtime: O(log(n))
        void dequeue();
        // Runtime: O(1)
        const T &front() const;
        // Runtime: O(1)
        bool empty() const;
        // Runtime: O(1)
        unsigned int size() const; 
        // Runtime: O(1)
        void clear();
        // Runtime: 
        void increaseEntry(T entry, T newValue);

    private:
        T *heap;
        unsigned int numEntries;
        unsigned int capacity;
        int (*comparisonFunc)(T&, T&);

        // Runtime: O(n)
        void increaseCapacity();
        // Runtime: O(log(n))
        void heapifyDown(unsigned int index);
        // Runtime: O(log(n))
        void heapifyUp(unsigned int index);

        // making copy constructor & assignment operator private to disallow copying
        HeapMaxPriorityQueue(const HeapMaxPriorityQueue&); 
        HeapMaxPriorityQueue& operator= (const HeapMaxPriorityQueue&);
};

#endif 