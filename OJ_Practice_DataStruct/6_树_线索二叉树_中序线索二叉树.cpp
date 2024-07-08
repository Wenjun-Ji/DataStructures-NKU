#include<iostream>
using namespace std;
typedef struct ThreadNode {
	char data;
	ThreadNode* lchild;
	ThreadNode* rchild;
	int ltag, rtag;
	ThreadNode():lchild(NULL),rchild(NULL),ltag(0),rtag(0),data('#') {}
	ThreadNode(char e) :lchild(NULL), rchild(NULL), ltag(0), rtag(0), data(e) {}

}ThreadNode,*ThreadTree;

void visit(ThreadNode* p) {
	cout << p->data << endl;
}

void Thread(ThreadTree&p,ThreadTree& pre) {
	if (p->lchild == NULL) {
		p->lchild = pre;
		p->ltag = 1;
	}
	if (pre != NULL && pre->rchild == NULL) {
		pre->rchild = p;
		pre->rtag = 1;
	}
	pre = p;
}

void InThread(ThreadTree & p,ThreadTree & pre){
	if (p != NULL) {
		InThread(p->lchild, pre);
		Thread(p,pre);
		InThread(p->rchild, pre);
	}
}

void CreateInThread(ThreadTree T) {
	ThreadNode* pre=NULL;
	if (T != NULL) {
		InThread(T, pre);
		if(pre->rchild == NULL)
			pre->rtag = 1;	
	}
}

ThreadNode* FirstNode(ThreadNode*p) {
	while (p->ltag != 1) { p = p->lchild; }
	return p;
}

ThreadNode* NextNode(ThreadNode*p) {
	if (p->rtag == 1)return p->rchild;
	else return FirstNode(p->rchild);
}

void Inorder(ThreadTree T) {
	for (ThreadNode* p = FirstNode(T); p != NULL; p = NextNode(p)) {
		visit(p);
	}
}

void InTraverse(ThreadTree T) {
	ThreadNode* p=T;
	while (p != NULL) {
		while (p->ltag == 0) {
			p = p->lchild;
		}
		cout << p->data;
		while (p->rtag == 1) {
			p = p->rchild;
			cout << p->data << endl;
		}
		p=p->rchild;
	}
}

int main() {
	ThreadTree a = new ThreadNode('A');
	ThreadTree b = new ThreadNode('B');
	ThreadTree c = new ThreadNode('C');
	ThreadTree d = new ThreadNode('D');
	ThreadTree e = new ThreadNode('E');
	ThreadTree f = new ThreadNode('F');
	ThreadTree g = new ThreadNode('G');

	a->lchild = b;
	a->rchild = c;
	b->lchild = d;
	b->rchild = e;
	d->rchild = g;
	c->lchild = f;

	CreateInThread(a);
	Inorder(a);
	InTraverse(a);

	system("pause");
	return 0;
}


