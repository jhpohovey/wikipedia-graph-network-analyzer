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
    while (!Q.empty()) {
        std::pair<Vertex, int> duo = Q.pop();
        Vertex u = duo.first;
        T.insertVertex(u);

        std::vector<Vertex> adjList = G.getAdjacent(u);
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