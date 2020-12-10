
#pragma once
#include <string>
#include "edge.h"
#include "graph.h"
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include "file_bot.hpp"

typedef std::string Vertex;

class NetworkBuilder {
    public:
        NetworkBuilder();
        NetworkBuilder(const std::string & filename);
        Graph& constructGraph();
        const Graph& getGraph() const;
        const std::unordered_map<Vertex, double>& getFreqTable() const;

    private:
        Graph g_;
        Vertex startPoint;
        void buildGraphSection(std::vector<Vertex>); //constructGraoh helper functions

        //each element in outer vector represents each line of the .txt file
        //each element j at every vector[i] represents the individual links from one line
        std::vector<std::vector<std::string>> data_;
        std::unordered_map<Vertex, double> vertexFreqTable;

};
