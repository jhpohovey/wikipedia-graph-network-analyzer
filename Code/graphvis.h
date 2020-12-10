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

typedef struct {
    double x;
    double y;
} PositionVector;

typedef struct {
    double x; 
    double y;
} DisplacementVector;

typedef struct {
    PositionVector pos;
    DisplacementVector disp;
} Node;

class GraphVisualizer {
    public:
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

        double k;
        double k_2;

        cs225::PNG png;
        unsigned width;
        unsigned height;
        double area;
        
        std::vector<Vertex> V;
        std::vector<Edge> E;
        std::unordered_map<Vertex, Node> vnTable;
        std::unordered_map<Vertex, double> freqList;
        

};

