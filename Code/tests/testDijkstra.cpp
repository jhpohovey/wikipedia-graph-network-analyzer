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
    /* G visual:
                        20
            Apple ------------------ Dragonfruit
              |                         |   5
           5  |                         |
            Banana ------------------ Carrot
                            5
    */
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
    Graph T = djsp.calculateShortestPaths();

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

    //show that Dijkstra returns longer path of 3 edges instead of 1 edge to get from Apple to Dragonfruit, b/c sum of weight of 3 edges is less than the 1 edge
    REQUIRE(T.getEdgeWeight("Apple", "Banana") + T.getEdgeWeight("Banana", "Carrot") + G.getEdgeWeight("Carrot", "Dragonfruit") <= G.getEdgeWeight("Dragonfruit", "Apple"));

    int cost = djsp.calculateCostToVertex("Dragonfruit");
    REQUIRE(cost == 15); // A to B = 5, B to C = 5, C to D = 5; 5 + 5 + 5 = 15 < 20

    std::vector<Vertex> path = djsp.pathToDestination("Dragonfruit");
    REQUIRE(path.size() == 4);
    REQUIRE(path[0] == "Apple");
    REQUIRE(path[1] == "Banana");
    REQUIRE(path[2] == "Carrot");
    REQUIRE(path[3] == "Dragonfruit");
}

TEST_CASE("Shortest Paths found on small graph (|V| = 4) Med", "[part=sssp][part=find]") {
        /* G visual:
                        20
            Apple ------------------ Dragonfruit
              |   \                     |   
           5  |        \   10           |
              |            \            |   15
              |                 \       |
              |                     \   |
            Banana ------------------ Carrot
                            6
    */

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
    Graph T = djsp.calculateShortestPaths();

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

    /* G visual:
                        20
            Apple ------------------ Dragonfruit
              |   \                  /   |   
           5  |    15  \        /        |
              |           / \            |   25
              |       /          \       |
              |   / 7                \   |
            Banana ------------------ Carrot
                            6
    */

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
    const Graph& T = djsp.calculateShortestPaths();

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
    const Graph& T = djsp.calculateShortestPaths();

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
    
    Vertex start = "14th_century";

    DijkstraSSSP djsp(G, start);
    const Graph& T = djsp.calculateShortestPaths();

    std::vector<Vertex> GvertexList = G.getVertices();
    std::vector<Vertex> TvertexList = T.getVertices();
    REQUIRE(GvertexList.size() == TvertexList.size());
    sort(GvertexList.begin(), GvertexList.end());
    sort(TvertexList.begin(), TvertexList.end());
    for (size_t i = 0; i < GvertexList.size(); ++i) {
        REQUIRE(GvertexList[i] == TvertexList[i]);
    }

    std::vector<Edge> TedgeList = T.getEdges();
    std::vector<Edge> GedgeList = G.getEdges();
    REQUIRE(GedgeList.size() == TedgeList.size() + 3);
    REQUIRE(T.edgeExists("Slavery", "British_Empire") == false);
    REQUIRE(T.edgeExists("United_States", "President_of_the_United_States") == false);
    REQUIRE(T.edgeExists("Pacific_Ocean", "16th_century") == false);
}

TEST_CASE ("Cost to travel from the startving vertex to a vertex B is correct (|V| = 4) Easy", "[part=sssp][part=cost]") {

    /* G visual:
                        20
            Apple ------------------ Dragonfruit
              |                         |   5
           5  |                         |
            Banana ------------------ Carrot
                            5
    */

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
    Graph T = djsp.calculateShortestPaths();
    
    Vertex destination = "Banana";
    int cost = djsp.calculateCostToVertex(destination);
    REQUIRE(cost == 5);

    destination = "Carrot";
    cost = djsp.calculateCostToVertex(destination);
    REQUIRE(cost == 10);

    destination = "Dragonfruit";
    cost = djsp.calculateCostToVertex(destination);
    REQUIRE(cost < 20);
    REQUIRE(cost == 15);
}

TEST_CASE("Cost to travel from the startving vertex to a vertex B is correct (|V| = 4) Med", "[part=sssp][part=cost]") {
    /* G visual:
                        20
            Apple ------------------ Dragonfruit
              |   \                     |   
           5  |        \   10           |
              |            \            |   15
              |                 \       |
              |                     \   |
            Banana ------------------ Carrot
                            6
    */
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
    Graph T = djsp.calculateShortestPaths();

    Vertex destination = "Banana";
    int cost = djsp.calculateCostToVertex(destination);
    REQUIRE(cost == 5);

    destination = "Carrot";
    cost = djsp.calculateCostToVertex(destination);
    REQUIRE(cost < 11);
    REQUIRE(cost == 10);

    destination = "Dragonfruit";
    cost = djsp.calculateCostToVertex(destination);
    REQUIRE(cost < (5 + 6 + 15));
    REQUIRE(cost < (10 + 15));
    REQUIRE(cost == 20);
}

TEST_CASE("Cost to travel from the startving vertex to a vertex B is correct (|V| = 4) Hard", "[part=sssp][part=cost]") {
    /* G visual:
                        20
            Apple ------------------ Dragonfruit
              |   \                  /   |   
           5  |    15  \        /        |
              |           / \            |   25
              |       /          \       |
              |   / 7                \   |
            Banana ------------------ Carrot
                            6
    */

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
    const Graph& T = djsp.calculateShortestPaths();

    Vertex destination = "Banana";
    int cost = djsp.calculateCostToVertex(destination);
    REQUIRE(cost == 5);

    destination = "Carrot";
    cost = djsp.calculateCostToVertex(destination);
    REQUIRE(cost < (20 + 25));
    REQUIRE(cost < 15);
    REQUIRE(cost == (5 + 6));

    destination = "Dragonfruit";
    cost = djsp.calculateCostToVertex(destination);
    REQUIRE(cost < 20);
    REQUIRE(cost < (5 + 6 + 25));
    REQUIRE(cost == (5 + 7));
    
}

