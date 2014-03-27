#include "graph.hpp"
#include <stack>

#ifndef _VIEW_
#define _VIEW_

/*
 * View class used the display informations in the console
 */

class View {
public:
	// Print the content of a stack
	static void showStack(Graph& g, stack<int> stack);
	/* Show vertices in the path p */
	static void showPath(Graph& g, vector<int> p);
	static void showPath(Graph& g, forward_list<int> p);
	// Ask the user to choose a vertex
	static Vertex* askForVertex(Graph& g, string sentence);
	// Show the list of vertices of a graph
	static void showListOfVertices(Graph& g);
	// Show the vertices whose ids are in vec
	static void showListOfVertices(Graph& g, vector<int> vec);
	// Show the vertices stored in vec
	static void showListOfVertices(Graph& g, vector<Vertex>& vec);
	// Display the time (sent in seconds) in a better looking way with hours, minutes, and seconds
	static void printTime(int sec);
};

/* Operator overloaded */
ostream& operator<<(ostream& os, vector<vector<int> >& matrix);
ostream& operator<<(ostream& os, vector<int>& vec);
ostream& operator<<(ostream& os, stack<int>& s);

#endif