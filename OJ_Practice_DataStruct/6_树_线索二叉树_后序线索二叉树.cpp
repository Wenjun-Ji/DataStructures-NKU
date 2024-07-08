#include<iostream>
using namespace std;
typedef struct ThreadNode {
	char data;
	ThreadNode* lchild;
	ThreadNode* rchild;
	ThreadNode* parent;
	int ltag, rtag;
	ThreadNode() :lchild(NULL), rchild(NULL), ltag(0), rtag(0), data('#') {}
	ThreadNode(char e) :lchild(NULL), rchild(NULL), ltag(0), rtag(0), data(e) {}

}ThreadNode, * ThreadTree;

void visit(ThreadNode* p) {
	cout << p->data << endl;
}

void Thread(ThreadTree& p, ThreadTree& pre) {
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

void PostThread(ThreadTree& p, ThreadTree& pre) {
	if (p != NULL) {
		if(p->ltag==0)
			PostThread(p->lchild, pre);
		if(p->rtag==0)
			PostThread(p->rchild, pre);
		Thread(p, pre);
	}
}

void CreateInThread(ThreadTree T) {
	ThreadNode* pre = NULL;
	if (T != NULL) {
		PostThread(T, pre);
		if (pre->rchild == NULL)//ֻ�к�������һ�����ܲ�ΪNULL,�������������һ����ΪNULL
			pre->rtag = 1;
	}
}

void PostTraverse(ThreadTree T) {
	ThreadNode* p = T;
	ThreadNode* pre = NULL;
	while (p!=NULL) {
		while (p->ltag == 0 && p->lchild != pre)//�ҵ�����ߵĽڵ�
		{
			p = p->lchild;
		}
		while (p->rtag == 1)//����������ڵ�ĺ��
		{
			cout << p->data;
			pre = p;//��¼��һ���ڵ�
			p = p->rchild;
		}
		if (p == T)//�ж��ǲ��Ǹ��ڵ�
		{
			cout << p->data;
			return;
		}
		while (p->rchild == pre)//���Ǹ��ڵ㣬���ʵ�ǰ�ڵ��˫�׽ڵ�
		{
			cout << p->data;
			pre = p;
			p = p->parent;
			if (p == nullptr)//���������ڵ㣬�˳�
			{
				return;
			}
		}
		if (p->rtag == 0)//����������
		{
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
	a->parent = NULL;
	b->parent = a;
	c->parent = a;
	b->lchild = d;
	b->rchild = e;
	d->parent = b;
	e->parent = b;
	d->rchild = g;
	g->parent = d;
	c->lchild = f;
	f->parent = c;

	CreateInThread(a);
	PostTraverse(a);


	system("pause");
	return 0;
}