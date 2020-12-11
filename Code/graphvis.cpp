#include "graphvis.h"

/**
 * @brief Constructor
 * 
 * @param nb, a NetworkBuilder object, which includes both a constructed graph and a frequency list (implemented as an unordered map)
 * @param widthPNG, the width of the png to visualize the graph onto
 * @param heightPNG, the height of the png to visualize the graph onto
 */
GraphVisualizer::GraphVisualizer(const NetworkBuilder& nb, unsigned widthPNG, unsigned heightPNG) 
        : G(true, false), png(widthPNG, heightPNG) {
    
    G = nb.getGraph();
    freqList = nb.getFreqTable();
    width = widthPNG;
    height = heightPNG;
    V = nb.getGraph().getVertices();
    E = nb.getGraph().getEdges();
    area = width * height;
    k_2 = area / V.size(); //constant used for force calculation
    k = sqrt(k_2);

    initRotational(); //initialize all vertices in a circular fashion around PNG center
}

/**
 * @brief Function computes attractive forces between vertices as a function of their x position
 * 
 * @param x, distance between two vertices
 * @return double, the force experienced at given distance
 */
double GraphVisualizer::attractiveForces (double x) {
    return (x * x / k);
}

/**
 * @brief Function computes repulsive forces between vertices as a function of their x position 
 * 
 * @param x, distance between two vertices
 * @return double, the force experienced at given distance
 */
double GraphVisualizer::repulsiveForces (double x) {
    return (k_2 / x);
}

/**
 * @brief Implementation of Fruchterman-Reingold Algorithm (in depth anaylsis linked below)
 * http://cs.brown.edu/people/rtamassi/gdhandbook/chapters/force-directed.pdf
 * 
 * @param iterations, used to calculate 'temperature' decrease for most optimal configuration
 * @return cs225::PNG, graph visualization
 */
void GraphVisualizer::FruchtermanReingold(size_t iterations) {

    double temperature = 1; //temperature controls the spread of point displacement over iterations
    for (size_t i = 0; i < iterations; ++i) {
        for(auto& v : vnTable) {
            //calculate all repulsive forces between vertices
            v.second.disp.x = 0;
            v.second.disp.y = 0;
            for (auto& u : vnTable) {
                if ((u.first != v.first) && 
                    (u.second.pos.x != v.second.pos.x) && (u.second.pos.y != v.second.pos.y)) { //run only if vectors or distinct from one another
                    PositionVector delta = vectorPositionSubtration(v.second, u.second);

                    if (delta.x < .0001 || delta.y < .0001) { //edge guard against division by 0
                        delta.x = (rand() % (unsigned int)(.5 * width)) - .5 * width;
                        delta.y = (rand() % (unsigned int)(.5 * height)) - .5 * height;
                    }
                    double mag = positionVectorMagnitude(delta);

                    v.second.disp.x = v.second.disp.x + ((delta.x / mag) * repulsiveForces(mag)); //updates displacements based on calculated force
                    v.second.disp.y = v.second.disp.y + ((delta.y / mag) * repulsiveForces(mag));
                }
            }
        }
        for (auto& e : E) {
            //calculates all attractive forces between vertices
            PositionVector delta;
            auto vlookup = vnTable.find(e.source);
            auto ulookup = vnTable.find(e.dest);
            if (vlookup != vnTable.end() && ulookup != vnTable.end()) {
                delta = vectorPositionSubtration(vlookup->second, ulookup->second);

                if (delta.x < .0001 || delta.y < .0001) { 
                    delta.x = (rand() % (unsigned int)(.5 * width)) - .5 * width;
                    delta.y = (rand() % (unsigned int)(.5 * height)) - .5 * height;
                }
                double mag = positionVectorMagnitude(delta);

                vlookup->second.disp.x = vlookup->second.disp.x - ((delta.x / mag) * attractiveForces(mag)); //updates displacements based on calculated force
                vlookup->second.disp.y = vlookup->second.disp.y - ((delta.y / mag) * attractiveForces(mag));
                ulookup->second.disp.x = ulookup->second.disp.x + ((delta.x / mag) * attractiveForces(mag));
                ulookup->second.disp.y = ulookup->second.disp.y + ((delta.y / mag) * attractiveForces(mag));
            }
            else {
                std::cout << "vnTable error" << std::endl;
                abort();
            }
        }

        for(auto& v : vnTable) {
            //constrains the displacement values as a function of temperature
            double mag = displacementVectorMagnitude(v.second.disp);
            v.second.pos.x = v.second.pos.x + ((v.second.disp.x / mag) * std::min(v.second.disp.x, temperature));
            v.second.pos.y = v.second.pos.y + ((v.second.disp.y / mag) * std::min(v.second.disp.y, temperature));
            v.second.pos.x = std::min((double)(width / 2), std::max((double)(width / 2), v.second.pos.x));
            v.second.pos.y = std::min((double)(height / 2), std::max((double)(height / 2), v.second.pos.y));
        }
        temperature *= (1 / iterations); //'cool' temperature to relax displacement calculation margins 
    }
}

