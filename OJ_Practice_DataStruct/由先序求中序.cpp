/*
题目描述
用户输入一个二叉树的先序遍历的字符串（每个节点用一个字符表示）后，请根据此字符串建立一棵二叉树，输出中序遍历序列。

例如：输入如下先序遍历序列：ABDG##H###CE#I##F##，其中#代表空树（叶子结点）。

输入：
输入1行先序遍历字符串，无空格。长度不超过100。

输出：
输出建立二叉树后的中序遍历字符串，每个字符由空格分隔，行末可带空格，输出结果占一行。

提示：可以使用栈结构或者递归。
*/

#include<iostream>
using namespace std;

struct Node{
	char data;
	Node* left;
	Node* right;
	Node() :data('*'),left(NULL),right(NULL){}
	Node(char c) :data(c),left(NULL),right(NULL){}
};

struct Tree{
	Node* root;
	Tree() :root(NULL) {}
};
Node* Creat(string s, int &i) {
	if (i < s.size()) {
		if ((char)s[i] == '#') {
			return NULL;
		}
		else {
			Node* cur = new Node(s[i]);
			i++; cur->left = Creat(s, i);
			i++; cur->right = Creat(s, i);
			return cur;
		}
	}
}

void visit(Node* root) {
	if(root!=NULL)
		cout << root->data;
}
void InTraverse(Node* root) {
	if (root == NULL)return;
	InTraverse(root->left);
	visit(root);
	InTraverse(root->right);
}


int main(){
	Tree t;
	string s;
	cin >> s;
	int i = 0;
	t.root=Creat(s, i);
	InTraverse(t.root);
	system("pause");
	return 0;
}