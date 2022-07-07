#include <set>
#include <fstream>
#include <string>
#include <map>
#include <iostream>
#include <stack>
#include <queue>
#include "C:\Users\Chami\Stanford_Cpp_Class\organized_materials_and_my_code\programming_assignments\pa6\priority_queue.cpp"
#include "C:\Users\Chami\Stanford_Cpp_Class\organized_materials_and_my_code\programming_assignments\pa6\priority_queue.h"
using namespace std;

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

void constructGraph(graphT &graph, set<string> &lexicon, map<string, nodeT*> &nodeNames);
void runOptionShortestLadder(graphT &graph, map<string, nodeT*> &nodeNames);
void findShortestLadder(graphT &graph, nodeT *start, nodeT *end, stack<nodeT*> &out);
void runOptionLongestLadder(graphT &graph, map<string, nodeT*> &nodeNames);
void findLongestLadder(graphT &graph, nodeT *node, stack<nodeT*> &out, stack<nodeT*> &curr, set<nodeT*> &visited);
void deallocateGraph(graphT &graph);
void printGraph(graphT &graph);

int main() {
    set<string> lex;
    ifstream f("section_problem_sets/section_handout_9/words_small.txt");
    string s;
    while (f >> s) {
        if (s.length() == 5) {
            for (string::iterator i = s.begin(); i != s.end(); i++) {
                *i = tolower(*i);
            }
            lex.insert(s);
        }
    }
    f.close();
    graphT g;
    map<string, nodeT*> nodeNames;
    constructGraph(g, lex, nodeNames);
    // printGraph(g);
    while (true) {
        cout << "Choices: \n(1) Shortest Path Between 2 words. \n(2) Longest Path from a word.\n(Other) Exit.\n";
        string choice;
        getline(cin, choice);
        if (choice=="1") {
            runOptionShortestLadder(g, nodeNames);
        }
        else if (choice=="2") {
            runOptionLongestLadder(g, nodeNames);
        }
        else {
            break;
        }
        cout << endl;
    }
    deallocateGraph(g);
    return 0;
}

void constructGraph(graphT &graph, set<string> &lexicon, map<string, nodeT*> &nodeNames) {
    char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    for (string word : lexicon) {
        nodeT *newNode = new nodeT;
        newNode->name = word;
        graph.nodes.insert(newNode);
        nodeNames[word] = newNode;
    }

    for (string word : lexicon) {
        for (size_t i = 0; i < word.length(); i++) {
            for (char letter : alphabet) {
                if (letter == word[i]) { // don't try permutation with letter = word[i] b/c we know word with this letter at word[i] is in the lexicon
                    continue;
                }
                string repl = word.substr(0, i) + letter + word.substr(i + 1);
                if (lexicon.find(repl) != lexicon.end()) {
                    edgeT *edge = new edgeT;
                    edge->start = nodeNames[word];
                    edge->end = nodeNames[repl];
                    nodeNames[word]->connected.insert(edge);
                }
            }
        }
    }    
}

void runOptionShortestLadder(graphT &graph, map<string, nodeT*> &nodeNames) {
    string start;
    cout << "Enter start word: ";
    getline(cin, start);
    string end;
    cout << "Enter end word: ";
    getline(cin, end);
    stack<nodeT*> out;
    findShortestLadder(graph, nodeNames.at(start), nodeNames.at(end), out);
    cout << "Shortest Word Ladder between " << start << " and " << end << ": ";
    if (out.empty()) {
        cout << "Does not exist.";
    }
    else {
        while (!out.empty()) {
            cout << out.top()->name << ' ';
            out.pop();
        }
    }
}

void runOptionLongestLadder(graphT &graph, map<string, nodeT*> &nodeNames) {
    string start;
    cout << "Enter start word: ";
    getline(cin, start);
    stack<nodeT*> out;
    set<nodeT*> visited;
    stack<nodeT*> curr;
    findLongestLadder(graph, nodeNames.at(start), out, curr, visited);
    cout << "\nLongest Word Ladder (Backwards) starting at " << start << " (" << out.size() << " words): ";
    while (!out.empty()) {
        cout << out.top()->name << ' ';
        out.pop();
    }
}

void findShortestLadder(graphT &graph, nodeT *start, nodeT *end, stack<nodeT*> &out) {
    map<nodeT*, nodeT*> predMap;
    predMap[start] = nullptr;

    queue<nodeT*> q;
    q.push(start);
    nodeT* curr;
    while (!q.empty()) {
        curr = q.front();
        q.pop();
        if (curr == end) {
            break;
        }
        for (edgeT *outgoing : curr->connected) {
            if (predMap.find(outgoing->end) == predMap.end()) {
                predMap[outgoing->end] = curr;
                q.push(outgoing->end);
            }
        }
    }

    if (curr != end) {
        return;
    }

    while (curr != nullptr) {
        out.push(curr);
        curr = predMap[curr];
    }
}

// took from soln. manual: dfs-based backtracking (straight BFS/DFS doesn't work). Apparently soln. has the ladder printed backwards?
void findLongestLadder(graphT &graph, nodeT *node, stack<nodeT*> &out, stack<nodeT*> &curr, set<nodeT*> &visited) {
    visited.insert(node);
    curr.push(node);

    if (curr.size() > out.size()) {
        out = curr;
    }
    for (edgeT *edge : node->connected) {
        if (visited.find(edge->end) == visited.end()) {
            findLongestLadder(graph, edge->end, out, curr, visited);
        }
    }

    visited.erase(node);
    curr.pop();
}

void deallocateGraph(graphT &graph) {
    for (nodeT *node : graph.nodes) {
        for (edgeT *edge : node->connected) {
            delete edge;
        }
        delete node;
    }
}

void printGraph(graphT &graph) {
    for (nodeT *node : graph.nodes) {
        cout << node->name << ": ";
        for (edgeT *edge : node->connected) {
            cout << edge->end->name << ' ';
        }
        cout << '\n';
    }
    cout << endl;
}