#include<iostream>
#include<queue>
using namespace std;
struct TreeNode {
	int data;
	bool isEmpty;
	TreeNode* lchild, * rchild;
	TreeNode() :data(-999), isEmpty(true), lchild(NULL), rchild(NULL) {}
	TreeNode(int e) :data(e), isEmpty(false), lchild(NULL), rchild(NULL) {}
};
/*
		 0
	  1    2
	 3 4  5 6
	7
*/

struct ListTree {
	TreeNode* root;
	ListTree() { root = new TreeNode(); }
	void creatTree() {
		root->data = 0;
		root->isEmpty = false;
		TreeNode* p1 = new TreeNode(1);
		TreeNode* p2 = new TreeNode(2);
		TreeNode* p3 = new TreeNode(3);
		TreeNode* p4 = new TreeNode(4);
		TreeNode* p5 = new TreeNode(5);
		TreeNode* p6 = new TreeNode(6);
		TreeNode* p7 = new TreeNode(7);

		root->lchild = p1;
		root->rchild = p2;
		p1->lchild = p3;
		p1->rchild = p4;
		p2->lchild = p5;
		p2->rchild = p6;
		p3->lchild = p7;
	}
	void visit(TreeNode* node) { if (!node)return; else cout << node->data << endl; }
	void preOrder_traverse(TreeNode* root) {
		if (root == NULL) { return; }
		visit(root);
		preOrder_traverse(root->lchild);
		preOrder_traverse(root->rchild);
	}
	void inOrder_traverse(TreeNode* root) {
		if (root == NULL) { return; }
		inOrder_traverse(root->lchild);
		visit(root);
		inOrder_traverse(root->rchild);
	}
	void postOrder_traverse(TreeNode* root) {
		if (root == NULL) { return; }
		postOrder_traverse(root->lchild);
		postOrder_traverse(root->rchild);
		visit(root);
	}




	//	   0
	//	1    2
	// 3 4  5 6
	//7
	void levelOrder_traverse(TreeNode* root) {
		queue<TreeNode*> q;
		if (root)q.push(root);
		while (!q.empty()) {
			TreeNode* front = q.front();
			q.pop();
			visit(front);
			if (front->lchild) {
				q.push((front->lchild));
			}
			if (front->rchild) {
				q.push((front->rchild));
			}
		}
	}
};