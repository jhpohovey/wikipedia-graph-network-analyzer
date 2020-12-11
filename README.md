# ggc2-hzliao2-jpohov2-arjunr4

# Final Project

Welcome to our CS225 Final Project. We decided to use a wikipedia hyperlink network to create a graph where the vertices consists of all the articles and the edges connect any two articles that are connected via hyperlink. 
We wanted to accomplish four main goals based on our graph.

1. Traverse each component and vertex in our graph using BFS
2. Implement Dijskta’s shortest path algorithm on our graph with set weights to determine the path between two vertices with the lowest combined edge weights
3. Use the landmark path algorithm to determine the least number of connections for a path between two nodes through any intermediate node.

4. Create a visual output that is visually appealing and also informational using the vertices and edges in our graph

          

## Input File

By default our code is running on our full data set from http://snap.stanford.edu/data/#wikipedia. To use your own data set, you MUST have a properly formatted input text file. Each line in the file must contain strings seperated by ";" where the strings are the vertices and a ";" represents a connection between the previous string and the following string.

__Example:__

```bash
14th_century;Europe;Africa;Atlantic_slave_trade;African_slave_trade
```
The file can contain any number of lines (as memory will allow
)
This file will be used to construct our graph and can easily be stored by modifying the following line to include the correct file path.

```bash
std::string filename = "file/path.txt"
```

## NetworkBuilder

Constructs network graph based on input file. Using the following lines you must create the NetworkBuilder object which stores the data. Then to construct the graph you must call __constructGraph()__. Calling this function also populates a frequency map, which records the amount of occurences of each specific topic read from the file. To access the graph we recommend storing the graph as a constant reference.

```bash
NetworkBuilder nb (filename);   //stores data
nb.constructGraph();            //creates graph
const Graph& g = nb.getGraph(); //returns a reference to the graph
```

## DijkstraSSSP
Determines the shortest (and/or lowest weight) path from a starting vertex to every other connected vertex in the graph. Edge weights are determined by choosing the lesser of the two lengths of two vertices connected by that edge.

You can create an object of the DijkstraSSSP class by passing in the graph reference created above, as well as a starting vertex. You can change the starting vertex by modifying the variable name. Make sure that the start vertex you choose is a part of the data set. Once an Dijkstra object has been constructed, the shortest path from this start vertex to all other connected vertices can be found by using __calculateShortestPaths()__. This function returns a graph object that will contain all the vertices as before, but will only include the edges that are necessary for providing the shortest paths to all of the vertices. If you would like to see a specific path from the start vertex to a destination vertex of your choosing, simply run __pathToDestination(destination)__. If you would like to see the cost of shortest path from the start vertex to a destination, simply run __calculateCostToVertex(destination)__. Both of these functions print to console. Below is an example code block you can run in order to use the DijkstraSSSP class.

```bash
Vertex startingVertex = "14th_century"; // starting vertex
Vertex destination = "Africa";          // destination vertex

DijkstraSSSP sssp(g, startingVertex);   // initializes a Dijkstra-type object
sssp.calculateShortestPaths();          // creates graph with shortest paths to all connected vertices from starting vertex
sssp.pathToDestination(destination);    // prints a specific  path to console
sssp.calculateCostToVertex(destination);// prints the cost of a specific path to console
```

## Landmark
Determine the least number of connections for a path between two nodes through any intermediate node.


Create the object using the reference to our graph and the given intermediate "landmark" node in path. Store the path using __store_path(startingVertex, mark, destination)__. You can modify these input vertices by changing their previous declaration. Make sure all inputs are actually part of the data set (no typos). The startingVertex and destination are allowed to be the same but they __CANNOT__ be the same as the landmark. Call __printPath()__ to print out any valid path and its length (number of edgest travelled).

```bash
startingVertex = "14th_century";    //starting vertex
destination = "Africa";             //destination vertex
Vertex landmark = "Atlantic_Ocean";     //landmark(intermediate) vertex

Landmark lm(g, landmark);                                //creates path between vertices
lm.store_path(startingVertex, landmark, destination);   //stores any valid path
lm.printPath();                                         //prints based on what has been stored
```

## Graph Visualizer
Implements the Fruchterman-Reingold Algorithm, an algorithm for force directed graphs. Once the algorithm is complete, the resulting graph is projected onto a PNG for visualizing.

Create an GraphVisualizer object by passing a reference to the NetworkBuilder, which was previously constructed. Using a NetworkBuilder object as the parameter allows access to both the base graph, as well as the frequency map storing the number of occurences of each topic in the data. This frequency map is used to determine the relative sizes of vertices projected onto the PNG. The other two parameters of the constructor are __width__ and __height__. These two parameters constitute the width and height of the PNG (for the full data set, I recommend a 10,000 x 10,000 PNG, and smaller dimensions for smaller data sets). Once an object has been constructed, you can run __FruchtermanReingold(iterations)__, where the __iterations__ parameter controls how many times new displacements are calculated based on attractive and repulsive forces between vertices. A lower number will yield a quicker runtime (i.e. use __iterations = 3__). Upon the completion of this function, the final resting positions of all vertices have been calculated, and are now ready for visualization. To project the computed graph, simply use __drawGraph(shape)__. This function returns a PNG-type object. The parameter __shape__ is a __boolean__ type; when __shape = true__, the graph will be rendered with all vertices being represented by circles. When __shape = false__, all vertices will be represented by squares. The last step is to run __png.writeToFile("name.png")__. This will save the PNG to a whatever filename you choose in order to view the computed graph.

```bash
GraphVisualizer gv(nb, PNG_width, PNG_height);   // Initializes a graph visualizer object; make sure choose appropriate dimensions for size of data set
gv.FruchtermanReingold(iterations);             // computes force directed gragh
cs225::PNG png = gv.drawGraph(true);            // draws the computed graph onto a PNG; choose true for circle representation of vertices, false for square
png.writeToFile("Output_Graph.png");            // writes the png to file
```