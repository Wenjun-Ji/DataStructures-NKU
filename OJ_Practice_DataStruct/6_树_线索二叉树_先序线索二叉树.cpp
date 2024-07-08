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
		if (p->ltag == 0) {//������ѭ��
			PreThread(p->lchild, pre);
		}
		if (p->rtag == 0) {//���ӵĻ����ڴ������һ���ڵ��ʱ�� pre���p����һ�� ��ѭ��
			//ԭ�����ڵ�p��F�������ҵݹ�ִ�������˵�c����ݹ�ִ���� ��ʱҪ����ִ��c���ҵݹ飬������p�ĵݹ麯����preҲ����c��rchild�Ѿ����趨Ϊf,����NULL���޷������Ļ��ˣ��ͻ�һֱ��f�ڵ���ѭ��
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