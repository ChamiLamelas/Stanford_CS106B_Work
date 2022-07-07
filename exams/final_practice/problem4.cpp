#include <set> 
#include "C:\Users\Chami\Stanford_Cpp_Class\organized_materials_and_my_code\my_lib\graphs.h"
#include <queue> 
using namespace std; 

struct compareNodes {
    // could simplify this to: return v->outgoing.size() - w->outgoing.size()
    bool operator() (const vertexT *&v, const vertexT *&w) const {
        if (v->outgoing.size() < w->outgoing.size()) {
            return 1;
        }
        else if (v->outgoing.size() > w->outgoing.size()) {
            return -1;
        }
        return 0;
    }
}; 

set<vertexT*> findSmallestDomSet(graphT &g) {
    priority_queue<vertexT*, vector<vertexT*>, compareNodes> q;
    for (vertexT *v : g.vertices) {
        q.push(v);
    }
    set<vertexT*> out;
    // bug! don't want to wait till Q is empty, use a second 'dominated' set
    set<vertexT*> dominated;

    while (dominated.size() < g.vertices.size()) {
        vertexT *u = q.top();
        q.pop();
        if (out.find(u) != out.end()) {
            // the 'isRedundant' check could be simplified if cpp set provided a high level 'subset' function as the cs106b lib does 
            bool isRedundant = false;
            for (edgeT *edge : u->outgoing) {
                if (out.find(edge->end) != out.end()) {
                    isRedundant = true;
                }
            }
            if (isRedundant) {
                continue;
            }
        }
        out.insert(u);
        dominated.insert(u);
        // the following addition of the now dominated neighbors could be simplified if cpp set provided a high level 'union' function as the cs106 lib does 
        for (edgeT *e : u->outgoing) {
            dominated.insert(e->end);
        }
    }
    return out;
}