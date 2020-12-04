#include "Network.h"


NetworkBuilder::NetworkBuilder() : g_(true, false) {
    //nothing 
}

NetworkBuilder::NetworkBuilder(const std::string & filename) : g_(true, false) {
    data_ = file_to_struct(filename);
}

//createSingleLineVertexList essentially replaced by "file_to_struct" in file_bot.hpp

/*std::vector<Vertex> NetworkBuilder::createSingleLineVertexList(const std::string & filename) {
    std::string line = readIn(filename);
    char semicolon = ';';
    char newLine = '\n';

    vector<Vertex> list;
    std::string temp = "";

    for (char& c : line) {
        if (c != semicolon && c != newLine) {
            temp += c;
        }
        else if (c == semicolon || c == newLine){
            list.push_back(temp);
            temp.clear();
        }
        else {
            std::cout << "NOPE" << std::endl;
            abort();
        }
    }

    for (size_t i = 0; i < list.size(); ++i) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;
    return list;
}*/

/**
 * @brief master functoin that uses the data previously read-in in the constructor 
 * and turns that data into a graph structure
 * 
 * @param filename 
 * @return Graph for traversal, other algorithms
 */
Graph NetworkBuilder::constructGraph(const std::string & filename) {
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

        g_.insertVertex(u);
        g_.insertVertex(v);
        g_.insertEdge(u, v);
        g_.setEdgeWeight(u,v, weight);
        }
    }
    else if (vertexList.size() == 1) {
        Vertex v1 = vertexList.at(0);
         g_.insertVertex(v1);
    }
}