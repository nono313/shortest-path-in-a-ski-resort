#include <array>
#include "graph.hpp"
#ifndef _FLOYD_WARSHALL_
#define _FLOYD_WARSHALL_

/*
 * Floyd Warshall's algorithm implementation of the shortest path problem
 */

class FloydWarshall {
private:
	// Reference to the graph g
	Graph& g;
	// 2D matrix containing the matrix used in the Floyd Warshall computation
	vector<vector<int> > matrix;
	// 2D matrix containing the next vertex in the shortest path (updated every time the computation matrix is changed)
	vector<vector<int> > next;
	
	// Give back the shortest path using the next matrix
	vector<int>* recursivePath(int i, int j);
	
public:
	// Constructor
	FloydWarshall(Graph &g);
	// Compute apply the Floyd Warshall's algorithm
	void compute();
	// Return the complete shortest path from i to j
	vector<int> getPath(int i, int j);
};

#endif