#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
typedef struct Node{
	char data;
	Node* lchild;
	Node* rchild;
	Node():lchild(NULL),rchild(NULL),data('#') {}
	Node(char e) :lchild(NULL), rchild(NULL), data(e) {}
};


void Creat_CompleteBinaryTree(vector<Node>& t,int flag, string s, int n,int &count) {//n=1 count=0
	if (n <= s.length()) {
		t[n].data = s[count];
		count++;
		Creat_CompleteBinaryTree(t,0, s, 2 * n,count);
		Creat_CompleteBinaryTree(t,1, s, 2 * n + 1,count);
	}
}

void visit(vector<Node> & t,int n) {
	if (n<=t.size()-1) {
		cout << t[n].data;
	}
}
void Post_Traverse(vector<Node> &t,int n) {
	if (n<=t.size()-1) {
		Post_Traverse(t,2*n);
		Post_Traverse(t,2*n+1);
		visit(t,n);
	}
}


int main() {
	string s;
	cin >> s;
	vector<Node> t(s.size()+1);
	int n = 1;
	int count = 0;
	int falg = 0;
	Creat_CompleteBinaryTree(t, 0, s, n, count);
	Post_Traverse(t,n);
	return 0;
}