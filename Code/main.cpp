#include <iostream>
#include <vector>

#include "graph.h"
#include "edge.h"
#include "Network.h"
#include "BFS.h"
#include "dijkstraSSSP.h"
#include "landmark.h"
#include "graphvis.h"

int main() {
  //name of the file to read from (throws SIGABRT if cannot read i.e. path incorrect)
  std::string filename = "tests/Sample1.txt";
  std::cout << "File in use: " << filename << std::endl;

  // Initilization phase
  std::cout << "Calling Network Builder..." << std::endl;
  NetworkBuilder nb (filename);
  nb.constructGraph();
  const Graph& g = nb.getGraph();


  //Perform BFS Traversal on graph built above
  std::cout << "\nCalling BFS..." << std::endl;
  BFS bfs;
  bfs.traverse(g); //writes the order of the vertices visisted to .TXT file


  //Use Dijktra's Algorithm to compute the shortest path from a starting vertex to every other connected point in the graph
  std::cout << "\nCalling Dijkstra's Algorithm..." << std::endl;
  Vertex startingVertex = "14th_century";
  Vertex destination = "Africa";

  DijkstraSSSP sssp(g, startingVertex);
  sssp.calculateShortestPaths();
  sssp.pathToDestination(destination); //this function prints the path to console
  sssp.calculateCostToVertex(destination); //this function prints the cost of the path to console


  //Landmark algorithm to get from A to B and stop in C
  std::cout << "\nCalling Landmark Algorithm..." << std::endl;
  startingVertex = "14th_century";
  destination = "Africa";
  Vertex mark = "Atlantic_Ocean";

  Landmark lm(g, mark);
  lm.store_path(startingVertex, mark, destination);
  lm.printPath();


  //To create a graph visualization
  std::cout << "\nCalling Graph Visualizer..." << std::endl;
  GraphVisualizer gv(nb, 100, 100);
  gv.FruchtermanReingold(5);
  cs225::PNG png = gv.drawGraph(true);
  png.writeToFile("Output_Graph.png");
  return 0;
}