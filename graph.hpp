#include <iostream>
#include <vector>
#include <queue> 
#include <string>
#include <forward_list>
#include "edge.hpp"
#include "vertex.hpp"

#ifndef _GRAPH_
#define _GRAPH_

using namespace std;

class Graph {
private:
	int size;
	vector<Vertex>* vertices;
	vector<Edge> edges;
	vector< vector<int> > matrix;
	
public:
	/* Constructors and destructors */
	Graph(string&);
	Graph(Graph& g, vector<EdgeType> filters);
	~Graph();
	
	/* Accessors */
	int V();	/* Get the number of vertices in the graph */
	int E();	/* Get the number of edges in the graph */
	vector<Vertex>* getVertices();
	vector< vector<int> > getMatrix();
	vector< Edge >& getEdges();
	bool adjacent(int a, int b);	/* true if there is an edge between the 2 vertices a and b */
	vector<int> neighbors(int a);	/* return all neighbors of vertex a */
	vector<int> neighbors(int a, vector<EdgeType> filters);
	
	void add(int id, string name, int a, int b, EdgeType edgeType); /* add an edge */
	void remove(int a, int b); 	/* remove the edge between vertices a and b */
	int get_edge_value(int x, int y);	/* get the cost of the edge between x and y */
	void set_edge_value(int x, int y, int value);	/* change the cost of the edge between x and y */
	int getPathLength(vector<int>& path);
	int getPathLength(forward_list<int>& path);
	Vertex* getVertex(int u);
	Vertex* getVertex(string str);
	Edge* getEdge(int a, int b);
	void DFS(int indexV, vector<int>& q);
	void initMarksAfterDFS(vector<int>& q);
	
	/* Operator overloading */
	friend ostream& operator<<(ostream& os, Graph& g);
	Vertex operator[](int a);
	int& operator()(int a, int b);
};
	

#endif