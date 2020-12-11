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

    //in case no data has been stored for graph
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

    //builds the graph line by line from data
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

    //inserts vertices and corresponding edges and weights
    //does something with a frequency table
    if (vertexList.size() > 1) {
        for (size_t i = 0; i < vertexList.size() - 1; ++i) {
            Vertex u = vertexList.at(i);
            Vertex v = vertexList.at(i + 1);

            auto lookup = vertexFreqTable.find(u);
            if (lookup == vertexFreqTable.end()) {
                vertexFreqTable.insert(std::make_pair(u, 1));
            } else {
                //std::cout << "Before " <<vertexFreqTable[u];
                if (lookup->second == 1) {
                    ++lookup->second;
                }
                else {
                    //printf("\tU %f\n", (log(lookup->second)));
                    if (lookup->second < 50) {
                        lookup->second += (log(lookup->second));//sqrt(lookup->second * sqrt(lookup->second * sqrt(lookup->second * sqrt(lookup->second))));
                        //std::cout <<", After " << vertexFreqTable[u] << std::endl;
                    }
                    else if (lookup->second >= 50 && lookup->second < 250) {
                        lookup->second += log(log(lookup->second));
                    }
                    else if(lookup->second >= 250 && lookup->second < 700) {
                        lookup->second += log(log(log(lookup->second)));
                    }
                    else if (lookup->second >= 700 && lookup->second < 1200) {
                        lookup->second += .5 * log(log(log(lookup->second)));
                    }
                    else {
                        lookup->second += .25 * (log(log(log(lookup->second))));
                    }
                }   
            }
            lookup = vertexFreqTable.find(v);
            if (lookup == vertexFreqTable.end()) {
                vertexFreqTable.insert(std::make_pair(v, 1));
            } else {
                if (lookup->second == 1) {
                    ++lookup->second;
                }
                else {
                    //printf("\tV %f\n", (log(lookup->second)));
                    if (lookup->second < 25) {
                        lookup->second += (log(lookup->second));//sqrt(lookup->second * sqrt(lookup->second * sqrt(lookup->second * sqrt(lookup->second))));
                        //std::cout <<", After " << vertexFreqTable[u] << std::endl;
                    }
                    else if (lookup->second >= 25 && lookup->second < 75) {
                        lookup->second += log(log(lookup->second));
                    }
                    else if(lookup->second >= 75 && lookup->second < 200) {
                        lookup->second += log(log(log(lookup->second)));
                    }
                    else if (lookup->second >= 200 && lookup->second < 400) {
                        lookup->second += .5 * log(log(log(lookup->second)));
                    }
                    else if (lookup->second >= 400 && lookup->second < 800){
                        lookup->second += .25 * (log(log(log(lookup->second))));
                    }
                    else {
                        lookup->second += .125 * (log(log(log(lookup->second))));
                    }
                    
                }
            }

            g_.insertVertex(u);    //inserts source vertex 
            g_.insertEdge(u, v);   //inserts destingation vertex
            int weight = u.length() <= v.length() ? u.length() : v.length(); //calculates edge weight
            g_.setEdgeWeight(u,v, weight);   //sets edge weight
        }
    }

    //accounts for case of only one vertex on a line
    else if (vertexList.size() == 1) {
        Vertex v1 = vertexList.at(0);
         g_.insertVertex(v1); //insert single vertex
    }
}

const Graph& NetworkBuilder::getGraph() const {
    return g_;
}

const std::unordered_map<Vertex, double>& NetworkBuilder::getFreqTable() const {
    return vertexFreqTable;
}