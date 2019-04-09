#include "Graph.h"
#include <iostream>

int main(){
	Graph<int, int> g;

	std::vector<int> vs = {0, 1, 2, 3, 4, 5};
	for(auto &v: vs)
		g.insertVertex(v);

	//case 1: for weighted path without negative circle
	
	g.insertEdge(0, 1, 10);
	g.insertEdge(0, 2, 3);
	g.insertEdge(1, 2, 5);
	g.insertEdge(2, 3, 4);
	g.insertEdge(3, 4, 7);
	g.insertEdge(3, 5, 6);
	g.insertEdge(4, 5, 1);

	g.printVertex(); std::cout << std::endl;

	//g.topoSort(); std::cout << std::endl;

	//g.unWeight(0); //g.print(); 
	//g.printPath(5); std::cout << std::endl;

	//g.Dijkstra(0); //g.print();
	g.AdvancedDijkstra(0);
	g.printPath(5); std::cout << std::endl;
	

	//case 2: for weighted path with negative circle
	/*
	//3 -----(-7)-----> 4 -----(1)------>  5  ------(1)------>  3
	g.insertEdge(0, 1, 10);
	g.insertEdge(0, 2, 3);
	g.insertEdge(1, 2, 5);
	g.insertEdge(2, 3, 4);
	g.insertEdge(3, 4, -7);
	g.insertEdge(3, 5, 6);
	g.insertEdge(4, 5, 1);
	g.insertEdge(5, 3, 1);
	
	//bool ret = g.BellmanFord(0);
	//bool ret = g.SPFA(0);

	if(!ret) {
		std::cout << "Exist negative circle..." << std::endl;
		g.print();
	}
	else {
		g.printPath(5); 
		std::cout << std::endl;
	}
	*/
	return 0;
}