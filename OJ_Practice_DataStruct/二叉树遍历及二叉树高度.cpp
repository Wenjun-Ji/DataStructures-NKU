#include<iostream>
#include<string>
using namespace std;
//实现树的数据结构
//使用creat函数和first前缀 和mid中缀递归构造二叉树
//求树高


typedef struct Node {
	char data;
	Node* left;
	Node* right;
	Node() :data('#'), left(NULL), right(NULL) {}
	Node(char c) :data(c), left(NULL), right(NULL) {}
}*Tree;


Node* Creat(string first, string mid) {//或者Node* & t
	char root = first[0];
	int len = mid.length();
	int index = mid.find(root);
	int left = index;
	int right = len - left - 1;
	if (len == 0)
		return NULL;
	Node* t = new Node(first[0]);
	t->left = Creat(first.substr(1, left), mid.substr(0, left));
	t->right = Creat(first.substr(left + 1, right), mid.substr(left + 1, right));
	return t;
}

void visit(Node* p) {
	if (p) {
		cout << p->data << endl;
	}
}

void firstTraverse(Tree& t) {
	if (t) {
		visit(t);
		firstTraverse(t->left);
		firstTraverse(t->right);
	}
}

int getH(Tree& t) {
	if (t == NULL) {
		return 0;
	}
	int leftH = getH(t->left);
	int rightH = getH(t->right);
	return leftH > rightH ? leftH + 1 : rightH + 1;
}

void func() {
	int n;
	string first, mid;
	cin >> n >> first >> mid;
	//cout << n << " " << first << " " << mid << endl;
	Tree t;
	t = Creat(first, mid);
	//firstTraverse(t);
	cout << getH(t);
}
int main() {
	func();
	system("pause");
	return 0;
}


/*
总结：
注意在递归函数中是通过传参参数（指针的引用）还是 通过在函数内创建临时变量来更新求解的值 这是一个问题


*/