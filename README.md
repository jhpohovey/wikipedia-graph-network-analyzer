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

Example:

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

Constructs network graph based on input file. Using the following lines you must create the NetworkBuilder object which stores the data. Then to construct the graph you must call __constructGraph()__. To access the graph we recommend storing the graph as a constant reference.

```bash
NetworkBuilder nb (filename);   //stores data
nb.constructGraph();            //creates graph
const Graph& g = nb.getGraph(); //returns a reference to the graph
```
## Landmark
Determine the least number of connections for a path between two nodes through any intermediate node.


Create the object using the reference to our graph and the given intermediate "landmark" node in path. Store the path using __store_path(startingVertex, mark, destination)__. You can modify those input vertices by changing their previous declaration. Make sure all inputs are actually part of the data set. The startingVertex and destination are allowed to be the same but they __CANNOT__ be the same as the mark. Call __printPath()__ to print out any valid path and its length (number of edgest travelled).

```bash
startingVertex = "14th_century";    //starting vertex
destination = "Africa";             //destination vertex
Vertex mark = "Atlantic_Ocean";     //landmark(intermediat) vertex

Landmark lm(g, mark);                                   //creates path between vertices
lm.store_path(startingVertex, mark, destination);       //stores any valid path
lm.printPath();                                         //prints based on what has been stored
```

