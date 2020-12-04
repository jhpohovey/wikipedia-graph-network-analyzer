
#pragma once
#include <string>
#include "edge.h"
#include "graph.h"
#include <vector>
#include <algorithm>
#include "file_bot.hpp"

typedef std::string Vertex;

class NetworkBuilder {
    public:
        NetworkBuilder();
        NetworkBuilder(const std::string & filename);
        //std::string reader(const std::string & filename);
        //std::vector<Vertex> createSingleLineVertexList(const std::string & filename);
        void NetworkBuilder::buildGraphSection(std::vector<Vertex>);
        Graph constructGraph(const std::string & filename);

    private:
        Graph g_;
        Vertex startPoint;
        const int weight = 1;

        //each element in outer vector represents each line of the .txt file
        //each element j at every vector[i] represents the individual links from one line
        std::vector<std::vector<std::string>> data_;

};
