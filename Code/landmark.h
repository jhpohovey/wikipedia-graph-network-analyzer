#pragma once

#include <string>
#include "edge.h"
#include "graph.h"
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "file_bot.hpp"

typedef std::string Vertex;

class Landmark {
    public:
        Landmark(const Graph & graph, Vertex landmark);
        void get_span(const Graph & graph, Vertex landmark);
        void store_path(Vertex begin, Vertex landmark, Vertex end);
        std::unordered_map<Vertex, Vertex> getPred();
        std::vector<Vertex> getPath();
        void printPath(); 
        int getLength();


    private:
        std::unordered_map<Vertex, Vertex> pred;
        std::vector<Vertex> path_;
        Vertex landmark_;

};