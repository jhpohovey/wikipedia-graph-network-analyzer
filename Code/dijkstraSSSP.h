/**
 * @file dijkstraSSSP.cpp
 * @author John Pohovey
 * @brief Implementation of Dijkstra's Single Source Shortest Path Algorithm,
 *        which given a starting vertex, returns the shortest path to reach any
 *        other vertex destination present in the graph with support for fetching
 *        shortest path to a given destination, a cost to reach the destination.
 * @version 0.1
 * 
 * @copyright Copyright (c) 2020
 * 
 */


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
        //implementations notes on function, parameters, returns, etc are all located in the .cpp file

        DijkstraSSSP(const Graph& G, Vertex u);
        const Graph& calculateShortestPaths();
        
        std::vector<Vertex> pathToDestination (Vertex dest);
        int calculateCostToVertex(const Vertex& v) const;
        bool checkConnectivity(const Vertex& v) const;

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