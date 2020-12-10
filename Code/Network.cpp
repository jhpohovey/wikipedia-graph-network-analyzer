#include "Network.h"


NetworkBuilder::NetworkBuilder() : g_(true, false) {
    //nothing 
}

NetworkBuilder::NetworkBuilder(const std::string & filename) : g_(true, false) {
    data_ = file_to_struct(filename);
}

/**
 * @brief master functoin that uses the data previously read-in in the constructor 
 * and turns that data into a graph structure
 * 
 * @param filename 
 * @return Graph for traversal, other algorithms
 */
Graph& NetworkBuilder::constructGraph() {
    if (data_.empty()) {
        std::cout << "Data structure was not correctly populated" << std::endl;
        g_.insertVertex("N O P E");
        return g_;
    }

    startPoint = data_[0][0]; //tbh idk if this is necessary, the graph class already stores it

    //accounts for edge case where there is only one node
    if (data_[0].size() == 1 && data_[0][0].size() == 1) {
        Vertex v = data_[0][0];
        g_.insertVertex(v);
        return g_;
    }

    for (size_t i = 0; i < data_.size(); ++i) {
        buildGraphSection(data_[i]);
    }

    return g_;
}

/**
 * @brief adds all vertex in vector to graph, and adds an edge between all
 * 
 * @param vertexList, a vector of strings representing one line from the input file
 */
void NetworkBuilder::buildGraphSection(std::vector<Vertex> vertexList) {
    if (vertexList.size() > 1) {
        for (size_t i = 0; i < vertexList.size() - 1; ++i) {
            Vertex u = vertexList.at(i);
            Vertex v = vertexList.at(i + 1);

            auto lookup = vertexFreqTable.find(u);
            if (lookup == vertexFreqTable.end()) {
                vertexFreqTable.insert(std::make_pair(u, 1));
            } else {
                //std::cout << "Before " <<vertexFreqTable[u];
                lookup->second += sqrt(lookup->second*sqrt(lookup->second));
                //std::cout <<", After " << vertexFreqTable[u] << std::endl;
            }
            lookup = vertexFreqTable.find(v);
            if (lookup == vertexFreqTable.end()) {
                vertexFreqTable.insert(std::make_pair(v, 1));
            } else {
                lookup->second = sqrt(lookup->second * sqrt(lookup->second));
            }

            g_.insertVertex(u);
            g_.insertVertex(v);
            g_.insertEdge(u, v);
            int weight = u.length() <= v.length() ? u.length() : v.length();
            g_.setEdgeWeight(u,v, weight);
        }
    }
    else if (vertexList.size() == 1) {
        Vertex v1 = vertexList.at(0);
         g_.insertVertex(v1);
    }
}

const Graph& NetworkBuilder::getGraph() const {
    return g_;
}

const std::unordered_map<Vertex, double>& NetworkBuilder::getFreqTable() const {
    return vertexFreqTable;
}