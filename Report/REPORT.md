CS 225 Final Project Report
John Pohovey, Arjun Ray, Girish Chinnadurai, Harrison Liao

The very first outcome of our project was a conversion of data in a .TXT file into storage of vector containers for later construction and processing. Once the file has been parsed and data 
stored in our 2-D structure, we construct an instance of a graph object, which models the data read in from the text file, as well as a frequency map for use in the graphical output phase. 
All of the following algorithms all used this preliminary outcome that is a graph in order to compute various outcomes, from traversals to searches to pictures.	In the creation of the 
Breadth First Search traversal algorithm, we found that in a very high level understanding, the traversal is meant to label the edges between each vertex. We chose this method rather than 
the DFS traversal as the data set we chose is more wide than deep. After you create a graph from the data set, the outcome of the BFS algorithm was a graph with its edges labeled as 
“DISCOVERY” if the vertex reaches an unvisited vertex or “CROSS” if the edge goes from a visited vertex to another visited vertex. The outcome of the algorithm also can differ for the same 
graph to a degree as it picks the starting vertex at random. It also picks the adjacent vertices to visit at random so there could be different edge labels for the same graph. This is in 
part due to the randomness stated above, but also that the BFS can’t choose an adjacent vertex in a specific order. We didn’t make any new discoveries with the BFS traversal as the 
algorithm did exactly what we expected it to.

After the construction of the graph object from parsing the data, the outcome of running Dijkstra’s Single Source Shortest Path Algorithm is another graph with all the vertices that the 
originally graph had, but only includes the edges that are necessary to enable the shortest path between the starting vertex and that desired destination vertex. Other outcomes of this 
algorithm are getting specific paths from the starting vertex to whatever your destination vertex is, which are printed to the console. Similarly, another outcome is the ability to ask for 
the cost of any specific path between the start vertex and any destination vertex. After implementing Dijkstra’s Algorithm, I spent some time playing around with it on our full data set, 
and seeing what types of paths I might get. Interestingly enough, more often than not the path length from start to finish, that is the amount of vertices that the path included, was always 
very low, usually no more than 4. It was very interesting to see such a high level of connectivity between seemingly completely unrelated terms. For example, in order to go from Batman to 
Africa, the path is just Batman -> Bat -> Cave -> Africa, which for two terms that seem so completely random to each other, are really remarkably related.

Another algorithm dealing with vertices and connectivity is the landmark path algorithm. This algorithm determines the minimum distance in terms of number of connections between a beginning 
and end vertex through a landmark vertex. It stores a spanning tree from the landmark vertex to determine the path between vertices. To keep track of the path we are using an ordered map to 
store the predecessors of the vertices that get visited. This algorithm only works on vertices that are connected to each other and only works as long as the landmark vertex is not the same 
as the beginning or the end. Using the spanning tree we construct a vector that contains the vertices in the correct order starting from the beginning, passing through the landmark, and 
finishing at the destination. After the running algorithm, if there is a valid path through these nodes, it is stored in the and can be printed. If any of the vertex is not connected to any 
of the other ones, no path is stored. After many trial runs, it was hard to find vertices through which a path didn’t exist. We concluded the graph was very well connected with few disjoint 
components. I also noticed that many of the paths ended up passing through countries.

The GraphVisualizer class has the most obvious outcome in this project. After constructing the graph from parsing the data file, the outcome of the Fruchterman-Reingold Algorithm is a force 
directed graph on a PNG. The colors of each vertex  are randomly chosen out of a vector of HSLAPixels. The diameter of each vertex is determined by its frequency in the data file, meaning 
that topics that occur more in the data file are larger. The other part of the graphical output is connecting all vertices to each other. In the full data set, there are approximately 120000 edges for the 4000 vertices that exist, so when rendered onto the PNG, it looks very much like an intricate web rather than simply a couple connections of similar ideas. What was really cool to see was the vast interconnections that exist within our data set and by extent, really just all information in general, as wikipedia is branded as the hub of all human knowledge. Secondly, it was really interesting to see how the frequency of some topics just blows up (admittedly, some vertices have such high frequency that I had to add some size growth restrictions when calculating the frequencies). But to see that topics such as continents, oceans, and prominent countries are so commonly referenced by so many seemingly unrelated terms is quite interesting.

