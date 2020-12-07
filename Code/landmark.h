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
        Landmark();
        std::map<Vertex, Vertex> spanning(const Graph & graph, Vertex v);

    private:
        Graph tree_;

};
