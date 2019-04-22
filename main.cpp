#include <iostream>
#include <queue>
using namespace std;


template <class DT>
class LinkedList{
private:
	DT* _info;
	LinkedList<DT>* _next;
public:
	LinkedList();
	LinkedList(DT& M);
	LinkedList(DT& M, LinkedList<DT>* next);
	~LinkedList();

	DT& info(); // return this _info
	LinkedList<DT>* next(); // return this _next
	bool isEmpty(); // return if this is empty
	void add(DT& M); // adds object to beginning of list
	LinkedList<DT>* setNext(LinkedList<DT>* M); // sets this _next = M, returns the previous value of _next
	void insertAt(DT& M, int pos); // inserts M into the specified position
	DT& infoAt(int pos); // returns the object at the specified position
	DT& remove(); // removes and returns the first link in the linked list
	DT& removeAt(int pos); // removes the link at the specified position
	int size(); // return the size of this linked list
	DT& operator[](int pos); // returns the object at the specified position

	void setNext(LinkedList<DT>& M);

};

class Graph{
protected:
	int _size;

public:
	virtual void addEdge(int a, int b);
	int size(){ return _size; };
	virtual int* getNeighbors(int node){ return new int(0); };
	~Graph(){};
};

class AdjMatrix: public Graph {
protected:
	int _size;
	int** _myMatrix;

public:
	AdjMatrix();
	AdjMatrix(int size);
	AdjMatrix(AdjMatrix& M);
	~AdjMatrix();
	int size();
	void addEdge(int a, int b);
	AdjMatrix& operator=(const AdjMatrix& M);
	int* getNeighbors(int node);

};

class AdjList: public Graph {
protected:
	int _size;
	LinkedList<int>** _myList;

public:
	AdjList();
	AdjList(int size);
	AdjList(AdjList& M);
	~AdjList();
	int size();
	void addEdge(int a, int b);
	AdjList& operator=(const AdjList& M);
	int* getNeighbors(int node);

};

int Graph::size(){
	return _size;
}
Graph::~Graph(){

}
///////  Linked List implementations


template <class DT>
LinkedList<DT>::LinkedList(){
	_info = NULL;
	_next = NULL;
}
template <class DT>
LinkedList<DT>::LinkedList(DT& M){
	_info = new DT(M);
	_next = NULL;
}
template <class DT>
LinkedList<DT>::LinkedList(DT& M, LinkedList<DT>* next){
	_info = new DT(M);
	_next = next;
}
template <class DT>
LinkedList<DT>::~LinkedList(){
	if(_info != NULL){  // deletes the contents of this box
		delete _info;
		_info = NULL;
	}
	if(_next != NULL){
		delete _next; // and now to delete the next box if _next != NULL
		_next = NULL;
	}
}
template <class DT>
DT& LinkedList<DT>::info(){
	return (*_info);
}
template <class DT>
LinkedList<DT>* LinkedList<DT>::next(){
	return _next;
}
template <class DT>
bool LinkedList<DT>::isEmpty(){
	return _info == NULL;
}
template <class DT>
int LinkedList<DT>::size(){
	// recursive method
	if(_info == NULL){           // if this link doesn't exist, return 0
		return 0;
	} else if(_next == NULL){    // if this link does exist but _next doesn't, return 1
		return 1;
	} else {
		return 1 + (*_next).size();  // if this link exists, and _next also, return 1 + ~~~
	}
}
template <class DT>
void LinkedList<DT>::add(DT& M){

	// make sure M is not on the stack, but on the heap or M will be deleted from the LL
	// after the stack is done with

	if (_info == NULL){
		_info = &M; // if this link does not exist (starting the list), add first link M
		_next = NULL; // set ptr to next link to NULL

	} else { // if this link does exist
		// create a copy of this link
		LinkedList<DT>* temp = new LinkedList((*_info), _next);
		_info = &M; // set this link's info to the new info
		_next = temp; // set this links next to point to temp
	}

}
template <class DT>
void LinkedList<DT>::insertAt(DT& M, int pos){

	if(pos == 0){  // base case
		add(M);    // add DT x at this link

	} else {

		if(_next == NULL){
			_next = new LinkedList(M, NULL);

		} else {
			(*_next).insertAt(M, pos-1); // recursively find where to insert x
		}

	}
}
template <class DT>
DT& LinkedList<DT>::remove(){

	DT* copyOf;


	if(_info != NULL){ // if this link does exist
		copyOf = _info;
		///delete _info;  // delete this current link info // delete
		_info = NULL;


		if(_next != NULL){   // if _next link does exist
			LinkedList<DT>* temp = _next; // create a temp link ptr to the next link
			_info = &(*temp).info(); // this link info is next links info
			_next = (*temp).next(); // this link next is next links next

			(*temp)._info = NULL; // use temp link ptr to delete next link
			(*temp)._next = NULL; // now this link has next link data and next link is deleted
			delete temp;
		}

	// return copy of _info, else NULL
	return *copyOf;

	} else{ // if this link does not exist

		copyOf = new DT();
		return *copyOf; // no idea what happens here, can't return NULL, find out later
	}
}
template <class DT>
DT& LinkedList<DT>::removeAt(int pos){

	if(pos == 0){
		return remove();
	} else {
		return (*_next).removeAt(pos-1);
	}


}
template <class DT>
DT& LinkedList<DT>::infoAt(int pos){

	if(pos == 0){
		return (*_info);
	} else{
		return (*_next).infoAt(pos -1);
	}

}
template <class DT>
DT& LinkedList<DT>::operator[](int pos){
	return infoAt(pos);
}


