#include "dijkstraSSSP.h"

DijkstraSSSP::DijkstraSSSP(const Graph& G, Vertex u) {
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
        std::cout << "Hash init error" << std::endl;
        abort();
    }

    Q = PriorityQueue(start);

}


Graph DijkstraSSSP::findSP(const Graph& G) {
    Graph T(true, false);

    while (!Q.empty()) {
        std::pair<Vertex, int> duo = Q.pop();
        Vertex u = duo.first;
        T.insertVertex(u);

        std::vector<Vertex> adjList = G.getAdjacent(u);
        for (Vertex& v : adjList) {
            T.insertVertex(v);
            T.insertEdge(u, v);
            T.setEdgeWeight(u, v, G.getEdgeWeight(u, v); // this just reconstructs Graph G
            //if (!T.vertexExists(v)) { //the optimization does not include this part

                auto lookupU = dist.find(u);
                auto lookupV = dist.find(v);
                if (lookupU == dist.end()) {
                    std::cout << "Crit fail; u" << std::endl;
                    abort();
                }
                if (lookupV == dist.end()) {
                    std::cout << "Crit fail; v" << std::endl;
                    abort();
                }

                int cost = G.getEdgeWeight(u, v);
                if (cost + dist[u] < dist[v]) {
                    dist[v] = cost + dist[u];
                    pred[v] = u;
                    Q.push(std::make_pair(v, dist[v]));
                }
            //}
        }


    }

    return T;
}