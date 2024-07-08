#include<iostream>
using namespace std;
typedef struct ThreadNode {
	char data;
	ThreadNode* lchild, * rchild;
	int ltag, rtag;
	ThreadNode() :lchild(NULL), rchild(NULL), ltag(0), rtag(0), data('#') {}
	ThreadNode(char e) :lchild(NULL), rchild(NULL), ltag(0), rtag(0), data(e) {}
}ThreadNode,*ThreadTree;

void visit(ThreadNode* p) {
	cout << p->data << endl;
}

void Thread(ThreadTree& p,ThreadTree& pre) {
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

void PreThread(ThreadTree &p, ThreadTree& pre) {
	if (p != NULL) {
		Thread(p, pre);
		if (p->ltag == 0) {//避免死循环
			PreThread(p->lchild, pre);
		}
		if (p->rtag == 0) {//不加的话正在处理最后一个节点的时候 pre会和p归在一起 死循环
			//原因在于当p在F处的左右递归执行完会回退到c的左递归执行完 此时要接着执行c的右递归，但是在p的递归函数种pre也就是c的rchild已经被设定为f,不是NULL，无法正常的回退，就会一直在f节点自循环
			PreThread(p->rchild, pre);
		}
	}
}

void CreatePreThread(ThreadTree&T) {
	ThreadNode* pre = NULL;
	if (T != NULL) {
		PreThread(T,pre);
		if (pre->rchild == NULL)
			pre->rtag = 1;
	}
}

ThreadNode* FirstNode(ThreadNode*p) {
	return p;
}

ThreadNode* NextNode(ThreadNode* p) {
	if (p->rtag == 1)return p->rchild;
	else return p->rchild;
}

void Preorder(ThreadNode *T) {
	for (ThreadNode* p = FirstNode(T); p != NULL; p = NextNode(p)) {
		visit(p);
	}
}


void PreTraverse(ThreadTree T) {
	ThreadNode* p = T;
	while (p != NULL) {
		cout << p->data << endl;
		if (p->ltag == 0) {
			p = p->lchild;
		}else{
			p = p->rchild;
		}
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

	CreatePreThread(a);
	PreTraverse(a);
	system("pause");
	return 0;
}