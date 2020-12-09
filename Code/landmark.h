#pragma once

#include <string>
#include "edge.h"
#include "graph.h"
#include "dsets.h"
#include <vector>
#include <map>
#include <algorithm>
#include "file_bot.hpp"

typedef std::string Vertex;

class Landmark {
    public:
        Landmark(const Graph & graph, Vertex landmark);
        void get_span(const Graph & graph, Vertex landmark);
        void store_path(Vertex begin, Vertex landmark, Vertex end);
        //void printPath; 


    private:
        //Graph tree_;
        std::map<Vertex, Vertex> pred;
        //std::vector<Vertex> path_;

};