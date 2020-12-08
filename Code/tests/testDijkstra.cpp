#include "../cs225/catch/catch.hpp"

#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <string>

#include "../edge.h"
#include "../graph.h"
#include "../file_bot.hpp"
#include "../Network.h"
#include "../random.h"
#include "../priorityqueue.h"
#include "../dijkstraSSSP.h"

TEST_CASE("Distance 'array' has correct initial value population (Small)", "[part=sssp]") {
    NetworkBuilder nb ("tests/SingleLine.txt");
    nb.constructGraph();

    const Graph& g = nb.getGraph();
    Vertex start = "Pacific_Ocean";

    DijkstraSSSP djsp(g, start);

    const std::unordered_map<Vertex,int>& res = djsp.getDists();
    std::vector<Vertex> ansLine = {"14th_century", "15th_century", "16th_century", "Pacific_Ocean", "Atlantic_Ocean", "Accra", "Africa", "Atlantic_slave_trade", "African_slave_trade"};

    REQUIRE(res.size() == ansLine.size());
    for (size_t i = 0; i < ansLine.size(); ++i) {
        Vertex v = ansLine[i];
        auto lookup = res.find(v);
        REQUIRE(lookup != res.end());
        REQUIRE(lookup->first == v);
        if (lookup->first != start) {
            REQUIRE(lookup->second == INT_MAX);
        }
        else {
            REQUIRE(lookup->second == 0);
        }
    }

}

TEST_CASE("Distance 'array' has correct initial value population (Med)", "[part=sssp]") {
    NetworkBuilder nb ("tests/Sample1.txt");
    nb.constructGraph();

    const Graph& g = nb.getGraph();
    Vertex start = "Atlantic_slave_trade";

    DijkstraSSSP djsp(g, start);

    const std::unordered_map<Vertex,int>& res = djsp.getDists();
    std::vector<Vertex> ans = g.getVertices();

    REQUIRE(res.size() == ans.size());
    for (size_t i = 0; i < ans.size(); ++i) {
        Vertex v = ans[i];
        auto lookup = res.find(v);
        REQUIRE(lookup != res.end());
        REQUIRE(lookup->first == v);

        if (lookup->first != start) {
            REQUIRE(lookup->second == INT_MAX);
        }
        else {
            REQUIRE(lookup->second == 0);
        }
    }
}

TEST_CASE("Predecessor 'array' has correct initial value population (Small)", "[part=sssp]") {
    NetworkBuilder nb ("tests/SingleLine.txt");
    nb.constructGraph();

    const Graph& g = nb.getGraph();
    Vertex start = "Accra";

    DijkstraSSSP djsp(g, start);
    const std::unordered_map<Vertex,Vertex>& res = djsp.getPreds();

    std::vector<Vertex> ansLine = {"14th_century", "15th_century", "16th_century", "Pacific_Ocean", "Atlantic_Ocean", "Accra", "Africa", "Atlantic_slave_trade", "African_slave_trade"};

    REQUIRE(res.size() == ansLine.size());
    for (size_t i = 0; i < ansLine.size(); ++i) {
        Vertex v = ansLine[i];
        auto lookup = res.find(v);
        REQUIRE(lookup != res.end());
        REQUIRE(lookup->first == v);
        REQUIRE(lookup->second == "");
    }
}   

TEST_CASE("Predecessor 'array' has correct initial value population (Med)", "[part=sssp]") {
    NetworkBuilder nb ("tests/Sample1.txt");
    nb.constructGraph();

    const Graph& g = nb.getGraph();
    Vertex start = "15th_century";

    DijkstraSSSP djsp(g, start);
    const std::unordered_map<Vertex,Vertex>& res = djsp.getPreds();
    std::vector<Vertex> ans = g.getVertices();

    REQUIRE(res.size() == ans.size());
    for (size_t i = 0; i < ans.size(); ++i) {
        Vertex v = ans[i];
        auto lookup = res.find(v);
        REQUIRE(lookup != res.end());
        REQUIRE(lookup->first == v);
        REQUIRE(lookup->second == "");
    }
}   

