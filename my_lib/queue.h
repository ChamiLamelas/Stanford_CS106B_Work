/* TODO 
Templatize sorted chunklist pq
Add comparison call back to sorted chunk list pq 
Add increase-key to sorted chunklist pq 
Create a Max Priority Queue abstract class. 
Add deep copy support to both Max Priority Queues
*/

#ifndef QUEUE_H
#define QUEUE_H

#include <string>
#include "general_utils.h"
using namespace std;

// Runtime: O(1)
void checkEmpty(bool emptyState, const string &opName);

template <typename T>
class Queue {
    public:
        Queue();
        ~Queue();

        unsigned int size() const;
        bool empty() const;
        void enqueue(const T &entry);
        void dequeue();
        const T& front() const;
        T& front();
        void clear();

    private:
        struct Node {
            T data;
            Node *next;
        };

        Node *head;
        Node *tail;
        unsigned int numElements;

        Queue(const Queue&); 
        Queue& operator= (const Queue&);
};

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
        /* Holds the maximum number of elements per block in a Node. 
        In Runtime analysis, will be referred to as M. */
        static const unsigned int MAX_ELEMS_PER_BLOCK = 4; 
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

        Node *head;
        unsigned int numEntries; 
        // Runtime: O(M)
        static void split(Node *&node);

        // making copy constructor & assignment operator private to disallow copying
        SortedChunkListMaxPriorityQueue(const SortedChunkListMaxPriorityQueue&); 
        SortedChunkListMaxPriorityQueue& operator= (const SortedChunkListMaxPriorityQueue&);
};

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
        static const unsigned int HEAP_SIZING_FACTOR = 2; 
        static const unsigned int INITIAL_HEAP_CAPACITY = 10;

        T *heap;
        unsigned int numEntries;
        unsigned int capacity;
        int (*comparisonFunc)(T&, T&);

        // Runtime: O(1)
        inline static int parent(int index) { return index/2; }
        // Runtime: O(1)
        inline static int leftChild(int index) { return 2*index; }
        // Runtime: O(1)
        inline static int rightChild(int index) { return 2*index + 1; }
        // Runtime: O(1)
        static void exchange(T &x, T &y);

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