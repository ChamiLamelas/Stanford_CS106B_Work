#include "map.h"
#include <stdexcept>
#include <stack>
#include <vector>
//#include <iostream> // debug
using namespace std; 

template <typename K, typename V>
HashMap<K, V>::HashMap(int (hashFn)(const K &key), int (cmpFn)(const K &key1, const K &key2)) {
    table.resize(INITIAL_TABLE_SIZE, nullptr);
    numPairs = 0;
    numBuckets = 0;
    hashFunc = hashFn;
    comparisonFunc = cmpFn;
}

template <typename K, typename V> 
HashMap<K, V>::~HashMap() {
    for (node *n : table) {
        while (n != nullptr) {
            node *tmp = n->next;
            delete n;
            n = tmp;
        }
    }
}

template <typename K, typename V>
bool HashMap<K, V>::containsKey(const K &key) const { 
    return findInBucket(key, hashToTableSize(key)) != nullptr;
}

template <typename K, typename V>
void HashMap<K, V>::put(const K &key, const V &value) {
    int bucket = hashToTableSize(key);
    node *res = findInBucket(key, bucket);
    if (res != nullptr) {
        res->data.value = value;
    }
    else {
        if (numBuckets > 0 && numPairs/numBuckets >= MAX_LOAD_FACTOR) {
            rehash();
        } 
        if (table[bucket] == nullptr) {
            numBuckets++;
        }
        node *newNode = new node;
        newNode->data.key = key;
        newNode->data.value = value;
        newNode->next = table[bucket];
        table[bucket] = newNode;
        numPairs++;
    }
}

template <typename K, typename V>
const V& HashMap<K, V>::get(const K &key) const {
    node *res = findInBucket(key, hashToTableSize(key));
    if (res == nullptr) {
        throw invalid_argument("Cannot retrieve value of nonexistent key.");
    }
    return res->data.value;
}

template <typename K, typename V>
V& HashMap<K, V>::get(const K &key) {
    node *res = findInBucket(key, hashToTableSize(key));
    if (res == nullptr) {
        throw invalid_argument("Cannot retrieve value of nonexistent key.");
    }
    return res->data.value;
}

template <typename K, typename V>
unsigned int HashMap<K, V>::size() const {
    return numPairs;
}

template <typename K, typename V> 
void HashMap<K, V>::rehash() {
    //cerr << "Rehashing...";
    vector<node*> tmp = table;
    table.clear();
    table.resize(SIZING_FACTOR*tmp.size());
    numPairs = 0;
    numBuckets = 0;
    for (typename vector<HashMap<K, V>::node*>::iterator itr = tmp.begin(); itr != tmp.end(); itr++) {
        node *cur = *itr;
        while (cur != nullptr) {
            node *tmp = cur->next;
            put(cur->data.key, cur->data.value);
            delete cur;
            cur = tmp;
        }
    }
}

template <typename K, typename V> 
int HashMap<K, V>::hashToTableSize(const K &key) const {
    return hashFunc(key) % table.size();
}

template <typename K, typename V> 
typename HashMap<K, V>::node *HashMap<K, V>::findInBucket(const K &key, int bucket) const {
    node *bucketTop = table[bucket];
    while (bucketTop != nullptr) {
        if (comparisonFunc(bucketTop->data.key, key) == 0) {
            return bucketTop;
        }
        bucketTop = bucketTop->next;
    }
    return nullptr;
}

template <typename K, typename V>
TreeMap<K, V>::TreeMap(int (cmpFn)(const K &key1, const K &key2)) {
    root = nullptr;
    numPairs = 0;
    comparisonFunc = cmpFn;
}

/* In class, a recursive post order soln. was recommended, but as with linked lists, I delete the root before moving on. Furthermore, I used an iterative algorithm to do the
preorder traversal. 
*/
template <typename K, typename V>
TreeMap<K, V>::~TreeMap() {
    stack<node*> s;
    while (root != nullptr || !s.empty()) {
        if (root == nullptr) {
            node *tmp = s.top()->rightChild;
            delete s.top();
            s.pop();
            root = tmp;
        }
        else{
            s.push(root);
            root = root->leftChild;
        }
    }
}

template <typename K, typename V>
bool TreeMap<K, V>::containsKey(const K &key) const {
    return bstSearch(key) != nullptr;
}

template <typename K, typename V>
void TreeMap<K, V>::put(const K &key, const V &value) {    
    node *curr = root; 
    node *addPt = nullptr; 
    while (curr != nullptr) {
        addPt = curr;
        if (comparisonFunc(key, curr->data.key) == 1) {
            curr = curr->rightChild;
        }
        else if (comparisonFunc(key, curr->data.key) == -1) {
            curr = curr->leftChild;
        }
        else {
            curr->data.value = value;
            return;
        }
    }

    node *newNode = new node;
    newNode->data.key = key;
    newNode->data.value = value;
    newNode->leftChild = nullptr;
    newNode->rightChild = nullptr;
    if (addPt == nullptr) {
        root = newNode;
    }
    else if (comparisonFunc(key, addPt->data.key) == -1) {
        addPt->leftChild = newNode;
    }
    else {
        addPt->rightChild = newNode;
    }
    numPairs++;
}

template <typename K, typename V>
const V& TreeMap<K, V>::get(const K &key) const {
    node *res = bstSearch(key);
    if (res == nullptr) {
        throw invalid_argument("Cannot retrieve data from nonexistent key.");
    }
    return res->data.value;
}

template <typename K, typename V>
V& TreeMap<K, V>::get(const K &key) {
    node *res = bstSearch(key);
    if (res == nullptr) {
        throw invalid_argument("Cannot retrieve data from nonexistent key.");
    }
    return res->data.value;
}

template <typename K, typename V>
unsigned int TreeMap<K, V>::size() const {
    return numPairs;
}

template <typename K, typename V>
void TreeMap<K, V>::erase(const K &key) {
    
}

template <typename K, typename V>
typename TreeMap<K, V>::node *TreeMap<K, V>::bstSearch(const K &key) const {
    node *curr = root;
    while (curr != nullptr && comparisonFunc(curr->data.key, key) != 0) {
        if (comparisonFunc(key, curr->data.key) == 1) {
            curr = curr->rightChild;
        }
        else {
            curr = curr->leftChild;
        }
    }
    return curr; 
}