#pragma once
#include "node.h"
#include <set>
#include <string>

class Graph {
private:
    std::set<Node*> nodes; // все вершины
    Node* findNode(const std::string& name) const;

public:
    Graph() = default;
    Graph(const char* fname); // конструктор из файла
    ~Graph();

    void addNode(Node* n) { nodes.insert(n); }
    void addEdge(Node* a, Node* b);
    void delNode(Node* n);

    using iter = std::set<Node*>::const_iterator;
    iter begin() const { return nodes.begin(); }
    iter end() const { return nodes.end(); }

    friend class BFS;
};