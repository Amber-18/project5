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

public:
	virtual void addEdge(int a, int b);
	virtual int size();
	virtual ~Graph();
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

};

class AdjList: public Graph {
protected:
	int _size;
	LinkedList<int>* _myList;

public:
	AdjList();
	AdjList(int size);
	AdjList(AdjList& M);
	~AdjList();
	int size();
	void addEdge(int a, int b);


};



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
int AdjMatrix::size(){
	return _size;
}
void AdjMatrix::addEdge(int a, int b){
	// add an edge to this graph
	// the edge is represented as a connection between the two nodes, a and b


}

void BFS(int node, int* visited){

}

void startBFS(Graph g){
	int size = g.size();

	int* visited = new int[size];

	for(int i = 0; i < size; ++i){
		visited[i] = false;
	}

	int node = 0;
	BFS(node, visited);

	delete[] visited;
}

void DFS(int node, int* visited){

	visited[node] = true;

	// for every neighbor of x

	if(!visited[neighbor]){
		parent[neighbor] = x;
		DFS(neighbor);
	}
}

void startDFS(Graph g){
	int size = g.size();

	int* visited = new int[size];

	for(int i = 0; i < size; ++i){
		visited[i] = false;
	}

	int node = 0;
	DFS(node, visited);

	delete[] visited;

}

int main(){

}
