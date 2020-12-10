#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "BFS.h"
#include "graph.h"
#include "edge.h"
#include <map>
using namespace std;

/**
 * @brief BFS constructor
 */
BFS::BFS() : g_(true,false){
}

/**
 * @brief Breadth First Search Traversal on a graph
 * @param graph - graph being traversed
 * @return a graph with labeled edges
 */
Graph BFS::BFScomplete(const Graph &g)  {
    Vertex v = g.getStartingVertex();
    for(Vertex v : g.getVertices()){
        g_.insertVertex(v);
        beenVisited_.insert(std::make_pair(v,false));
    }
    for(Edge e : g.getEdges()) {
        g_.insertEdge(e.source,e.dest);
        g_.setEdgeLabel(e.source, e.dest, "UNEXPLORED");
    }
    for(Vertex v : g.getVertices()) {
        if(beenVisited_.at(v) == false) {
            BFShelper(g, v);
        }
    }
    return g_;
}

/**
 * @brief BFS traversal helper that labels connected vertices
 * @param graph - graph being traversed
 * @param vertex - head vertex 
 */
void BFS::BFShelper(const Graph &g,const Vertex &v) {
    std::queue<Vertex> q;
    Vertex temp;
    beenVisited_.at(v) = true;
    q.push(v);
    while(!q.empty()) {
        temp = q.front();
        q.pop();
        for(Vertex w : g.getAdjacent(temp)) {
            if(beenVisited_.at(w) == false) {
                g_.setEdgeLabel(temp, w, "DISCOVERY");
                beenVisited_.at(w) = true;
                q.push(w);
            } else if(g_.getEdgeLabel(temp, w) == "UNEXPLORED") {
                g_.setEdgeLabel(temp, w, "CROSS");
            }
        }
    }
}

/**
 * @brief runs BFS traversal on graph and returns the graph with BFS labels
 * @param graph - graph being traversed
 * @return graph that has been traversed using BFS
 */
Graph BFS::getGraphBFS(Graph g) {
    BFS bfs;
    Graph temp = bfs.BFScomplete(g);
    return temp;
}