#pragma once
#include <vector>
using namespace std;

/* 伸展树 Splay Tree
 * ADT和AVL都不能保证分摊时间(amortized time)始终保持在O(logN)，而伸展树可以。
*/

struct SplayNode{
	int value;
	SplayNode *left, *right;
	SplayNode(int val):value(val), left(NULL), right(NULL){}
};

class SplayTree{
public:
	SplayTree(): root(NULL){}
	SplayTree(vector<int> &arr);
	void Insert(int val);
	void Delete(int val);
	void PostOrder();
	void Splay(int val);
	void Clear();
private:
	SplayNode* LeftRotation(SplayNode* G); //X从右子树旋到根结点
	SplayNode* RightRotation(SplayNode* G); //X从左子树旋转到根结点	
	SplayNode* RecursiveInsert(int val, SplayNode* T);
	SplayNode* RecursiveClear(SplayNode* T);
	SplayNode* getMax(SplayNode* T);
	void SpecificSplay(int val, SplayNode* &T);
	void RecursivePostOrder(SplayNode* T);
	SplayNode* root;
};