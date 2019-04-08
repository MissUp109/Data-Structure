#include <iostream>
#include <vector>
#include <utility>
#include <queue>

//邻近矩阵

template<class T>
class Graph{
public:
	std::vector<T> vset;
	std::vector<int> id;
	std::vector<std::vector<int>> vmap;
	
	Graph(int s, std::vector<T> vs, std::vector<std::pair<int, int>> edge): size(s), vset(s), id(s, 0), vmap(s, std::vector<int>(s, 0)){
		int idx = 0;
		for(auto &v: vs){
			vset[idx++] = v;
		}

		for(auto &e: edge){
			vmap[e.first][e.second] = 1;
			++id[e.second];
		}
	}

	void topoSort(){
		std::queue<int> id_zero;
		for(auto &i: id){
			if(i == 0) id_zero.push(i);
		}

		while(!id_zero.empty()){
			int cur = id_zero.front();
			std::cout << vset[cur] << " ";
			id_zero.pop();
			for(int i = 0; i < size; ++i){
				if(i!= cur && vmap[cur][i]){
					if(--id[i] == 0) id_zero.push(i);
				}
			}
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