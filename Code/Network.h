
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

    private:
        Graph g_;
        Vertex startPoint;

};
