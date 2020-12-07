#include "landmark.h"
#include <queue>
#include <map>

Landmark::Landmark() : tree_(true, false) {
    //nothing 
}

std::map<Vertex, Vertex> Landmark::spanning(const Graph & graph, Vertex v){
    
    std::queue<Vertex> q;
    tree_ = graph;

    std::map<Vertex, bool> visited;
    std::map<Vertex, Vertex> predecessor;
    for(Vertex u : tree_.getVertices()){
        visited[u] = false;
        predecessor[u] = "0";
    }

    visited[v] = true;
    q.push(v);

    while(!q.empty()){
        Vertex w = q.front();
        q.pop();
        for(Vertex y : tree_.getAdjacent(w)){
            if (visited[y] == false){
                visited[y] = true;
                predecessor[y] = w;
            }
        }
    }

    return predecessor;
}
