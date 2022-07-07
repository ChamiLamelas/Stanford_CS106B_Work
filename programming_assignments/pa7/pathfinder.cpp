#include <iostream> 
#include <string>
#include "C:\Users\Chami\Stanford_Cpp_Class\organized_materials_and_my_code\programming_assignments\pa6\priority_queue.h"
#include "C:\Users\Chami\Stanford_Cpp_Class\organized_materials_and_my_code\programming_assignments\pa6\priority_queue.cpp"
#include <vector>
#include <set>
#include <fstream>
#include <limits>
#include <stack>
using namespace std; 


// TODO fix addEdge() so that pre-condition isn't necessary
class Graph { 

    public:
        struct node;

        struct edge {
            double distance;
            node *start, *end;
        };

        struct node {
            string name;
            double dist; // used by Dijkstra's 
            node* pred; // ^
            vector<edge*> outgoing;
        };

        struct set_comp {
            bool operator()(const node *n1, const node *n2) {
                return n1->name < n2->name;
            }
        };

        ~Graph() {
            clear();
        }

        void addNode(string nodeName) {
            node *newNode = new node;
            newNode->name = nodeName;
            nodes.insert(newNode);
        }

        node *getNodeWithName(const string &name) {
            node *searchNode = new node;
            searchNode->name = name;
            set<node*>::iterator itr = nodes.find(searchNode);
            delete searchNode;
            if (itr == nodes.end()) {
                return nullptr;
            }
            else {
                return *itr;
            }
        }

        // pre-condition: user has not created an edge from node with name=edgeStart to node with name=edgeEnd before this
        void addEdge(string edgeStart, string edgeEnd, double edgeDist) {
            node* start = getNodeWithName(edgeStart);
            node* end = getNodeWithName(edgeEnd);
            if (start == nullptr || end == nullptr) {
                return;
            }

            edge *newEdge = new edge;
            newEdge->start = start;
            newEdge->end = end;
            newEdge->distance = edgeDist;
            start->outgoing.push_back(newEdge);
        }

        void print() {
            for (node *node : nodes) {
                cout << node->name << ": "; 
                for (edge *adj : node->outgoing) {
                    cout << adj->end->name << " (" << adj->distance << ") ";
                }
                cout << '\n';
            }
            cout << endl;
        }

        void clear() {
            for (node *node : nodes) {
                for (edge *adj : node->outgoing) {
                    delete adj;
                }
                delete node;
            }
            nodes.clear();
        }

        const set<node*, set_comp>& getNodes() const {
            return nodes;
        }

    private:
        set<node*, set_comp> nodes;
};

bool readGraphDataFile(Graph &g, string filepath);
void printShortestPath(Graph &g, const string &start, const string &end);
void printMST(Graph &g);

int main() {
    string defaultDataFilepath = "programming_assignments/pa7/extra.txt";
    Graph g;
    if (!readGraphDataFile(g, defaultDataFilepath.c_str())) {
        cerr << "error reading data file";
        return 1;
    }
    // g.print();

    while (true) {
        cout << "Your options are:\n\t(1) Choose a new graph data file\n\t(2) Find shortest path\n\t(3) Compute the minimum spanning tree\n\t(Other) Quit\nEnter choice:";
        int choice;
        cin >> choice;
        cin.ignore(); // move stream to end of line 
        if (cin.fail()) {
            cerr << "invalid choice.";
            return 1;
        }
        if (choice == 1) {
            cout << "New graph data file: ";
            string newFilepath; 
            getline(cin, newFilepath);
            g.clear();
            if (!readGraphDataFile(g, newFilepath)) {
                cerr << "Error reading data file.";
                return 1;
            }
            // g.print();
        }
        else if (choice == 2) {
            string start, end;
            cout << "Enter the starting node: ";
            getline(cin, start);
            cout << "Enter the ending node: ";
            getline(cin, end);
            printShortestPath(g, start, end);
        }
        else if (choice == 3) {
            printMST(g);
        }
        else {
            break;
        }
    }

    return 0;
}

