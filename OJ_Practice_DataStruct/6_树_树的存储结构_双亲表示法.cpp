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
//ɾ����ʱ�����ѡ���λ�ÿ��ţ�Ҳ��ѡ�������һ�����
//ɾ���Ľڵ��ʱ�� ҲҪ���ӽڵ�ɾ��

//�ŵ㣺�ܿ�ĵõ��ڵ��˫�׽ڵ