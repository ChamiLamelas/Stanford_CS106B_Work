#ifndef STACK_H
#define STACK_H

#include "vector.h"
#include "vector.cpp"

template <typename T>
class VectorStack {
    public:
        VectorStack() {};
        ~VectorStack() {};

        void push(const T &entry);
        void pop();
        const T& peek() const;
        T& peek();
        bool empty() const;
        unsigned int size() const;
        void clear();

    private:
        Vector<T> buf;

        VectorStack(const VectorStack&); 
        VectorStack& operator= (const VectorStack&);
};

template <typename T>
struct Node {
    T data;
    Node<T> *next;
};

template <typename T>
class LinkedListStack {
    public: 
        LinkedListStack();
        ~LinkedListStack();

        void push(const T &entry);
        void pop();
        const T& peek() const;
        T& peek();
        bool empty() const;
        unsigned int size() const;
        void clear();

    private:
        unsigned int numElements;
        Node<T> *head;

        LinkedListStack(const LinkedListStack&); 
        LinkedListStack& operator= (const LinkedListStack&);
};

#endif 