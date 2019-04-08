#include "AVLTree.h"
#include <algorithm>
#include <iostream>
using namespace std;

AVLTree::AVLTree(vector<int> &arr){
	for(auto &i: arr)
		Insert(i);
}

int AVLTree::Height(AVLNode* T){
	if(!T) return -1;
	else return T->height;
}

void AVLTree::Insert(int val){
	root = RecursiveInsert(val, root);
}

AVLNode* AVLTree::RecursiveInsert(int val, AVLNode* T){
	if(!T) T = new AVLNode(val);
	else if(val > T->value){
		T->right = RecursiveInsert(val, T->right);
		if(Height(T->right) - Height(T->left) == 2){
			if(val > T->right->value)
				T = SingleRightRotation(T);
			else T = DoubleRightRotation(T);
		}
	}
	else if(val < T->value){
		T->left = RecursiveInsert(val, T->left);
		if(Height(T->left) - Height(T->right) == 2){
			if(val > T->left->value)
				T = DoubleLeftRotation(T);
			else T = SingleLeftRotation(T);
		}
	}
		
	T->height = max(Height(T->left), Height(T->right)) + 1;
	return T;
}

AVLNode* AVLTree::getMin(AVLNode* T){
	if(!T) return NULL;
	if(!T->left) return T;
	else return getMin(T->left);
}

void AVLTree::Delete(int val){
	root = RecursiveDelete(val, root);
}

AVLNode* AVLTree::RecursiveDelete(int val, AVLNode* T){
	if(!T) return NULL;
	if(val > T->value){
		T->right = RecursiveDelete(val, T->right);
		
		if(Height(T->left) - Height(T->right) == 2){
			if(Height(T->left->left) >= Height(T->left->right)){
				T = SingleLeftRotation(T);
				//cout << "Delete: single left rotation." << endl;
			}
			else{ 
				//cout << "Delete: double left rotation." << endl;
				T = DoubleLeftRotation(T);
			}
		}
	}
	else if(val < T->value){
		T->left = RecursiveDelete(val, T->left);
		if(Height(T->right) - Height(T->left) == 2){
			if(Height(T->right->right) >= Height(T->right->left)){
				T = SingleRightRotation(T);
				//cout << "Delete: single right rotation." << endl;
			}
			else {
				//cout << "Delete: ouble right rotation." << endl;
				T = DoubleRightRotation(T);
			}
		}
	}
	else{
		if(T->left && T->right){
			T->value = getMin(T->right)->value;
			T->right = RecursiveDelete(T->value, T->right);
		}
		else{
			AVLNode* tmp = T;
			if(!T->left) T = T->right;
			else if(!T->right) T = T->left;
			delete tmp; tmp = NULL;
		}
	}

	if(T) T->height = max(Height(T->left), Height(T->right)) + 1;
	return T;
}

void AVLTree::Clear(){
	root = RecursiveClear(root);
}

AVLNode* AVLTree::RecursiveClear(AVLNode* T){
	if(!T) return NULL;
	T->left = RecursiveClear(T->left);
	T->right = RecursiveClear(T->right);
	delete T; T = NULL;
	return T;
}


AVLNode* AVLTree::SingleLeftRotation(AVLNode* K2){
	AVLNode* K1 = K2->left;
	K2->left = K1->right;
	K1->right = K2;
	K2->height = max(Height(K2->left), Height(K2->right)) + 1;
	K1->height = max(Height(K1->left), Height(K1->right)) + 1;
	return K1;
}

AVLNode* AVLTree::SingleRightRotation(AVLNode* K2){
	AVLNode* K1 = K2->right;
	K2->right = K1->left;
	K1->left = K2;
	K2->height = max(Height(K2->left), Height(K2->right)) + 1;
	K1->height = max(Height(K1->left), Height(K1->right)) + 1;
	return K1;
}

AVLNode* AVLTree::DoubleLeftRotation(AVLNode* K3){
	K3->left = SingleRightRotation(K3->left);
	return SingleLeftRotation(K3);
}

AVLNode* AVLTree::DoubleRightRotation(AVLNode* K3){
	K3->right = SingleLeftRotation(K3->right);
	return SingleRightRotation(K3);
}

void AVLTree::PostOrder(){
	RecursivePostOrder(root);
}

void AVLTree::RecursivePostOrder(AVLNode* T){
	if(!T) return;
	RecursivePostOrder(T->left);
	RecursivePostOrder(T->right);
	cout << T->value << "(" << T->height << ")  ";
}






