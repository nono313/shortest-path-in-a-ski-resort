#include "vertex.hpp"

/* Initialization of the static variable cout, used to generate the vertices' IDs */
int Vertex::count = 0;

/* 
 * Constructors and destructors 
 */

/* Constructor by default */
Vertex::Vertex(){
	id = count;
	count++;
	explored = 0;
}

/* Constructor with a name attribute for the lavel */
Vertex::Vertex(string name) : label(name){
	id = count;
	count++;
	explored = false;
}
Vertex::Vertex(string name, int alt) {
	id = count;
	label = name;
	altitude = alt;
	count++;
}
/* Destructor*/
Vertex::~Vertex() { }

/* 
 * Accessors 
 */
int Vertex::getId() {
	return id;
}
void Vertex::setExplored(bool b) {
	explored = b;
}
int Vertex::getAltitude() {
	return altitude;
}
string Vertex::getLabel() {
	return label;
}
bool Vertex::isExplored() {
	return explored;
}

/* 
 * Operator overloading 
 * operator<< : used to print either the label or the id of a vertex
 */
ostream& operator<<(ostream& os, Vertex v) {
	if(atoi(v.label.c_str()) == v.id+1)
		os << v.label;
	else
		os << v.label << " (" << (v.id+1) << ")";
	return os;
}