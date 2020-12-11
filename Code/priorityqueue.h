/**
 * @file Network.h
 * @author John Pohovey
 * @brief Augments the STL priority_queue to act as a Min-heap for pairs of Vertex and ints,
 *        a Vertex and its distance from the start vertex. For use with Dijkstra's 
 *        Shortest Path Algorithm
 * @version 0.1
 * @date December 2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#pragma once

#include <queue>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

typedef std::string Vertex;

/**
 * @brief Custom compare class for Min-heap functionality on pairs
 * 
 */
class Compare {
    public: 
        int operator() (const std::pair<Vertex, int>& i, const std::pair<Vertex, int>& j) {
            return i.second > j.second;
        }
};

class PriorityQueue {
    public:
        PriorityQueue();
        PriorityQueue(Vertex& s);
        void push(std::pair<Vertex, int> p);
        std::pair<Vertex, int> pop();
        std::pair<Vertex, int> top();
        size_t size();
        bool empty();
        bool clear();
    private:
        std::priority_queue<std::pair<Vertex, int>, std::vector<std::pair<Vertex, int>>, Compare> pq;
};