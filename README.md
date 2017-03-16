# graphtraversal
A graph traversal algorithm using adjacency list.

Currently supports [Depth-first search](https://en.wikipedia.org/wiki/Depth-first_search).

Input is a text file named `matrix.txt` containing an [Adjacency Matrix](https://en.wikipedia.org/wiki/Adjacency_matrix).
The program converts the adjacency matrix to an [Adjacency List](https://en.wikipedia.org/wiki/Adjacency_list), then traverses the graph starting from a vertex, using DFS.

See: [Graph and its representations](http://www.geeksforgeeks.org/graph-and-its-representations/)

#### Make
`g++ Graph.cpp`

#### Sample Execution
```text
Adjacency Matrix:
0 1 0 0 1 
1 0 1 1 1 
0 1 0 1 0 
0 1 1 0 1 
1 1 0 1 0 
 
Adjacency List:
[0] -> 1 -> 4
[1] -> 0 -> 2 -> 3 -> 4
[2] -> 1 -> 3
[3] -> 1 -> 2 -> 4
[4] -> 0 -> 1 -> 3
 
Enter Start Vertex for DFS: 0
 
HEAD -> 0 -> 1 -> 2 -> 3 -> 4
```
