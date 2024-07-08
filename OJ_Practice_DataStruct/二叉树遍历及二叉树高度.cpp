#include<iostream>
#include<string>
using namespace std;
//ʵ���������ݽṹ
//ʹ��creat������firstǰ׺ ��mid��׺�ݹ鹹�������
//������


typedef struct Node {
	char data;
	Node* left;
	Node* right;
	Node() :data('#'), left(NULL), right(NULL) {}
	Node(char c) :data(c), left(NULL), right(NULL) {}
}*Tree;


Node* Creat(string first, string mid) {//����Node* & t
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
�ܽ᣺
ע���ڵݹ麯������ͨ�����β�����ָ������ã����� ͨ���ں����ڴ�����ʱ��������������ֵ ����һ������


*/