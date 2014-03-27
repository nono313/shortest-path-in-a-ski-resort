#include "vertex.hpp"
#include "graph.hpp"
#include "priorityQueue.hpp"
#include <stack>
#include <forward_list>

#ifndef _SHORTEST_PATH_
#define _SHORTEST_PATH_

/*
 * Shortest path : implements Dijkstra's algorithm
 */
class ShortestPath {
private:
	// Reference to the graph g
	Graph& g;
	/* Two sets used for the Dijkstra's algorithm */
	PriorityQueue<int> openSet;
	PriorityQueue<int> closedSet;
	// Array containing for each element i, the previous vertex in the shortest path
	int* previousVertex;
	
public:
	/* Constructors and destructors */
	ShortestPath(Graph& g);
	~ShortestPath();
	
	/* Accessors */
	Graph& getGraph();
	vector<Vertex>* vertices();
	int getDistanceOfVertex(int a);
	PriorityQueue<int> getClosedSet();
	
	/*Compute the shortest path from a source vertex (u) to any other vertex and put them in the previousVertex array*/
	void dijkstra(int u);
	/* Recover the shortest path from the previousVertex array and the closedSet */
	forward_list<int> path(int u, int w);
	/* Get the length of the shortest path */
	int path_size(int u, int w);
	/* Compute the average shortest path from the source vertex to any other vertex of the graph */
	float average_path(int source);
};

#endif