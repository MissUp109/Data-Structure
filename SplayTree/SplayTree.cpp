#include "SplayTree.h"
#include <algorithm>
#include <iostream>
using namespace std;

SplayTree::SplayTree(vector<int> &arr){
	for(auto &i: arr)
		Insert(i);
}

void SplayTree::Insert(int val){
	root = RecursiveInsert(val, root);
}


SplayNode* SplayTree::RecursiveInsert(int val, SplayNode* T){
	if(!T) return new SplayNode(val);
	if(val > T->value)
		T->right = RecursiveInsert(val, T->right);
	else if(val < T->value)
		T->left = RecursiveInsert(val, T->left);
	else {cout << "This node already exits." << endl;}
	return T;
}

SplayNode* SplayTree::getMax(SplayNode* T){
	if(!T) return NULL;
	if(!T->right) return T;
	else return getMax(T->right);
}

/* 
 * 方法说明：
 *    将要删除的结点splay到root，删去，获取左子树最大值的结点leftTreeMax
 *    将其splay到左子树的root，最后leftTree->right = rightTree;合并左
 *    右子树。
 */
void SplayTree::Delete(int val){
	if(!root) return;
	SpecificSplay(val, root);
	SplayNode *leftTree = root->left, *rightTree = root->right;
	SplayNode *leftTreeMax = getMax(root->left);//左子树最大值

	delete root;

	if(!leftTreeMax)  
		root = rightTree;
	else{
		SpecificSplay(leftTreeMax->value, leftTree);
		leftTree->right = rightTree;
		root = leftTree;
	}
}

void SplayTree::PostOrder(){
	RecursivePostOrder(root);
}

void SplayTree::RecursivePostOrder(SplayNode* T){
	if(!T) {return;}
	RecursivePostOrder(T->left);
	RecursivePostOrder(T->right);
	cout << T->value << " ";
}

 /*
  * X一开始处于左子树
  *               G                X
  *              /                /  \
  *             X     ==>      left   G
  *           /   \                  /
  *         left right            right
  */
SplayNode* SplayTree::LeftRotation(SplayNode* G){
	SplayNode* X = G->left;
	G->left = X->right;
	X->right = G;
	return X;
}


/*
 * X一开始处于右子树:
 * 
 *             G                   X
 *            /  \                /  \
 *         left1  X    ==>       G  right
 *              /   \          /   \ 
 *           left2 right    left1  left2 
 */
SplayNode* SplayTree::RightRotation(SplayNode* G){
	SplayNode* X = G->right;
	G->right = X->left;
	X->left = G;
	return X;
}

void SplayTree::Splay(int val){
	SpecificSplay(val, root);
}

void SplayTree::SpecificSplay(int val, SplayNode* &T){
	if(!T) return;
	if(val == T->value) return;

	SplayNode* G = T;
	for(;;){
		if(val < G->value){
			if(!G->left) break;
			if(val < G->left->value){
				G = LeftRotation(G);
			}
			else if(val > G->left->value){
				G->left = RightRotation(G->left);
			}

			G = LeftRotation(G);
		}
		else if(val > G->value){
			if(!G->right) break;

			if(val < G->right->value){
				G = LeftRotation(G);
			}
			else if(val > G->right->value){
				G = RightRotation(G);
			}
			G = RightRotation(G);
		}
		else break;
	}

	T = G;
}

void SplayTree::Clear(){
	root = RecursiveClear(root);
}

SplayNode* SplayTree::RecursiveClear(SplayNode* T){
	if(!T) return NULL;
	T->left = RecursiveClear(T->left);
	T->right = RecursiveClear(T->right);
	delete T; T = NULL;
	return T;
}


