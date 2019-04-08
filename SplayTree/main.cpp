#include "SplayTree.h"
#include <iostream>
using namespace std;

int main(){
	vector<int> arr = {10, 6, 8, 4, 5, 3, 11};
	SplayTree test(arr);

	//Insertion Test
	cout << "After Insertion: ";
	test.PostOrder(); cout << endl;
	cout << endl;

	//Splay Test 1: Left Zig-Zag
	test.Splay(8);
	cout << "First Splaying: ";
	test.PostOrder(); cout << endl;

	//Splay Test 2: Left Zig
	test.Splay(6);
	cout << "Second Splaying: ";
	test.PostOrder(); cout << endl;

	//Splay Test 3: Left Zig-Zig
	test.Splay(3);
	cout << "Third Splaying: ";
	test.PostOrder(); cout << endl;

	//Splay Test 4: Right Zig-Zig + Left Zig-Zag
	test.Splay(5);
	cout << "Fourth Splaying: ";
	test.PostOrder(); cout << endl;	

	//Splay Test 5: Right Zig
	test.Splay(6);
	cout << "Fifth Splaying: ";
	test.PostOrder(); cout << endl;	

	//Insert 9 for Test 5
	cout << endl;
	test.Insert(9);
	cout << "Insert 9: ";
	test.PostOrder(); cout << endl;	
	cout << endl;

	//Splay Test 5: Right Zig-Zig + Right Zig-Zag
	test.Splay(9);
	cout << "Sixth Splaying: ";
	test.PostOrder(); cout << endl;	

	//Deletion Test
	cout << "After Deletion: ";
	test.Delete(6);
	test.PostOrder(); cout << endl;

	//Clearing Test
	cout << "After Clearing: ";
	test.Clear();
	test.PostOrder(); cout << endl;
}


/* output
After Insertion: 3 5 4 8 6 11 10

First Splaying: 3 5 4 6 11 10 8
Second Splaying: 3 5 4 11 10 8 6
Third Splaying: 5 11 10 8 6 4 3
Fourth Splaying: 3 4 11 10 8 6 5
Fifth Splaying: 3 4 5 11 10 8 6

Insert 9: 3 4 5 9 11 10 8 6

Sixth Splaying: 3 4 5 6 8 11 10 9
After Deletion: 3 4 11 10 9 8 5
After Clearing:
*/