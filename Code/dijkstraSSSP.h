#pragma once

#include "graph.h"
#include "Network.h"
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <queue>
#include <unordered_map>
#include "priorityqueue.h"

class DijkstraSSSP {
    public:
        DijkstraSSSP(const Graph& G, Vertex u);
        Graph findSP(const Graph& G);
    private:
        PriorityQueue Q;
        Vertex start;
        Graph g;
        std::unordered_map<Vertex, int> dist;
        std::unordered_map<Vertex, Vertex> pred;

};