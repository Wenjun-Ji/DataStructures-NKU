#include<iostream>
using namespace std;
#define MaxVertexNum 100
typedef int EdgeType;//带权图边上权值的数据类型
typedef char VexType;//顶点的数据类型

typedef struct ArcNode{
	int adjvex;//该弧指向的顶点的位置
	ArcNode* nextarc;//指向下一条弧的指针
	EdgeType wight;//边的权
};

typedef struct VexNode {
	VexType data;
	ArcNode* firstArc;
}VexNode,AdjList[MaxVertexNum];

typedef struct ALGraph {//无向图
	AdjList vertics;//邻接表
	int vexnum, arcnum;
	bool CreateGraph();    //图的创建
	bool DestroyGraph();    //图的销毁
	VexType GetVex(int v);    //返回编号v顶点的值
	bool InsertVex();    //插入顶点
	bool InsertArc(int v, int w);    //插入边
	bool DeleteVex(int v);    //删除顶点
	bool DeleteArc(int v, int w);    //删除边
	bool Print();    //打印邻接表
};


bool ALGraph::CreateGraph() {//图的创建
	cin >> vexnum >> arcnum;    //输入图的顶点数和边数
	int i, v, w;
	for (i = 0; i < vexnum; i++) {    //输入各顶点的信息
		cin >> vertics[i].data;
		vertics[i].firstArc = NULL;
	}
	ArcNode* p;
	for (i = 0; i < arcnum; i++) {    //创建各边
		cin >> v >> w;    //输入一条边的两个顶点
		p = new ArcNode;    //创建一个用于存放当前边的顶点
		if (p == NULL) exit(0);
		p->adjvex = w;    //该边的起点是v终点是w
		p->nextarc = vertics[v].firstArc;    //将该边结点链接到v号顶点
		vertics[v].firstArc = p;

		p = new ArcNode;    //由于是无向图还要创建一条对称的边，起点w终点v
		if (p == NULL) exit(0);
		p->adjvex = v;
		p->nextarc = vertics[w].firstArc;    //将该边链接到w号顶点
		vertics[w].firstArc = p;
	}
	return true;
}   

bool ALGraph::DestroyGraph() {//图的销毁
	for (int i = 0; i < vexnum; i++) {
		DeleteVex(i);
	}
	return true;
}  

VexType ALGraph::GetVex(int v) {//返回编号v顶点的值
	return vertics[v].data;
}    

bool ALGraph::InsertVex() {//插入顶点
	//初始化顶点
	int v, w;
	ArcNode* p;
	vexnum++;
	cin >> vertics[vexnum - 1].data;
	vertics[vexnum - 1].firstArc = NULL;
	//完善边的信息
	while (true) {
		//输入起点终点
		cin >> v >> w;
		if (v == -1)
			break;
		//从v到w
		p = new ArcNode;
		if (p == NULL) exit(0);
		p->adjvex = w;    //该边的起点是v终点是w
		p->nextarc = vertics[v].firstArc;    //将该边结点链接到v号顶点
		vertics[v].firstArc = p;
		//从w到v
		p = new ArcNode;    //由于是无向图还要创建一条对称的边，起点w终点v
		if (p == NULL) exit(0);
		p->adjvex = v;
		p->nextarc = vertics[w].firstArc;    //将该边链接到w号顶点
		vertics[w].firstArc = p;
		arcnum++;
	}
	return true;
}    

bool ALGraph::InsertArc(int v, int w) {//插入边
	ArcNode* p;
	p = new ArcNode;
	if (p == NULL) exit(0);
	p->adjvex = w;    //该边的起点是v终点是w
	p->nextarc = vertics[v].firstArc;    //将该边结点链接到v号顶点
	vertics[v].firstArc = p;

	p = new ArcNode;    //由于是无向图还要创建一条对称的边，起点w终点v
	if (p == NULL) exit(0);
	p->adjvex = v;
	p->nextarc = vertics[w].firstArc;    //将该边链接到w号顶点
	vertics[w].firstArc = p;

	arcnum++;
	return true;
}    
bool ALGraph::DeleteVex(int v) {//删除顶点
	ArcNode* p, * q;
	int i;
	p = q = vertics[v].firstArc;
	while (p) {
		i = p->adjvex;
		ArcNode* p1, * q1;
		p1 = q1 = vertics[i].firstArc;//用于删除以节点v为终点的边结点（方法类似于链表节点的删除）
		if (p1->adjvex == v) {//在头节点的情况
			vertics[i].firstArc = p1->nextarc;
			delete p1;
			p1 = q1 = NULL;
		}
		else {//节点在中间的情况
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
		//销毁以v为起点的边界点链表 类似于销毁链表
		p = p->nextarc;
		delete q;
		q = p;
		arcnum--;
	}
	//销毁节点 并对节点数组做数据覆盖
	vertics[v].firstArc = NULL;
	for (i = v; i < vexnum - 1; i++)
		vertics[i] = vertics[i + 1];
	vexnum--;
	return true;
}    
bool ALGraph::DeleteArc(int v, int w) {//删除边
	ArcNode* p, * q;
	//删除从v到w的边界点
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
	//删除从w到v的边界点
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
bool ALGraph::Print() { //打印邻接表
	int i;
	ArcNode* p;
	//沿着顶点节点遍历边节点链表
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