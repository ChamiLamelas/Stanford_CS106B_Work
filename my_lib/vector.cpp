#include "vector.h"
#include <stdexcept>
// #include <iostream> // used in testing 
using namespace std;

template <typename T>
void Vector<T>::checkIdx(int idx, int max) const {
    if (idx < 0 || idx >= max) {
        throw invalid_argument("Index out of bounds.");
    }
}

template <typename T>
void Vector<T>::resize(unsigned int newSize) {
    // cout << "resizing " << capacity << " -> " << newSize << '\n'; // used in testing 
    T* cpy = new T[newSize];
    int stop = min(newSize, used);
    for (unsigned int i = 0; i < stop; i++) {
        cpy[i] = buf[i];
    }
    // now, we want the buffer to point to the larger array. However, doing that without first deleting the memory buffer currently
    // points to would cause a resource leak. That is because the memory could never be tracked down again. Since a deep copy
    // has successfully been performed of the data in the buffer into the copy, deleting the buffer has no effect on the copy
    delete[] buf; 
    buf = cpy;
    capacity = newSize;
    // warning! do not delete cpy now even though its been allocated with new. This is because buffer now points to that location
    // the pointer cpy will just go out of scope (like any local variable)
}

template <typename T>
Vector<T>::Vector() {
    capacity = INTIAL_CAPACITY;
    buf = new T[capacity];
    used = 0;
}

template <typename T>
Vector<T>::~Vector() {
    delete[] buf;
}

template <typename T>
unsigned int Vector<T>::size() const {
    return used; 
}

template <typename T>
void Vector<T>::add(const T &entry) {
    if (used == capacity) {
        resize(capacity*SIZING_FACTOR);
    }
    buf[used++] = entry; 
}

template <typename T>
void Vector<T>::insert(int idx, const T &entry) {
    checkIdx(idx, used+1);
    if (used == capacity) {
        resize(capacity*SIZING_FACTOR);
    }
    for (int i = used - 1; i >= idx; i--) {
        buf[i+1] = buf[i];
    }
    buf[idx] = entry;
    used++;
}

template <typename T>
void Vector<T>::remove(int idx) {
    checkIdx(idx, used);
    // Resizing down removed
    // if (capacity > INTIAL_CAPACITY && capacity == used*SIZING_FACTOR) {
    //     resize(capacity/SIZING_FACTOR);
    // }
    for (int i = idx; i < used - 1; i++) {
        buf[i] = buf[i + 1];
    }
    used--;
}

template <typename T>
const T& Vector<T>::get(int idx) const {
    checkIdx(idx, used);
    return buf[idx];
}

template <typename T>  
T& Vector<T>::get(int idx) {
    checkIdx(idx, used);
    return buf[idx];
}

template <typename T>
void Vector<T>::clear() {
    delete[] buf; // free what ever resources were currently in use before re-initializing buffer (prevents resource leak )
    used = 0;
    capacity = INTIAL_CAPACITY;
    buf = new T[capacity];
}

template <typename T>
bool Vector<T>::empty() const {
    return size()==0;
}