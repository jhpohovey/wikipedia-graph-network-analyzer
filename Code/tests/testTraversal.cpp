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
    BFS test;
    Graph result = test.BFScomplete(g);
    
    for(Edge e : result.getEdges()){
        REQUIRE(result.getEdgeLabel(e.source,e.dest) == "DISCOVERY");
    }
}

TEST_CASE("Graph with disconnected nodes", "[part=bfs]") {
    NetworkBuilder nb("tests/Disconnected.txt");
    nb.constructGraph();
    
    const Graph& g = nb.getGraph();
    BFS test;
    Graph result = test.BFScomplete(g);

    REQUIRE(result.edgeExists("A", "B") == true);
    REQUIRE(result.edgeExists("B", "C") == true);
    REQUIRE(result.edgeExists("C", "D") == true);
    REQUIRE(result.edgeExists("E", "F") == true);
    REQUIRE(result.edgeExists("F", "G") == true);
    REQUIRE(result.edgeExists("G", "H") == true);
    REQUIRE(result.edgeExists("D", "E") == false);
    REQUIRE(result.getEdgeLabel("A","B") == "DISCOVERY");
    REQUIRE(result.getEdgeLabel("B","C") == "DISCOVERY");
    REQUIRE(result.getEdgeLabel("C","D") == "DISCOVERY");
    REQUIRE(result.getEdgeLabel("E","F") == "DISCOVERY");
    REQUIRE(result.getEdgeLabel("F","G") == "DISCOVERY");
    REQUIRE(result.getEdgeLabel("G","H") == "DISCOVERY");   
}

TEST_CASE("Graph with a disconnected vertex", "[part=bfs]") {
    NetworkBuilder nb("tests/unexplored.txt");
    nb.constructGraph();
    
    const Graph& g = nb.getGraph();
    BFS test;
    Graph result = test.BFScomplete(g);

    REQUIRE(result.vertexExists("A") == true);
    REQUIRE(result.vertexExists("B") == true);
    REQUIRE(result.vertexExists("C") == true);
    REQUIRE(result.vertexExists("D") == true);
    REQUIRE(result.edgeExists("A", "B") == true);
    REQUIRE(result.edgeExists("B", "C") == true);
    REQUIRE(result.edgeExists("A", "D") == false);
    REQUIRE(result.edgeExists("B", "D") == false);
    REQUIRE(result.edgeExists("C", "D") == false);
    REQUIRE(result.getEdgeLabel("A","B") == "DISCOVERY");
    REQUIRE(result.getEdgeLabel("B","C") == "DISCOVERY"); 
}

TEST_CASE("Graph with discovery and cross edges 1", "[part=bfs]") {
    NetworkBuilder nb("tests/crossedge.txt");
    nb.constructGraph();
    
    const Graph& g = nb.getGraph();
    BFS test;
    Graph result = test.BFScomplete(g);

    REQUIRE(result.vertexExists("A") == true);
    REQUIRE(result.vertexExists("B") == true);
    REQUIRE(result.vertexExists("C") == true);
    REQUIRE(result.vertexExists("D") == true);
    REQUIRE(result.vertexExists("E") == true);
    REQUIRE(result.getEdgeLabel("A","B") == "DISCOVERY");
    REQUIRE(result.getEdgeLabel("A","C") == "DISCOVERY");
    REQUIRE(result.getEdgeLabel("A","E") == "DISCOVERY");

    bool REQ1 = false;
    bool REQ2 = false;
    bool REQ3 = false;
    if(result.getEdgeLabel("B","C") == "DISCOVERY") {
        if(result.getEdgeLabel("D","C") == "CROSS" && result.getEdgeLabel("E","C") == "CROSS") {
            REQ1 = true;
        }
    }
    if(result.getEdgeLabel("D","C") == "DISCOVERY") {
        if(result.getEdgeLabel("B","C") == "CROSS" && result.getEdgeLabel("E","C") == "CROSS") {
            REQ2 = true;
        }
    }
    if(result.getEdgeLabel("E","C") == "DISCOVERY") {
        if(result.getEdgeLabel("B","C") == "CROSS" && result.getEdgeLabel("D","C") == "CROSS") {
            REQ3 = true;
        }
    }
    REQUIRE(REQ1 == true);
    REQUIRE(REQ2 == true);
    REQUIRE(REQ3 == true);
}

TEST_CASE("Graph with discovery and cross edges 2", "[part=bfs]") {
    NetworkBuilder nb("tests/discoverycross.txt");
    nb.constructGraph();
    
    const Graph& g = nb.getGraph();
    BFS test;
    Graph result = test.BFScomplete(g);

    bool REQ1 = false;
    bool REQ2 = false;
    if(result.getEdgeLabel("A","B") == "DISCOVERY") REQ1 = true;
    if(result.getEdgeLabel("A","C") == "CROSS" || result.getEdgeLabel("A","C") == "DISCOVERY") REQ2 = true;
    REQUIRE(REQ1 == true);
    REQUIRE(REQ2 == true);
    REQUIRE(result.getEdgeLabel("B","C") == "DISCOVERY");
    REQUIRE(result.getEdgeLabel("C","D") == "DISCOVERY");
}

TEST_CASE("Graph with discovery and cross edges 3", "[part=bfs]") {
    NetworkBuilder nb("tests/discoverycross2.txt");
    nb.constructGraph();
    
    const Graph& g = nb.getGraph();
    BFS test;
    Graph result = test.BFScomplete(g);

    bool REQ1 = false;
    bool REQ2 = false;

    REQUIRE(result.getEdgeLabel("A","B") == "DISCOVERY");
    REQUIRE(result.getEdgeLabel("A","C") == "DISCOVERY");
    REQUIRE(result.getEdgeLabel("A","D") == "DISCOVERY");
    REQUIRE(result.getEdgeLabel("C","D") == "CROSS");
    if(result.getEdgeLabel("B","E") == "DISCOVERY") {
        if(result.getEdgeLabel("C","E") == "CROSS") {
            REQ1 = true;
        }
    } 
    if(result.getEdgeLabel("C","E") == "DISCOVERY") {
        if(result.getEdgeLabel("B","E") == "CROSS") {
            REQ2 = true;
        }
    }
    REQUIRE(REQ1 == true);
    REQUIRE(REQ2 == true);

}