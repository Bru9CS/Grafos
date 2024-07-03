#ifndef GRAPH_H
#define GRAPH_H

#include <tuple>
#include <vector>
#include <algorithm>

class Graph{
    private:
        std::vector<int> vertices;
        std::vector< std::tuple<int, int, int> > edges;
        bool bidirectional;
    public:
        Graph(std::vector<int> v, std::vector<std::tuple<int, int, int> > e, bool bi = true);

        void printMatrix();
        void printList();
};

#endif