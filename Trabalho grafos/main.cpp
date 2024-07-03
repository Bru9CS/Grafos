#include "Graph.h"

#include <tuple>
#include <vector>
#include <iostream>

using namespace std;

int main(){
    vector<int> vertices = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<tuple<int, int, int> > arestas = {{1, 2, 5}, {1, 3, 8}, {1, 4, 3},
                                        {2, 3, 6}, {2, 5, 9}, {3, 4, 2},
                                        {3, 6, 7}, {4, 7, 4}, {5, 6, 1},
                                        {5, 8, 5}, {6, 9, 3}, {7, 8, 2},
                                        {7, 10, 6}, {8, 9, 4}, {9, 10, 7}};

    Graph teste(vertices, arestas);

    teste.printMatrix();
    cout << "\n\n";
    teste.printList();

    return 0;
}