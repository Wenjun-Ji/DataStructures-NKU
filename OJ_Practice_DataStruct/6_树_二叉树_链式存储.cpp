#include<iostream>
#include<queue>
using namespace std;
struct TreeNode{
	int data; 
	bool isEmpty;
	TreeNode* lchild, * rchild;
	TreeNode() :data(-999), isEmpty(true), lchild(NULL), rchild(NULL) {}
	TreeNode(int e):data(e),isEmpty(false),lchild(NULL),rchild(NULL) {}
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
	int get_Root() {
		if (root->isEmpty) {
			cout << "二叉树为空" << endl; return -999;
		}
		return root->data;
	}
	int get_Depth(TreeNode* root) {
		if (root==NULL) { return 0; }//叶子节点
		int i = get_Depth(root->lchild);
		int j = get_Depth(root->rchild);
		return i > j ? i+1 : j+1;
	}
	int get_Count(TreeNode* root) {
		if (root == NULL) { return 0; }
		return get_Count(root->lchild) + get_Count(root->rchild) + 1;
	}
	int get_leafCount(TreeNode* root) {
		if (root == NULL) { return 0; }
		else if (root->lchild == NULL && root->rchild == NULL) { return 1; }
		else { return get_leafCount(root->lchild) + get_leafCount(root->rchild); }
	}
	int get_kLeveLCount(TreeNode*root,int k) {
		if (root == NULL) {
			return 0;
		}
		if (k == 1) {
			return 1;
		}
		return get_kLeveLCount(root->lchild, k - 1) + get_kLeveLCount(root->rchild, k - 1);
	}
	TreeNode* find(TreeNode*root,int e) {
		if (root == NULL) {
			return NULL;
		}
		if (root->data == e) {
			return root;
		}
		TreeNode* lret = find(root->lchild, e);
		if (lret) { return lret; }
		TreeNode* rret = find(root->rchild, e);
		if (rret) { return rret; }
		return NULL;
		
	}
	void PrintAllPath(TreeNode* root, int path[], int len) {
		int i;
		if (root != NULL) {
			path[len] = root->data;
			if (root->lchild == NULL && root->rchild == NULL) {
				for (i = len; i >= 0; i--) {
					cout << path[i] << " ";
				}
				cout << endl;
			}
			else {
				PrintAllPath(root->lchild,path, len + 1);
				PrintAllPath(root->rchild, path, len + 1);

			}
		}
		else {
			
		}
	}


	void visit(TreeNode* node) { if (!node)return; else cout << node->data<<endl; }
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
				q.push( (front->lchild));
			}
			if (front->rchild) {
				q.push( (front->rchild));
			}
		}
	}
	bool BinaryTreeComplete() {
		queue<TreeNode*> q;
		if (root)q.push(root);
		while (!q.empty()) {
			TreeNode* front = q.front();
			q.pop();
			if (front == NULL) { break; }
			//visit(front);
			//if (front->lchild) {
				q.push((front->lchild));
			//}
			//if (front->rchild) {
				q.push((front->rchild));
			//}
		}
		while (!q.empty()) {
			TreeNode* front = q.front();
			q.pop();
			if (front != NULL) { return false; }
		}
		return true;
	}

	bool destroy_Tree(TreeNode * root) {
		if (root == NULL) { return false; }
		destroy_Tree(root->lchild);
		destroy_Tree(root->rchild);
		delete root;
		root = NULL;
		return true;
	}
};



int main() {

	ListTree t;
	t.creatTree();
	cout << "先序遍历" << endl;
	t.preOrder_traverse(t.root);
	cout << "中序遍历" << endl;
	t.inOrder_traverse(t.root);
	cout << "后序遍历" << endl;
	t.postOrder_traverse(t.root);
	cout << "层序遍历" << endl;
	t.levelOrder_traverse(t.root);
	cout << endl;

	cout<<(t.find(t.root,4))->data<<endl;
	cout << t.get_Count(t.root) << endl;
	cout << t.get_Depth(t.root) << endl;
	cout << t.get_kLeveLCount(t.root,3) << endl;
	cout << t.get_leafCount(t.root) << endl;
	cout << t.get_Root() << endl;
	cout << t.BinaryTreeComplete() << endl;

	int path[100];
	int len = 0;
	t.PrintAllPath(t.root, path, len);






	system("pause");
	return 0;
}