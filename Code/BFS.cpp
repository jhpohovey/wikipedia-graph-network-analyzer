#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "BFS.h"
#include "Graph.h"

using namespace std;



BFS::Iterator::Iterator() {//done
    current_ = "";
}

BFS::Iterator::Iterator(Graph &g, Vertex &start){//done
    g_ = g;
    start_ = start;
    current_ = start;
    vector<Vertex> vert = getVertices();
    int size = vert.size();
    beenVisited_.resize(size, false);
}

BFS::BFS(const Graph &g) {//done
    Vertex v = getStartingVertex();
    for(Edge e : g.getEdges()) {
        setEdgeLabel(e.source, e.dest, "UNEXPLORED");
    }
    for(Vertex v : g.getVertices()) {
        if(beenVisited_.at(v) == "UNEXPLORED") {
            BFS(g, v);
        }
    }
}

BFS::BFS(const Graph &g, const Vertex &v) {//done
    std::queue q;
    beenVisited_[v] = "VISITED";
    q.push(v);
    while(!nodeQueue_.empty()) {
        v = nodeQueue_.pop();
        for(Vertex w : g.getAdjacent(v) {
            if(!beenVisited_.at(w)) {
                setEdgeLabel(v, w, "DISCOVERY");
                beenVisited_.at(w) = true;
                nodeQueue_.add(w);
            } else if(getEdgeLabel(v, w) == "UNEXPLORED") {
                setEdgeLabel(v, w, "CROSS");
            }
        }
    }

}

BFS::Iterator & BFS::Iterator::operator++() {//not done yet
    if(!BFS->empty()) {
        //BFS->pop();
        beenVisited_[] = true; //find out
        
        
    }
}

Vertex BFS::Iterator::operator*() {//done
    return current_;
}

bool BFS::Iterator::operator!=(const BFS::Iterator &other) {//not done yet
    bool thisEmpty = false;
    bool otherEmpty = false;
    if (this == NULL) thisEmpty = true;
    if (other == NULL) thisEmpty = true;
    
}
                     
bool BFS::Iterator::visited(const Vertex &vertex) {//done
    return beenVisited_.at(vertex);
}

void BFS::add(const Vertex &vertex) {//done
    nodeQueue_.push(vertex);
}

Vertex BFS::pop() {//done
    Vertex ret = nodeQueue_.front();
    nodeQueue_.pop();
    return ret;
}

Vertex BFS::peek() const {//done
    return nodeQueue_.front();
}
bool BFS::empty() const {//done
    return nodeQueue_.empty();
}


Iterator BFS::begin() {//done
    return Graph::Iterator(this, start_);
}


Iterator BFS::end() {//done
    return Graph::Iterator();    
}