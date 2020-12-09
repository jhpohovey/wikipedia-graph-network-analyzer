#include "../cs225/catch/catch.hpp"

#include <string>
#include "../edge.h"
#include "../graph.h"
#include <vector>
#include <algorithm>
#include <map>
#include "../file_bot.hpp"
#include "../Network.h"
#include "../random.h"
#include "../landmark.h"

TEST_CASE("Scanning SingleLine.txt forwards creates the right predecessors/", "[part=landmark]") {
    NetworkBuilder nb ("tests/SingleLine.txt");
    nb.constructGraph();

    const Graph& g = nb.getGraph();

    Landmark span(g, "14th_century");
    std::map<Vertex, Vertex> result = span.getPred();

    std::vector<Vertex> ansLine = {"14th_century", "15th_century", "16th_century", "Pacific_Ocean", "Atlantic_Ocean", "Accra", "Africa", "Atlantic_slave_trade", "African_slave_trade"};
    for (size_t i = 0; i < ansLine.size(); i ++){
        if (i == 0){
            REQUIRE(result.at(ansLine[i]) == "Starting");
            continue;
        }
        REQUIRE(result.at(ansLine[i]) == ansLine[i-1]);
    }
}

TEST_CASE("Scanning SingleLine.txt backwards creates the right predecessors/", "[part=landmark]") {
    NetworkBuilder nb ("tests/SingleLine.txt");
    nb.constructGraph();

    const Graph& g = nb.getGraph();

    Landmark span(g, "African_slave_trade");
    std::map<Vertex, Vertex> result = span.getPred();

    std::vector<Vertex> ansLine = {"14th_century", "15th_century", "16th_century", "Pacific_Ocean", "Atlantic_Ocean", "Accra", "Africa", "Atlantic_slave_trade", "African_slave_trade"};
    for (size_t i = 0; i < ansLine.size(); i ++){
        if (i == ansLine.size()-1){
            REQUIRE(result.at(ansLine[i]) == "Starting");
            continue;
        }
        REQUIRE(result.at(ansLine[i]) == ansLine[i+1]);
    }
}