bool readGraphDataFile(Graph &g, string filepath) {
    ifstream f; 
    f.open(filepath.c_str());
    if (f.fail()) {
        return false;
    }
    string line;
    getline(f, line);
    if (f.fail() || line != "NODES") {
        return false;
    }
    while (getline(f, line) && line != "ARCS") {
        g.addNode(line);
    }
    if (f.fail()) {
        return false;
    }
    int i = 0;
    string start, end;
    double dist; 
    while (!f.fail()) {
        if (i % 3 == 0) {
            f >> start;
        }
        else if (i % 3 == 1) {
            f >> end;
        }
        else {
            f >> dist;
            g.addEdge(start, end, dist);
        }
        i++;
    }
    if (!f.eof()) {
        return false;
    }
    f.close();
    return true;
}

int node_pq_comp(Graph::node *(&n1), Graph::node *(&n2)) {
    if (n1->dist > n2->dist) {
        return -1;
    }
    else if (n1->dist < n2->dist) {
        return 1;
    }
    return 0;
}

/* Dijkstra's Shortest Path Algorithm 
Runtime: O(EV) where E = no. of edges and V = no. of nodes/vertices. Algorithm could be improved if Priority Queue's 
increaseEntry() was not O(V).

Part 1: Prepare the necessary data structures
Find start and end node 
Initialize max pq with backwards comparison callback func. so it functions as min pq 
Initialize set to hold nodes that have been visited (set can use pointer comparison (*) for this - not like set in Graph class)
For each node in the Graph
    set the predecessor to NULL 
    if its not the start, set its distance to infinity
    If its the start, set its distance to 0
    add it to the pq

Part 2: Find the shortest path from the start node to every other node in the graph
while the pq isn't empty 
    get the minimum and put into the visited node set 
    dequeue from the pq 
    for each of its outgoing edges
        relax the edge. Let w = the edge's distance and v = the end of the edge (i.e. a node adjacent to min)
        if v.dist > w + min.dist then 
            v.dist = w + min.dist
            update the pq with this change by calling increaseEntry (which now works as decreaseEntry b/c of opposite comparison fn. mentioned earlier)

Part 3: Print the shortest path from start to end nodes
If the end node's distance field was not changed from infinity, then it could not be reached from the start node. 
Otherwise, initialize a stack to hold the names of the nodes on the path and a node (curr) to point to the end node 
while curr != NULL do
    push curr's name onto the stack
    curr = curr->pred
Then pop and print the elements from the stack which will now display the path start to end
At the end, one could also add the path's total distance which is end->dist. This comes from the relaxation process in the
algorithm.

Note (*): while it is possible for 2 pointers who are unequal in value to point to the same data, Graph protects against this
by allowing nodes to be added through their name, so nodes with the same name won't be duplicated. Thus, if this function
uses g.getNodes(), it won't get 2 different pointers pointing to the same data who could then potentially be added to the pq.
*/
void printShortestPath(Graph &g, const string &start, const string &end) {
    Graph::node *startNode = g.getNodeWithName(start);
    Graph::node *endNode = g.getNodeWithName(end);
    if (startNode == nullptr || endNode == nullptr) {
        cout << "Provided nodes could not be found in the graph.\n";
    }

    HeapMaxPriorityQueue<Graph::node*> q(node_pq_comp);
    set<Graph::node*> visited;
    for (Graph::node *n : g.getNodes()) {
        if (n != startNode) {
            n->dist = numeric_limits<double>::infinity();
        }
        else { // can't update start afterwords because there's no "update-key" functionality in cpp std. pq
            n->dist = 0;
        }
        n->pred = nullptr;        
        q.enqueue(n);
    }
    
    while (!q.empty()) {
        Graph::node *min = q.front();
        q.dequeue();
        visited.insert(min);
        for (Graph::edge *out : min->outgoing) {
            // Relax 
            if (visited.find(out->end) == visited.end() && min->dist + out->distance < out->end->dist) {
                out->end->dist = min->dist + out->distance; // updates what pointer points to, but doesn't automatically change q
                out->end->pred = min;
                q.increaseEntry(out->end, out->end); // force changes to q by making it check out->end's position
            }
        }
    }

    if (endNode->dist == numeric_limits<double>::infinity()) {
        cout << "A path from " << start << " to " << end << " could not be found.\n";
    }
    else {
        cout << "Shortest Path: ";
        stack<string> path;
        Graph::node *curr = endNode;
        while (curr != nullptr) {
            path.push(curr->name);
            curr = curr->pred;
        }
        while (!path.empty()) {
            cout << path.top() << ' ';
            path.pop();
        }
        cout << '(' << endNode->dist << " mi)\n" << endl;
    }
}

