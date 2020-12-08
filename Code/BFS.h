#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <queue>

class BFS {
    public: 
        class Iterator : std::iterator<std::forward_iterator_tag, Vertex> {
            public:
                Iterator();
                Iterator & operator++();
                Vertex operator*();
                bool operator!=(const Iterator &other);
                Iterator(Graph &g, Vertex &start);
                bool visited(const Vertex &vertex);   
                   
            private:
                Graph g_;
                Vertex start_;
                Vertex current_;
                std::map<Vertex, bool> beenVisited_;
        };
        
        BFS(const Graph &g);
        BFS(const Graph &g, const Vertex &v);
        void add(const Vertex &vertex);
        Vertex pop();
        Vertex peek() const;
        bool empty() const;
        Iterator begin();
        Iterator end();

    private: 
        Graph g_;
        Vertex start_;
        std::queue<Vertex> nodeQueue_;
};