TEST_CASE("Shortest Paths found on small graph (|V| = 4) Easy", "[part=sssp][part=find]") {
    Graph G(true, false);
    G.insertVertex("Apple");
    G.insertVertex("Banana");
    G.insertVertex("Carrot");
    G.insertVertex("Dragonfruit");

    G.insertEdge("Apple", "Banana");
    G.setEdgeWeight("Apple", "Banana", 5);

    G.insertEdge("Banana", "Carrot");
    G.setEdgeWeight("Banana", "Carrot", 5);

    G.insertEdge("Carrot", "Dragonfruit");
    G.setEdgeWeight("Carrot", "Dragonfruit", 5);

    G.insertEdge("Apple", "Dragonfruit");
    G.setEdgeWeight("Apple", "Dragonfruit", 20);

    DijkstraSSSP djsp(G, "Apple");
    Graph T = djsp.findSP(G);

    std::vector<Vertex> GvertexList = G.getVertices();
    std::vector<Vertex> TvertexList = T.getVertices();
    REQUIRE(GvertexList.size() == TvertexList.size());
    sort(GvertexList.begin(), GvertexList.end());
    sort(TvertexList.begin(), TvertexList.end());
    for (size_t i = 0; i < GvertexList.size(); ++i) {
        REQUIRE(GvertexList[i] == TvertexList[i]);
    }

    std::vector<Edge> TedgeList = T.getEdges();
    REQUIRE(TedgeList.size() == 3); // A to B, B to C, C to D (excludes A to D)
    REQUIRE(T.edgeExists("Apple", "Banana") == true);
    REQUIRE(T.edgeExists("Banana", "Carrot") == true);
    REQUIRE(T.edgeExists("Carrot", "Dragonfruit") == true);
    REQUIRE(T.edgeExists("Dragonfruit", "Apple") == false);

}

TEST_CASE("Shortest Paths found on small graph (|V| = 4) Med", "[part=sssp][part=find]") {
    Graph G(true, false);
    G.insertVertex("Apple");
    G.insertVertex("Banana");
    G.insertVertex("Carrot");
    G.insertVertex("Dragonfruit");

    G.insertEdge("Apple", "Banana");
    G.setEdgeWeight("Apple", "Banana", 5);

    G.insertEdge("Apple", "Carrot");
    G.setEdgeWeight("Apple", "Carrot", 10);

    G.insertEdge("Banana", "Carrot");
    G.setEdgeWeight("Banana", "Carrot", 6);

    G.insertEdge("Carrot", "Dragonfruit");
    G.setEdgeWeight("Carrot", "Dragonfruit", 15);

    G.insertEdge("Apple", "Dragonfruit");
    G.setEdgeWeight("Apple", "Dragonfruit", 20);

    DijkstraSSSP djsp(G, "Apple");
    Graph T = djsp.findSP(G);

    std::vector<Vertex> GvertexList = G.getVertices();
    std::vector<Vertex> TvertexList = T.getVertices();
    REQUIRE(GvertexList.size() == TvertexList.size());
    sort(GvertexList.begin(), GvertexList.end());
    sort(TvertexList.begin(), TvertexList.end());
    for (size_t i = 0; i < GvertexList.size(); ++i) {
        REQUIRE(GvertexList[i] == TvertexList[i]);
    }

    std::vector<Edge> TedgeList = T.getEdges();
    REQUIRE(TedgeList.size() == 3); // A to B, A to C, A to D
    REQUIRE(T.edgeExists("Apple", "Banana") == true);
    REQUIRE(T.edgeExists("Apple", "Carrot") == true);
    REQUIRE(T.edgeExists("Banana", "Carrot") == false);
    REQUIRE(T.edgeExists("Carrot", "Dragonfruit") == false);
    REQUIRE(T.edgeExists("Dragonfruit", "Apple") == true);

}

