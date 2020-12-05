#include "../cs225/catch/catch.hpp"

#include <string>
#include "../edge.h"
#include "../graph.h"
#include <vector>
#include <algorithm>
#include "../file_bot.hpp"
#include "../Network.h"
#include "../random.h"

TEST_CASE("Testing a single line read", "[part=network]") {
    std::string filename = "tests/SingleLine.txt";
    std::vector<std::vector<std::string>> ansVect;
    
    std::vector<std::string> ansLine = {"14th_century", "15th_century", "16th_century", "Pacific_Ocean", "Atlantic_Ocean", "Accra", "Africa", "Atlantic_slave_trade", "African_slave_trade"};
    ansVect.push_back(ansLine);
    std::vector<std::vector<std::string>> out = file_to_struct(filename);

    REQUIRE(ansVect[0].size() == out[0].size());
    for (size_t i = 0; i < ansVect[0].size(); ++i) {
        REQUIRE(ansVect[0][i] == out[0][i]);
    }
}

TEST_CASE("Testing full read from a file", "[part=network]") {
    std::string filename = "tests/Sample1.txt";
    std::vector<std::vector<std::string>> ansVect;
    
    std::vector<std::string> ansLine = {"14th_century", "15th_century", "16th_century", "Pacific_Ocean", "Atlantic_Ocean", "Accra", "Africa", "Atlantic_slave_trade", "African_slave_trade"};
    ansVect.push_back(ansLine);
    ansLine = {"14th_century", "Europe", "Africa", "Atlantic_slave_trade", "African_slave_trade"};
    ansVect.push_back(ansLine);
    ansLine = {"14th_century", "Niger", "Nigeria", "British_Empire", "Slavery", "Africa", "Atlantic_slave_trade", "African_slave_trade"};
    ansVect.push_back(ansLine);
    ansLine = {"14th_century", "Renaissance", "Ancient_Greece", "Greece"};
    ansVect.push_back(ansLine);
    ansLine = {"14th_century", "Italy", "Roman_Catholic_Church", "HIV", "Ronald_Reagan", "President_of_the_United_States", "John_F._Kennedy"};
    ansVect.push_back(ansLine);
    ansLine = {"14th_century", "Europe", "North_America", "United_States", "President_of_the_United_States", "John_F._Kennedy"};
    ansVect.push_back(ansLine);

    std::vector<std::vector<std::string>> out = file_to_struct(filename);

    REQUIRE(ansVect.size() == out.size());
    for (size_t i = 0; i < ansVect.size(); ++i) {
        REQUIRE(ansVect[i].size() == out[i].size());
        for (size_t j = 0; j < ansVect[i].size(); ++j) {
            REQUIRE(ansVect[i][j] == out[i][j]);
        }
    }
}

TEST_CASE("NetworkBuilder(SingleLine.txt) produces correct vertices", "[part=network]") {
    NetworkBuilder nb ("tests/SingleLine.txt");
    nb.constructGraph();

    const Graph& G = nb.getGraph();

    REQUIRE(G.vertexExists("14th_century") == true);
    REQUIRE (G.vertexExists("15th_century") == true);
    REQUIRE (G.vertexExists("16th_century") == true);
    REQUIRE (G.vertexExists("Pacific_Ocean") == true);
    REQUIRE (G.vertexExists("Atlantic_Ocean") == true);
    REQUIRE (G.vertexExists("Accra") == true);
    REQUIRE (G.vertexExists("Africa") == true);
    REQUIRE (G.vertexExists("Atlantic_slave_trade") == true);
    REQUIRE (G.vertexExists("African_slave_trade") == true);
}

TEST_CASE("NetworkBuilder(SingleLine.txt) produces correct edges", "[part=network]") {
    NetworkBuilder nb ("tests/SingleLine.txt");
    nb.constructGraph();

    const Graph& G = nb.getGraph();

    REQUIRE(G.edgeExists("14th_century","15th_century") == true);
    REQUIRE(G.edgeExists("16th_century","15th_century") == true);
    REQUIRE(G.edgeExists("Pacific_Ocean","Atlantic_Ocean") == true);
    REQUIRE(G.edgeExists("Pacific_Ocean","Atlantic_slave_trade") == false);
    REQUIRE(G.edgeExists("Atlantic_slave_trade","African_slave_trade") == true);
}