/////// AdjMatrix Implementations


AdjMatrix::AdjMatrix(){
	// default constructor, set matrix to 10x10 and size=10
	_myMatrix = new int*[10];
	for(int i = 0; i < 10; ++i){
		_myMatrix[i] = new int[10];
	}
	_size = 10;
}
AdjMatrix::AdjMatrix(int size){
	// constuctor with variable size, set matrix to be sizeXsize and size field to size param
	_myMatrix = new int*[size];
	for(int i = 0; i < size; ++i){
		_myMatrix[i] = new int[size];
	}
	_size = size;

	// set all values in the matrix to
	for(int i = 0; i < _size; ++i){
		for(int j = 0; j < _size; ++j){
			_myMatrix[i][j] = 0;
		}
	}
}
AdjMatrix::AdjMatrix(AdjMatrix& M){
	// copy constructor, after transfering size var and creating this matrix using size
	// transfer contents of matrix in M to this matrix
	_size = M._size;
	_myMatrix = new int*[_size];
	for(int i = 0; i < _size; ++i){
		_myMatrix[i] = new int[_size];
	}

	// transfer the data
	for(int i = 0; i < _size; ++i){
		for(int j = 0; j < _size; ++j){
			_myMatrix[i][j] = M._myMatrix[i][j];
		}
	}
}
AdjMatrix::~AdjMatrix(){
	//destructor

	// delete all sub arrays, then delete myMatrix array
	for(int i = 0; i < _size; ++i){
		delete[] _myMatrix[i];
	}

	delete[] _myMatrix;
}
void AdjMatrix::addEdge(int a, int b){
	// add an edge to this graph
	// the edge is represented as a connection between the two nodes, a and b
	// set the indices (a,b) and (b,a) in the matrix to one
	_myMatrix[a][b] = 1;
	_myMatrix[b][a] = 1;

}
AdjMatrix& AdjMatrix::operator=(const AdjMatrix& M){
	// overload the = operator
	// copied the code from the copy constructor
	// the this object is inherent in the = assignment operator

	// after transfering size var and creating this matrix using size
	// transfer contents of matrix in M to this matrix
	_size = M._size;
	_myMatrix = new int*[_size];
	for(int i = 0; i < _size; ++i){
		_myMatrix[i] = new int[_size];
	}

	// transfer the data
	for(int i = 0; i < _size; ++i){
		for(int j = 0; j < _size; ++j){
			_myMatrix[i][j] = M._myMatrix[i][j];
		}
	}

	return *this;
}
int* AdjMatrix::getNeighbors(int node){
	int numNeighbors = 0;

	// find how many neighbors the given node has
	for(int i = 0; i < _size; ++i){
		if(_myMatrix[node][i] == 1){
			++numNeighbors;
		}
	}

	// create an array with size of the number of neighbors
	int* neighbors = new int[numNeighbors];
	int counter = 0;

	// iterate through the matrix again and store the value of each node
	// that is a neighbor in the neighbors array
	for(int i = 0; i < _size; ++i){
		if(_myMatrix[node][i] == 1){
			neighbors[counter] = i;
			counter++;
		}
	}

	return neighbors;
}


/////// AdjList Implementations


