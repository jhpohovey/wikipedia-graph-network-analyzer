#include "graphvis.h"

GraphVisualizer::GraphVisualizer(const NetworkBuilder& nb, unsigned widthPNG, unsigned heightPNG) 
        : G(true, false), png(widthPNG, heightPNG) {
    
    G = nb.getGraph();
    freqList = nb.getFreqTable();
    width = widthPNG;
    height = heightPNG;
    V = nb.getGraph().getVertices();
    E = nb.getGraph().getEdges();
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
 * @brief Implementation of theme and variation of Fruchterman-Reingold Algorithm
 * http://cs.brown.edu/people/rtamassi/gdhandbook/chapters/force-directed.pdf
 * 
 * @param iterations, used to calculate 'temperature' decrease for most optimal configuration
 * @return cs225::PNG, graph visualization
 */
void GraphVisualizer::FruchtermanReingold(size_t iterations) {

    double temperature = 1;
    for (size_t i = 0; i < iterations; ++i) {
        temperature *= (1 / iterations);
        for(auto& v : vnTable) {
            v.second.disp.x = 0;
            v.second.disp.y = 0;
            for (auto& u : vnTable) {
                if ((u.first != v.first) && 
                    (u.second.pos.x != v.second.pos.x) && (u.second.pos.y != v.second.pos.y) /*&& 
                    (u.second.disp.x != v.second.disp.x) && (u.second.disp.y != v.second.disp.y)*/) {
                    PositionVector delta = vectorPositionSubtration(v.second, u.second);
                    if (delta.x < .0001 || delta.y < .0001) {
                        delta.x = (rand() % (unsigned int)(.5 * width)) - .5 * width;
                        delta.y = (rand() % (unsigned int)(.5 * height)) - .5 * height;
                    }
                    //std::cout << "Vertex delta: x: " << delta.x << ", y: " << delta.y << std::endl;
                    double mag = positionVectorMagnitude(delta);
                    //std::cout << "Magnitude of Delta:" << mag << std::endl;
                    v.second.disp.x = v.second.disp.x + ((delta.x / mag) * repulsiveForces(mag));
                    v.second.disp.y = v.second.disp.y + ((delta.y / mag) * repulsiveForces(mag));
                    //std::cout << "Dispx: " << v.second.disp.x << ", Dispy: " <<v.second.disp.y << std::endl << std::endl;
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
                //std::cout << std::endl << "Edge delta: x: " << delta.x << ", y: " << delta.y << std::endl;
                if (delta.x < .0001 || delta.y < .0001) {
                    delta.x = (rand() % (unsigned int)(.5 * width)) - .5 * width;
                    delta.y = (rand() % (unsigned int)(.5 * height)) - .5 * height;
                }
                double mag = positionVectorMagnitude(delta);
                //std::cout << "Magnitude of Delta:" << mag << std::endl;
                vlookup->second.disp.x = vlookup->second.disp.x - ((delta.x / mag) * attractiveForces(mag));
                vlookup->second.disp.y = vlookup->second.disp.y - ((delta.y / mag) * attractiveForces(mag));
                //std::cout << "v Dispx: " << vlookup->second.disp.x << ", v Dispy: " << vlookup->second.disp.y << std::endl << std::endl;
                ulookup->second.disp.x = ulookup->second.disp.x + ((delta.x / mag) * attractiveForces(mag));
                ulookup->second.disp.y = ulookup->second.disp.y + ((delta.y / mag) * attractiveForces(mag));
                //std::cout << "u Dispx: " << ulookup->second.disp.x << ", u Dispy: " << ulookup->second.disp.y << std::endl << std::endl;
            }
            else {
                std::cout << "vnTable error" << std::endl;
                abort();
            }
        }

        for(auto& v : vnTable) {
            double mag = displacementVectorMagnitude(v.second.disp);
            //std::cout << "before: " << v.second.pos.x << ", " << v.second.pos.y;
            v.second.pos.x = v.second.pos.x + ((v.second.disp.x / mag) * std::min(v.second.disp.x, temperature));
            v.second.pos.y = v.second.pos.y + ((v.second.disp.y / mag) * std::min(v.second.disp.y, temperature));
            //std::cout <<", mid: " << v.second.pos.x << ", " << v.second.pos.y;
            v.second.pos.x = std::min((double)(width / 2), std::max((double)(width / 2), v.second.pos.x));
            v.second.pos.y = std::min((double)(height / 2), std::max((double)(height / 2), v.second.pos.y));
            //std::cout << "Possible: max " << (double)(height / 2) << ", " << v.second.pos.y;
            //std::cout << "\tPossible: min " << (double)(height / 2) << ", " << std::max((double)(height / 2), v.second.pos.y) << std::endl;
            //std::cout <<", after: " << v.second.pos.x << ", " << v.second.pos.y << std::endl;
        }
    }
}

/**
 * @brief Plots the graph onto a PNG using a variation of Fruchterman-Reingold Algorithm
 * 
 * @param shape, boolean, true to draw vertices as circles, false to draw as squares
 * @return cs225::PNG 
 */
cs225::PNG GraphVisualizer::drawGraph(bool shape) {

    int div = 10;
    std::vector<cs225::HSLAPixel> colors;
    for (int i = 0; i < 360 / div; ++i) {
        cs225::HSLAPixel p((i * div), .75, .5, .75);
        colors.push_back(p);
    }

    for (auto it = vnTable.begin(); it != vnTable.end(); ++it) {
        Vertex v = it->first;

        Node& n = it->second;
        double xpos = n.pos.x;
        double ypos = n.pos.y;
        double xdisp = n.disp.x;
        double ydisp = n.disp.y;

        auto lookup = freqList.find(v);
        if (lookup == freqList.end()) {
            std::cout << "Frequency hashmap error" << std::endl;
            abort();
        }
        int freq = lookup->second;
        //std::cout << "Xpos:" << xpos << ", Xdisp: " << xdisp << std::endl;
        //std::cout << "Ypos:" << ypos << ", Ydisp: " << ydisp << std::endl << std::endl;
        unsigned xfin = (unsigned int) (std::abs(xpos + xdisp)) % (unsigned int) (.9 * width) + (.05 * width);
        unsigned yfin = (unsigned int) (std::abs(ypos + ydisp)) % (unsigned int) (.9 * height) + (.05 * height);
        //std::cout << n.pos.x << "Before " << n.pos.y << std::endl;
        //std::cout << it->second.pos.x << " Before " << it->second.pos.y << std::endl << std::endl;
        n.pos.x = xfin;
        n.pos.y = yfin;
        //std::cout << n.pos.x << " After" << n.pos.y << std::endl << std::endl;
        //std::cout << it->second.pos.x << " After " << it->second.pos.y << std::endl << std::endl;
        drawEdges();
        //unsigned xfin = std::abs(xpos);
        //unsigned yfin = std::abs(ypos);
        //xfin = (xfin + rand() % width) % width;
        //yfin = (yfin + rand() % height) % height;

        cs225::HSLAPixel color = colors[rand() % colors.size()];
        //std::cout << "Freq" << freq << std::endl;
        for (unsigned int i = xfin - .5 * freq; i < xfin + .5 * freq; ++i) {
            for (unsigned int j = yfin - .5 * freq; j < yfin + .5 * freq; ++j) {
                //std::cout << "Pixel - " << i << ", " << j << std::endl;
                /*std::cout << "xfin - .25 * 20: " << xfin - .25 * 20 << ", xfin + .25 * 20: " << xfin + .25 * 20 << std::endl;
                std::cout << "yfin - .25 * 20: " << yfin - .25 * 20 << ", yfin + .25 * 20: " << yfin + .25 * 20 << std::endl;*/
                //std::cout << "i: " << i << ", j: " << j << std::endl;
                //std::cout << "xfin " << xfin << ", yfin " << yfin << std::endl;
                //std::cout << "Pythag: " << (xfin - i) * (xfin - i) + (yfin - j) * (yfin - j) << std::endl;
                if (i < width && j < height) {
                    if (shape) {
                        if (((xfin - i) * (xfin - i) + (yfin - j) * (yfin - j) <= .25 * freq * freq)) {
                        //std::cout << "\tPixel - " << i << ", " << j << std::endl;
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

void GraphVisualizer::drawLine(double x1, double x2, double y1, double y2) {
    cs225::HSLAPixel black(0, 1, 0, 1);
    //std::cout << "x1 " << x1 << ", x2 " << x2 << ", y1 " << y1 << ", y2 " << y2<<std::endl;

    double slope;
    if ((std::abs(y1 - y2) < .001) && std::abs(x1 - x2) < .1) {
        //same point / close enough, do nothing
        return;
    }
    else if (std::abs(y1 - y2) < .001) {
        if (x1 > x2) {
            for (size_t i = x1; i > x2; --i) {
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
    else if (std::abs(x1 - x2) < .1) {
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
        /*if (x1 > x2) {
            if (y1 > y2) {
                for (size_t i = x1; i > x2; --i) {
                    for (size_t j = y1; j > y2; --j) {
                        if (std::abs(j - (slope * (i - x1) + y1)) < 2) {
                            cs225::HSLAPixel& pixel = png.getPixel(x1, j);
                            pixel.l = black.l;
                        }
                    }
                }
            }
            else {
                for (size_t i = x1; i > x2; --i) {
                    for (size_t j = y1; j < y2; ++j) {
                        if (std::abs(j - (slope * (i - x1) + y1)) < 2) {
                            cs225::HSLAPixel& pixel = png.getPixel(x1, j);
                            pixel.l = black.l;
                        }
                    }
                }
            }
        }
        else {
            if (y1 > y2) {
                for (size_t i = x1; i < x2; ++i) {
                    for (size_t j = y1; j > y2; --j) {
                        if (std::abs(j - (slope * (i - x1) + y1)) < 2) {
                            cs225::HSLAPixel& pixel = png.getPixel(x1, j);
                            pixel.l = black.l;
                        }
                    }
                }
            }
            else {
                for (size_t i = x1; i < x2; ++i) {
                    for (size_t j = y1; j < y2; ++j) {
                        if (std::abs(j - (slope * (i - x1) + y1)) < 2) {
                            cs225::HSLAPixel& pixel = png.getPixel(x1, j);
                            pixel.l = black.l;
                        }
                    }
                }
            }
        }*/
        
        if (x1 > x2) {
            double x = x2;
            //std::cout << x1 << " " << x2 << std::endl;
            while (x < x1) {
                int y = slope * (x - x1) + y1;
                cs225::HSLAPixel& pixel = png.getPixel(x, y);
                pixel.l = black.l;
                x+=10;
                //std::cout << x << std::endl;
            }
        }
        else {
            double x = x1;
            //std::cout << x1 << " " << x2 << std::endl;
            while (x < x2) {
                int y = slope * (x - x2) + y2;
                cs225::HSLAPixel& pixel = png.getPixel(x, y);
                pixel.l = black.l;
                x+=10;
                //std::cout << x << std::endl;
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
    //printf("%lu\n", V.size());
    double rot = 0;
    for (size_t i = 0; i < V.size(); ++i) {
        Node n;
        n.pos.x = .5 * width + .25 * width * cos(rot);
        n.pos.y = .5 * height + .25 * height * sin(rot);
        //std::cout << "Vertex: " << V[i] << ", Xpos: " << n.pos.x << ", Ypos: " << n.pos.y << std::endl;
        vnTable.insert(std::make_pair(V[i], n));
        rot += (2 * pi * dRad);
        //printf("rot: %f\n", rot);
    }

    
}

PositionVector GraphVisualizer::vectorPositionSubtration(const Node& a, const Node& b) {
    PositionVector d;
    d.x = a.pos.x - b.pos.x;
    d.y = a.pos.y - b.pos.y;
    return d;
}

double GraphVisualizer::positionVectorMagnitude(const PositionVector& a) {
    return sqrt((a.x * a.x) + (a.y * a.y));
}

double GraphVisualizer::displacementVectorMagnitude(const DisplacementVector& a) {
    return sqrt((a.x * a.x) + (a.y * a.y));
}