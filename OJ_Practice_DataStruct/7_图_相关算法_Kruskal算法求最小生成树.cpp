#include<iostream>
#include<algorithm>
using namespace std;
#include<vector>
#define MaxSize 100
#define INF 999
struct Edge {
	int _u, _v;
	int _weight;
	Edge():
		_u(-1),
		_v(-1),
		_weight(INF)
	{}
	Edge(int u, int v, int w):
		_u(u),
		_v(v),
		_weight(w)
	{}
};

struct ArcNode {
	int adjVex;//边指向的顶点
	ArcNode* nextArc;//邻近边
	int weight;//边的权重
	ArcNode():
		adjVex(-1),
		nextArc(NULL),
		weight(INF)
	{}
};

typedef struct VecNode {
	int data;
	ArcNode* firstArc;
	VecNode() :
		data(-1),
		firstArc(NULL)
	{}
}AdjList[MaxSize];

struct AdjGraph {
	AdjList vertics;//顶点数组
	int vex_num, arc_num;
	AdjGraph():
		vex_num(0),
		arc_num(0)
	{}
	void Init() {
		cin >> vex_num >> arc_num;
		for (int i = 1; i <= vex_num; i++) {
			cin >> vertics[i].data;
		}
		for (int i = 0; i < arc_num; i++) {
			int u=-1, v=-1, w=INF;
			cin >> u >> v >> w;
			ArcNode* edge = new ArcNode();
			edge->weight = w;
			edge->adjVex = v;
			edge->nextArc = vertics[u].firstArc;
			vertics[u].firstArc = edge;
			//无向图
			ArcNode* edgee = new ArcNode();
			edgee->weight = w;
			edgee->adjVex = u;
			edgee->nextArc = vertics[v].firstArc;
			vertics[v].firstArc = edgee;
		}
	}
	void show() {
		for (int i = 1; i <= vex_num; i++) {
			cout <<i<<"->";
			ArcNode* cur = vertics[i].firstArc;
			while (cur) {
				cout << cur->adjVex<<"->";
				cur = cur->nextArc;
			}
			cout << endl;
		}
	}

	void getSortEdge(vector<Edge*>& sortEdge) {
		for (int i = 1; i <= vex_num; i++) {
			ArcNode* cur = vertics[i].firstArc;
			while (cur) {
				Edge* e = new Edge(i, cur->adjVex, cur->weight);
				sortEdge.push_back(e);
				cur = cur->nextArc;
			}
		}
	}

};
bool cmp(Edge* e1, Edge* e2) {
	return e1->_weight > e2->_weight;
}
int findRoot(int u,int father[]) {
	int a=u;
	while (a!=father[a]) {
		a = father[a];
	}
	return a;
}
bool sameRoot(int u,int v,int father[]) {
	if (findRoot(u, father) == findRoot(v, father)) {
		return true;
	}else{
		return false;
	}
}
void Kruskal(AdjGraph& G) {
	//初始化edge数组和并查集
	vector<Edge*> sortEdge;
	G.getSortEdge(sortEdge);
	int* father = new int[G.vex_num+1];
	//sort(sortEdge.begin(),sortEdge.end(), cmp);//从小到大
	sort(sortEdge.rbegin(),sortEdge.rend(), cmp);//从大到小
	for (int i = 1; i <= G.vex_num; i++) {
		father[i] = i;
	}
	//确定边
	int edgeCount = 0;
	for (int i = 0; i < 2 * G.arc_num; i++) {//无向图
		int u = sortEdge[i]->_u;
		int v = sortEdge[i]->_v;
		int uRoot = findRoot(u, father);
		int vRoot = findRoot(v, father);
		if (!sameRoot(u, v, father)) {
			father[v] = u;
			cout << u << "--" << v << endl;
			edgeCount++;
		}
		if (edgeCount == G.vex_num - 1) {
			break;
		}
	}
}

void func() {
	AdjGraph G;
	G.Init();
	G.show();
	Kruskal(G);
}


int main() {
	func();

	system("pause");
	return 0;
}

/*
6 10
1 2 3 4 5 6
1 2 4
1 5 1
1 6 2
2 3 1
2 6 3
3 6 5
3 4 6
4 6 4
4 5 5
5 6 3

*/