int edge_pq_comp(Graph::edge *&e1, Graph::edge *&e2) {
    if (e1->distance > e2->distance) {
        return -1;
    }
    else if (e1->distance < e2->distance) {
        return 1;
    }
    return 0;
}

/*
Kruskal's Minimum Spanning Tree Algorithm: 
Runtime: O(EV) where E = no. of edges and V = no. of vertices/nodes. Suffers due to the fact that the vector must be searched
linearly to find the set that contains the ends of an edge. 

Part 1: Prepare the necessary data structures
Initialize a max pq for the Graph's edges using a backwards comparison function (see above) so that the pq functions as a min pq
Initialize a vector of sets of nodes who use regular pointer value comparison (*). This will represent the progress of the MST's
construction. THat is, it will start with N sets with 1 element each where N = no. of nodes in G. As parts of the MST are 
assembled, the vector's size will shrink and the sets will grow as more nodes are connected. The vector should end with size 0
if all the nodes can be connected into 1 MST. If they cannot, a MST or any spanning tree cannot be made as the graph isn't 
connected.
For each node in the graph
    initialize a set S
    add this node to S
    put S into the vector of sets 
    for each outgoing edge of this node
        enqueue it into the pq (**)

Part 2: Build the MST and print while it's being built
while the pq isn't empty do
    get the minimum edge of the pq
    dequeue the pq 
    find the sets that the starting and ending node of the minimum edge belong to
    if they aren't the same, union the end's set into the start's set and erase the old ending set (note: this just erases a set
    of pointers, the data they point to should not be deleted), and print the edge's start and end to inform the user that a new
    edge has been found that will be part of the MST (if all the sets end up unioned into 1)
        by performing this union, one has connected 2 parts of the mst 
        the erasing makes sure that one node cannot somehow be in 2 sets
    

After this loop completes, I added a check to make sure that the size of vector of sets really did reach 1. If it did not,
the graph wasn't connected so I inform the user that the list of printed edges are not actually connected b/c a valid MST 
could not be formed.

Note (*): by using g.getNodes() like printShortestPath(), this function will avoid getting 2 different pointers to the same data.
More on this explained in the printShortestPath() method comment. 
Note (**): this assumes that there aren't duplicates of the same edge, this is possible since g.addEdge() has no duplicate
edge protection (just a pre-condition). However, since this program is allowed to assume a valid graph data file, this issue
can be ignored.
*/
void printMST(Graph &g) {
    HeapMaxPriorityQueue<Graph::edge*> q(edge_pq_comp);
    vector<set<Graph::node*>> connectedSets;

    for (Graph::node *node : g.getNodes()) {
        set<Graph::node*> connected;
        connected.insert(node);
        connectedSets.push_back(connected);
        for (Graph::edge *edge : node->outgoing) {
            q.enqueue(edge);
        }
    }

    while (!q.empty()) {
        Graph::edge *curr = q.front();
        q.dequeue();
        size_t startSetIdx, endSetIdx;
        for (size_t i = 0; i < connectedSets.size(); i++) {
            if (connectedSets[i].find(curr->start) != connectedSets[i].end()) {
                startSetIdx = i;
            }
            if (connectedSets[i].find(curr->end) != connectedSets[i].end()) {
                endSetIdx = i;
            }
        }
        if (startSetIdx != endSetIdx) {
            connectedSets[startSetIdx].insert(connectedSets[endSetIdx].begin(), connectedSets[endSetIdx].end());
            connectedSets.erase(connectedSets.begin() + endSetIdx);
            cout << curr->start->name << "->" << curr->end->name << '\n';
        }
    }

    if (connectedSets.size() != 1) {
        cout << "Some parts of the graph could not be reached. The edges that have been printed aren't all be part of the same tree.\n";
    }
    cout << endl;
}