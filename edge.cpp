#include "edge.hpp"

/*
 * Edge class
 * (see comments in edge.hpp)
 */

 // Initialization of the datas regarding the names of the different tracks and the length of the tracks
map<EdgeType, int> Edge::defaultTime = {
	{EdgeType::TK, 60}, 
	{EdgeType::TS, 60}, 
	{EdgeType::TSD, 60}, 
	{EdgeType::TC, 2*60}, 
	{EdgeType::TPH, 4*60} };
map<EdgeType, int> Edge::timePer100m = {
	{EdgeType::TK, 4*60}, 
	{EdgeType::TS, 4*60}, 
	{EdgeType::TSD, 3*60}, 
	{EdgeType::TC, 3*60}, 
	{EdgeType::TPH, 2*60},
	{EdgeType::V, 5*60}, 
	{EdgeType::B, 4*60}, 
	{EdgeType::R, 3*60}, 
	{EdgeType::N, 2*60}, 
	{EdgeType::KL, 10}, 
	{EdgeType::SURF, 10*60} };
map<EdgeType, string> Edge::toString = {
	{EdgeType::TK , "TK (ski lift)"},
	{EdgeType::TS , "TS (chair lift)"},
	{EdgeType::TSD , "TSD (special chair lift)"},
	{EdgeType::TC , "TC (cabin)"},
	{EdgeType::TPH, "TPH (telepheric)"},
	{EdgeType::BUS , "BUS (shuttle bus)"},
	{EdgeType::V , "V (green piste)"},
	{EdgeType::B , "B (blue piste)"},
	{EdgeType::R , "R (red piste)"},
	{EdgeType::N , "N (black piste)"},
	{EdgeType::KL , "KL (track skiing)"},
	{EdgeType::SURF , "SURF (reserved for surfing)"} };

Edge::Edge(int id, string name, int s, int d, int w, EdgeType et) : id(id), name(name), src(s), dest(d), weight(w), explored(false), type(et) {
	
}
void Edge::setWeight(int w) {
	weight = w;
}
int Edge::getWeight() {
	return weight;
}
bool Edge::isConnectedTo(int v) {
	return (this->src == v || this->dest == v);
}
int Edge::getSrc() {
	return src;
}
int Edge::getDest() {
	return dest;
}
int Edge::getId() {
	return id;
}
string Edge::getName() {
	return name;
}
EdgeType Edge::getType() {
	return type;
}
void Edge::setExplored(bool b) {
	explored = b;
}
bool Edge::isExplored() {
	return explored;
}

bool operator<(Edge a, Edge b) {
	return a.weight < b.weight;
}
ostream& operator<<(ostream& os, Edge e) {
	os << e.id << " : (" << e.src << "," << e.dest << " : " << e.weight << ")";
	return os;
}

EdgeType Edge::getEdgeTypeFromString(string str) {
	if(str == "TK")
		return EdgeType::TK;
	else if(str == "TS")
		return EdgeType::TS;
	else if(str == "TSD")
		return EdgeType::TSD;
	else if(str == "TC")
		return EdgeType::TC;
	else if(str == "TPH")
		return EdgeType::TPH;
	else if(str == "BUS")
		return EdgeType::BUS;
	else if(str == "V")
		return EdgeType::V;
	else if(str == "B")
		return EdgeType::B;
	else if(str == "R")
		return EdgeType::R;
	else if(str == "N")
		return EdgeType::N;
	else if(str == "KL")
		return EdgeType::KL;
	else if(str == "SURF")
		return EdgeType::SURF;
	else
		return EdgeType::NONE;
}

ostream& operator<<(ostream& os, EdgeType& et) {
	os << Edge::toString[et];
	return os;
}

map<EdgeType, string>& Edge::getToString() {
	return Edge::toString;
}

int Edge::getDefaultTime(EdgeType et) {
	return defaultTime.find(et)->second;
}
int Edge::getVariableTime(EdgeType et) {
	return timePer100m.find(et)->second;
}

