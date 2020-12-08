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
//using namespace std;



BFS::Iterator::Iterator() {//done
    current_ = "";
}

BFS::Iterator::Iterator(Graph &g, Vertex &start){//done
    g_ = g;
    start_ = start;
    current_ = start;
    vector<Vertex> vert = g.getVertices();
    int size = vert.size();
    for(int i = 0; i < size; i++){
        beenVisited_.insert(std::pair<std::string, bool> ("", false));
    }
}

BFS::BFS(const Graph &g) {//done
    Vertex v = g.getStartingVertex();
    for(Edge e : g.getEdges()) {
        setEdgeLabel(e.source, e.dest, "UNEXPLORED");
    }
    for(Vertex v : g.getVertices()) {
        if(beenVisited_.at(v) == false) {
            BFS(g, v);
        }
    }
}

BFS::BFS(const Graph &g, const Vertex &v) {//done
    std::queue<Vertex> q;
    Vertex temp = v;
    beenVisited_.at(v) = true;
    q.push(v);
    while(!q.empty()) {
        temp = q.front();
        q.pop();
        for(Vertex w : g.getAdjacent(temp)) {
            if(!beenVisited_.at(w)) {
                setEdgeLabel(temp, w, "DISCOVERY");
                beenVisited_.at(w) = true;
                q.push(w);
            } else if(getEdgeLabel(temp, w) == "UNEXPLORED") {
                setEdgeLabel(temp, w, "CROSS");
            }
        }
    }

}

BFS::Iterator & BFS::Iterator::operator++() {//not done yet
    if(!bfs_->empty()) {
        beenVisited_.at(current_) = true;

        while(!bfs_->empty() && visited(current_) == true){
        current_ = bfs_->peek();
        bfs_->pop();
        }

        if(!visited(current_)) bfs_->add(current_);
        if(!bfs_->empty()) current_ = bfs_->peek();
        
    }
    return *this;
}

Vertex BFS::Iterator::operator*() {//done
    return current_;
}

bool BFS::Iterator::operator!=(const BFS::Iterator &other) {//not done yet
    bool thisEmpty = false;
    bool otherEmpty = false;
    if (this == NULL) thisEmpty = true;
    if (other.bfs_ == NULL) thisEmpty = true;
    if (!thisEmpty) thisEmpty = bfs_->empty(); 
    if (!otherEmpty) otherEmpty = other.bfs_->empty(); 
    if (thisEmpty && otherEmpty) return false; 
    else if ((!thisEmpty)&&(!otherEmpty)) return (bfs_ != other.bfs_); 
    else return true;
    
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


BFS::Iterator BFS::begin() {//done
    return BFS::Iterator(this->g_, start_);
}


BFS::Iterator BFS::end() {//done
    return BFS::Iterator();    
}