#include "shortestPath.hpp"

/* Constructors and destructors */
ShortestPath::ShortestPath(Graph& g) : g(g) {
	previousVertex = new int[g.V()];
	for(int i = 0; i < g.V(); ++i) {
		previousVertex[i] = -1;
	}
}

ShortestPath::~ShortestPath() {
	delete [] previousVertex;
}


/* Accessors */
vector<Vertex>* ShortestPath::vertices() {
	return g.getVertices();
}
Graph& ShortestPath::getGraph() {
	return g;
}
PriorityQueue<int> ShortestPath::getClosedSet() {
	return closedSet;
}
int ShortestPath::getDistanceOfVertex(int a) {
	int result = -1;
	result = closedSet.getPriorityOfVertex(a);
	if(result == -1)
		result = openSet.getPriorityOfVertex(a);
}


/*
 * Computations for the shortest path
 */
/* Compute the shortest path from a source vertex (u) to any other vertex and put them in the previousVertex array */
void ShortestPath::dijkstra(int u) {
	/* Clear the two sets for another computation */
	openSet.clear();
	closedSet.clear();
	
	/* initialize the distances at an impossible value */
	for(int i = 0; i < g.V(); ++i) {
		previousVertex[i] = -1;
	}
	/* insert the source vertex in the open set */
	openSet.insert(u, 0);
	while(openSet.size() > 0) {
		pair<int,int> p = openSet.top();
		openSet.minPriority();
		closedSet.insert(p);
		vector<int> listNeighbors = g.neighbors(p.first);
		/* Go through the neighbors of p */
		for(int i = 0; i < listNeighbors.size(); ++i) {
			/* Do not compute for the node itself or if it is already in the closedSet */
			if(listNeighbors[i] != p.first && !closedSet.contains(listNeighbors[i])) {
				if(openSet.contains(listNeighbors[i])) {
					/* if distance is grater than the sum of the distance of p and the edge cost between p and the current neighbor : update the value and the corresponding previousVertex */
					if(openSet.getPriorityOfVertex(listNeighbors[i]) > getDistanceOfVertex(p.first) + g.get_edge_value(p.first, listNeighbors[i])) {
						openSet.chgPriority(listNeighbors[i], getDistanceOfVertex(p.first) + g.get_edge_value(p.first, listNeighbors[i]));
						previousVertex[listNeighbors[i]] = p.first;
					}
				}
				else {	/* if the node is not in the open set, we just insert it */
					openSet.insert(listNeighbors[i], g.get_edge_value(p.first, listNeighbors[i]) + getDistanceOfVertex(p.first));
					previousVertex[listNeighbors[i]] = p.first;
				}
			}
		}
	}
	
}

/* Recover the shortest path from the previousVertex array and the closedSet */
forward_list<int> ShortestPath::path(int u, int w) {
	/* if the dijkstra compatution doesn't correspond to what we are looking for, we execute it */
	if(closedSet.size() == 0 || getDistanceOfVertex(u) != 0) {
		dijkstra(u);
	}
	forward_list<int> s;
	int target = w;
	while(previousVertex[target] != -1) {
		s.push_front(target);
		target = previousVertex[target];
	}
	s.push_front(u);
	return s;
}

/* Get the length of the shortest path */
int ShortestPath::path_size(int u, int w) {
	if(closedSet.size() == 0 || getDistanceOfVertex(u) != 0)
		dijkstra(u);
	return closedSet.getPriorityOfVertex(w);
}

/* Compute the average shortest path from the source vertex to any other vertex of the graph */
float ShortestPath::average_path(int source) {
	float average = 0;
	int count = 0;
	if(closedSet.size() == 0 || getDistanceOfVertex(source) != 0)
		dijkstra(source);
	for(int i = 0; i < closedSet.size(); ++i) {
		if(i != source && closedSet.getPriorityOfVertex(i) != -1) {
			average += closedSet.getPriorityOfVertex(i);
			++count;
		}
	}
	average /= count;
	return average;

}