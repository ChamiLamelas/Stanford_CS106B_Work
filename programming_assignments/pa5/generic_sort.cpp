/* Sorting Write-up: 

I chose to have a generic sort function that uses shell sort and heap sort. First, I will outline the pros & cons of this algorithm.

Pros:
Both shell sort and heap sort are in-place 
If the data set is small, shell sort is used and is in the worst case is O(N^2), but is a better N^2 than insertion, selection, or
quick sort. 
If the data set is large, heap sort is used and is in the worst case O(NlogN)

Cons: 
O(nlogn) for sorted data 
Heaps require 1-based array indexing, thus heapsort must shift all the elements of the input vector up by 1 before sorting it and
shift them back after. Thus 2 O(n) ops. must be done. 
Harder to code, must have knowledge of constructing a max heap & maintaining the max heap property
Hard to calculate runtime of Shell Sort making it difficult to find a good crossing over point

Since neither algorithm is recursive, they can be used separately (not like a mesh of merge/quick sort with insertion/selection sort for
example). However, the cross over point to switch between the 2 is difficult to calculate as mentioned above and I used experimental
data to switch between the 2. That is, I counted the approx. number of ops. done by shell sort using print statements & used the following
runtime function for heap sort: 3n + nlogn. By comparing their outputs for the 2, between 100-1000 elements, heap sort begins to 
do less operations than shell sort.

V.S. merge sort individually: 

This algorithm does not use up extra space like merge sort does and could potentially perform less ops. For smaller to medium range
data sets thanks to the lower N^2 constant factor of shell sort which can be used for those size ranges. 

V.S. quick sort individually: 

This algorithm would never degrade to O(N^2) for large data sets like Quick Sort could (in the case of the data being sorted/reverse
sorted for example). It would only degrade to O(N^2) when shell sort is used on small-medium data sets and in that case has a lower
constant factor. However, if a good pivot is chosen in the Quick Sort algorithm, the likelihood of O(N^2) behavior is significantly
lowered and Quick sort would most likely outperform this algorithm on large data sets when the additional O(N) steps taken by 
heapSort to prepare the heap are done. 

V.S. a (merge sort / quick sort) + insertion sort hybrid: 

This algorithm does better against this hybrid when the data is not sorted. This is because shell sort internally optimizes insertion
sort, hence it has a smaller constant factor in its runtime. 
However, the algorithm may suffer if the data set is either sorted or made up of chunks that are individually sorted. This is because
the hybrid in those cases would switch to insertion sort which is O(n) for sorted data. This algorithm would lag behind at O(nlogn) in
the best case.

 */

#include <vector>
#include <set> 
#include <iostream> 
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

void sort(vector<int> &v);
void shellSort(vector<int> &v);
void heapSort(vector<int> &v);
void buildMaxHeap(vector<int> &v);
void maxHeapifyDown(vector<int> &v, int heapsize, int i);
void exchange(int &x, int &y);
inline int leftChild(int i);
inline int rightChild(int i);

int compare(string s1, string s2) {
    if (s1.length() < s2.length()) {
        return -1;
    }
    else if (s1.length() > s2.length()) {
        return 1;
    }
    return 0;
}

int compare(set<int> s1, set<int> s2) {
    int sumS1 = 0, sumS2 = 0;
    for (auto i = s1.begin(); i != s1.end(); i++) {
        sumS1 += *i;
    }
    for (auto j = s2.begin(); j != s2.end(); j++) {
        sumS2 += *j;
    }
    if (sumS1 < sumS2) {
        return -1;
    }
    else if (sumS1 > sumS2) {
        return 1;
    }
    return 0;
}

int main() {
    vector<int> v;
    int n, state;
    cout << "n=";
    cin >> n;
    cout << "state (inc. 1, dec. 2, custom 3, other)=";
    cin >> state;
    if (state==1) {
        for (int i = 0; i < n; i++) {
            v.push_back(i);
        }
    }
    else if (state==2) {
        for (int i = n-1; i >= 0; i--) {
            v.push_back(i);
        }
    }
    else if (state==3) {
        v.resize(n);
        for (int i = 0; i < n; i++) {
            cout << "v[" << i << "]=";
            cin >> v[i];
        }
    }
    else {
        srand(time(0));
        for (int i = 0; i < n; i++) {
            v.push_back(rand() % n);
        }
    }

    vector<int> w = v;
    //shellSort(v);
    // for (vector<int>::iterator itr = w.begin(); itr != w.end(); itr++){ 
    //     cout << *itr << ' ';
    // }
    // cout << '\n';
    heapSort(w);
    // for (vector<int>::iterator itr = w.begin(); itr != w.end(); itr++){ 
    //     cout << *itr << ' ';
    // }
    // cout << '\n'; 

}

