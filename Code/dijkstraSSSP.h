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
        const Graph& findSP(const Graph& G);
        std::unordered_map<Vertex, int> getDists() const;
        std::unordered_map<Vertex, Vertex> getPreds() const;
        Vertex getStart() const;
    private:
        PriorityQueue Q;
        Vertex start;
        Graph g;
        Graph T;
        std::unordered_map<Vertex, int> dist;
        std::unordered_map<Vertex, Vertex> pred;

};