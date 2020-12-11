# ggc2-hzliao2-jpohov2-arjunr4

# Final Project

Welcome to our CS225 Final Project. We decided to use a wikipedia hyperlink network to create a graph where the vertices consists of all the articles and the edges connect any two articles that are connected via hyperlink. 
We wanted to accomplish four main goals based on our graph.

⋅⋅* Traverse each component and vertex in our graph using BFS
          

## Input File

By default our code is running on our full data set from http://snap.stanford.edu/data/#wikipedia. To use your own data set, you MUST have a properly formatted input text file. Each line in the file must contain strings seperated by ";" where the strings are the vertices and a ";" represents a connection between the previous string and the following string.

Example:

```bash
14th_century;Europe;Africa;Atlantic_slave_trade;African_slave_trade
```

This file will be used to construct our graph and can easily be storeds by modifying the following line to include the correct file path.

```bash
td::string filename = "file/path.txt"
```

## NetworkBuilder




