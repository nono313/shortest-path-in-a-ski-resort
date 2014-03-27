/*
 * PriorityQueue class : the first element that can be popped is the one with the smallest priority
 */

/*
 * Constructors and destructors
 */
template <class T>
PriorityQueue<T>::PriorityQueue() {
	
}
template <class T>
PriorityQueue<T>::~PriorityQueue() {
	
}


/* 
 * Accessors
 */
template <class T>
vector<pair<T,int> >& PriorityQueue<T>::getContent() {
	return pq;
}
template <class T>
void PriorityQueue<T>::chgPriority(T vertex, int priority) {
	for(int i = 0; i < pq.size(); ++i) {
		if(pq[i].first == vertex)
			pq[i].second = priority;
	}
	make_heap(pq.begin(), pq.end(), CompareDist<T>());
}
template <class T>
int PriorityQueue<T>::getPriorityOfVertex(T vertex) {
	int result = -1;
	for(int i = 0; i < pq.size(); ++i) {
		if(pq[i].first == vertex)
			result = pq[i].second;
	}
	return result;
}

/* = pop() : removes the top element of the queue.*/
template <class T>
void PriorityQueue<T>::minPriority() { 
	pop_heap(pq.begin(), pq.end(), CompareDist<T>());
	pq.pop_back();
}

/*does the queue contain queue_element*/
template <class T>
bool PriorityQueue<T>::contains(T vertex) { 
	bool b = false;
	for(int i = 0; i < pq.size(); ++i) {
		if(pq[i].first == vertex)
			b = true;
	}
	return b;
}

/*insert element into the queue*/
template <class T>
void PriorityQueue<T>::insert(T vertex, int priority) {  
	pair<T,int> p(vertex, priority);
	pq.push_back(p);
	push_heap(pq.begin(), pq.end(), CompareDist<T>());
}
template <class T>
void PriorityQueue<T>::insert(pair<T,int> p) {  
	pq.push_back(p);
	push_heap(pq.begin(), pq.end(), CompareDist<T>());
}

/* returns the top element of the queue (with the minimum priority / distance) */
template <class T>
pair<T,int> PriorityQueue<T>::top() { 
	return pq.front();
}

/*return the number of queue_elements.*/
template <class T>
int PriorityQueue<T>::size() { 
	return pq.size();
}

/* clear the priorityQueue by removing each elements */
template <class T>
void PriorityQueue<T>::clear() {
	while(pq.size() > 0) {
		minPriority();
	}
}


/*
 * Operator overloading
 */
template <class T>
pair<T, int> PriorityQueue<T>::operator[](int i) {
	return pq[i];
}

template <class T>
ostream& operator<<(ostream& os, PriorityQueue<T>& queue) {
	for(int i = 0; i < queue.size(); ++i) {
		os << queue[i].first << " : " << queue[i].second << endl;
	}
	return os;
}