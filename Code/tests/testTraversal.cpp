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