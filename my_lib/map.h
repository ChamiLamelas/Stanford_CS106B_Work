// TODO have a Map abstract class that has comparison function & numPairs, leaves containsKey(), put(), get(), erase() as abstract and implement size().
// TODO Implement erase(), clear() for TreeMap & HashMap

#ifndef MAP_H
#define MAP_H

#include <vector>
#include "general_utils.h"
using namespace std;

// load factor = no. of entries / no. of buckets (in best case this would be about 1)
const int MAX_LOAD_FACTOR = 2;
const int INITIAL_TABLE_SIZE = 13;
const int SIZING_FACTOR = 2;

template <typename K, typename V>
struct pairT {
    K key;
    V value;
};

template <typename K, typename V>
class HashMap {
    public:
        HashMap(int (hashFn)(const K &key), int (cmpFn)(const K &key1, const K &key2) = operatorCmp);
        ~HashMap();
        bool containsKey(const K &key) const;
        void put(const K &key, const V &value); 
        V& get(const K& key);
        const V& get(const K &key) const;
        unsigned int size() const;

    private:
        struct node {
            node *next;
            pairT<K, V> data;
        };

        vector<node*> table;
        unsigned int numPairs; 
        unsigned int numBuckets;
        int (*comparisonFunc)(const K &key1, const K &key2);
        int (*hashFunc)(const K &key);

        void rehash();
        node *findInBucket(const K &key, int bucket) const;
        int hashToTableSize(const K &key) const;

        // Disallow copying
        HashMap(const HashMap&); 
        HashMap& operator= (const HashMap&);
};

template <typename K, typename V>
class TreeMap {
    public:
        // Runtime: O(1)
        TreeMap(int (cmpFn)(const K &key1, const K &key2) = operatorCmp);
        // Runtime: O(N)
        ~TreeMap();
        // Runtime: O(N) 
        bool containsKey(const K &key) const;
        // Runtime: O(N) 
        void put(const K &key, const V &value); 
        // Runtime: O(N)
        V& get(const K& key);
        // Runtime: O(N)
        const V& get(const K &key) const;
        // Runtime: N/A
        void erase(const K &key);
        // Runtime: O(1)
        unsigned int size() const;

    private:
        struct node {
            node *leftChild;
            node *rightChild;
            pairT<K, V> data;
        };

        node *root;
        unsigned int numPairs;
        int (*comparisonFunc)(const K &key1, const K &key2);
        
        // Runtime: O(N) 
        node *bstSearch(const K &key) const;

        // Disallow copying
        TreeMap(const TreeMap&); 
        TreeMap& operator= (const TreeMap&);
};

#endif