#include <iostream>
#include "AVLTree.h"
using namespace std;

int main(){
	//vector<int> arr = {3, 2, 1, 4, 5, 6, 7}; //only single rotaion
	vector<int> arr = {3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9};
	AVLTree test(arr);
	cout << "Before deleting 12: ";
	test.PostOrder();
	cout << endl;

	test.Delete(12); //single rotation
	//test.Delete(8); //double rotaion
	cout << "After deleting 12: ";
	test.PostOrder();
	cout << endl;

	test.Clear();
	cout << "After clearing: ";
	test.PostOrder();
	cout << endl;
}

