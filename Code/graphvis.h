#include <string>
#include <algorithm>
#include <cmath>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "cs225/RGB_HSL.h"
#include "edge.h"
#include "graph.h"

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
        GraphVisualizer(const Graph& g, unsigned widthPNG, unsigned heightPNG);
        cs225::PNG FruchtermanReingold(size_t iterations);
    private:
        Graph G;   
        double attractiveForces(double x);
        double repulsiveForces(double x);

        void initRotational();

        double k;
        double k_2;

        cs225::PNG png;
        unsigned width;
        unsigned height;
        double area;
        
        std::vector<Vertex> V;
        std::vector<Edge> E;
        std::unordered_map<Vertex, Node> vnTable;
        

};

