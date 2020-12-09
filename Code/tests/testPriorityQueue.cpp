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
#include "../priorityqueue.h"

std::vector<int> makeIncVect(size_t n) {
    std::vector<int> inc;
    inc.reserve(n);
    for (size_t i = 1; i < n + 1; ++i) {
        inc.push_back(i);
    }
    return inc;
}

TEST_CASE("Clearing PriorityQueue works correctly", "[part=pq]") {
    std::vector<Vertex> vList = {"14th_century", "15th_century", "16th_century", "Pacific_Ocean", "Atlantic_Ocean", "Accra", "Africa", "Atlantic_slave_trade", "African_slave_trade"};
    PriorityQueue pq(vList[0]);
    for (size_t i = 1; i < vList.size(); ++i) {
        pq.push(make_pair(vList[i], 1));
    }

    pq.clear();
    REQUIRE(pq.empty() == true);
}

TEST_CASE("PriorityQueue puts pairs in correct order (min-heap) - 1", "[part=pq]") {
    std::vector<Vertex> vList = {"14th_century", "15th_century", "16th_century", "Pacific_Ocean", "Atlantic_Ocean", "Accra", "Africa", "Atlantic_slave_trade", "African_slave_trade"};
    //                                  0               1               2               3               4               5       6                   7                       8
    PriorityQueue pq (vList[0]);
    pq.push(std::make_pair("16th_century", 2));
    pq.push(std::make_pair("15th_century", 1));
    pq.push(std::make_pair("African_slave_trade", 8));
    pq.push(std::make_pair("Pacific_Ocean", 3));
    pq.push(std::make_pair("Atlantic_Ocean", 4));
    pq.push(std::make_pair("Africa", 6));
    pq.push(std::make_pair("Atlantic_slave_trade", 7));
    pq.push(std::make_pair("Accra", 5));

    std::vector<std::pair<Vertex, int>> ans;
    for (size_t i = 0; i < vList.size(); ++i) {
        ans.push_back(std::make_pair(vList[i], i));
    }

    REQUIRE(ans.size() == pq.size());
    for (size_t i = 0; i < ans.size(); ++i) {
        REQUIRE(ans[i] == pq.top());
        REQUIRE(ans[i] == pq.pop());
    }
}

TEST_CASE("PriorityQueue puts pairs in correct order - 2", "[part=pq]") {
    std::vector<Vertex> vList = {"14th_century", "15th_century", "16th_century", "Pacific_Ocean", "Atlantic_Ocean", "Accra", "Africa", "Atlantic_slave_trade", "African_slave_trade"};

    Vertex start = "14th_century";
    PriorityQueue pq(start);
    pq.push(std::make_pair("16th_century", 2));
    pq.push(std::make_pair("Accra", 5));
    pq.push(std::make_pair("15th_century", 1));
    pq.push(std::make_pair("Atlantic_Ocean", 4));
    pq.push(std::make_pair("African_slave_trade", 8));
    pq.push(std::make_pair("Pacific_Ocean", 3));
    pq.push(std::make_pair("Atlantic_slave_trade", 7));
    pq.push(std::make_pair("Africa", 6));
    
    std::vector<std::pair<Vertex, int>> ans;
    for (size_t i = 0; i < vList.size(); ++i) {
        ans.push_back(std::make_pair(vList[i], i));
    }

    REQUIRE(ans.size() == pq.size());
    for (size_t i = 0; i < ans.size(); ++i) {
        REQUIRE(ans[i] == pq.top());
        REQUIRE(ans[i] == pq.pop());
    }


}
