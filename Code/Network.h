/**
 * @file Network.h
 * @author John Pohovey
 * @brief This class makes use the functions in file_bot.hpp in order to read data in from a .TXT file
 *        and store this data in a 2D vector. This 2D vector is used to build and populate the graph
 *        object with all vertices and edges, based on formatting in the input data file. While 
 *        building the graph, a map is used to keep track of each vertex's frequency (occurence 
 *        within the data file). This vertex-frequency map is used in the GraphVisualizer class
 *        to determine the relative sizes at which to draw the vertices.  
 * @version 0.1
 * @date December 2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#pragma once
#include <string>
#include "edge.h"
#include "graph.h"
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include "file_bot.hpp"

typedef std::string Vertex;

class NetworkBuilder {
    public:
        //implementations notes on function, parameters, returns, etc are all located in the .cpp file

        NetworkBuilder();
        NetworkBuilder(const std::string & filename);
        Graph& constructGraph();
        const Graph& getGraph() const;
        const std::unordered_map<Vertex, double>& getFreqTable() const;

    private:
        Graph g_;
        Vertex startPoint;
        void buildGraphSection(std::vector<Vertex>); //constructGraoh helper functions

        //each element in outer vector represents each line of the .txt file
        //each element j at every vector[i] represents the individual links from one line
        std::vector<std::vector<std::string>> data_;

        //records the each vertex's frequency of occurrence within the .txt file
        std::unordered_map<Vertex, double> vertexFreqTable;

};
