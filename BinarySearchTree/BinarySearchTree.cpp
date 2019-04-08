#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/* 二叉查找树 - Binary Search Tree需满足以下条件：
 * a.若任意节点的左子树不空，则左子树上所有结点的值均小于它的根结点的值；
 * b.若任意节点的右子树不空，则右子树上所有结点的值均大于它的根结点的值；
 * c.任意节点的左、右子树也分别为二叉查找树；
 * d.没有键值相等的节点。
 */

struct TreeNode{
	int value;
	TreeNode *left, *right;
	TreeNode(int val): value(val), left(NULL), right(NULL){}
};

class SearchTree {
public:
	SearchTree():root(NULL){}
	SearchTree(vector<int> &arr);
	void PrintPreorder();
	void PrintInorder();
	void PrintPostorder();
	void PrintLevelorder();
	void Insert(int val);
	void Delete(int val);
	TreeNode* Find(int val);
	TreeNode* Min();
	void Clear();
private:
	void Preorder(TreeNode* head);
	void Inorder(TreeNode* head);
	void Postorder(TreeNode* head);
	void Levelorder(queue<TreeNode*> &nodeQueue);
	TreeNode* RecursiveInsert(int val, TreeNode* head);
	TreeNode* RecursiveDelete(int val, TreeNode* head);
	TreeNode* RecursiveFind(int val, TreeNode* head);
	TreeNode* RecursiveMin(TreeNode* head);
	TreeNode* RecursiveClear(TreeNode* &head);
	TreeNode* root;
};

SearchTree::SearchTree(vector<int> &arr){
	for(auto i: arr)
		Insert(i);
}

void SearchTree::Insert(int val){
	root = RecursiveInsert(val, root);
}

TreeNode* SearchTree::RecursiveInsert(int val, TreeNode* head){
	if(!head){return new TreeNode(val);}
	if(val > head->value){
		head->right = RecursiveInsert(val, head->right);
	}
	else if(val < head->value){
		head->left = RecursiveInsert(val, head->left);
	}
	return head;
}


void SearchTree::Delete(int val){ 
	RecursiveDelete(val, root);
}

TreeNode* SearchTree::RecursiveDelete(int val, TreeNode* head){
	if(!head) return NULL;
	if(head->value < val){
		head->right = RecursiveDelete(val, head->right);
	}
	else if(head->value > val){
		head->left = RecursiveDelete(val, head->left);
	}
	else{
		if(head->left && head->right){
			head->value = RecursiveMin(head->right)->value;
			head->right = RecursiveDelete(head->value, head->right);
		}
		else{
			TreeNode* tmp = head;
			if(!head->left) head = head->right;
			else if(!head->right) head = head->left;
			delete tmp; tmp = NULL;
		}
	}
	return head;
}

TreeNode* SearchTree::Find(int val){
	return RecursiveFind(val, root);
}

TreeNode* SearchTree::RecursiveFind(int val, TreeNode* head){
	if(!head) return NULL;
	if(head->value > val)
		return RecursiveFind(val, head->left);
	else if(head->value < val)
		return RecursiveFind(val, head->right);
	else return head;
}

TreeNode* SearchTree::Min(){
	return RecursiveMin(root);
}

TreeNode* SearchTree::RecursiveMin(TreeNode* head){
	if(!head) return NULL;
	if(!head->left) return head;
	return RecursiveMin(head->left);
}

void SearchTree::Clear(){
	RecursiveClear(root);
}

TreeNode* SearchTree::RecursiveClear(TreeNode* &head){
	if(head){
		head->left = RecursiveClear(head->left);
		head->right = RecursiveClear(head->right);
		delete head; head = NULL;
	}
	return NULL;
}

void SearchTree::PrintPreorder(){
	Preorder(root);
}

void SearchTree::Preorder(TreeNode* head){
	if(!head) return;
	cout << head->value << " ";
	Preorder(head->left);
	Preorder(head->right);
}

void SearchTree::PrintInorder(){
	Inorder(root);
}

void SearchTree::Inorder(TreeNode* head){
	if(!head) return;
	Inorder(head->left);
	cout << head->value << " ";
	Inorder(head->right);
}

void SearchTree::PrintPostorder(){
	Postorder(root);
}

void SearchTree::Postorder(TreeNode* head){
	if(!head) return;
	Postorder(head->left);
	Postorder(head->right);
	cout << head->value << " ";
}

void SearchTree::PrintLevelorder(){
	if(!root) return;
	queue<TreeNode*> nodeQueue;
	nodeQueue.push(root);
	Levelorder(nodeQueue);
}

void SearchTree::Levelorder(queue<TreeNode*> &nodeQueue){
	if(nodeQueue.empty()) return;
	int size = nodeQueue.size();
	TreeNode* cur = NULL;
	while(size--){
		cur = nodeQueue.front();
		cout << cur->value << " ";
		nodeQueue.pop();
		if(cur->left) nodeQueue.push(cur->left);
		if(cur->right) nodeQueue.push(cur->right);
	}
	return Levelorder(nodeQueue);
}


int main(){
	vector<int> arr = {8, 4, 15, 2, 6, 9, 17};
	
	SearchTree test(arr); //Insertion Test
	
	cout << "Before deletion: " << endl; 
	cout << "Preorder: "; test.PrintPreorder(); cout << endl; 
	cout << "Inorder: "; test.PrintInorder(); cout << endl;
	cout << "Postorder: "; test.PrintPostorder(); cout << endl;
	cout << "Levelorder: "; test.PrintLevelorder(); cout << endl;


	test.Delete(8);//Deletion Test
	cout << "After deletion: ";
	test.PrintPreorder(); cout << endl; 

	TreeNode* fRet = test.Find(8);//Find Test
	if(fRet) cout << "Find: " << fRet->value << endl;
	else cout << "Can't find."<< endl;

	test.Clear(); //Clear Test
	test.PrintPreorder(); cout << endl; 
	//cout << (test.root)->right->right->value << endl;
	//if(!test.root) cout << "clear success!" << endl;
	//else cout << "failure " << test.root << endl; 
}

/*
//非递归插入
bool Tree::Insert(int val){
	TreeNode* node = new TreeNode(val);
	if(!root) {root = node; return true;}

	TreeNode *ptr = root, *parent = NULL;
	while(ptr){
		parent = ptr;
		if(ptr->value > node->value){
			ptr = ptr->left;
		}
		else if(ptr->value < node->value){
			ptr = ptr->right;
		}
	}
	if(node->value > parent->value){
		parent->right = node;
	}
	else if(node->value < parent->value){
		parent->left = node;
	}
	
	return false;
}

//非递归查找
TreeNode* Tree::Find(int val){
	if(!root) return NULL;

	TreeNode* head = root;
	while(head){
		if(head->value > val){
			head = head->left;
		}
		else if(head->value < val){
			head = head->right;
		}
		else return head;
	}
	return NULL;
}

//可以看到，PrintPreorder/PrintInorder/PrintPostorder的内容
//其实是一样的，为了减少冗余，我们可以将它们并成一个函数Print()，
//并通过函数指针作为参数，来选择不同的函数操作。
void Print(void (SearchTree::*func)(TreeNode*)); //声明
void Tree::Print(void (SearchTree::*func)(TreeNode*)){//定义
	TreeNode* head = root;
	(this->*func)(head);
}
test.Print(&SearchTree::Preorder); cout << endl;//调用方法，注意Preorder需要变成public

*/