AdjList::AdjList(){
	// default constructor, set size to 10
	_size = 10;
	_myList = new LinkedList<int>*[10];

	// initiliaze each index as an empty LL link
	for(int i = 0; i < _size; ++i){
		_myList[i] = new LinkedList<int>();
	}
}
AdjList::AdjList(int size){
	// constructor with size param, set size to size param
	_size = size;
	_myList = new LinkedList<int>*[size];

	// initiliaze each index as an empty LL link
	for(int i = 0; i < size; ++i){
		_myList[i] = new LinkedList<int>();
	}
}
AdjList::AdjList(AdjList& M){
	// copy constructor, copy the size from M, construct this list
	// then copy M's list into this list
	_size = M._size;
	_myList = new LinkedList<int>*[_size];

	// for every node in the graph
	for(int i = 0; i < _size; ++i){

		int MListSize = (*M._myList[i]).size();

		// for every node in the LL in index i in M's list
		for(int j = 0; j < MListSize; ++j){
			// add a copy of  node to this list LL at the same index i
			// get info from node j, index i in M.list
			int mListInfo = (*M._myList[i]).infoAt(j);
			// add a new node with that info to to the list at index i
			// in this list
			(*_myList[i]).add(mListInfo);
		}

	}
}
AdjList::~AdjList(){

	// delete all LL in this list
	// then delete this list

	for(int i = 0; i < _size; ++i){
		// _myList[i] returns a pointer to a LL
		// delete takes a ptr to the LL object and deletes it
		delete _myList[i];
	}

	delete[] _myList;
}
void AdjList::addEdge(int a, int b){
	// add the indices (a,b) and (b,a) to this list
	(*_myList[a]).add(b);
	(*_myList[b]).add(a);
}
AdjList& AdjList::operator=(const AdjList& M){

	// overload the = operator
	// copied the code from the copy constructor
	// the this object is inherent in the = assignment operator

	// copy the size from M, construct this list
	// then copy M's list into this list
	_size = M._size;
	_myList = new LinkedList<int>*[_size];

	// for every node in the graph
	for(int i = 0; i < _size; ++i){

		int MListSize = (*M._myList[i]).size();

		// for every node in the LL in index i in M's list
		for(int j = 0; j < MListSize; ++j){
			// add a copy of  node to this list LL at the same index i
			// get info from node j, index i in M.list
			int mListInfo = (*M._myList[i]).infoAt(j);
			// add a new node with that info to to the list at index i
			// in this list
			(*_myList[i]).add(mListInfo);
		}

	}

	return *this;
}
int* AdjList::getNeighbors(int node){

	// get the size of the list of neighbors for the given node
	int numNeighbors = (*_myList[node]).size();

	// create an arry of the nieghbors of the given node
	int* neighbors = new int[numNeighbors];

	// transfer the information of the neighbors into the int array
	for(int i = 0; i < numNeighbors; ++i){
	  	neighbors[i] = (*_myList[node]).infoAt(i);
	}

	return neighbors;
}

void BFS(int node, bool* visited, queue<int> Q, Graph g){

	Q.push(node);
	visited[node] = true;

	while(!Q.empty()){
		int currNode = Q.front(); // get the element at the front
		Q.pop(); // remove the element at the front

		// for each unvisited neighbor of the currNode
		g.getNeighbors(currNode);


	}

}

void startBFS(Graph g, int firstNode){
	int size = g.size();
	bool* visited = new bool[size];
	queue<int>* Q = new queue<int>();

	for(int i = 0; i < size; ++i){
		visited[i] = false;
	}

	//BFS(firstNode, visited, Q, g);

	delete[] visited;
}

//void DFS(int node, int* visited){
//
//	visited[node] = true;
//
//	// for every neighbor of x
//
//	if(!visited[neighbor]){
//		parent[neighbor] = x;
//		DFS(neighbor);
//	}
//}
//void startDFS(Graph g){
//	int size = g.size();
//
//	int* visited = new int[size];
//
//	for(int i = 0; i < size; ++i){
//		visited[i] = false;
//	}
//
//	int node = 0;
//	DFS(node, visited);
//
//	delete[] visited;
//
//}

int main(){

	int numNodes, x, y;

	cin >> numNodes;

	AdjMatrix* myAM = new AdjMatrix(numNodes);
	AdjList* myAL = new AdjList(numNodes);

	while(!cin.eof()){
		cin >> x >> y;

		(*myAM).addEdge(x, y);
		(*myAL).addEdge(x, y);
	}

}
