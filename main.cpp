#include <cstdlib>
#include "graph.hpp"
#include "floydWarshall.hpp"
#include "shortestPath.hpp" 
#include "view.hpp"

using namespace std;

/*
 * The (console) user interface is managed here in the main function.
 * See subject and report for more informations about the possibilities.
 * 
 * Nathan Olff (nathan.olff@utbm.fr)
 */
int main(int argc, char** argv) {
	string fileName("dataski.txt");
	Graph g(fileName);
	Graph* gMin = nullptr;
	FloydWarshall fw(g);
	
	int choice = 0;
	string str;
	vector<EdgeType> filters;
	do {
		system("clear");
		cout << "======== Ski resort ========" << endl;
		cout << endl << "---- Menu ----" << endl;
		if(filters.size() == 0) {
			cout << endl;
			cout << "1. Show every places available on the skiing area." << endl;
			cout << "2. Display the shortest path between two places." << endl;
			cout << "3. Apply route restrictions on the map." << endl;
		}
		else {
			gMin = new Graph(g, filters);
			cout << "without taking the pistes of type :\n\t\t";
			for(auto& et : filters) {
				cout << Edge::getToString()[et] << "\t";
			}
			cout << endl << endl;
			cout << "1. Print the list of accessible places from a place." << endl;
			cout << "2. Display the shortest path between two places." << endl;
			cout << "3. Remove the restrictions." << endl;
		}
		cout << "0. Exit the program." << endl;
		cout << "What to do want to do ?" << endl;
		cin >> choice;
		int total;
		Vertex* src = nullptr;
		Vertex* dest = nullptr;
		vector<int> vectorP;
		forward_list<int> fList;
		if(filters.size() == 0) {
			switch(choice) {
				case 1:
					View::showListOfVertices(g);
					break;
				case 2:
					src = View::askForVertex(g, "Where are you ?");
					dest = View::askForVertex(g, "Where do you want to go ?");
					cout << "The shortest path from " << *src << " to " << *dest << " is : " << endl;
					vectorP = fw.getPath(src->getId(), dest->getId());
					total = g.getPathLength(vectorP);
					cout << '\t';
					View::showPath(g, vectorP);
					cout << "It would take " << endl << '\t';
					View::printTime(total);
					break;
				case 3:
					cout << "---- Types of route ----" << endl;
					auto it = Edge::getToString().begin();
					int i = 0;
					while(it != Edge::getToString().end()) {
						cout << it->second << endl;
						it++;
					}
					cout << endl << "Which types of route do you NOT want to use ?" << endl;
					cout << "\tSeperate types by whitespace or new line and then type an incorrect type to end the input." << endl;
					EdgeType et;
					while(cin >> str && (et = Edge::getEdgeTypeFromString(str)) != EdgeType::NONE && str != ";") {
						filters.push_back(et);
					}
					break;
			}
		}
		else {
			switch(choice) {
				case 1:
					src = View::askForVertex(*gMin, "Where are you ?");
					vectorP.clear();
					gMin->DFS(src->getId(), vectorP);
					gMin->initMarksAfterDFS(vectorP);
					vectorP.erase(vectorP.begin());
					if(vectorP.empty()) {
						cout << "You can't go anywhere with the selected restrictions." << endl;
					}
					else {
						cout << "You can go to : " << endl;
						sort(vectorP.begin(), vectorP.end());
						View::showListOfVertices(*gMin, vectorP);
					}
					break;
				case 2:
				{
					src = View::askForVertex(*gMin, "Where are you ? ");
					dest = View::askForVertex(*gMin, "Where do you want to go ? ");
					ShortestPath sp(*gMin);
					fList = sp.path(src->getId(), dest->getId());
					if(++(fList.begin()) == fList.end()) {
						cout << "There is no path between " << *src << " and " << *dest << " with the selected restrictions." << endl;
					}
					else {
						total = gMin->getPathLength(fList);
						cout << '\t';
						View::showPath(*gMin, fList);
						cout << "It would take " << endl << '\t';
						View::printTime(total);
					}
					cout << endl;
					break;
				}
				case 3:
					filters.clear();
					break;
			}
					
		}
		if(choice != 0) {
			cout << endl << "Appuyer sur une touche pour continuer...";
			cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
			getchar();
		}
	} while(choice != 0); 
	
		
		
		

	return 0;
}