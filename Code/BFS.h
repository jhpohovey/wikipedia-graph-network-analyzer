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
        const Graph& traverse(const Graph &g);
        const Graph& getGraph();
        

    private: 
        Graph g_;
        std::map<Vertex, bool> beenVisited_;   
        void BFShelper(const Graph &g, const Vertex &v);
};