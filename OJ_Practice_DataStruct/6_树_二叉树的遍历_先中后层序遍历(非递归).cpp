#include<iostream>
using namespace std;
#include<stack>

typedef struct Node{
	int data;
	Node* left;
	Node* right;
	Node() :data(-999), left(NULL), right(NULL) {}
	Node(int d) :data(d), left(NULL), right(NULL) {}

}* Tree;


void visit(Node* t){
	if (t) {
		cout << t->data <<" ";
	}
}

void FirstTraverse(Node* t) {
	stack<Node*>s;
	while (t || !s.empty()) {
		if (t) {
			visit(t); s.push(t);
			t = t->left;
		}
		else {
			t = s.top();
			s.pop();
			t = t->right;
		}
	}
}

void InTraverse(Node* t) {
	stack<Node*>s;
	while (t || !s.empty()) {
		if (t) {
			s.push(t);
			t = t->left;
		}
		else {
			t = s.top();
			s.pop(); visit(t);
			t = t->right;
		}
	}
}

void PostTraverse(Node* t) {
	stack<Node*>s;
	Node* r=NULL;
	while (t || !s.empty()) {
		if (t) {
			s.push(t);
			t = t->left;//先走到最左边
		}
		else {
			t = s.top(); 
			if (t->right && t->right != r) {//如果右节点存在且不是在回溯的过程（前驱不是right）则继续向右
				t = t->right;
			}
			else {//右节点为空或者在回溯的过程中
				s.pop();
				visit(t);
				r = t;
				t = NULL;//注意要重置指针，确保在回溯
			}
			
		}
	}
}

void func() {
	Tree t = new Node(0);
	t->left = new Node(1);
	t->right = new Node(2);
	t->left->left = new Node(3);
	t->left->right = new Node(4);
	t->right->left = new Node(5);
	t->right->right = new Node(6);
	FirstTraverse(t); cout << endl;
	InTraverse(t); cout << endl;
	PostTraverse(t);

}


int main() {
	func();
	system("pause");
	return 0;
}