#include "landmark.h"
#include <queue>
#include <map>

Landmark::Landmark(const Graph & graph, Vertex landmark) {
    get_span(graph, landmark);
}

void Landmark::get_span(const Graph & graph, Vertex landmark){
    
    std::queue<Vertex> q;
    std::map<Vertex, bool> visited;
    for(Vertex u : graph.getVertices()){
        visited[u] = false;
        pred[u] = "0";
    }

    visited[landmark] = true;
    pred[landmark] = "starting";
    q.push(landmark);

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

void Landmark::store_path(Vertex begin, Vertex landmark, Vertex end){

    std::vector<Vertex> path;
    if (pred[begin] == "0" || pred[end] == "0"){
        std::cout << "There is no path through these points :(" << std::endl;
        return;
    }

    //std::cout << begin << ", " << landmark << ", " << "and " << end << " are connected." << std::endl;
    //std::cout << "Thank god1" << std::endl;
    Vertex curr = begin;
    //std::cout << "This is the current value: " << curr << std::endl;
    //std::cout << "This is the predecessor: " << pred[curr] << std::endl;

    while (curr != landmark){
        path_.push_back(curr);
        //std::cout << curr;
        curr = pred[curr];
    }

    //std::cout << landmark;
    path_.push_back(landmark);

    std::vector<Vertex> reverse;
    curr = end;

    while (curr != landmark){
        reverse.push_back(curr);
        curr = pred[curr];
    }

    for (int i = reverse.size() - 1; i >= 0; i--){
        //std::cout << reverse[i];
        path_.push_back(reverse[i]);
    }
    std::cout << begin << landmark << end << std::endl;
    printPath();

    return;
}

void Landmark::printPath(){
    if (path_.size() == 0 || path_.size() == 1 || path_.size() == 2){
        std::cout << "Sorry there is no path between these" << std::endl;
    }

    for (size_t i = 0; i < path_.size(); i++){
        std::cout << path_[i];
    }

    return;
}

std::map<Vertex, Vertex> Landmark::getPred(){
    return pred;
}

std::vector<Vertex> Landmark::getPath(){
    return path_;
}

