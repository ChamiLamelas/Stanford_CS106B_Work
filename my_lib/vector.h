/* File that holds my implementation of the vector class. */

#ifndef VECTOR_H
#define VECTOR_H

const unsigned int INTIAL_CAPACITY = 10; // Initial capacity of a Vector object 
// When the Vector is full, it will be resized to its current capacity * SIZING_FACTOR
// When the Vector's no. of used entries = its capacity / SIZING_FACTOR, it will be downsized to capacity / SIZING_FACTOR 
const unsigned int SIZING_FACTOR = 2; 

/* Class that represents a Vector of entries of type T. It has the majority of downsides of a regular array usage (e.g. having to
shift entries when one is removed from the middle or when the user wants to add a new one), but it provides a few benefits over working
with regular arrays.

(i) resizing is done automatically when you insert/remove from the middle
(ii) dynamic memory allocation is wrapped
(iii) bounds checking, any entered index will be checked before trying to access data at that location

Warning: As of now it cannot be copied! 
 */
template <typename T>
class Vector {
    public: 
        /* Default Constructor: Constructs a new empty Vector. */
        Vector();
        /* Destructor: deconstructs the Vector. */
        ~Vector(); 

        /* Retrieves the number of elements that are in this Vector.
        @return the number of elements in the Vector 
         */
        unsigned int size() const;
        /* Adds an entry to the end of the Vector. 
        @param entry - reference to the const variable that will be added to the Vector 
         */
        void add(const T &entry); 
        /* Inserts an entry at a given index in the Vector. 
        @param idx - the index to add at 
        @param entry - reference to the const variable that will be added to the Vector
        @throws invalid_argument if idx < 0 or idx > size() (note: inserting at idx=size() is the same as using add())
         */
        void insert(int idx, const T &entry);
        /* Removes the entry at a given index in the Vector. 
        @param idx - the index to remove from 
        @throws invalid_argument if idx < 0 or idx >= size() 
         */
        void remove(int idx);
        /* Gets the entry at a given index for reading.
        @param idx - index to retrieve entry from
        @return const reference to entry at idx 
        @throws invalid_argument if idx < 0 or idx >= size()
         */
        const T& get(int idx) const;
        /* Gets the entry at a given index for reading/writing.
        @param idx - index to retrieve entry from
        @return reference to entry at idx
        @throws invalid_argument if idx < 0 or idx >= size() 
         */
        T& get(int idx);
        /* Reports to the user if the Vector has no elements. 
        @return truth value of Vector being empty
         */
        bool empty() const;
        /* Empties the Vector. Vector can now be used as if it was just constructed.
         */
        void clear();

    private: 
        T *buf; // Pointer to internal dynamically allocated array of T type 
        unsigned int used; // used is the number of entries the user has put in the Vector
        /* capacity is the number of total slots that the Vector has to work with. This is because C++ doesn't internally track
        the size of arrays. Thus, the only way Vector knows when to resize is by tracking how much free space it has to work with. 
         */
        unsigned int capacity; 

        /* Resizes the vector to a new size.
        @param newSize - a new size 
        @precondition newSize > 0, not checked as this method is used internally 
         */
        void resize(unsigned int newSize);
        /* Checks an index to see if its a positive integer smaller than a max.
        @param idx - an index
        @param max - some max val. 
        @throws invalid_argument if idx is not in [0, max)
         */
        void checkIdx(int idx, int max) const;    

        // Disallowing copying by making copy constructor & copy assignment operator private.
        Vector(const Vector&); 
        Vector& operator= (const Vector&);
};

#endif 