/**
 * @brief Function plots the graph onto a PNG using a variation of Fruchterman-Reingold Algorithm
 * 
 * @param shape, boolean, true to draw vertices as circles, false to draw as squares
 * @return cs225::PNG, graph drawn with all vertices and edges
 */
cs225::PNG GraphVisualizer::drawGraph(bool shape) {

    int div = 10;
    bool edge = true;
    std::vector<cs225::HSLAPixel> colors;
    for (int i = 0; i < 360 / div; ++i) {
        cs225::HSLAPixel p((i * div), .75, .5, .75);
        colors.push_back(p);
    }

    for (auto it = vnTable.begin(); it != vnTable.end(); ++it) {
        Vertex v = it->first;

        Node& n = it->second; //get all components to calculate final x and y positions
        double xpos = n.pos.x;
        double ypos = n.pos.y;
        double xdisp = n.disp.x;
        double ydisp = n.disp.y; 

        unsigned xfin = (unsigned int) (std::abs(xpos + xdisp)) % (unsigned int) (.9 * width) + (.05 * width); //calculates final resting position
        unsigned yfin = (unsigned int) (std::abs(ypos + ydisp)) % (unsigned int) (.9 * height) + (.05 * height); //add a small border on all edges of PNG

        n.pos.x = xfin; //update node positions for use in drawing edges
        n.pos.y = yfin;
    }

    //draw edges after calculating the final resting coordinates of all vertices, but before drawing vertices
    // so that edges are drawn underneath vertices.
    drawEdges(); 

    for (auto it = vnTable.begin(); it != vnTable.end(); ++it) {
        Vertex v = it->first; 

        Node& n = it->second; 
        unsigned xfin = n.pos.x; //get final x,y coordinates
        unsigned yfin = n.pos.y;

        auto lookup = freqList.find(v); //lookup Vertex, frequency pair to get vertex's occurrence in file
        if (lookup == freqList.end()) {
            std::cout << "Frequency hashmap error" << std::endl;
            abort();
        }
        int freq = lookup->second; 

        cs225::HSLAPixel color = colors[rand() % colors.size()]; //choose a random color for drawing vertex 
        double factor  = .5; //determines how much of the full vertex will be drawn onto png
        for (unsigned int i = xfin - std::ceil(factor * freq); i < xfin + std::ceil(factor * freq); ++i) {
            for (unsigned int j = yfin - std::ceil(factor * freq); j < yfin + std::ceil(factor * freq); ++j) {
                if (i < width && j < height) {
                    if (shape) { //determines if vertices will be square or circular in shape based on passed param
                        if (((xfin - i) * (xfin - i) + (yfin - j) * (yfin - j) <= .25 * freq * freq)) { //only colors pixels within the radius of the center
                            cs225::HSLAPixel& pixel = png.getPixel(i, j);
                            pixel.h = color.h;
                            pixel.l = color.l;
                            pixel.s = color.s;
                            pixel.a = color.a;
                        }
                    } 
                    else {
                        cs225::HSLAPixel& pixel = png.getPixel(i, j);
                        pixel.h = color.h;
                        pixel.l = color.l;
                        pixel.s = color.s;
                        pixel.a = color.a;
                    }
                }
                
            }
        }
    }
    
    return png;
}

/**
 * @brief Function draw all edges between all vertices (in black)
 * 
 */
