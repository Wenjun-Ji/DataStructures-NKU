#include<iostream>
#include<queue>
using namespace std;
#define MaxVertexNum 100
struct ArcNode {
	int adjvex;//该边指向的终点
	ArcNode* nextarc;//起点相同的下一条临边
	ArcNode(int w) :adjvex(w), nextarc(NULL) {}
};

typedef struct VexNode {
	char data;
	ArcNode* firstarc;
	VexNode():data(-999),firstarc(NULL) {}
	VexNode(char c) :data(c), firstarc(NULL) {}
	
}AdjList[MaxVertexNum];


struct ALGraph {
	AdjList vertics;
	int vexnum, arcnum;
	ALGraph();
	bool visit(int v);
	bool InitALGraph();
	int FirstNeighbor(int v);
	int NextNeighbor(int v, int w);
	bool Print();
};

ALGraph::ALGraph() {
	vexnum = 0;
	arcnum = 0;
}
bool ALGraph::visit(int v){
	if (v<0 || v>=vexnum)return false;

	cout<<vertics[v].data<<endl;
	return true;
}
bool ALGraph::InitALGraph() {
	cin >> vexnum >> arcnum;
	for (int i = 0; i < vexnum; i++) {
		cout << "请输入无向图顶点的数据" << endl;
		cin >> vertics[i].data;
	}
	ArcNode* p;
	for (int i = 0; i < arcnum; i++) {
		int v, w;
		cout << "请输入无向图边的起点和终点"<<endl;
		cin >> v>> w;

		p = new ArcNode(w);
		p->nextarc = vertics[v].firstarc;
		vertics[v].firstarc = p;

		p = new ArcNode(v);
		p->nextarc = vertics[w].firstarc;
		vertics[w].firstarc = p;
	}
	return true;
}
int  ALGraph::FirstNeighbor(int v) {
	if (v < 0 || v >= vexnum)return -1;

	if (vertics[v].firstarc != NULL)
		return vertics[v].firstarc->adjvex;
	else 
		return -1;
}
int  ALGraph::NextNeighbor(int v,int w) {
	if (v < 0 || v >= vexnum)return -1;
	if (w < 0 || w >= vexnum)return -1;

	ArcNode* p = vertics[v].firstarc;
	if (p == NULL) { 
		return -1;
	}

	while (p->nextarc) {
		if (p->adjvex == w) {
			return p->nextarc->adjvex;
		}
		p = p->nextarc;
	}
	return -1;
}


bool ALGraph::Print() { //打印邻接表
	int i;
	ArcNode* p;
	//沿着顶点节点遍历边节点链表
	for (i = 0; i < vexnum; i++) {
		p = vertics[i].firstarc;
		cout <<vertics[i].data << "-->";
		while (p) {
			cout << vertics[p->adjvex].data << " ";
			p = p->nextarc;
		}
		cout << endl;
	}
	return true;
}

void BFS(ALGraph &G,int v,queue<int>&Q,bool*visit) {
	G.visit(v);
	visit[v] = true;
	Q.push(v);
	while (!Q.empty()) {
		v = Q.front();
		Q.pop();
		for (int w = G.FirstNeighbor(v); w >= 0&&w<G.vexnum; w = G.NextNeighbor(v, w)) {
			if (!visit[w]) {
				G.visit(w);
				visit[w] = true;
				Q.push(w);
			}
		}
	}

}
void BFS_Traverse(ALGraph &G,int v) {
	queue<int> Q;
	bool* visit = new bool[G.vexnum];
	for (int i = 0; i < G.vexnum; i++) {
		visit[i] = false;
	}
	BFS(G, v, Q, visit);//先从哪个节点开始访问
	for (int i = 0; i < G.vexnum; i++)
		if (!visit[i])
			BFS(G, i,Q,visit);
}



int main() {
	ALGraph G;
	G.InitALGraph();
	G.Print();
	BFS_Traverse(G,1);
}



//修改一下下标  从0或1 开始 统一一下
/*
8 10

1 2 3 4 5 6 7 8

0 4

0 1

1 5

5 2

5 6

2 6

2 3

6 3

6 7

3 7
*/