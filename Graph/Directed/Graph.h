#pragma once

#include <utility>
#include <iostream>
#include <queue>
#include <climits>
#define INFINITE (INT_MAX >> 1)
//class Edge
template<class WeightType>
class Edge{
public:
	Edge(int dest, WeightType weight){
		this->dest = dest;
		this->weight = weight;
		next = nullptr;
	}
	~Edge(){
		std::cout << "delete edge: "<< "dest " << dest << ", weight " << weight << std::endl;
	}
	int dest;//the dest vertex of the edge
	WeightType weight;
	Edge<WeightType>* next;
};

//class Vertex
template<class VertexType, class WeightType> class Graph;

template<class VertexType, class WeightType>
class Vertex{
public:
	Vertex(): degree(0), neighbours(nullptr), known(false), path(-1), dst(INFINITE){}
	Vertex(VertexType val): value(val), degree(0), neighbours(nullptr), known(false), path(-1), dst(INFINITE){}
	~Vertex(){
		while(neighbours){
			Edge<WeightType>* tmp = neighbours;
			neighbours = neighbours->next;
			delete tmp;
		}
	}
private:
	friend class Graph<VertexType, WeightType>;
	Edge<WeightType>* neighbours;
	VertexType value;

	//for topoSort
	int degree; 

	//for shortest path
	bool known;
	int path;
	WeightType dst;
};


//class Graph
template<class VertexType, class WeightType>
class Graph{
public:
	Graph(int vnum = DEFAULT_SIZE): vertexNum(0), edgeNum(0){
		capacity = vnum;
		try{
			vset = new Vertex<VertexType, WeightType>[capacity];
		}
		catch(const std::bad_alloc& e){
			std::cerr << "bad_malloc of Graph()..." << std::endl;
		}
	}

	~Graph(){
		delete[] vset;
		vset = nullptr;
	}

	bool isFull();
	bool isEmpty();
	bool insertVertex(VertexType &v);
	bool insertEdge(int idx1, int idx2, WeightType weight);

	void printVertex();//print each vertex and it's neighbours
	void print(); //print each vertex's [known, path, dst]
	void printPath(int n);//print shortest path of vset[n]
	void initPath();//init [known, path, dst] value of each vertex

	void topoSort(); //TopoSort

	//shortest path algorithm
	void unWeight(int n); //unweighted shortest path
	void Dijkstra(int n); //weighted shortest path, O(V*V)
	bool BellmanFord(int n);//weighted shortest path with negative circle, O(V * E)
	bool SPFA(int n); //weighted shortest path with negative circle, O(k * E)
private:
	int vertexNum; // number of vertexs
	int edgeNum;   // number of edges
	int capacity;  // maximum size of Graph
	static const int DEFAULT_SIZE = 10;
	Vertex<VertexType, WeightType>* vset; // set of vertexs
	//bool (*insertEdgeFunc)(int, int, WeightType);//insertEdge Function
};



template<class VertexType, class WeightType>
bool Graph<VertexType, WeightType>::isFull(){ return vertexNum == capacity;}

template<class VertexType, class WeightType>
bool Graph<VertexType, WeightType>::isEmpty(){ return vertexNum == 0; }

template<class VertexType, class WeightType>
bool Graph<VertexType, WeightType>::insertVertex(VertexType &v){
	if(isFull()) {
		std::cerr << "insertVertex(): The Graph is Full..." << std::endl;
		return false;
	}
	vset[++vertexNum - 1].value = v;
	return true;
}

template<class VertexType, class WeightType>
bool Graph<VertexType, WeightType>::insertEdge(int idx1, int idx2, WeightType weight){
	if(idx1 < 0 || idx1 >= vertexNum || idx2 < 0 || idx2 >= vertexNum ){
		std::cerr << "insertEdge(): Array Index Out Of Bounds Exception..." << std::endl;
		return false;
	}

	try{
		if(nullptr == vset[idx1].neighbours){
			//std::cout << "==nullptr " << vset[idx1].value << std::endl;
			vset[idx1].neighbours = new Edge<WeightType>(idx2, weight);
		}
		else{
			//std::cout << "!=nullptr " << vset[idx1].value << std::endl;
			Edge<WeightType>* ptr = vset[idx1].neighbours;
			while(ptr->next) ptr = ptr->next;
			ptr->next = new Edge<WeightType>(idx2, weight);
		}
		++edgeNum;
		++vset[idx2].degree;
		return true;
	}
	catch(const std::bad_alloc &e){
		std::cerr << "bad_malloc of graph..." << std::endl;
	}
	return false;
}


template<class VertexType, class WeightType>
void Graph<VertexType, WeightType>::printVertex(){
	if(isEmpty()){
		std::cout << "isEmpty()" << std::endl;
		return;
	}
	for(int i = 0; i < vertexNum; ++i){
		std::cout << vset[i].value << ": "; 
		Edge<WeightType>* ptr = vset[i].neighbours;
		while(ptr){
			std::cout << vset[ptr->dest].value << "(" << ptr->weight << ")  ";
			ptr = ptr->next;
		}
		std::cout << std::endl;
	}
}


template<class VertexType, class WeightType>
void Graph<VertexType, WeightType>::print(){
	for(int i = 0; i < vertexNum; ++i)
		std::cout << "known: " << vset[i].known << ", dst: " << vset[i].dst << ", path: " << vset[i].path << std::endl;
}


