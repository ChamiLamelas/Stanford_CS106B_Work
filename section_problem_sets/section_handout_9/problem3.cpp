#include <map>
#include <set>
using namespace std;

enum visitStateT {
    UNKNOWN = 0, DISCOVERED = 1, EXPLORED = 2
};

struct edgeT;

struct nodeT {
    string name;
    set<edgeT *> connected;
};

struct edgeT {
    nodeT *start;
    nodeT *end;
};

struct graphT {
    set<nodeT*> nodes;
};

bool dfsVisit(nodeT *node, map<nodeT*, visitStateT> &visited) {
    visited[node] = DISCOVERED;
    for (edgeT *edge : node->connected) {
        if (visited[edge->end] == DISCOVERED) {
            return true;
        }
        else if (visited[edge->end] == UNKNOWN) {
            if (dfsVisit(edge->end, visited)) {
                return true;
            }
        }
    }
    visited[node] = EXPLORED;
    return false;
}

bool isCyclicGraph(graphT &graph) {
    map<nodeT*, visitStateT> visited;
    for (nodeT *node : graph.nodes) {
        visited[node] = UNKNOWN;
    }
    for (nodeT *node : graph.nodes) {
        if (visited[node] == UNKNOWN && dfsVisit(node, visited)) {
            return true;
        }
    }
    return false;
}