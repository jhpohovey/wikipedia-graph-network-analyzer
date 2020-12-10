#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <queue>
#include "graph.h"
#include "edge.h"
#include <map>

class BFS {
    public: 
        BFS();
        Graph BFScomplete(const Graph &g);
        void BFShelper(const Graph &g, const Vertex &v);
        Graph getGraphBFS(Graph );
        Graph g_;

    private: 
        std::map<Vertex, bool> beenVisited_;   
};