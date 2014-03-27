#include <iostream>
#include <string>

#ifndef _VERTEX_
#define _VERTEX_

/*
 * Vertex class
 */

using namespace std;

class Vertex {
private:
	// Number of total vertices in the graph
	static int count;
	// Identifier of the vertex
	int id;
	// Altitude of the vertex (the ski station) in meters
	int altitude;
	// Boolean used for traversal algorithms
	bool explored;
	// Name of the vertex (when no specific name is given, the id is used)
	string label;
	
public:
	/* Constructors and destructors */
	Vertex();
	Vertex(string name);
	Vertex(string name, int altitude);
	~Vertex();
	
	/* Accessors */
	int getId();
	void setExplored(bool b);
	string getLabel();
	bool isExplored();
	int getAltitude();
	
	/* Operator overloading */
	friend ostream& operator<<(ostream& os, Vertex v);
};

#endif

