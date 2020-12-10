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

    Landmark lpath(g, "14th_century");
    std::map<Vertex, Vertex> result = lpath.getPred();

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

    Landmark lpath(g, "African_slave_trade");
    std::map<Vertex, Vertex> result = lpath.getPred();

    std::vector<Vertex> ansLine = {"14th_century", "15th_century", "16th_century", "Pacific_Ocean", "Atlantic_Ocean", "Accra", "Africa", "Atlantic_slave_trade", "African_slave_trade"};
    for (size_t i = 0; i < ansLine.size(); i ++){
        if (i == ansLine.size()-1){
            REQUIRE(result.at(ansLine[i]) == "Starting");
            continue;
        }
        REQUIRE(result.at(ansLine[i]) == ansLine[i+1]);
    }
}

TEST_CASE("Each vertex has been visited in graph and has a valid predeccessor (Sample1.txt)/", "[part=landmark]") {
    NetworkBuilder nb ("tests/Sample1.txt");
    nb.constructGraph();

    const Graph& g = nb.getGraph();

    Landmark lpath(g, "Atlantic_Ocean");
    std::map<Vertex, Vertex> result = lpath.getPred();
    std::vector<Vertex> v = g.getVertices();

    for (size_t i = 0; i < v.size(); i ++){
        int flag = 0;
        REQUIRE(result.at(v[i]) != "0");
        if (std::find(v.begin(), v.end(), result.at(v[i])) != v.end() || result.at(v[i]) == "Starting") flag = 1;
        REQUIRE(flag == 1);
    }
}

TEST_CASE("Test most simple case/", "[part=landmark]") {
    /* G visual:
                        
            Apple ------------------ Dragonfruit
              |                          |
             |                          |
            Banana ------------------ Carrot
                            
    */
    Graph G(true, false);
    G.insertVertex("Apple");
    G.insertVertex("Banana");
    G.insertVertex("Carrot");
    G.insertVertex("Dragonfruit");

    G.insertEdge("Apple", "Banana");
    G.insertEdge("Banana", "Carrot");
    G.insertEdge("Apple", "Dragonfruit");
    G.insertEdge("Carrot", "Dragonfruit");

    Landmark lpath(G, "Dragonfruit");
    lpath.store_path("Apple", "Dragonfruit", "Carrot");
    std::vector<Vertex> result = lpath.getPath();

    std::vector<Vertex> ansLine = {"Apple", "Dragonfruit", "Carrot"} ;

    for (size_t i = 0; i < result.size(); i ++){
        REQUIRE(result[i] == ansLine[i]);
    }

}

TEST_CASE("Easy graph with landmark path through origin/", "[part=landmark]") {
    /* G visual:
                        
            Apple ------------------ Dragonfruit
              |                          
             |                         
            Banana ------------------ Carrot
                            
    */
    Graph G(true, false);
    G.insertVertex("Apple");
    G.insertVertex("Banana");
    G.insertVertex("Carrot");
    G.insertVertex("Dragonfruit");

    G.insertEdge("Apple", "Banana");
    G.insertEdge("Banana", "Carrot");
    G.insertEdge("Apple", "Dragonfruit");

    Landmark lpath(G, "Dragonfruit");
    lpath.store_path("Apple", "Dragonfruit", "Carrot");
    std::vector<Vertex> result = lpath.getPath();

    std::vector<Vertex> ansLine = {"Apple", "Dragonfruit", "Apple", "Banana", "Carrot"} ;

    REQUIRE(lpath.getLength() == 4);
    REQUIRE(result.size() == 5);

    for (size_t i = 0; i < result.size(); i ++){
        REQUIRE(result[i] == ansLine[i]);
    }

}

TEST_CASE("Finds a shorteset path among multiple paths of equal distance/", "[part=landmark]") {
    /* G visual:
                        
            Apple ------------------ Dragonfruit ------------ Elderberry
              |                                 \            /   
              |                                     \    /
              |                                     /   \    
              |                                   /          \
            Banana ---------------------- Carrot  ------------  Fig
                            
    */
    Graph G(true, false);
    G.insertVertex("Apple");
    G.insertVertex("Banana");
    G.insertVertex("Carrot");
    G.insertVertex("Dragonfruit");

    G.insertEdge("Apple", "Banana");
    G.insertEdge("Banana", "Carrot");
    G.insertEdge("Apple", "Dragonfruit");
    G.insertEdge("Elderberry", "Dragonfruit");
    G.insertEdge("Elderberry", "Carrot");
    G.insertEdge("Dragonfruit", "Fig");
    G.insertEdge("Carrot", "Fig");

    Landmark lpath(G, "Dragonfruit");
    lpath.store_path("Apple", "Dragonfruit", "Carrot");
    std::vector<Vertex> result = lpath.getPath();
    lpath.printPath();

    REQUIRE(lpath.getLength() == 3);
    REQUIRE(result.size() == 4);

}

TEST_CASE("No path is stored for a landmark that isn't connected to other vertices/", "[part=landmark]") {
    /* G visual:
                        
            Apple                   Dragonfruit
              |                            
             |                         
            Banana ------------------ Carrot
                            
    */
    Graph G(true, false);
    G.insertVertex("Apple");
    G.insertVertex("Banana");
    G.insertVertex("Carrot");
    G.insertVertex("Dragonfruit");

    G.insertEdge("Apple", "Banana");
    G.insertEdge("Banana", "Carrot");

    Landmark lpath(G, "Dragonfruit");
    lpath.store_path("Apple", "Dragonfruit", "Carrot");
    std::vector<Vertex> result = lpath.getPath();

    REQUIRE(result.size() == 0);

}

TEST_CASE("Landmark is connected to one vertex but not the other/", "[part=landmark]") {
    /* G visual:
                        
            Apple ------------------ Dragonfruit
                                         
                                     
            Banana ------------------ Carrot
                            
    */
    Graph G(true, false);
    G.insertVertex("Apple");
    G.insertVertex("Banana");
    G.insertVertex("Carrot");
    G.insertVertex("Dragonfruit");

    G.insertEdge("Apple", "Dragonfruit");
    G.insertEdge("Banana", "Carrot");

    Landmark lpath(G, "Dragonfruit");
    lpath.store_path("Apple", "Dragonfruit", "Carrot");
    std::vector<Vertex> result = lpath.getPath();

    REQUIRE(result.size() == 0);

}