void GraphVisualizer::drawEdges() {
    for (auto& e : E) {
        auto ulookup = vnTable.find(e.source);
        auto vlookup = vnTable.find(e.dest);
        if (ulookup != vnTable.end() && vlookup != vnTable.end()) {
            drawLine(ulookup->second.pos.x, vlookup->second.pos.x, ulookup->second.pos.y, vlookup->second.pos.y);
        }
        else {
            std::cout << "Error reading in drawEdge()" << std::endl;
            abort();
        }
    }
}

/**
 * @brief Function is a helper function for drawEdge. Calculates slope and plots 
 *        line between the two coordinate params.
 * 
 * @param x1, X component of first coordinate
 * @param x2, X component of second coordinate
 * @param y1, Y component of first coordinate
 * @param y2, Y component of second coordinate
 */
void GraphVisualizer::drawLine(double x1, double x2, double y1, double y2) {
    cs225::HSLAPixel black(0, 1, 0, 1);

    double slope;
    if ((std::abs(y1 - y2) < .001) && std::abs(x1 - x2) < .1) {
        //coordinates are the same point / are close enough, do nothing
        return;
    }
    else if (std::abs(y1 - y2) < .001) { // if same y values, can just increment x values (no slope needed).
        if (x1 > x2) {
            for (size_t i = x1; i > x2; --i) { //direction of iteration depends on which component is greater
                cs225::HSLAPixel& pixel = png.getPixel(i, y1);
                pixel.l = black.l;
            }
        }
        else {
            for (size_t i = x1; i < x2; ++i) {
                cs225::HSLAPixel& pixel = png.getPixel(i, y1);
                pixel.l = black.l;
            }
        }
    }
    else if (std::abs(x1 - x2) < .1) { // if same x values, can just increment y values (no slope needed).
        if (y1 > y2) {
            for (size_t j = y1; j > y2; --j) {
                cs225::HSLAPixel& pixel = png.getPixel(x1, j);
                pixel.l = black.l;
            }
        }
        else {
            for (size_t j = y1; j < y2; ++j) {
                cs225::HSLAPixel& pixel = png.getPixel(x1, j);
                pixel.l = black.l;
            }
        }
    }
    else {
        slope = (y2 - y1) / (x2 - x1);
        if (x1 > x2) {
            double x = x2;
            while (x < x1) {
                int y = slope * (x - x1) + y1;
                cs225::HSLAPixel& pixel = png.getPixel(x, y);
                pixel.l = black.l;
                x+=2;
            }
        }
        else {
            double x = x1;
            while (x < x2) {
                int y = slope * (x - x2) + y2;
                cs225::HSLAPixel& pixel = png.getPixel(x, y);
                pixel.l = black.l;
                x+=2;
            }
        }
    }
}

/**
 * @brief Since the Fruchterman-Reingold algorithm is based on 
 * force interactions between particles, an optimal initialization 
 * for reduced computational needs is in a circular form
 * 
 */
void GraphVisualizer::initRotational() {
    const double pi = M_PI;
    double dRad = (double) 1 / (double) V.size();
    double rot = 0;
    for (size_t i = 0; i < V.size(); ++i) {
        Node n;
        n.pos.x = .5 * width + .25 * width * cos(rot);
        n.pos.y = .5 * height + .25 * height * sin(rot);
        vnTable.insert(std::make_pair(V[i], n));
        rot += (2 * pi * dRad);
    }
}

/**
 * @brief Function performs vector subtraction
 * 
 * @param a, Minuend vector for subtraction operation
 * @param b, subtrahend vector for subtraction operation
 * @return PositionVector, which is the resulting difference vector
 */
PositionVector GraphVisualizer::vectorPositionSubtration(const Node& a, const Node& b) {
    PositionVector d;
    d.x = a.pos.x - b.pos.x;
    d.y = a.pos.y - b.pos.y;
    return d;
}

/**
 * @brief Function calculates the magnitude of a (position) vector 
 * 
 * @param a, the vector whose magnitude will be calculated
 * @return double, the magnitude of the vector
 */
double GraphVisualizer::positionVectorMagnitude(const PositionVector& a) {
    return sqrt((a.x * a.x) + (a.y * a.y));
}

/**
 * @brief Function calculates the magnitude of a (displacement) vector 
 * 
 * @param a, the vector whose magnitude will be calculated
 * @return double, the magnitude of the vector
 */
double GraphVisualizer::displacementVectorMagnitude(const DisplacementVector& a) {
    return sqrt((a.x * a.x) + (a.y * a.y));
}