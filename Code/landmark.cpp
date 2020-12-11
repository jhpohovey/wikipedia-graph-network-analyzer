#include "landmark.h"
#include <queue>
#include <map>

Landmark::Landmark(const Graph & graph, Vertex landmark) {
    get_span(graph, landmark);
}

/*
 * get_span() is using a modified version of BFS to create a 
 * minimum spanning tree from the landmark vertex. This way, 
 * only one call to get_span() will give the minimum connections
 * between beginning vertex, landmark vertex, and end vertex
 */
void Landmark::get_span(const Graph & graph, Vertex landmark){
    
    std::queue<Vertex> q;
    std::map<Vertex, bool> visited;

    //Set every vertex as being unvisited and no predecessor
    for(Vertex u : graph.getVertices()){
        visited[u] = false;
        pred[u] = "";
    }

    //Processes landmark vertex as starting point in spanning tree
    visited[landmark] = true;
    pred[landmark] = "";
    q.push(landmark);

    //Modification on BFS to only search one component
    //Keeps track of each vertex's immediate predecessor
    while(!q.empty()){
        Vertex w = q.front();
        q.pop();
        for(Vertex y : graph.getAdjacent(w)){
            if (visited[y] == false){
                visited[y] = true;
                pred[y] = w;
                q.push(y);
            }
        }
    }

    return;
}

/*
 * Manipulates the predecessor map to create a vector of 
 * vertices that starts at the beggining vertex, passes 
 * through the landmark vertex, and ends at the end vertex
 */
void Landmark::store_path(Vertex begin, Vertex landmark, Vertex end){

    //Determine if the vertices of interest are actually conncected
    if (pred[begin] == "" || pred[end] == "" || begin == landmark || end == landmark){
        std::cout << "There is no path through these points :(" << std::endl;
        return;
    }

    //Following predecessors from beginning
    //vertex to landmark creates beginning 
    //of desired path
    Vertex curr = begin;
    while (curr != landmark){
        path_.push_back(curr);
        curr = pred[curr];
    }

    
    path_.push_back(landmark); //include landmark in path

    //Following predecessor from end
    //vertex to landmark creates a reversed verion
    //of end of desired path
    std::vector<Vertex> reverse;
    curr = end;
    while (curr != landmark){
        reverse.push_back(curr);
        curr = pred[curr];
    }

    //Reverse the end of path and add to resultant path
    for (int i = reverse.size() - 1; i >= 0; i--){
        path_.push_back(reverse[i]);
    }

    return;
}

/*
 * Prints out formatted path using the previously
 * determined path vector
 */
void Landmark::printPath(){

    //No valid path exists
    if (path_.size() == 0 || path_.size() == 1 || path_.size() == 2){
        std::cout << "Sorry there is no path between these" << std::endl;
    }

    //Iterate through path and print;
    std::cout << "Start -> ";
    for (size_t i = 0; i < path_.size(); i++){
        std::cout << path_[i] << " -> ";
    }
    std::cout << "End" <<std::endl;

    return;
}

std::map<Vertex, Vertex> Landmark::getPred(){
    return pred;
}

std::vector<Vertex> Landmark::getPath(){
    return path_;
}

int Landmark::getLength(){
    return path_.size() -1;
}
