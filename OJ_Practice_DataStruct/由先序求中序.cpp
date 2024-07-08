/*
��Ŀ����
�û�����һ��������������������ַ�����ÿ���ڵ���һ���ַ���ʾ��������ݴ��ַ�������һ�ö��������������������С�

���磺������������������У�ABDG##H###CE#I##F##������#���������Ҷ�ӽ�㣩��

���룺
����1����������ַ������޿ո񡣳��Ȳ�����100��

�����
������������������������ַ�����ÿ���ַ��ɿո�ָ�����ĩ�ɴ��ո�������ռһ�С�

��ʾ������ʹ��ջ�ṹ���ߵݹ顣
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