#include "Heap.hpp"
#include <vector>
#include <iostream>
using namespace std;

int main(){
	std::vector<int> vec = {11, 7, 13, 2, 19, 31, -3, 1};
	Heap<int> test(vec);
	test.Print();
	cout << endl;

	cout << "====Find Min====" << endl;
	int out;
	if(test.FindMin(out)) 
		cout << out << endl;
	cout << endl;

	cout << "====Delete Min====" << endl;
	test.DeleteMin();
	test.Print();
	cout << endl;

	cout << "====Increase Key====" << endl;
	test.IncreaseKey(2, 20);
	test.Print();
	cout << endl;
	
	cout << "====Decrease Key====" << endl;
	test.DecreaseKey(5, 40);
	test.Print();
	cout << endl;

	cout << "====Delete====" << endl;
	test.Delete(4);
	test.Print();
	cout << endl;
	return 0;
}