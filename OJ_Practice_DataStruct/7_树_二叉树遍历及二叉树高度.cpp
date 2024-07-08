#include<iostream>
using namespace std;
typedef struct Node{
	char data;
	Node* lchild;
	Node* rchild;
	Node() :lchild(NULL), rchild(NULL) {}
	Node(char e) :lchild(NULL), rchild(NULL) ,data(e){}
}*Tree;

Node* PreInTree(string Pre,string In) {
	int len = Pre.size();
	if (len<=0) { return NULL; }
	int rootIndex = In.find(Pre[0]);
	int left = rootIndex;
	int right = len - 1 - left;
	Node*bt = new Node(Pre[0]);
	bt->lchild=PreInTree(Pre.substr(1, left), In.substr(0, left));
	bt->rchild=PreInTree(Pre.substr(1 + left, right), In.substr(rootIndex + 1, right));
	return bt;
}
	//cout << len <<" " <<left<< " "<<right<< endl;
	//cout << rootIndex << endl;
	//cout << Pre.substr(1, left)<<endl;
	//cout << Pre.substr(1 + left, right) << endl;
	//cout<<In.substr(0, left)<<endl;
	//cout << In.substr(rootIndex + 1, right) << endl;
Node* PostInTree(string Post,string In) {
	int len = Post.size();
	if (len <= 0) { return NULL; }
	int rootIndex = In.find(Post.back());
	int left = rootIndex;
	int right = len - 1 - left;
	Node* bt = new Node(Post.back());
	bt->lchild = PostInTree(Post.substr(0, left), In.substr(0, left));
	bt->rchild = PostInTree(Post.substr(left, right), In.substr(left + 1, right));
	return bt;
}	
	//cout << len <<" " <<left<< " "<<right<< endl;
	//cout << Post.substr(0, left)<<endl;
	//cout << Post.substr(left, right) << endl;
	//cout<<In.substr(0, left)<<endl;
	//cout << In.substr(left + 1, right) << endl;
	//cout << Post << endl;


void visit(Node*p) {
	if (p != NULL)cout << p->data;
}
void PreTraverse(Tree t) {
	if (t != NULL) {
		visit(t);
		PreTraverse(t->lchild);
		PreTraverse(t->rchild);
	}
}

int height(Tree t) {
	if (t == NULL) { return 0; }
	int i = height(t->lchild);
	int j = height(t->rchild);
	return i > j ? i + 1 : j + 1;
}

void func() {
	int n;
	string pre;
	string in;
	string post;
	cin >>n>> post >> in;
	Tree t=NULL;
	//t=PreInTree(pre,in);
	t = PostInTree(post, in);
	//PreTraverse(t);
	cout << height(t);
}

int main() {
	func();
	//system("pause");
	return 0;
}

/*
9
GHDBEIFCA
GDHBAEICF
*/