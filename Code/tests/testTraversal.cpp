#include "../cs225/catch/catch.hpp"

#include <string>
#include "../edge.h"
#include "../graph.h"
#include <vector>
#include <algorithm>
#include <map>

#include "../edge.h"
#include "../graph.h"
#include "../file_bot.hpp"
#include "../Network.h"
#include "../random.h"
#include "../priorityqueue.h"
#include "../BFS.h"

TEST_CASE("testing one line for all discovery (Discovery Edge Test)", "[part=bfs]") {

    NetworkBuilder nb("tests/SingleLine.txt");
    nb.constructGraph();
    
    const Graph& g = nb.getGraph();
    BFS something(g);
    
    for(Edge e : g.getEdges()){
        REQUIRE(g.getEdgeLabel(e.source,e.dest) == "DISCOVERY");
    }
}

TEST_CASE("Graph with a disconnected vertex") {
    NetworkBuilder nb("tests/unexplored.txt");
    nb.constructGraph();
    
    const Graph& g = nb.getGraph();
    BFS something(g);

    REQUIRE(g.vertexExists("A") == true);
    REQUIRE(g.vertexExists("B") == true);
    REQUIRE(g.vertexExists("C") == true);
    REQUIRE(g.vertexExists("D") == true);
    REQUIRE(g.edgeExists("A", "B") == true);
    REQUIRE(g.edgeExists("B", "C") == true);
    REQUIRE(g.edgeExists("A", "D") == false);
    REQUIRE(g.edgeExists("B", "D") == false);
    REQUIRE(g.edgeExists("C", "D") == false);
    REQUIRE(g.getEdgeLabel("A","B") == "DISCOVERY");
    REQUIRE(g.getEdgeLabel("B","C") == "DISCOVERY"); 
}

TEST_CASE("Graph with cross edge") {
    NetworkBuilder nb("tests/crossedge.txt");
    nb.constructGraph();
    
    const Graph& g = nb.getGraph();
    BFS something(g);

    REQUIRE(g.vertexExists("A") == true);
    REQUIRE(g.vertexExists("B") == true);
    REQUIRE(g.vertexExists("C") == true);
    REQUIRE(g.vertexExists("D") == true);
    REQUIRE(g.getEdgeLabel("A","B") == "DISCOVERY");
    REQUIRE(g.getEdgeLabel("A","C") == "DISCOVERY");
    REQUIRE(g.getEdgeLabel("A","E") == "DISCOVERY");

    bool REQ1 = false;
    bool REQ2 = false;
    bool REQ3 = false;
    if(g.getEdgeLabel("B","C") == "DISCOVERY") {
        if(g.getEdgeLabel("D","C") == "CROSS" && g.getEdgeLabel("E","C") == "CROSS") {
            REQ1 = true;
        }
    }
    if(g.getEdgeLabel("D","C") == "DISCOVERY") {
        if(g.getEdgeLabel("B","C") == "CROSS" && g.getEdgeLabel("E","C") == "CROSS") {
            REQ2 = true;
        }
    }
    if(g.getEdgeLabel("E","C") == "DISCOVERY") {
        if(g.getEdgeLabel("B","C") == "CROSS" && g.getEdgeLabel("D","C") == "CROSS") {
            REQ3 = true;
        }
    }
    REQUIRE(REQ1 == true);
    REQUIRE(REQ2 == true);
    REQUIRE(REQ3 == true);
}

TEST_CASE("Graph with discovery and cross edges") {
    NetworkBuilder nb("tests/discoverycross.txt");
    nb.constructGraph();
    
    const Graph& g = nb.getGraph();
    BFS something(g);

    bool REQ1 = false;
    bool REQ2 = false;
    if(g.getEdgeLabel("A","B") == "DISCOVERY") || g.getEdgeLabel("A","B") == "CROSS") REQ1 = true;
    if(g.getEdgeLabel("A","C") == "CROSS" || g.getEdgeLabel("A","C") == "DISCOVERY") REQ2 = true;
    REQUIRE(REQ1 == true);
    REQUIRE(REQ2 == true);
    REQUIRE(g.getEdgeLabel("B","C") == "DISCOVERY");
    REQUIRE(g.getEdgeLabel("C","D") == "DISCOVERY");

    NetworkBuilder nb("tests/discoverycross2.txt");
    nb.constructGraph();
    
    const Graph& g = nb.getGraph();
    BFS something(g);

    bool REQ1 = false;
    bool REQ2 = false;

    REQUIRE(g.getEdgeLabel("A","B") == "DISCOVERY");
    REQUIRE(g.getEdgeLabel("A","C") == "DISCOVERY");
    REQUIRE(g.getEdgeLabel("A","D") == "DISCOVERY");
    REQUIRE(g.getEdgeLabel("C","D") == "CROSS");
    if(g.getEdgeLabel("B","E") == "DISCOVERY") {
        if(g.getEdgeLabel("C","E") == "CROSS") {
            REQ1 = true;
        }
    } 
    if(g.getEdgeLabel("C","E") == "DISCOVERY") {
        if(g.getEdgeLabel("B","E") == "CROSS") {
            REQ2 = true;
        }
    }
    REQUIRE(REQ1 == true);
    REQUIRE(REQ2 == true);
}

TEST_CASE("Graph with disconnected nodes") {
    NetworkBuilder nb("tests/Disconnected.txt");
    nb.constructGraph();
    
    const Graph& g = nb.getGraph();
    BFS something(g);

    REQUIRE(g.edgeExists("A", "B") == true);
    REQUIRE(g.edgeExists("B", "C") == true);
    REQUIRE(g.edgeExists("C", "D") == true);
    REQUIRE(g.edgeExists("E", "F") == true);
    REQUIRE(g.edgeExists("F", "G") == true);
    REQUIRE(g.edgeExists("G", "H") == true);
    REQUIRE(g.edgeExists("D", "E") == false);
    REQUIRE(g.getEdgeLabel("A","B") == "DISCOVERY");
    REQUIRE(g.getEdgeLabel("B","C") == "DISCOVERY");
    REQUIRE(g.getEdgeLabel("C","D") == "DISCOVERY");
    REQUIRE(g.getEdgeLabel("E","F") == "DISCOVERY");
    REQUIRE(g.getEdgeLabel("F","G") == "DISCOVERY");
    REQUIRE(g.getEdgeLabel("G","H") == "DISCOVERY");   
}