#include "graph.h"
#include <fstream>
#include <sstream>

Graph::Graph(const char* fname) {
    std::ifstream file(fname);
    if (!file.is_open()) return;

    std::string line;
    std::getline(file, line); // заголовок

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::string a, b;
        std::istringstream iss(line);
        iss >> a >> b;

        Node* u = findNode(a);
        if (!u) {
            u = new Node(a);
            addNode(u);
        }

        Node* v = findNode(b);
        if (!v) {
            v = new Node(b);
            addNode(v);
        }

        addEdge(u, v);
    }
}

Graph::~Graph() {
    // узлы не удаляем, чтобы избежать двойного удаления при копировании
    nodes.clear();
}

Node* Graph::findNode(const std::string& name) const {
    for (Node* n : nodes) {
        if (n->getName() == name) return n;
    }
    return nullptr;
}

void Graph::addEdge(Node* a, Node* b) {
    if (nodes.find(a) == nodes.end() || nodes.find(b) == nodes.end()) return;
    a->addNeigh(b);
    b->addNeigh(a);
}

void Graph::delNode(Node* n) {
    nodes.erase(n);
    for (Node* other : nodes) {
        other->remNeigh(n);
    }
    delete n;
}