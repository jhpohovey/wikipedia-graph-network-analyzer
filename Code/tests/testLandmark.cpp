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

TEST_CASE("Scanning(landmarktest.txt) produces correct predecessors/", "[part=landmark]") {
    NetworkBuilder nb ("tests/landmarktest.txt");
    nb.constructGraph();

    const Graph& g = nb.getGraph();

    Landmark span(g, "E");
    //std::cout<< temp["A"] << std::endl;
    //std::cout<< temp["B"] << std::endl;
    //std::cout<< temp["C"] << std::endl;
    //std::cout<< temp["D"] << std::endl;
    //std::cout<< temp["E"] << std::endl;
    //std::cout<< temp["F"] << std::endl;
    span.store_path("A", "E", "F");
    //for (size_t i = 0; i < path.size() - 1; i++){
    //    std::cout<< path[i] << std::endl;
    //}
}
