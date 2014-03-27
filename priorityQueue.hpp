#include <vector>
#include <queue>
#include <iostream>

using namespace std;

#ifndef _PRIORITY_QUEUE_
#define _PRIORITY_QUEUE_

/*
 * PriorityQueue class : the first element that can be popped is the one with the smallest priority
 */

template <class T>
class PriorityQueue {
private:
	// The queue is represented as a vector of pairs element-priority
	vector<pair<T,int> > pq;
	
public:
	/* Constructors and destructors */
	PriorityQueue();
	~PriorityQueue();
	
	/* Accessors */
	vector<pair<T,int> >& getContent();
	int size();
	void chgPriority(T vertex, int priority);
	void minPriority();	/* remove the top element */
	bool contains(T vertex);
	void insert(T vertex, int priority);
	void insert(pair<T,int> p);
	pair<T,int> top();	/* leave in on the top ! */
	int getPriorityOfVertex(T a);
	void clear();	/* clear the priorityQueue by removing each elements */
	
	/* Operator overloading */
	pair<T, int> operator[](int i);
	template <class Te>
	friend ostream& operator<<(ostream& os, PriorityQueue<Te>& queue);
};

/* 
 * Compare the elements of the PriorityQueue 
 * used to put the vertex with the minimum distance at the top
 */
template <class T>
class CompareDist {
public:
	bool operator()(pair<T,int>& a, pair<T,int>& b) {
		return a.second > b.second;
	}
};

#include "priorityQueue.tpp"

#endif