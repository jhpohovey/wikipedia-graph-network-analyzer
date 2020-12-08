#pragma once

#include <queue>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

typedef std::string Vertex;

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