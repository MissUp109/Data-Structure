#include "UndirectedGraph.h"
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
	//g.insertEdge(2, 3, 4);
	//g.insertEdge(3, 4, 7);
	//g.insertEdge(3, 5, 6);
	//g.insertEdge(4, 5, 1);

	g.printVertex(); std::cout << std::endl;
	return 0;
}