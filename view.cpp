#include <iomanip>
#include "view.hpp"

/*
 * View class used the display informations in the console
 */

/* Display function used to print the shortest path from the stack */
void View::showStack(Graph& g, stack<int> s) {
	while(s.size() > 1) {
		cout << g[s.top()] << " => ";
		
		s.pop();
	}
	cout << g[s.top()] << endl;;
	s.pop();
}

ostream& operator<<(ostream& os, vector<vector<int> >& matrix) {
	int size = matrix.size();
	for(int i = 0; i < size; ++i) {
		for(int j = 0; j < size; ++j) {
			os << matrix[i][j] << " ";
		}
		os << endl;
	}
	return os;
}

ostream& operator<<(ostream& os, vector<int>& vec) {
	for(auto &a : vec) {
		os << a << " ";
	}
	return os;
}


ostream& operator<<(ostream& os, stack<int>& s) {
	while(s.size() > 1) {
		os << s.top() << " => ";
		s.pop();
	}
	os << s.top() << endl;
	s.pop();
	return os;
}

void View::showPath(Graph& g, vector<int> p) {
	auto it = p.begin();
	while(it != p.end()) {
		cout << g[*it];
		it++;
		if(it != p.end())
			cout <<  " => ";
	}
	cout << endl;
}
void View::showPath(Graph& g, forward_list<int> p) {
	auto it = p.begin();
	while(it != p.end()) {
		cout << g[*it];
		it++;
		if(it != p.end())
			cout <<  " => ";
	}
	cout << endl;
// 	cout << g[p.size()-1] << endl;;
}
void View::showListOfVertices(Graph& g) {
	View::showListOfVertices(g, *(g.getVertices()));
}
void View::showListOfVertices(Graph& g, vector<int> vec) {
	vector<Vertex> vec2;
	for(auto& v : vec) {
		vec2.push_back(*(g.getVertex(v)));
	}
	View::showListOfVertices(g, vec2);
}
void View::showListOfVertices(Graph& g, vector<Vertex>& vec) {
	int i = 0;
	auto it = vec.begin();
	cout << "--- List of places ---";
	while(it != vec.end()) {
		if(i%4 == 0)
			cout << endl;
		i++;
		cout << *it << '\t';
		if(it->getLabel().length() < 9-4)
			cout << "\t";
		if(it->getLabel().length() < 18-4)
			cout << "\t";
		if(it->getLabel().length() < 9*3-4)
			cout << "\t";
		it++;
	}
	cout << endl;
	
}

Vertex* View::askForVertex(Graph& g, string sentence) {
	string str;
	cout << sentence;
	cin >> str;
	Vertex* src = g.getVertex(str);
	while(src == nullptr) {
		cout << "This place doesn't exists. Please choose between these places : " << endl;
		showListOfVertices(g);
		cout << sentence;
		cin >> str;
		src = g.getVertex(str);
	}
	return src;
}

void View::printTime(int sec) {
	int h,m,s;
	h = sec/3600;
	m = (sec%3600)/60;
	s = sec%60;
// 	if(sec >= 3600) {
// 		cout << setw(2) << std::setfill('0') << h <<":";
// 	}
// 	cout  << setw(2) << std::setfill('0') << m << ":" << setw(2) << std::setfill('0') << s;
		
	if(h > 0) {
		cout << h << " hour";
		if(h > 1)
			cout << 's';
	}
	if(m > 0) {
		if(h > 0) {
			if(s > 0)
				cout << ", ";
			else
				cout << " and ";
		}
		cout << m << " minute";
		if(m > 1)
			cout << 's';
	}
	if(s > 0) {
		if(sec >= 60)
			cout << " and ";
		cout << s << " second";
		if(s > 1)
			cout << 's';
	}
	cout << " ( = " << sec << " seconds )";
}