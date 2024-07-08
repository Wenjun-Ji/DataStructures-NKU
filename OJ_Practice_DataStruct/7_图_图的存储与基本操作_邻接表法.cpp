#include<iostream>
using namespace std;
#define MaxVertexNum 100
typedef int EdgeType;//��Ȩͼ����Ȩֵ����������
typedef char VexType;//�������������

typedef struct ArcNode{
	int adjvex;//�û�ָ��Ķ����λ��
	ArcNode* nextarc;//ָ����һ������ָ��
	EdgeType wight;//�ߵ�Ȩ
};

typedef struct VexNode {
	VexType data;
	ArcNode* firstArc;
}VexNode,AdjList[MaxVertexNum];

typedef struct ALGraph {//����ͼ
	AdjList vertics;//�ڽӱ�
	int vexnum, arcnum;
	bool CreateGraph();    //ͼ�Ĵ���
	bool DestroyGraph();    //ͼ������
	VexType GetVex(int v);    //���ر��v�����ֵ
	bool InsertVex();    //���붥��
	bool InsertArc(int v, int w);    //�����
	bool DeleteVex(int v);    //ɾ������
	bool DeleteArc(int v, int w);    //ɾ����
	bool Print();    //��ӡ�ڽӱ�
};


bool ALGraph::CreateGraph() {//ͼ�Ĵ���
	cin >> vexnum >> arcnum;    //����ͼ�Ķ������ͱ���
	int i, v, w;
	for (i = 0; i < vexnum; i++) {    //������������Ϣ
		cin >> vertics[i].data;
		vertics[i].firstArc = NULL;
	}
	ArcNode* p;
	for (i = 0; i < arcnum; i++) {    //��������
		cin >> v >> w;    //����һ���ߵ���������
		p = new ArcNode;    //����һ�����ڴ�ŵ�ǰ�ߵĶ���
		if (p == NULL) exit(0);
		p->adjvex = w;    //�ñߵ������v�յ���w
		p->nextarc = vertics[v].firstArc;    //���ñ߽�����ӵ�v�Ŷ���
		vertics[v].firstArc = p;

		p = new ArcNode;    //����������ͼ��Ҫ����һ���ԳƵıߣ����w�յ�v
		if (p == NULL) exit(0);
		p->adjvex = v;
		p->nextarc = vertics[w].firstArc;    //���ñ����ӵ�w�Ŷ���
		vertics[w].firstArc = p;
	}
	return true;
}   

bool ALGraph::DestroyGraph() {//ͼ������
	for (int i = 0; i < vexnum; i++) {
		DeleteVex(i);
	}
	return true;
}  

VexType ALGraph::GetVex(int v) {//���ر��v�����ֵ
	return vertics[v].data;
}    

bool ALGraph::InsertVex() {//���붥��
	//��ʼ������
	int v, w;
	ArcNode* p;
	vexnum++;
	cin >> vertics[vexnum - 1].data;
	vertics[vexnum - 1].firstArc = NULL;
	//���Ʊߵ���Ϣ
	while (true) {
		//��������յ�
		cin >> v >> w;
		if (v == -1)
			break;
		//��v��w
		p = new ArcNode;
		if (p == NULL) exit(0);
		p->adjvex = w;    //�ñߵ������v�յ���w
		p->nextarc = vertics[v].firstArc;    //���ñ߽�����ӵ�v�Ŷ���
		vertics[v].firstArc = p;
		//��w��v
		p = new ArcNode;    //����������ͼ��Ҫ����һ���ԳƵıߣ����w�յ�v
		if (p == NULL) exit(0);
		p->adjvex = v;
		p->nextarc = vertics[w].firstArc;    //���ñ����ӵ�w�Ŷ���
		vertics[w].firstArc = p;
		arcnum++;
	}
	return true;
}    

bool ALGraph::InsertArc(int v, int w) {//�����
	ArcNode* p;
	p = new ArcNode;
	if (p == NULL) exit(0);
	p->adjvex = w;    //�ñߵ������v�յ���w
	p->nextarc = vertics[v].firstArc;    //���ñ߽�����ӵ�v�Ŷ���
	vertics[v].firstArc = p;

	p = new ArcNode;    //����������ͼ��Ҫ����һ���ԳƵıߣ����w�յ�v
	if (p == NULL) exit(0);
	p->adjvex = v;
	p->nextarc = vertics[w].firstArc;    //���ñ����ӵ�w�Ŷ���
	vertics[w].firstArc = p;

	arcnum++;
	return true;
}    
bool ALGraph::DeleteVex(int v) {//ɾ������
	ArcNode* p, * q;
	int i;
	p = q = vertics[v].firstArc;
	while (p) {
		i = p->adjvex;
		ArcNode* p1, * q1;
		p1 = q1 = vertics[i].firstArc;//����ɾ���Խڵ�vΪ�յ�ı߽�㣨��������������ڵ��ɾ����
		if (p1->adjvex == v) {//��ͷ�ڵ�����
			vertics[i].firstArc = p1->nextarc;
			delete p1;
			p1 = q1 = NULL;
		}
		else {//�ڵ����м�����
			while (true) {
				p1 = p1->nextarc;
				if (p1->adjvex == v) {
					q1->nextarc = p1->nextarc;
					delete p1;
					p1 = NULL;
					break;
				}
				q1 = p1;
			}
		}
		//������vΪ���ı߽������ ��������������
		p = p->nextarc;
		delete q;
		q = p;
		arcnum--;
	}
	//���ٽڵ� ���Խڵ����������ݸ���
	vertics[v].firstArc = NULL;
	for (i = v; i < vexnum - 1; i++)
		vertics[i] = vertics[i + 1];
	vexnum--;
	return true;
}    
bool ALGraph::DeleteArc(int v, int w) {//ɾ����
	ArcNode* p, * q;
	//ɾ����v��w�ı߽��
	p = q = vertics[v].firstArc;
	if (p->adjvex == w) {
		vertics[v].firstArc = p->nextarc;
		delete p;
		p = q = NULL;
	}
	else {
		while (true) {
			p = p->nextarc;
			if (p->adjvex == w) {
				q->nextarc = p->nextarc;
				delete p;
				p = q = NULL;
				break;
			}
		}
	}
	//ɾ����w��v�ı߽��
	p = q = vertics[w].firstArc;
	if (p->adjvex == v) {
		vertics[w].firstArc = p->nextarc;
		delete p;
		p = q = NULL;
	}
	else {
		while (true) {
			p = p->nextarc;
			if (p->adjvex == v) {
				q->nextarc = p->nextarc;
				delete p;
				p = q = NULL;
				break;
			}
		}
	}
	arcnum--;
	return true;

}    
bool ALGraph::Print() { //��ӡ�ڽӱ�
	int i;
	ArcNode* p;
	//���Ŷ���ڵ�����߽ڵ�����
	for (i = 0; i < vexnum; i++) {
		p = vertics[i].firstArc;
		cout << vertics[i].data << "-->";
		while (p) {
			cout << p->adjvex << " ";
			p = p->nextarc;
		}
		cout << endl;
	}
	return true;
}   





int main() {
	ALGraph graph;
	graph.CreateGraph();
	graph.Print();
	cout << endl;
	cout << graph.GetVex(2) << endl;
	graph.InsertVex();
	graph.Print();
	cout << endl;
	graph.InsertArc(0, 4);
	graph.Print();
	cout << endl;



	system("pause");
	return 0;
}