void sort(vector<int> &v) {
    if (v.size() < 100) {
        shellSort(v);
    }
    else {
        heapSort(v);
    }
}

/* Let v[1...n] be the input vector and g be some gapsize. Let i=g...n
For v[i], let v_gi be the set of sorted elements such that for each element in v_gi, they have an index = i-k*g where k >= 1 
That is, each element in v_gi lies some multiple of g before i.
Use insertion sort to place v[i] correctly among the elements of v_gi, moving elements that are larger than it up to make space. 
Repeat this process for i=g...n with a smaller gapsize (could divide g by 2, or take from a given seq. as in the implementation
below.)

In general the underlying idea is as follows: 
"Shellsort is a generalization of insertion sort that allows the exchange of items that are far apart. The idea is to arrange the 
list of elements so that, starting anywhere, considering every hth element gives a sorted list. Such a list is said to be h-sorted. 
Equivalently, it can be thought of as h interleaved lists, each individually sorted. Beginning with large values of h, this 
rearrangement allows elements to move long distances in the original list, reducing large amounts of disorder quickly, and leaving 
less work for smaller h-sort steps to do."

Ref: https://en.wikipedia.org/wiki/Shellsort

The algorithm is O(n^2) in the worst case, but has a smaller constant than the other O(N^2) sorting algorithms: insertion, selection,
and bubble.
 */
void shellSort(vector<int> &v) { 
    int gapSeq[] = {701, 301, 132, 57, 23, 10, 4, 1}; // Marcin Ciura's gap sequence, also taken from Wikipedia 
    int numGaps = 8;
    for (int gapCtr = 0; gapCtr < numGaps; gapCtr++) { 
        for (int i = gapSeq[gapCtr]; i < v.size(); i++) { 
            int tmp = v[i];
            int j = i; 
            for (; j - gapSeq[gapCtr] >= 0 && tmp < v[j - gapSeq[gapCtr]]; j -= gapSeq[gapCtr]) { 
                v[j] = v[j - gapSeq[gapCtr]];
            }
            v[j] = tmp;
        }
    }
}

/* runtime: 

heap building is O(n) as well as insertion & removal at the head of a vector. maxHeapifyDown is in the worst case O(logn) and is run
n times. Thus the runtime is the sum of 3O(n) ops. and 1 O(nlogn) op. which means its O(nlogn).
 */
void heapSort(vector<int> &v) {
    v.insert(v.begin(), -1); // just want a shift, inserting rand. # 
    buildMaxHeap(v);
    cout << endl;
    int heapsize = v.size() - 1;
    for (int i = v.size()-1; i > 1; i--) {
        exchange(v[i], v[1]);
        heapsize--;
        maxHeapifyDown(v, heapsize, 1);
    }
    v.erase(v.begin()); // have to shift again
}

void buildMaxHeap(vector<int> &v) {
    int heapsize = v.size()-1;
    for (int i = heapsize/2; i >= 1; i--) {
        maxHeapifyDown(v, heapsize, i);
    }
}

void maxHeapifyDown(vector<int> &v, int heapsize, int i) {
    int largest = i; 
    int l = leftChild(i);
    int r = rightChild(i);
    if (l <= heapsize && v[l] > v[largest]) {
        largest = l;
    }
    if (r <= heapsize && v[r] > v[largest]) {
        largest = r;
    }
    if (largest != i) {
        exchange(v[largest], v[i]);
        maxHeapifyDown(v, heapsize, largest);
    }
}

inline int leftChild(int i) {
    return i*2; 
}

inline int rightChild(int i) {
    return i*2 + 1;
}

void exchange(int &x, int &y) {
    int tmp = x;
    x = y;
    y = tmp;
}
