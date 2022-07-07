#include <set>
using namespace std;

struct vertexT;

struct edgeT {
    vertexT *start, *end;
};

struct vertexT {
    set<edgeT*> outgoing;
};

struct graphT {
    set<vertexT*> vertices;
};

void deallocateGraph(graphT &graph) {
    for (vertexT *v : graph.vertices) {
        for (edgeT *edge : v->outgoing) {
            delete edge;
        }
        delete v;
    }
}