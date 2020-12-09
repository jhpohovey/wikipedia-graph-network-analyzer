#include "graphvis.h"

GraphVisualizer::GraphVisualizer(const Graph& g, unsigned widthPNG, unsigned heightPNG) 
        : G(true, false), png(widthPNG, heightPNG) {
    
    G = g;
    width = widthPNG;
    height = heightPNG;
    V = g.getVertices();
    E = g.getEdges();
    area = width * height;
    k_2 = area / V.size();
    k = sqrt(k_2);

    initRotational();
}

double GraphVisualizer::attractiveForces (double x) {
    return (x * x / k);
}

double GraphVisualizer::repulsiveForces (double x) {
    return (k_2 / x);
}

/**
 * @brief Implementation of the Fruchterman-Reingold Algorithm
 * http://cs.brown.edu/people/rtamassi/gdhandbook/chapters/force-directed.pdf
 * 
 * @param iterations, the amount of times to perform outerloop until complete
 * @return cs225::PNG, graph visualization
 */
cs225::PNG GraphVisualizer::FruchtermanReingold(size_t iterations) {

    double temperature;
    for (size_t i = 0; i < iterations; ++i) {
        for(auto& v : vnTable) {
            v.second.disp.x = 0;
            v.second.disp.y = 0;
            for (auto& u : vnTable) {
                if (u != v) {
                    PositionVector delta = vectorPositionSubtration(v.second, u.second);
                    double mag = positionVectorMagnitude(delta);
                    v.second.disp.x = v.second.disp.x + ((delta.x / mag) * repulsiveForces(mag));
                    v.second.disp.y = v.second.disp.y + ((delta.y / mag) * repulsiveForces(mag));
                }
            }
        }
        for (auto& e : E) {
            PositionVector delta;
            auto vlookup = vnTable.find(e.source);
            auto ulookup = vnTable.find(e.dest);
            if (vlookup != vnTable.end() && ulookup != vnTable.end()) {
                /*delta.x = vlookup->second.pos.x - ulookup->second.pos.x;
                delta.y = vlookup->second.pos.y - ulookup->second.pos.y;*/
                delta = vectorPositionSubtration(vlookup->second, ulookup->second);

                double mag = positionVectorMagnitude(delta);
                vlookup->second.disp.x = vlookup->second.disp.x - ((delta.x / mag) * attractiveForces(mag));
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
            double mag = displacementVectorMagnitude(v.second.disp);
            v.second.pos.x = v.second.pos.x + ((v.second.disp.x / mag) * std::min(v.second.disp.x, temperature));
            v.second.pos.y = v.second.pos.y + ((v.second.disp.y / mag) * std::min(v.second.disp.y, temperature));
            
            v.second.pos.x = std::min((double)(width / 2), std::max((double)(-width / 2), v.second.pos.x));
            v.second.pos.y = std::min((double)(height / 2), std::max((double)(-height / 2), v.second.pos.y);
        }

        if (temperature > 0) {
            temperature -= 2;
        }
        else {
            temperature = 0;
        }
    }

return png;
}

/**
 * @brief Since the Fruchterman-Reingold algorithm is based on 
 * force interactions between particles, an optimal initialization 
 * for reduced computational needs is in a circular form
 * 
 */
void GraphVisualizer::initRotational() {
    const double pi = M_PI;
    double dRad = 1 / V.size();
    double rot = 0;
    for (size_t i = 0; i < V.size(); ++i) {
        Node n;
        n.pos.x = .5 * width * cos(rot);
        n.pos.y = .5 * height * sin(rot);
        vnTable.insert(std::make_pair(V[i], n));
        rot += (2 * pi * dRad);
    }
}

PositionVector vectorPositionSubtration(const Node& a, const Node& b) {
    PositionVector d;
    d.x = a.pos.x - b.pos.x;
    d.y = a.pos.y - b.pos.y;
    return d;
}

double positionVectorMagnitude(const PositionVector& a) {
    return sqrt((a.x * a.x) + (a.y * a.y));
}

double displacementVectorMagnitude(const DisplacementVector& a) {
    return sqrt((a.x * a.x) + (a.y * a.y));
}