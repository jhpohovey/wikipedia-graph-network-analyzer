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
#include <iostream>
#include <fstream>
using namespace std;

/**
 * @brief BFS constructor
 */
BFS::BFS() : g_(true,false) {
    //do nothing
}

/**
 * @brief Breadth First Search Traversal on a graph
 * @param graph - Graph to be traversed
 * @return A graph with edges labeled either "CROSS" or "DISCOVERY"
 */
const Graph& BFS::traverse(const Graph &g)  {
    Vertex v = g.getStartingVertex();
    for(Vertex v : g.getVertices()){ // Inserts all vertexes from passed in graph into g_ private graph for object
        g_.insertVertex(v);
        beenVisited_.insert(std::make_pair(v,false)); // initializes table containing visits
    }
    for(Edge e : g.getEdges()) { // Inserts all edges from passed in graph to g_ with the label "UNEXPLORED"
        g_.insertEdge(e.source,e.dest);
        g_.setEdgeLabel(e.source, e.dest, "UNEXPLORED");
    }
    for(Vertex v : g.getVertices()) { // Once an unvisited vertex is found, BFShelper is called to complete BFS on that connected peice
        if(beenVisited_.at(v) == false) { // Will reach other unconnected vertex groups
            BFShelper(g, v);
        }
    }
    return g_;
}

/**
 * @brief BFS traversal helper that labels connected vertices
 * @param graph - graph being traversed
 * @param vertex - start vertex 
 */
void BFS::BFShelper(const Graph &g, const Vertex &v) {
    std::queue<Vertex> q;
    Vertex temp;
    beenVisited_.at(v) = true;
    q.push(v);
    while(!q.empty()) { // runs until all connected vertexes become correctly labelled
        temp = q.front();
        q.pop();
        for(Vertex w : g.getAdjacent(temp)) { // iterates through each adjancent vertex of "parent" vertex while maintaining it
            if(beenVisited_.at(w) == false) { // If you find a vertex for the first time, label the edge you used as "DISCOVERY"
                g_.setEdgeLabel(temp, w, "DISCOVERY");
                beenVisited_.at(w) = true;
                q.push(w);
            } else if(g_.getEdgeLabel(temp, w) == "UNEXPLORED") { // If vertex already visited, edge used labelled as "CROSS"
                g_.setEdgeLabel(temp, w, "CROSS");
            }
        }
    }
}

/**
 * @brief gets a constant reference to the graph after the traversal occurs
 * @return graph that has been traversed using BFS
 */
const Graph& BFS::getGraph() {
    return g_;
}

/**
 * @brief prints the source, destination, and label of each edge in the graph to BFSoutput.txt
 */
void BFS::printBFS() {
    ofstream file;
    file.open("../BFSoutput.txt");
    for(Edge e : g_.getEdges()) { // Iterates through each edge in the private Graph
        file << "Source: " << e.source <<std::endl;
        file << "Destination: " << e.dest <<std::endl;
        file << "Edge Label: " << g_.getEdgeLabel(e.source, e.dest) <<std::endl;
        file << " " <<std::endl;
    }
    file.close();
}