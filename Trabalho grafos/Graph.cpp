#include "Graph.h"

#include <tuple>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <iostream>

#ifndef INF
#define INF 0x3F3F3F3F
#endif

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

void depth(int vertex, int v, std::list<std::pair<int, int> > *adj, std::list<std::pair<int, int> > &e, int *num, int i)
{
    //anota a profundidade, iniciando em 1
    num[v] = i++;

    //para a busca se achar
    if(v == vertex) return;

    //percorre os 
    for(auto u : adj[v]){
        int next = u.first;
        if(num[next]){
            e.push_back({v, next});
            depth(vertex, next, adj, e, num, i);
        }
    }
}

void Graph::dfs(int vertex)
{
    //previne que o vertice procurado esteja fora do vetor
    if(vertex < 0 || vertex > vertices.size()+1){
        std::cout << "Vértice de número fora do tamanho do vetor de vértices";
        return;
    }

    //inicia o vetor
    std::list<std::pair<int, int> > *adj = new std::list<std::pair<int, int> >[vertices.size()+1];

    //preenche a lista
    for(int i = 0; i < edges.size(); i++){
        adj[std::get<0>(edges[i])].push_back( {std::get<1>(edges[i]), std::get<2>(edges[i])} );
        if(bidirectional){
            adj[std::get<1>(edges[i])].push_back( {std::get<0>(edges[i]), std::get<2>(edges[i])} );
        }
    }

    //incia a lista do caminho encontrado
    std::list<std::pair<int, int> > path;
    int *num = new int[vertices.size()+1];

    for(int i = 0; i <= vertices.size(); i++){
        num[i] = 0;
    }

    //faz a busca
    for(auto v : vertices){
        if(num[v] == 0){
            path.clear();
            int i = 1;
            depth(vertex, v, adj, path, num, i);
            if(num[vertex] != 0) break;
        }
    }

    //impressão do caminho
    if(num[vertex] != 1){
        std::cout << "Econtrado com caminho:\n";
        for(std::list<std::pair<int, int> >::iterator it = path.begin(); it != path.end(); it++){
            std::cout << it->first << " -> " << it->second << " ";
        }
    }
    else{
        std::cout << "Econtrado na primeira posição";
    }

    delete [] num;

    //deleta o vetor
    delete [] adj;
}

void Graph::djikstra(int start, int end)
{
    //algoritmo um pouco diferente do pseudocódigo aprendido porque foi o ensinado na disciplina de maratona de programação

    //inicia o vetor
    std::list<std::pair<int, int> > *adj = new std::list<std::pair<int, int> >[vertices.size()+1];

    //preenche a lista
    for(int i = 0; i < edges.size(); i++){
        adj[std::get<0>(edges[i])].push_back( {std::get<1>(edges[i]), std::get<2>(edges[i])} );
        if(bidirectional){
            adj[std::get<1>(edges[i])].push_back( {std::get<0>(edges[i]), std::get<2>(edges[i])} );
        }
    }

    //djikstra
    std::vector<int> dist(vertices.size()+1, INF);
    std::vector<int> pred(vertices.size()+1, -1);
    std::vector<bool> visited(vertices.size()+1, false);

    std::priority_queue<std::pair<int, int> > q;

    dist[start] = 0;
    q.push({0, start});

    while(!q.empty()){
        int a = q.top().second;
        q.pop();

        if(visited[a]) continue;
        visited[a] = true;
        if(a == end) break;

        for(auto u : adj[a]){
            int b = u.first;
            int w = u.second;

            if(dist[a]+w < dist[b]){
                dist[b] = dist[a]+w;
                pred[b] = a;
                q.push({-dist[b], b});
            }
        }
    }

    //impressão
    std::cout << "Caminho de " << start << " a "<< end << ":\n";

    if(!visited[end]){
        std::cout << "Não encontrado :(";
    }

    std::cout << start;

    std::stack<int> path;
    path.push(end);
    int a = end;
    while(pred[a] != start){
        path.push(pred[a]);
        a = pred[a];
    }

    while(!path.empty()){
        std::cout << " -> " << path.top();
        path.pop();
    }
}