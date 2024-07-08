#include<iostream>
using namespace std;
#define MaxSize 100
struct PTNode{
	int data;
	int parent;
};
struct PTree {
	PTNode nodes[MaxSize];
	int n;
};
//删除的时候可以选择把位置空着，也可选择让最后一个填充
//删除的节点的时候 也要给子节点删除

//优点：很快的得到节点的双亲节点