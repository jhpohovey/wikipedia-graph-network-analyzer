#include "dijkstraSSSP.h"

/**
 * @brief Constructor.
 * 
 * @param G, a constant reference to the graph that we are going to find all shortest paths from a start vertex
 * @param u, the start vertex where all shortest paths will be calculated from
 */
DijkstraSSSP::DijkstraSSSP(const Graph& G, Vertex u) : g(true, false), T(true, false) {
    start = u;
    g = G;
    std::vector<Vertex> vertexList = G.getVertices();
    dist.reserve(vertexList.size());
    pred.reserve(vertexList.size());
    for (Vertex& v : vertexList) {
        dist.insert(std::make_pair(v, INT_MAX)); //initialize all distances from the start vertex to infinity
        pred.insert(std::make_pair(v, "")); //initalize all predecessor of each vertex to an empty string
    }

    auto it = dist.find(start);
    if (it != dist.end()) {
        it->second = 0; //update the distance from the start vertex to the start vertex to 0
    }
    else {
        std::cout << "Starting vertex does not exist within passed graph, exitting..." << std::endl;
        abort();
    }

    Q = PriorityQueue(start); //custom implementation of priority queue for custom Compare class
}

/**
 * @brief Core of Dijkstra's Algorithm, this function calculates the shortest path from the start vertex
 *        to all other connected vertices in the graph. This specific implementation of Dijkstra's Shortest
 *        Path Algorithm forgoes the need to update elements within the priority queue, instead inserting 
 *        new copies with lower values
 * 
 * @return const Graph&,  a new graph that includes the shortest (cheapest) amount of edges that connect
 *          all vertices in the passed Graph parameter
 */
const Graph& DijkstraSSSP::calculateShortestPaths() {
    bool flag = false;
    while (!Q.empty()) {
        std::pair<Vertex, int> duo = Q.pop();
        Vertex u = duo.first;
        T.insertVertex(u); 

        std::vector<Vertex> adjList = g.getAdjacent(u);
        if (adjList.empty()) { //ensure that the starting vertex is connected to others, or don't need to run algorithm
            flag = true;
            break;
        }
        for (Vertex& v : adjList) { //interact with all neighbors of the current Vertex u
            T.insertVertex(v);
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

            int cost = g.getEdgeWeight(u, v);
            if (cost + dist[u] < dist[v]) { //update the distance and predecessor maps if the sum of the cost and the new distance is less the current best
                dist[v] = cost + dist[u];
            pred[v] = u;
                Q.push(std::make_pair(v, dist[v])); //since stl priority queue doesn't support updating, we add a copy of the element so don't need to worry about being able to update
            }
        }

    }
    if (flag) {
        pred[start] = "No results possible";
        return T;
    }

    for (auto it = pred.begin(); it != pred.end(); ++it) {
        if (it->second != "") {
            T.insertEdge(it->second, it->first);
            int weight = g.getEdgeWeight(it->second, it->first);
            T.setEdgeWeight(it->second, it->first, weight);
        }   
    }

    return T;
}


/** RUN calculateShortestPath() BEFORE RUNNING THIS FUNCTION
 * @brief Function finds the cost to travel from the start vertex to parameter
 *          destination vertex, and returns -1 and INT_MAX in respective cases 
 *          when there is no path.
 * 
 * @param dest 
 * @return int, the cost if there is a path from start vertex to destination,
 *              -1 if the destination does not exist in the graph, or
 *              INT_MAX if the destination is not connected to the start vertex
 *              
 */
int DijkstraSSSP::calculateCostToVertex(const Vertex& dest) const {
    int cost = 0;
    auto lookup = dist.find(dest);
    if (lookup == dist.end()) {
        std::cout << "This vertex is not a vertex within the graph." << std::endl;
        return -1;
    }
    else {
        if (lookup->second == INT_MAX) {
            std::cout << "\nThis vertex is not connected to the starting vertex." << std::endl;
            return INT_MAX;
        }
        else {
            std::cout << "\nThe cost of the path from " << start << " to " << dest << " is:  " << lookup->second << std::endl;
            return lookup->second;
        }
    }
}

/** RUN calculateShortestPath() BEFORE RUNNING THIS FUNCTION
 * @brief Function that takes a vertex as a paramter, and determines whether this vertex
 *        is connected to the start vertex initialized in the constructor
 * 
 * @param v The vertex which we want to determine whether it is connected to the start vertex
 * @return true, Vertex v is connected to the start vertex
 * @return false, Vertex v is not connected to the start vertex 
 */
bool DijkstraSSSP::checkConnectivity(const Vertex& v) const{
    bool costCheck = false;
    bool vertexReached = true;

    auto lookup1 = dist.find(v);
    if (lookup1 == dist.end()) {
        std::cout << "This vertex is not a vertex within the graph." << std::endl;
        return -1;
    }
    else {
        if (lookup1->second < INT_MAX) { //If vertex has a "weight" of infinity (INT_MAX), then it never has been visisted, and therefore is not connected
            costCheck = true;
        }
    }

    //Secondary stage verification of connectivity of vertex to start
    auto lookup2 = pred.find(v);
    if (lookup2 == pred.end()) {
        std::cout << "This vertex is not a vertex within the graph." << std::endl;
        return -1;
    }
    else {
        if (lookup2->first != start && lookup2->second == "") { //if the predessecor of the vertex is an empty string, then it never has been visited, and therefore is not connected
            vertexReached = false;
        }
    }

    return (vertexReached && costCheck);
}


/** RUN calculateShortestPath() BEFORE RUNNING THIS FUNCTION
 * @brief Function finds the shortest path to the parameter Vertex destination from the start vertex
 * 
 * @param dest, the destination vertex that we want to return the shortest path to
 * @return std::vector<Vertex>, the shortest path to travel from the start vertex to the destination vertex
 */
std::vector<Vertex> DijkstraSSSP::pathToDestination (Vertex dest) {
    std::vector<Vertex> path;
    if (!checkConnectivity(dest)) {
        path.push_back("Destination is not connected to starting vertex, so no shortest path exists.");
        return path;
    }
    path.push_back(dest);
    auto lookup = pred.find(dest);
    while (lookup->second != "") { //backtraces through the predessecor map until it reaches the start vertex
        lookup = pred.find(lookup->second);
        path.push_back(lookup->first);
    }

    reverse(path.begin(), path.end()); //backtracing results in a destination -> start path, so reverses to give forward path

    //print path to terminal
    std::cout << "\nShortest path from " << start << " to " << dest << ":\n\t{ ";
    for (size_t i = 0; i < path.size(); ++i) {
        if (i < path.size() - 1) {
            std::cout << path[i] << " -> ";
        }
        else {
            std::cout << path[i] << " }\n" << std::endl;
        }
    } 
    
    return path;
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