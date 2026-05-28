#include "bfs.h"
#include <iostream>

int main() {
    try {
        // textgraph.txt
        Graph g1("data/testgraph.txt");
        BFS bfs1(g1);
        auto comps1 = bfs1.findAllComponents();
        bfs1.saveComponents(comps1, "testgraph_component");

        // 1000.csv
        Graph g2("data/1000.csv");
        BFS bfs2(g2);
        auto comps2 = bfs2.findAllComponents();
        bfs2.saveComponents(comps2, "graph1000_component");

        std::cout << "готово!" << std::endl;
        std::cout << "testgraph: " << comps1.size() << " компонент" << std::endl;
        std::cout << "1000.csv: " << comps2.size() << " компонент" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}