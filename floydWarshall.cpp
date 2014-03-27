#include <limits>
#include "floydWarshall.hpp"
#include "view.hpp"

/*
 * Floyd Warshall's algorithm implementation of the shortest path problem
 */

FloydWarshall::FloydWarshall(Graph &g) : g(g){
	matrix = g.getMatrix();
	next.resize(g.V());
	for(int i = 0; i < g.V(); ++i) {
		next[i].resize(g.V());
		for(int j = 0; j < g.V(); ++j) {
			next[i][j] = -1;
			if(matrix[i][j] == 0 && i != j) {
				matrix[i][j] = numeric_limits<int>::max()/2;
			}
		}
	}
	compute();
}

void FloydWarshall::compute() {
	for(int k = 0; k < g.V(); ++k) {
		for(int i = 0; i < g.V(); ++i) {
			for(int j = 0; j < g.V(); ++j) {
				if(matrix[i][k] + matrix[k][j] < matrix[i][j]) {
					matrix[i][j] = matrix[i][k] + matrix[k][j];
					next[i][j] = k;
				}
			}
		}
	}
}

vector<int>* FloydWarshall::recursivePath(int i, int j) {
	vector<int>* path = nullptr;
	if(matrix[i][j] != -1) {
		int intermediate = next[i][j];
		if(intermediate == -1) {
			path = new vector<int>();
		}
		else {
			path = new vector<int>();
			vector<int>* prev = recursivePath(i, intermediate);
			vector<int>* forward = recursivePath(intermediate, j);

			path->insert(path->begin(), prev->begin(), prev->end());
			path->push_back(intermediate);
			path->insert(path->end(), forward->begin(), forward->end());
			delete prev;
			delete forward;
		}
	}
	return path;
}
vector<int> FloydWarshall::getPath(int i, int j) {
	vector<int> finalPath;
	vector<int>* p = recursivePath(i,j);
	if(p == nullptr) {
		cout << "IMPOSSIBLE";
	}
	else {
		finalPath.push_back(i);
		finalPath.insert(finalPath.end(), p->begin(), p->end());
		finalPath.push_back(j);
		delete p;
	}
	return finalPath;
}
