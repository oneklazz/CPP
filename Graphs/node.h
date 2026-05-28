#pragma once
#include <set>
#include <string>

class Node {
private:
    std::string name; // имя вершины
    std::set<Node*> neigh; // соседи

    void addNeigh(Node* n) { neigh.insert(n); }
    void remNeigh(Node* n) { neigh.erase(n); }

public:
    Node(const std::string& n) : name(n) {}

    const std::string& getName() const { return name; }

    using iter = std::set<Node*>::const_iterator;
    iter begin() const { return neigh.begin(); }
    iter end() const { return neigh.end(); }

    friend class Graph;
    friend class BFS;
};