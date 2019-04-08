#pragma once
#include <vector>
using namespace std;

/* 平衡二叉树 AVL Tree
 * 性质：平衡二叉树的每个结点，其左子树和右子树的高度差不超过1.
 * 存储height->根据height判断imbalance->single rotation or double rotation
*/

struct AVLNode{
	int value;
	AVLNode *left, *right;
	int height;
	AVLNode(int val):value(val), left(NULL), right(NULL), height(0){}
};

class AVLTree{
public:
	AVLTree(): root(NULL){}
	AVLTree(vector<int> &arr);
	void Insert(int val);
	void Delete(int val);
	void PostOrder();
	AVLNode* getMin(AVLNode* T);
	void Clear();
private:
	AVLNode* SingleLeftRotation(AVLNode* K2);
	AVLNode* SingleRightRotation(AVLNode* K2);
	AVLNode* DoubleLeftRotation(AVLNode* K3);
	AVLNode* DoubleRightRotation(AVLNode* K3);
	AVLNode* RecursiveInsert(int val, AVLNode* T);
	AVLNode* RecursiveDelete(int val, AVLNode* T);
	AVLNode* RecursiveClear(AVLNode* T);
	void RecursivePostOrder(AVLNode* T);
	int Height(AVLNode* T);
	AVLNode* root;
};

