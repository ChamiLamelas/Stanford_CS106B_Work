#include "testing_lib.h"
#include "testing_lib.cpp"
#include "queue.h"
#include "queue.cpp"
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

int main() {

    Tester t;

    Queue<int> q;
    q.enqueue(100);
    t.report(q.size(), (unsigned int)1);
    t.report(q.empty(), false);
    t.report(q.front(), 100);
    q.dequeue();
    q.clear();
    t.report(q.empty(), true);
    t.report(q.size(), (unsigned int)0);

    for (int i = 1; i <= 7; i++) {
        q.enqueue(i);
        t.report(q.front(), 1);
        t.report(q.size(), (unsigned int)i);
    }

    unsigned int k = q.size();
    for (int j = 1; j <= k; j++) {
        t.report(q.front(), j);
        q.enqueue(q.front());
        q.dequeue();
    }

    q.clear();

    Queue<char> qc;
    t.report(qc.empty(), true);
    qc.enqueue('a');
    qc.dequeue();
    qc.enqueue('b');
    qc.clear();

    //LSMaxPQ l;
    HeapMaxPriorityQueue<int> l;

    t.report(l.empty(), true);
    t.report(l.size(), (unsigned int)0);
    l.enqueue(10);
    t.report(l.front(), 10);
    t.report(l.size(), (unsigned int)1);
    l.enqueue(15);
    t.report(l.front(), 15);
    t.report(l.size(), (unsigned int)2);
    l.dequeue();
    t.report(l.front(), 10);
    t.report(l.size(), (unsigned int)1);
    l.dequeue();
    t.report(l.empty(), true);

    for (unsigned int i = 1; i <= 5; i++) {
        l.enqueue(i);
        t.report(l.front(), int(i));
        t.report(l.size(), i);
    }
    l.clear();
    for (unsigned int j = 5; j >= 1; j--) {
        l.enqueue(j);
        t.report(l.front(), 5);
        t.report(l.size(), 5-j+1);
    }
    l.clear();

    int max = 0;

    srand(time(0));
    vector<int> v;
    for (unsigned int i = 0; i < 100; i++) {
        int r = rand() % 100 + 1;
        //cout << r << ' ';
        if (r > max) {
            max = r;
        }
        l.enqueue(r);
        t.report(l.front(), max);
        v.push_back(r);
    }
    sort(v.begin(), v.end());
    while (!l.empty()) {
        t.report(l.front(), v.back());
        l.dequeue();
        v.pop_back();
    }

    for (int i = 1; i <= 5; i++) {
        l.enqueue(i);
        t.report(l.front(), i);
    }
    l.enqueue(2);
    l.increaseEntry(1, 10);
    t.report(l.front(), 10);
    l.dequeue();
    t.report(l.front(), 5);
    l.increaseEntry(2, 8);
    t.report(l.front(), 8);
    l.dequeue();
    t.report(l.front(), 8);
    l.dequeue();
    t.report(l.front(), 5);
    l.dequeue();
    t.report(l.front(), 4);
    l.dequeue();
    t.report(l.front(), 3);
    l.dequeue();
    t.report(l.empty(), true);

    return 0;
}