/**
 * @file dijkstraSSSP.cpp
 * @author John Pohovey, Arjun Ray
 * @brief Class for generating a graphical visual of a NetworkBuilder's graph object.
 *        This graph visualization is a force directed graph, and is an implementation
 *        of the Fruchterman-Reingold Algorithm (1991). Vertices are initialized with 
 *        positions that together form a circle (this is aids in optimizing the scattering
 *        that ocurrs when running the algorithm.). The computations are then drawn 
 *        onto a PNG-type object.
 * @version 0.1
 * 
 * @date December 2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#pragma once

#include <string>
#include <algorithm>
#include <cmath>
#include <math.h>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "cs225/RGB_HSL.h"
#include "edge.h"
#include "graph.h"
#include "Network.h"
#include <stdio.h>

typedef struct { //struct to represent a vertex's position vector
    double x;
    double y;
} PositionVector;

typedef struct { //struct to represent a vertex's displacement vector
    double x; 
    double y;
} DisplacementVector;

typedef struct { //struct to combine both vectors into a vertex's node
    PositionVector pos;
    DisplacementVector disp;
} Node;

class GraphVisualizer {
    public:
        //implementations notes on function, parameters, returns, etc are all located in the .cpp file

        GraphVisualizer(const NetworkBuilder& nb, unsigned widthPNG, unsigned heightPNG);
        void FruchtermanReingold(size_t iterations);
        cs225::PNG drawGraph(bool shape);
    private:
        Graph G;   
        double attractiveForces(double x);
        double repulsiveForces(double x);

        void initRotational();
        PositionVector vectorPositionSubtration(const Node& a, const Node& b);
        double positionVectorMagnitude(const PositionVector& a);
        double displacementVectorMagnitude(const DisplacementVector& a);

        void drawEdges();
        void drawLine(double x1, double x2, double y1, double y2);

        cs225::PNG png;
        unsigned width;
        unsigned height;
        double area;
        double k;
        double k_2;
        
        std::vector<Vertex> V;
        std::vector<Edge> E;
        std::unordered_map<Vertex, Node> vnTable;
        std::unordered_map<Vertex, double> freqList;
        

};