template<class VertexType, class WeightType>
void Graph<VertexType, WeightType>::printPath(int n){
	if(vset[n].path >= 0) printPath(vset[n].path);
	std::cout << vset[n].value << "-->";
}


template<class VertexType, class WeightType>
void Graph<VertexType, WeightType>::initPath(){
	for(int i = 0; i < vertexNum; ++i){
		vset[i].known = false;
		vset[i].dst = INFINITE;
		vset[i].path = -1;
	}
}

template<class VertexType, class WeightType>
void Graph<VertexType, WeightType>::topoSort(){
	std::queue<int> zero;
	for(int i = 0; i < vertexNum; ++i)
		if(vset[i].degree == 0) zero.push(i);

	while(!zero.empty()){
		int cur = zero.front();
		zero.pop();
		std::cout << vset[cur].value << " ";
		Edge<WeightType>* ptr = vset[cur].neighbours;
		while(ptr){
			if(--vset[ptr->dest].degree == 0) 
				zero.push(ptr->dest);
			ptr = ptr->next;
		}
	}
	std::cout << std::endl;
}

template<class VertexType, class WeightType>
void Graph<VertexType, WeightType>::unWeight(int n){
	if(n < 0 || n >= vertexNum){
		std::cerr << "unWeight(): Array Index Out Of Bounds Exception..." << std::endl;
		return;
	}
	initPath();

	std::queue<int> que;
	vset[n].dst = 0;
	que.push(n);

	while(!que.empty()){
		int cur = que.front();
		//vset[cur].known = true;//don't need known flag
		que.pop();
		Edge<WeightType>* ptr = vset[cur].neighbours;
		while(ptr){
			if(vset[ptr->dest].dst == INFINITE){
				vset[ptr->dest].dst = vset[cur].dst + 1;
				vset[ptr->dest].path = cur;
				que.push(ptr->dest);
			}
			ptr = ptr->next;
		}
	}
}

template<class VertexType, class WeightType>
void Graph<VertexType, WeightType>::Dijkstra(int n){
	if(n < 0 || n >= vertexNum){
		std::cerr << "Dijkstra(): Array Index Out Of Bounds Exception..." << std::endl;
		return;
	}

	initPath();
	std::priority_queue< std::pair<WeightType, int> > pq;
	vset[n].dst = 0;
	pq.push(std::pair<WeightType, int>(0, n));

	while(!pq.empty()){
		WeightType minDst = pq.top().first;
		int minIdx = pq.top().second;
		vset[minIdx].known = true;
		pq.pop();
		Edge<WeightType>* ptr = vset[minIdx].neighbours;
		while(ptr){
			if(!vset[ptr->dest].known && minDst + ptr->weight < vset[ptr->dest].dst){
				vset[ptr->dest].dst = minDst + ptr->weight;
				vset[ptr->dest].path = minIdx;
				pq.push(std::pair<WeightType, int>(vset[ptr->dest].dst, ptr->dest));
			}
			ptr = ptr->next;
		}
	}
}


template<class VertexType, class WeightType>
bool Graph<VertexType, WeightType>::BellmanFord(int n){
	if(n < 0 || n >= vertexNum){
		std::cerr << "Dijkstra(): Array Index Out Of Bounds Exception..." << std::endl;
		return false;
	}

	initPath();
	vset[n].dst = 0;

	//slack operation on each edge
	int k = 1;
	while(k++ < vertexNum){
		for(int j = 0; j < vertexNum; ++j){
			Edge<WeightType>*ptr = vset[j].neighbours;
			while(ptr){
				if(vset[j].dst + ptr->weight < vset[ptr->dest].dst){
					vset[ptr->dest].dst = vset[j].dst + ptr->weight;
					vset[ptr->dest].path = j;
				}
				ptr = ptr->next;
			}
		}
	}

	//check the negative circle
	for(int i = 0; i < vertexNum; ++i){
		Edge<WeightType>* ptr = vset[i].neighbours;
		while(ptr){
			if(vset[i].dst + ptr->weight < vset[ptr->dest].dst)
				return false;//exists negative circle
			ptr = ptr->next;
		}
	}
	return true;
}


template<class VertexType, class WeightType>
bool Graph<VertexType, WeightType>::SPFA(int n){
	if(n < 0 || n >= vertexNum){
		std::cerr << "Dijkstra(): Array Index Out Of Bounds Exception..." << std::endl;
		return false;
	}

	initPath();

	vset[n].dst = 0; 
	vset[n].known = true;//decide whether vertex is included in queue.
	std::priority_queue<int> pq;
	pq.push(n);

	//record the dequeued times of each vertex
	std::vector<int> dq(vertexNum, 0);
	dq[n] = 1;

	while(!pq.empty()){
		int cur = pq.top();
		pq.pop();
		vset[cur].known = false;
		Edge<WeightType>* ptr = vset[cur].neighbours;
		while(ptr){
			if(vset[cur].dst + ptr->weight < vset[ptr->dest].dst){
				vset[ptr->dest].dst = vset[cur].dst + ptr->weight;
				vset[ptr->dest].path = cur;
				if(!vset[ptr->dest].known){
					vset[ptr->dest].known = true;
					pq.push(ptr->dest);
					if(++dq[ptr->dest] > vertexNum - 1)
						return false;				
				}
			}
			ptr = ptr->next;
		}
	}
	return true;
}






















