#include <cstdlib>
#include <list>
#include <algorithm>
#include <map>
#include <fstream>
#include <cmath>
#include "graph.hpp"

using namespace std; 

/* 
 * Constructors and destructors 
 */
Graph::Graph(string& fileName) {
	vertices = new vector<Vertex>();
	ifstream file(fileName.c_str());
	if(file.is_open()) {
		int number, altitude;
		string name;
		string temp;
		file >> size;
		matrix.resize(size);
		for(int i = 0; i < size; ++i) {
			matrix[i].resize(size);
			file >> number >> name >> altitude;
			vertices->push_back(Vertex(name, altitude));	
			for(int j = 0; j < size; ++j) {
				matrix[i][j] = 0;
			}
		}

		int nEdges, startPoint, endPoint;
		string type;
		file >> nEdges;
		for(int i = 0; i < nEdges; ++i) {
			file >> number >> name >> type >> startPoint >> endPoint;
			add(number, name, startPoint-1, endPoint-1, Edge::getEdgeTypeFromString(type));
		}
		sort(edges.begin(), edges.end(), CompareEdge());

	}
}
Graph::Graph(Graph& g, vector<EdgeType> filters) {
	vertices = g.vertices;
	size = g.size;
	matrix.resize(size);
	for(int i = 0; i < size; ++i) {
		matrix[i].resize(size);
		for(int j = 0; j < size; ++j) {
			matrix[i][j] = 0;
		}
	}
	
	for(auto e : g.edges) {
		if(find(filters.begin(), filters.end(), e.getType()) == filters.end()) {
			add(e.getId(), e.getName(), e.getSrc(), e.getDest(), e.getType());
		}
	}
}
Graph::~Graph() { 
	
}


/*
 * Accessors
 */

/* Get the number of vertices in the graph */
int Graph::V() {
	return size;
}

/* Get the number of edges in the graph */
int Graph::E() {
	int edges = 0;
	for(int i = 0; i < size; ++i) {
		for(int j = i+1; j < size; ++j) {
			if(matrix[i][j] != 0) {
				edges++;
			}
		}
	}
	return edges;
}

vector<Vertex>* Graph::getVertices() {
	return vertices;
}
vector<Edge>& Graph::getEdges() {
	return edges;
}

vector< vector<int> > Graph::getMatrix() {
	return matrix;
}

/* Return true if there is an edge between the 2 vertices a and b */
bool Graph::adjacent(int a, int b) {
	return (matrix[a][b] != 0);
}

/* return all neighbors of vertex a */
vector<int> Graph::neighbors(int a) {
	vector<int> neighB;
	for (int i = 0; i < size; ++i) {
		if(i != a && matrix[a][i] != 0) {
			neighB.push_back(i);
		}
	}
	return neighB;
}

/* add an edge */
void Graph::add(int id, string name, int a, int b, EdgeType edgeType) {
	int cost = 1;
	float diffAlt = 0;
	int fixedTime = 0;
	int variableTime = 0;
	if(edgeType != EdgeType::BUS) {
		diffAlt = abs(getVertex(a)->getAltitude() - getVertex(b)->getAltitude())/100.;
		fixedTime = Edge::getDefaultTime(edgeType);
		variableTime = Edge::getVariableTime(edgeType);
		cost = round(fixedTime + diffAlt * variableTime);
// 			cout << cost << endl;
	}
	else {
		string labelA = getVertex(a)->getLabel();
		string labelB = getVertex(b)->getLabel();
		if(labelA == "arc2000" && labelB == "arc1600" || (labelA == "arc1600" && labelB == "arc2000"))
			cost = 40*60;
		else if(labelA == "arc1600" && labelB == "arc1800" || (labelA == "arc1800" && labelB == "arc1600"))
			cost = 30*60;
	}
	edges.push_back(Edge(id, name, a, b, cost, edgeType));
	if(matrix[a][b] == 0 || matrix[a][b] > cost) {
		(*this)(a,b) = cost;
	}
}
/* Depth-first search */
void Graph::DFS(int indexV, vector<int>& q) {
	Vertex* current = getVertex(indexV);
	current->setExplored(true);
	Vertex* v = nullptr;
	if(find(q.begin(), q.end(), indexV ) == q.end()) {
		q.push_back(indexV);
		for(int tmp : neighbors(indexV)) {
			v = getVertex(tmp);
			if(!v->isExplored()) {
				this->DFS(v->getId(),q);
			}
		}
	}
}
/* Initialize every vertex as "unexplored" */
void Graph::initMarksAfterDFS(vector<int>& q) {
	for(auto temp : q) {
		getVertex(temp)->setExplored(false);
	}
}

/* remove the edge between vertices a and b */
void Graph::remove(int a, int b) {
	matrix[a][b] = matrix[b][a] = 0;
}

/* get the cost of the edge between x and y */
int Graph::get_edge_value(int x, int y) {
	return matrix[x][y];
}

/* change the cost of the edge between x and y */
void Graph::set_edge_value(int x, int y, int value) {
	matrix[x][y] = matrix[y][x] = value;
}

int Graph::getPathLength(vector<int>& path) {
	int total = 0;
	int prev;
	auto it = path.begin();
	if(it != path.end()) {
		prev = *it;
		it++;
		while(it != path.end()) {
			total += get_edge_value(prev, *it);
			prev = *it;
			it++;
		}
	}
	return total;
}
int Graph::getPathLength(forward_list<int>& path) {
	int total = 0;
	int prev;
	auto it = path.begin();
	if(it != path.end()) {
		prev = *it;
		it++;
		while(it != path.end()) {
			total += get_edge_value(prev, *it);
			prev = *it;
			it++;
		}
	}
	return total;
}

/*
 * Operator overloading
 */

ostream& operator<<(ostream& os, Graph& g) {
	for(int i = 0; i < g.V(); ++i) {
		for(int j = 0; j < g.V(); ++j) {
			os << g.getMatrix()[i][j] << " ";
		}
		os << endl;
	}
	return os;
}

Vertex* Graph::getVertex(int u) {
	Vertex* v = nullptr;
	if(u < vertices->size())
		v = &(*vertices)[u];
	return v;
}
Vertex* Graph::getVertex(string str) {
	Vertex* v = nullptr;
	auto it = vertices->begin();
	while(v == nullptr && it != vertices->end()) {
		if(it->getLabel() == str || atoi(str.c_str()) == (it->getId()+1))
			v = &(*it);
		it++;
	}
	return v;
}
Edge* Graph::getEdge(int a, int b) {
	Edge* e = nullptr;
	auto it = edges.begin();
	while(it != edges.end() && it->getSrc() != a && it->getDest() != b) {
		it++;
	}
	if(it != edges.end()) {
		e = &(*it);
	}
	return e;
}

Vertex Graph::operator[](int a) {
	return (*vertices)[a];
}
int& Graph::operator()(int a, int b) {
 	return matrix[getVertex(a)->getId()][getVertex(b)->getId()];
}
	
	