TEST_CASE("Checks that on a graph with disconnected subgraphs, algorithm can determine which vertices are disconnected", "[part=sssp][part=cost]") {
    Graph G(true, false);
    G.insertVertex("Apple");
    G.insertVertex("Banana");
    G.insertVertex("Carrot");
    G.insertVertex("Dragonfruit");
    G.insertVertex("Not_Connected_Vertex");

    G.insertEdge("Apple", "Banana");
    G.setEdgeWeight("Apple", "Banana", 5);

    G.insertEdge("Banana", "Carrot");
    G.setEdgeWeight("Banana", "Carrot", 5);

    G.insertEdge("Carrot", "Dragonfruit");
    G.setEdgeWeight("Carrot", "Dragonfruit", 5);

    G.insertEdge("Apple", "Dragonfruit");
    G.setEdgeWeight("Apple", "Dragonfruit", 20);

    DijkstraSSSP djsp(G, "Apple");
    Graph T = djsp.calculateShortestPaths();
    int cost = djsp.calculateCostToVertex("Not_Connected_Vertex");
    REQUIRE(cost == INT_MAX); //since cost is infinity, this means that the destination vertex is not connected to the starting vertex, since the value never got udpated.
    bool connected = djsp.checkConnectivity("Not_Connected_Vertex");
    REQUIRE(connected == false); //second way of showing that we are able to determine connectivity

    connected = djsp.checkConnectivity("Banana");
    REQUIRE(connected == true);

    std::vector<Vertex> path = djsp.pathToDestination("Not_Connected_Vertex");
    REQUIRE(path.size() == 1);
    REQUIRE(path[0] == "Destination is not connected to starting vertex, so no shortest path exists.");
}

TEST_CASE("Check that Dijkstra's algorithm does not run on a disconnected starting vertex", "[part=sssp][part=cost]") {
    Graph G(true, false);
    G.insertVertex("Apple");
    G.insertVertex("Banana");
    G.insertVertex("Carrot");
    G.insertVertex("Dragonfruit");
    G.insertVertex("Not_Connected_Vertex");

    G.insertEdge("Apple", "Banana");
    G.setEdgeWeight("Apple", "Banana", 5);

    G.insertEdge("Banana", "Carrot");
    G.setEdgeWeight("Banana", "Carrot", 5);

    G.insertEdge("Carrot", "Dragonfruit");
    G.setEdgeWeight("Carrot", "Dragonfruit", 5);

    G.insertEdge("Apple", "Dragonfruit");
    G.setEdgeWeight("Apple", "Dragonfruit", 20);

    DijkstraSSSP djsp(G, "Not_Connected_Vertex");
    Graph T = djsp.calculateShortestPaths();

    REQUIRE(T.getVertices().size() == 1);
    REQUIRE(T.getEdges().size() == 0);
}

TEST_CASE("Shortest path from start to destination is returned (|V| = 4) Med","[part=sssp][part=path]") {
    /* G visual:
                        20
            Apple ------------------ Dragonfruit
              |   \                     |   
           5  |        \   10           |
              |            \            |   15
              |                 \       |
              |                     \   |
            Banana ------------------ Carrot
                            6
    */
    
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
    Graph T = djsp.calculateShortestPaths();

    Vertex dest = "Carrot";
    std::vector<Vertex> path = djsp.pathToDestination(dest);
    REQUIRE(path.size() == 2);
    REQUIRE(path[0] == "Apple");
    REQUIRE(path[1] == "Carrot");
    path.clear();

    dest = "Banana";
    path = djsp.pathToDestination(dest);
    REQUIRE(path.size() == 2);
    REQUIRE(path[0] == "Apple");
    REQUIRE(path[1] == "Banana");
    path.clear();

    dest = "Dragonfruit";
    path = djsp.pathToDestination(dest);
    REQUIRE(path.size() == 2);
    REQUIRE(path[0] == "Apple");
    REQUIRE(path[1] == "Dragonfruit");
}

TEST_CASE("Shortest path from start to destination is returned (|V| = 4) Hard","[part=sssp][part=path]") {

    /* G visual:
                        20
            Apple ------------------ Dragonfruit
              |   \                  /   |   
           5  |    15  \        /        |
              |           / \            |   25
              |       /          \       |
              |   / 7                \   |
            Banana ------------------ Carrot
                            6
    */

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
    const Graph& T = djsp.calculateShortestPaths();

    Vertex dest = "Banana";
    std::vector<Vertex> path = djsp.pathToDestination(dest);
    REQUIRE(path.size() == 2);
    REQUIRE(path[0] == "Apple");
    REQUIRE(path[1] == "Banana");
    path.clear();

    dest = "Carrot";
    path = djsp.pathToDestination(dest);
    REQUIRE(path.size() == 3);
    REQUIRE(path[0] == "Apple");
    REQUIRE(path[1] == "Banana");
    REQUIRE(path[2] == "Carrot");
    path.clear();

    dest = "Dragonfruit";
    path = djsp.pathToDestination(dest);
    REQUIRE(path.size() == 3);
    REQUIRE(path[0] == "Apple");
    REQUIRE(path[1] == "Banana");
    REQUIRE(path[2] == "Dragonfruit");
    path.clear();

}