TEST_CASE("Shortest Paths found on small graph (|V| = 4) Hard", "[part=sssp][part=find]") {
    Graph G(true, false);
    G.insertVertex("Apple");
    G.insertVertex("Banana");
    G.insertVertex("Carrot");
    G.insertVertex("Dragonfruit");

    G.insertEdge("Apple", "Banana");
    G.setEdgeWeight("Apple", "Banana", 5);

    G.insertEdge("Apple", "Carrot");
    G.setEdgeWeight("Apple", "Carrot", 15);

    G.insertEdge("Banana", "Carrot");
    G.setEdgeWeight("Banana", "Carrot", 6);

    G.insertEdge("Banana", "Dragonfruit");
    G.setEdgeWeight("Banana", "Dragonfruit", 7);

    G.insertEdge("Carrot", "Dragonfruit");
    G.setEdgeWeight("Carrot", "Dragonfruit", 25);

    G.insertEdge("Apple", "Dragonfruit");
    G.setEdgeWeight("Apple", "Dragonfruit", 20);

    DijkstraSSSP djsp(G, "Apple");
    const Graph& T = djsp.findSP(G);

    std::vector<Vertex> GvertexList = G.getVertices();
    std::vector<Vertex> TvertexList = T.getVertices();
    REQUIRE(GvertexList.size() == TvertexList.size());
    sort(GvertexList.begin(), GvertexList.end());
    sort(TvertexList.begin(), TvertexList.end());
    for (size_t i = 0; i < GvertexList.size(); ++i) {
        REQUIRE(GvertexList[i] == TvertexList[i]);
    }

    std::vector<Edge> TedgeList = T.getEdges();
    REQUIRE(TedgeList.size() == 3); // A to B, B to C, B to D
    REQUIRE(T.edgeExists("Apple", "Banana") == true);
    REQUIRE(T.edgeExists("Apple", "Carrot") == false);
    REQUIRE(T.edgeExists("Banana", "Carrot") == true);
    REQUIRE(T.edgeExists("Banana", "Dragonfruit") == true);
    REQUIRE(T.edgeExists("Carrot", "Dragonfruit") == false);
    REQUIRE(T.edgeExists("Dragonfruit", "Apple") == false);

}

TEST_CASE("Shortest paths found for small graph from file (SingleLine.txt)","[part=sssp][part=find]") {
    NetworkBuilder nb("tests/SingleLine.txt");
    nb.constructGraph();

    const Graph& G = nb.getGraph();
    Vertex start = "Atlantic_slave_trade";

    DijkstraSSSP djsp(G, start);
    const Graph& T = djsp.findSP(G);

    std::vector<Vertex> GvertexList = G.getVertices();
    std::vector<Vertex> TvertexList = T.getVertices();
    REQUIRE(GvertexList.size() == TvertexList.size());
    sort(GvertexList.begin(), GvertexList.end());
    sort(TvertexList.begin(), TvertexList.end());
    for (size_t i = 0; i < GvertexList.size(); ++i) {
        REQUIRE(GvertexList[i] == TvertexList[i]);
    }

    std::vector<Edge> TedgeList = T.getEdges();
    REQUIRE(TedgeList.size() == 8); //since this file is a single line, there is only 1 edge between each vertex
    std::vector<std::vector<Vertex>> file = file_to_struct("tests/SingleLine.txt");
    for (size_t i = 0; i < file.size(); ++i) {
        for (size_t j = 0; j < file[i].size() - 1; ++j) {
            REQUIRE(T.edgeExists(file[i][j], file[i][j + 1]) == true);
        }
    }

    REQUIRE(T.edgeExists(file[0][0], file[0][file[0].size() - 1]) == false);
    REQUIRE(T.edgeExists(file[0][8], file[0][5]) == false);
    REQUIRE(T.edgeExists(file[0][2], file[0][4]) == false);
}

TEST_CASE("Shortest paths found for med graph from file (Sample1.txt)", "[part=sssp][part=find]") {
    NetworkBuilder nb("tests/Sample1.txt");
    nb.constructGraph();

    const Graph& G = nb.getGraph();
    Vertex start = "Atlantic_slave_trade";

    DijkstraSSSP djsp(G, start);
    const Graph& T = djsp.findSP(G);

    std::vector<Vertex> GvertexList = G.getVertices();
    std::vector<Vertex> TvertexList = T.getVertices();
    REQUIRE(GvertexList.size() == TvertexList.size());
    sort(GvertexList.begin(), GvertexList.end());
    sort(TvertexList.begin(), TvertexList.end());
    for (size_t i = 0; i < GvertexList.size(); ++i) {
        REQUIRE(GvertexList[i] == TvertexList[i]);
    }

    //need to test edges here still
}