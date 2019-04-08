#include <iostream>
#include <vector>
#include <utility>
#include <queue>

//邻近链表
template<class T>
class Vetex{
public:
	T value;
	int degree;
	std::vector<int> neigbours;//record index of neigbours
	Vetex(T val): value(val), degree(0){}
};

template<class T>
class Graph{
public:
	std::vector<Vetex<T>> vset;
	Graph(int s, std::vector<T> vs, std::vector<std::pair<int, int>> es): size(s){
		for(auto &v: vs){
			Vetex<T> tmp(v);
			vset.push_back(tmp);
		}

		for(auto &e: es){
			vset[e.first].neigbours.push_back(e.second);
			++vset[e.second].degree;
		}
	}

	void topoSort(){
		std::queue<int> id_zero;
		for(int i = 0; i < size; ++i)
			if(vset[i].degree == 0) id_zero.push(i);

		while(!id_zero.empty()){
			Vetex<T> curv = vset[id_zero.front()];
			id_zero.pop();
			std::cout << curv.value << " ";
			for(auto &n: curv.neigbours)
				if(--vset[n].degree == 0) id_zero.push(n);
		}
		std::cout << std::endl;
	}
private:
	int size;
};


int main(){
	int s = 5;
	std::vector<int> vs = {7, 8, 2, 3, 4};
	std::vector<std::pair<int, int>> edge = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 2}, {3, 2}, {4, 2}};
	Graph<int> g(s, vs, edge);
	g.topoSort();
}