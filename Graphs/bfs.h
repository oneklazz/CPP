#pragma once
#include "graph.h"
#include <vector>
#include <string>

class BFS {
private:
    const Graph& g;

    // поиск одной компоненты от стартовой вершины
    Graph getComponent(Node* start, std::set<Node*>& unvisited);

public:
    BFS(const Graph& graph) : g(graph) {}

    // найти все компоненты связности
    std::vector<Graph> findAllComponents();

    // сохранить компоненты в файлы
    void saveComponents(const std::vector<Graph>& comps, const std::string& outPrefix);
};