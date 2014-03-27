#include <ostream>
#include <vector>
#include <algorithm>
#include <map>

#ifndef _EDGE_
#define _EDGE_

/*
 * Edge class.
 */

enum class EdgeType {NONE, TK, TS, TSD, TC, TPH, BUS, V, B, R, N, KL, SURF};

using namespace std;

class Edge {
private:
	// Integer used to identify the edge.
	int id;
	// Name of the edge (not really used)
	string name;
	// Id of the vertex where the edge come from
	int src;
	// Id of the vertex where the edge goes to
	int dest;
	// Weight is used as a length to compute the shortest paths
	int weight;
	// Boolean used in the depth-first search algorithm to mark the edges while running through them
	bool explored;
	// Type of the edge (see the enumeration above)
	EdgeType type;
	
	// 3 static maps linking the edge types to their fixed time, their proportional time (for every 100 meters of slope), and a complete name used to display the type
	static map<EdgeType, int > defaultTime;
	static map<EdgeType, int > timePer100m;
	static map<EdgeType, string> toString;
	
public:
	// Constructor initializing the attributes
	Edge(int id, string name, int s, int d, int w, EdgeType et);
	
	/* Getters and setters */
	void setWeight(int w);
	int getWeight();
	int getSrc();
	int getDest();
	int getId();
	EdgeType getType();
	string getName();
	void setExplored(bool);
	bool isExplored();
	static map<EdgeType, string>& getToString();
	static int getDefaultTime(EdgeType et);
	static int getVariableTime(EdgeType et);
	
	// Check if an edge is connected (from the source or destination) to the vertex of id v
	bool isConnectedTo(int v);
	bool isConnectedToOneVertexOf(vector<int> vec);
	
	// Get the enum corresponding to the edge type sent as a string in parameter
	static EdgeType getEdgeTypeFromString(string str);
	
	/* Operator overloading */
	friend bool operator<(Edge a, Edge b);
	friend ostream& operator<<(ostream& os, Edge e);
	friend ostream& operator<<(ostream& os, EdgeType& et);
};

class CompareEdge {
public:
	bool operator()(Edge a, Edge b) {
		return a.getSrc() < b.getSrc();
	}
};

#endif