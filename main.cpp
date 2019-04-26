#include <iostream>
#include <queue>
#include <list>
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
	int size();
	virtual int* getNeighbors(int node);
	~Graph();
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
	void addEdge(int a, int b);
	AdjMatrix& operator=(const AdjMatrix& M);
	int* getNeighbors(int node);
	friend ostream& operator<<(ostream& stream, const AdjMatrix& M);

};

class AdjList: public Graph {
protected:
	int _size;
	list<int>** _myList;
	int numEdges;

public:
	AdjList();
	AdjList(int size);
	AdjList(AdjList& M);
	~AdjList();
	void addEdge(int a, int b);
	AdjList& operator=(const AdjList& M);
	int* getNeighbors(int node);
	friend ostream& operator<<(ostream& stream, const AdjList& M);

};

void Graph::addEdge(int a, int b){
// leave empty
}
int Graph::size(){
	return _size;
}
int* Graph::getNeighbors(int node){
	return new int(-1);
}
Graph::~Graph(){

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
	int* neighbors = new int[numNeighbors+1];
	int counter = 1;

	neighbors[0] = numNeighbors; // the first index in the array holds size

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
ostream& operator<<(ostream& stream, const AdjMatrix& M){
	int** matrix = M._myMatrix;
	// overload the << operator for AdjMatrix

	int counter = 0;
	// for every node i
	for(int i = 0; i < M._size; ++i){

		// for every nieghbor j of that node
		for(int j = 0; j < M._size; ++j){
			if(counter == 0){ // if this is the first edge
				if(matrix[i][j] == 1){ // if the current index = 1 (there is an edge)
					stream << "(" << i << ", " << j << ")";
					counter = 1;
				}
			} else { // this is not the first edge
				if(matrix[i][j] == 1){ // there is an edge at the current index
					stream << ", (" << i << ", " << j << ")";
				}
			}
		}

	}


	return stream;
}


/////// AdjList Implementations


AdjList::AdjList(){
	// default constructor, set size to 10
	_size = 10;
	_myList = new list<int>*[10];
    numEdges = 0;
	// initiliaze each index as an empty LL link
	for(int i = 0; i < _size; ++i){
		_myList[i] = new list<int>();
	}
}
AdjList::AdjList(int size){
	// constructor with size param, set size to size param
	_size = size;
	_myList = new list<int>*[size];
     numEdges = 0;

	// initiliaze each index as an empty LL link
	for(int i = 0; i < size; ++i){
		_myList[i] = new list<int>();
	}
}
AdjList::AdjList(AdjList& M){
	// copy constructor, copy the size from M, construct this list
	// then copy M's list into this list
	_size = M._size;
	_myList = new list<int>*[_size];
	numEdges = M.numEdges;

	// for every node i in the graph
	for(int i = 0; i < _size; ++i){

		// for every node in the LL in index i in M's list
		for(auto iter = (*M._myList[i]).cbegin(); iter != (*M._myList[i]).cend(); ++iter){
			// add a copy of  node to this list LL at the same index i
			// get info from node j, index i in M.list
			int data = *iter;

			cout << "node: " << i << " data: " << data << endl;

			// add a new node with that info to to the list at index i
			// in this list
			(*_myList[i]).emplace_back(data);
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
	(*_myList[a]).emplace_back(b);
	(*_myList[b]).emplace_back(a);
	++numEdges;
}
AdjList& AdjList::operator=(const AdjList& M){

	// overload the = operator
	// copied the code from the copy constructor
	// the this object is inherent in the = assignment operator

	// copy the size from M, construct this list
	// then copy M's list into this list
	_size = M._size;
	_myList = new list<int>*[_size];

	// for every node in the graph
	for(int i = 0; i < _size; ++i){

		// for every node in the LL in index i in M's list
		for(auto iter = (*M._myList[i]).cbegin(); iter != (*M._myList[i]).cend(); ++iter){
			// add a copy of  node to this list LL at the same index i
			// get info from node j, index i in M.list
			int data = *iter;

			// add a new node with that info to to the list at index i
			// in this list
			(*_myList[i]).emplace_back(data);
		}

	}

	return *this;
}
int* AdjList::getNeighbors(int node){

	// get the size of the list of neighbors for the given node
	int numNeighbors = (*_myList[node]).size();

	// create an arry of the nieghbors of the given node
	int* neighbors = new int[numNeighbors + 1];

	neighbors[0] = numNeighbors; // first index holds size of array

	int i = 0;
	// transfer the information of the neighbors into the int array
	for(auto iter = (*_myList[node]).cbegin(); iter != (*_myList[node]).cend(); ++iter){
		neighbors[i+1] = *iter;
		++i;
	}

	return neighbors;
}
ostream& operator<<(ostream& stream, const AdjList& M){

	int counter = 0; // counter for the first edge vs all other edges
	// for every node in M
	for(int node = 0; node < M._size; ++node){

		// for every neighbor
		for(auto neighbor = (*M._myList[node]).cbegin(); neighbor != (*M._myList[node]).cend(); ++neighbor){
			if(counter == 0){ // on first run, put no comma
				stream << "(" << node << ", " << *neighbor << ")";
				counter = 1;
			} else { // on all other runs, put the comma before
				stream << ", (" << node << ", " << *neighbor << ")";
			}

		}

	}

	return stream;
}

int* BFS(int node, Graph* g){

	// starting vars
	int size = (*g).size();
	queue<int>* Q = new queue<int>();
	int* parents = new int[size]; // the parent array
	bool visited[size];

	// initalize visited array
	for(int i = 0; i < size; ++i){
		visited[i] = false;
	}

	parents[node] = -1; // parent of the root node is -1

	// add first node to the queue and modify visited
	(*Q).push(node);
	visited[node] = true;
	// use the while loop to iterate through the rest of the graph
	while(!(*Q).empty()){
		int currNode = (*Q).front(); // get the element at the front
		(*Q).pop(); // remove the element at the front

		// for each unvisited neighbor of the currNode
		int* neighbors = (*g).getNeighbors(currNode);
		int size = neighbors[0];

		for(int i = 0; i < size; ++i){
			int neighborNode = neighbors[i+1];
			// visited == true if so
			if(!visited[neighborNode]){
				parents[neighborNode] = currNode;
				visited[neighborNode] = true;
				(*Q).push(neighborNode);
			}
		}


	}

	delete Q;
	return parents;

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

	int* parents; // parent array for BFS and DFS
	int numNodes;
	double x, y;

	cin >> numNodes;

	// create the two graphs
	AdjMatrix* myAM = new AdjMatrix(numNodes);
	AdjList* myAL = new AdjList(numNodes);

	// for every edge, add that edge to the graph implementations
	for(int i = 0; i < 10; ++i){
		cin >> x >> y;

		(*myAM).addEdge(x, y);
		(*myAL).addEdge(x, y);
	}

	// Display the two graphs, the Adj matrix and Adj list objects
	cout << "Display the adjacency matrix " << endl;
	cout << (*myAM) << endl;
	cout << "Display the adjacency list " << endl;
	cout << (*myAL) << endl;

	// Display the copy constructor (both Adj matrix and Adj list)
	AdjList* copyOfAL = new AdjList(*myAL);
	AdjMatrix* copyOfAM = new AdjMatrix(*myAM);
	cout << "Display the copy of the adjacency matrix " << endl;
	cout << *copyOfAM;
	cout << "Display the copy of the adjacency list " << endl;
	cout << *copyOfAL;
	delete copyOfAM;
	delete copyOfAL;

	// Display the overloaded '=' operator (both Adj matrix and Adj list)
	//*copyOfAL = *myAL;
	*copyOfAM = *myAM;
	cout << "Display the copy of the adjacency matrix " << endl;
	cout << *copyOfAM;
	cout << "Display the copy of the adjacency list " << endl;
	cout << *copyOfAL;
	delete copyOfAM;
	delete copyOfAL;


	// And so display the copied graph in the same format.


    cout << "testing the original objects" << endl;
	cout << "Display the adjacency matrix " << endl;
	cout << (*myAM) << endl;
	cout << "Display the adjacency list " << endl;
	cout << (*myAL) << endl;

	// perform a BFS and output the parent array
	cout << "Display BFS on AdjMatrix parent array:" << endl;
	parents = BFS(0, myAM);

	// display the BFS parents array for both AdjList and AdjMatrix
	cout << "0: " << parents[0];
	for(int i = 1; i < numNodes; ++i){
		cout << "  " << i << ": " << parents[i];
	}
	delete[] parents;

	// perform a BFS and output the parent array
	cout << "Display BFS on AdjList parent array:" << endl;
	parents = BFS(0, myAL);

	// display the BFS parents array for both AdjList and AdjMatrix
	cout << "0: " << parents[0];
	for(int i = 1; i < numNodes; ++i){
		cout << "  " << i << ": " << parents[i];
	}
	delete[] parents;

	// perform a BFS and output the parent array
	cout << "Display DFS on AdjMatrix parent array:" << endl;
	//parents = DFS(0, myAM);

	// display the BFS parents array for both AdjList and AdjMatrix
	cout << "0: " << parents[0];
	for(int i = 1; i < numNodes; ++i){
		cout << "  " << i << ": " << parents[i];
	}
	delete[] parents;

	// perform a BFS and output the parent array
	cout << "Display DFS on AdjList parent array:" << endl;
	//parents = DFS(0, myAL);

	// display the BFS parents array for both AdjList and AdjMatrix
	cout << "0: " << parents[0];
	for(int i = 1; i < numNodes; ++i){
		cout << "  " << i << ": " << parents[i];
	}
	delete[] parents;


}
