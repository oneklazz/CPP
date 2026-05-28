#include "bfs.h"
#include <queue>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <sys/stat.h>

void makeDir(const char* path) {
    mkdir(path, 0777);
}

// поиск одной компоненты связности
Graph BFS::getComponent(Node* start, std::set<Node*>& unvisited) {
    Graph comp;
    std::queue<Node*> q;
    std::unordered_map<Node*, Node*> old2new; // // связь старых узлов с новымии

    q.push(start);
    unvisited.erase(start); // удаляем из непосещенных

    Node* newStart = new Node(start->getName());
    comp.addNode(newStart);
    old2new[start] = newStart;

    while (!q.empty()) {
        Node* cur = q.front();
        q.pop();

        Node* newCur = old2new[cur];

        // обход всех соседей
        for (Node* nb : *cur) {
            // если сосед ещё не скопирован
            if (old2new.find(nb) == old2new.end()) {
                Node* newNb = new Node(nb->getName());
                comp.addNode(newNb);
                old2new[nb] = newNb;

                // если сосед ещё не посещён в bfs
                if (unvisited.find(nb) != unvisited.end()) {
                    unvisited.erase(nb);
                    q.push(nb);
                }
            }

            // добавляем ребро только один раз u < v
            if (cur->getName() < nb->getName()) {
                comp.addEdge(newCur, old2new[nb]);
            }
        }
    }

    return comp;
}

// поиск всех компонент связности графа
std::vector<Graph> BFS::findAllComponents() {
    std::vector<Graph> comps;
    std::set<Node*> unvisited;

    // все вершины сначала непосещённые и пока есть непосещённые вершины
    for (Node* n : g) {
        unvisited.insert(n);
    }

    while (!unvisited.empty()) {
        Node* start = *unvisited.begin();
        Graph comp = getComponent(start, unvisited);
        comps.push_back(comp);
    }

    return comps;
}

// сохр компонент в папку
void BFS::saveComponents(const std::vector<Graph>& comps, const std::string& outPrefix) {
    makeDir("results");

    int idx = 1;
    for (const Graph& comp : comps) {
        std::string fname = "results/" + outPrefix + "_" + std::to_string(idx++) + ".txt";
        std::ofstream file(fname);

        if (!file.is_open()) {
            std::cerr << "ошибка: не удалось создать " << fname << std::endl;
            continue;
        }

        file << "source\t target\n";

        for (Node* u : comp) {
            for (Node* v : *u) {
                if (u->getName() < v->getName()) {
                    file << u->getName() << "\t" << v->getName() << std::endl;
                }
            }
        }
    }
}