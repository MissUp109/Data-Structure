#pragma once

#include <utility>
#include <iostream>
#include <queue>
#include <climits>
#define INFINITE (INT_MAX >> 1)
//undirected graph

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
		//std::cout << "delete edge: "<< "dest " << dest << ", weight " << weight << std::endl;
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
	Vertex(): neighbours(nullptr), known(false), path(-1), dst(INFINITE){}
	Vertex(VertexType val): value(val), neighbours(nullptr), known(false), path(-1), dst(INFINITE){}
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

	//minimum spanning tree
	void prim(int n, std::vector<pair<int, int> > &primEdges);
	void kruskal(int n, std::vector<pair<int, int> > &primEdges);
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
			vset[idx1].neighbours = new Edge<WeightType>(idx2, weight);
		}
		else{
			Edge<WeightType>* ptr = vset[idx1].neighbours;
			while(ptr->next) ptr = ptr->next;
			ptr->next = new Edge<WeightType>(idx2, weight);
		}

		if(nullptr == vset[idx2].neighbours){
			vset[idx2].neighbours = new Edge<WeightType>(idx1, weight);
		}
		else{
			Edge<WeightType>* ptr = vset[idx2].neighbours;
			while(ptr->next) ptr = ptr->next;
			ptr->next = new Edge<WeightType>(idx1, weight);
		}

		++edgeNum;
		
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
void Graph<VertexType, WeightType>::prim(int n, std::vector<pair<int, int>> &primEdges){
	if(n < 0 || n >= vertexNum){
		std::cerr << "Dijkstra(): Array Index Out Of Bounds Exception..." << std::endl;
		return;
	}

	initPath();

	primEdges.clear();

	std::priority_queue< std::pair<WeightType, int> > pq;
	vset[n].dst = 0;
	pq.push(std::pair<WeightType, int>(0, n));

	while(!pq.empty()){
		auto cur = pq.top(); 
		vset[cur.second].known = true;
		primEdges.push_back(std::pair<int, int>(vset[cur.second].path, cur.second));
		pq.pop();
		Edge<WeightType>* ptr = vset[cur.second].neighbours;
		while(ptr){
			if(!vset[ptr->dest].known &&  cur.first + ptr->weight < vset[ptr->dest].dst){
				vset[ptr->dest].dst = cur.first + ptr->weight;
				vset[ptr->dest].path = cur.second;
				pq.push(std::pair<WeightType, int>(vset[ptr->dest].dst, ptr->dest));
			}
			ptr = ptr->next;
		}
	}
}





















