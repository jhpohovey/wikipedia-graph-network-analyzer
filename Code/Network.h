
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
        //std::string reader(const std::string & filename);
        //std::vector<Vertex> createSingleLineVertexList(const std::string & filename);
        Graph& constructGraph();
        const Graph& getGraph();
        std::map<Vertex, Vertex> get_span(Vertex landmark);
        std::vector<Vertex> store_path(std::map<Vertex, Vertex> & predecessor, Vertex begin, Vertex landmark, Vertex end);

    private:
        Graph g_;
        Vertex startPoint;
        const int weight = 1;
        void buildGraphSection(std::vector<Vertex>); //constructGraoh helper functions

        //each element in outer vector represents each line of the .txt file
        //each element j at every vector[i] represents the individual links from one line
        std::vector<std::vector<std::string>> data_;

};
