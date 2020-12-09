#include "dijkstraSSSP.h"

DijkstraSSSP::DijkstraSSSP(const Graph& G, Vertex u) : g(true, false), T(true, false) {
    start = u;
    g = G;
    std::vector<Vertex> vertexList = G.getVertices();
    dist.reserve(vertexList.size());
    pred.reserve(vertexList.size());
    for (Vertex& v : vertexList) {
        dist.insert(std::make_pair(v, INT_MAX));
        pred.insert(std::make_pair(v, ""));
    }

    auto it = dist.find(start);
    if (it != dist.end()) {
        it->second = 0; //does this work, otherwise
        dist[start] = 0;
    }
    else {
        std::cout << "Hash initialization error." << std::endl;
        abort();
    }

    Q = PriorityQueue(start);

}


const Graph& DijkstraSSSP::findSP(const Graph& G) {
    bool flag = false;
    while (!Q.empty()) {
        std::pair<Vertex, int> duo = Q.pop();
        Vertex u = duo.first;
        T.insertVertex(u);

        std::vector<Vertex> adjList = G.getAdjacent(u);
        if (adjList.empty()) { //ensure that the starting vertex is connected to others, or don't need to run alg
            flag = true;
            break;
        }
        for (Vertex& v : adjList) {
            T.insertVertex(v);
            //if (!T.vertexExists(v)) { //the optimization from lecture does not include this part

                auto lookupU = dist.find(u);
                auto lookupV = dist.find(v);
                if (lookupU == dist.end()) {
                    std::cout << "Critical failure on u; " << u << " does not exist in dist array" << std::endl;
                    abort();
                }
                if (lookupV == dist.end()) {
                    std::cout << "Critical failure on v; " << v << " does not exist in dist array" << std::endl;
                    abort();
                }

                int cost = G.getEdgeWeight(u, v);
                if (cost + dist[u] < dist[v]) {
                    dist[v] = cost + dist[u];
                    pred[v] = u;
                    Q.push(std::make_pair(v, dist[v])); //since stl priority queue doesn't support updating, we add a copy of the element so you need to worry about updating
                }
            //}
        }

    }
    if (flag) {
        pred[start] = "No results possible";
        return T;
    }

    for (auto it = pred.begin(); it != pred.end(); ++it) {
        //std::cout << it->first << ", " << it->second << std::endl;
        if (it->second != "") {
            T.insertEdge(it->second, it->first);
            int weight = G.getEdgeWeight(it->second, it->first);
            T.setEdgeWeight(it->second, it->first, weight);
        }
        
    }

    return T;
}

std::unordered_map<Vertex, int> DijkstraSSSP::getDists() const {
    return dist;
}

std::unordered_map<Vertex, Vertex> DijkstraSSSP::getPreds() const {
    return pred;
}

Vertex DijkstraSSSP::getStart() const {
    return start;
}

int DijkstraSSSP::calculateCostToVertex(const Vertex& v) const {
    int cost = 0;
    auto lookup = dist.find(v);
    if (lookup == dist.end()) {
        std::cout << "This vertex is not a vertex within the graph." << std::endl;
        return -1;
    }
    else {
        if (lookup->second == INT_MAX) {
            std::cout << "This vertex is not connected to the starting vertex" << std::endl;
            return INT_MAX;
        }
        else {
            return lookup->second;
        }
    }
}

bool DijkstraSSSP::checkConnectivity(const Vertex& v) const{
    bool costCheck = false;
    bool vertexReached = true;

    auto lookup1 = dist.find(v);
    if (lookup1 == dist.end()) {
        std::cout << "This vertex is not a vertex within the graph." << std::endl;
        return -1;
    }
    else {
        if (lookup1->second < INT_MAX) {
            costCheck = true;
        }
    }

    //cross check as secondary stage validation of connectivity of vertex
    auto lookup2 = pred.find(v);
    if (lookup2 == pred.end()) {
        std::cout << "This vertex is not a vertex within the graph." << std::endl;
        return -1;
    }
    else {
        //std::cout << lookup2->second << " LOL " << lookup2->first << std::endl;
        if (lookup2->first != start && lookup2->second == "") {
            vertexReached = false;
        }
    }

    return (vertexReached && costCheck);
}