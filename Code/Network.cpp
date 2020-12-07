#include "Network.h"


NetworkBuilder::NetworkBuilder() : g_(true, false) {
    //nothing 
}

NetworkBuilder::NetworkBuilder(const std::string & filename) : g_(true, false) {
    data_ = file_to_struct(filename);
}

//createSingleLineVertexList essentially replaced by "file_to_struct" in file_bot.hpps

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

std::map<Vertex, Vertex> NetworkBuilder::get_span(Vertex landmark){
    
    std::queue<Vertex> q;
    Graph temp = g_;

    std::map<Vertex, bool> visited;
    std::map<Vertex, Vertex> predecessor;
    for(Vertex u : temp.getVertices()){
        visited[u] = false;
        predecessor[u] = "0";
    }

    visited[landmark] = true;
    predecessor[landmark] = "starting";
    //std::cout<< "Okay we are starting at " << v << std::endl;
    q.push(landmark);

    while(!q.empty()){
        Vertex w = q.front();
        q.pop();
        for(Vertex y : temp.getAdjacent(w)){
            if (visited[y] == false){
                //std::cout << y << " has not been visited yet" << std::endl;
                visited[y] = true;
                predecessor[y] = w;
                q.push(y);
            }
        }
    }

    return predecessor;
}

std::vector<Vertex> NetworkBuilder::store_path(std::map<Vertex, Vertex> & p, Vertex begin, Vertex landmark, Vertex end){
    if (p[begin] == "0" || p[end] == "0"){
        std::cout << "There is no path through these points :(" << std::endl;
    }
    std::vector<Vertex> path;

    Vertex curr = begin;
    //std::cout << "This is the current value";
    while (curr != landmark){
        std::cout << curr << std::endl;
        curr = p[curr];
    }
    std::cout << landmark << std::endl;

    std::vector<Vertex> reverse;
    curr = end;

    while (curr != landmark){
        reverse.push_back(curr);
        curr = p[curr];
    }
    
    //std::cout << "now we here" << std::endl;
    //std::cout << reverse[1] << std::endl;
    //std::cout << reverse[0] << std::endl;
    for (int i = reverse.size() - 1; i >= 0; i--){
        std::cout << reverse[i] << std::endl;
    }

    return path;
}

const Graph& NetworkBuilder::getGraph() {
    return g_;
}