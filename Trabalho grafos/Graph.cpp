#include "Graph.h"

#include <tuple>
#include <vector>
#include <list>
#include <iostream>

Graph::Graph(std::vector<int> v, std::vector<std::tuple<int, int, int> > e, bool bi) : bidirectional(bi)
{
    //copia os vértices e os organiza
    vertices = v;
    std::sort(vertices.begin(), vertices.end());

    //copia as arestas
    edges = e;
    std::sort(edges.begin(), edges.end());
}

void Graph::printMatrix()
{
    //cria a matriz
    int **matrix = new int*[vertices.size()];
    for(int i = 0; i < vertices.size(); i++){
        matrix[i] = new int[vertices.size()];
    }

    //incializa com 0
    for(int i = 0; i < vertices.size(); i++){
        for(int j = 0; j < vertices.size(); j++){
            matrix[i][j] = 0;
        }
    }

    //dá valores à matriz
    for(int i = 0; i < vertices.size(); i++){
        for(int j = 0; j < vertices.size(); j++){
            for(int k = 0; k < edges.size(); k++){
                if(i+1 == std::get<0>(edges[k]) && j+1 == std::get<1>(edges[k])){
                    matrix[i][j] = std::get<2>(edges[k]);
                    
                    if(bidirectional){
                        matrix[j][i] = std::get<2>(edges[k]);
                    }
                    
                    break;
                }
            }
        }
    }

    //imprime a matriz
    std::cout << "Matriz de adjacências:\n ";
    for(int i = 0; i < vertices.size(); i++){
        std::cout << " " << vertices[i];
    }
    for(int i = 0; i < vertices.size(); i++){
        std::cout << std::endl << vertices[i];
        for(int j = 0; j < vertices.size(); j++){
            std::cout << " " << matrix[i][j];
        }
    }

    //deleta a matriz
    for (int i = 0; i < vertices.size(); i++){
        delete [] matrix[i];
    }
    delete [] matrix;
}

void Graph::printList()
{
    //inicia o vetor
    std::list<std::pair<int, int> > *adj = new std::list<std::pair<int, int> >[vertices.size()+1];

    //preenche a lista
    for(int i = 0; i < edges.size(); i++){
        adj[std::get<0>(edges[i])].push_back( {std::get<1>(edges[i]), std::get<2>(edges[i])} );
        if(bidirectional){
            adj[std::get<1>(edges[i])].push_back( {std::get<0>(edges[i]), std::get<2>(edges[i])} );
        }
    }

    //imprime a lista
    std::cout << "Lista de adjacências:";
    for(int i = 1; i <= vertices.size(); i++){
        std::cout << std::endl << i << ": ";
        for(std::list<std::pair<int, int> >::iterator it = adj[i].begin(); it != adj[i].end(); it++){
            std::cout << "(" << it->first << ", " << it->second << ")";
        }
    }

    //deleta o vetor
    delete [] adj;
}