#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <queue>
#include "graph.h"
#include "edge.h"
#include <map>

class BFS {
    public: 
    /*
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
                
        };
        */
       BFS();
        Graph BFScomplete(const Graph &g);
        void BFShelper(const Graph &g, const Vertex &v);
        Graph getGraphBFS(Graph );
        void add(const Vertex &vertex);
        Vertex pop();
        Vertex peek() const;
        bool empty() const;
        Graph g_;


    private: 
        
        Vertex start_;
        std::queue<Vertex> nodeQueue_;
        std::map<Vertex, bool> beenVisited_;  
        
};



/*
class Iterator : std::iterator<std::forward_iterator_tag, Vertex> {
    public:
        Iterator();
        Iterator & operator++();
        Vertex operator*();
        bool operator!=(const Iterator &other);
        Iterator(Graph &g, Vertex &start);
        bool visited(const Vertex &vertex);   
           

        class BFS {
            public: 
                
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
    private:
        Graph g_;
        Vertex start_;
        Vertex current_;
        std::map<Vertex, bool> beenVisited_;
        BFS *bfs_;
    };
*/