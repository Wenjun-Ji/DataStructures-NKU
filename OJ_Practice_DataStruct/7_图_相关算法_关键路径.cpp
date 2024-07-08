#include<iostream>
using namespace std;
#include<stack>
#include<queue>
#define MaxSize 100
#define INF 999
struct ArcNode {
	int adjvex;
	int weight;
	ArcNode* nextArc;
	ArcNode() :adjvex(-1), weight(-1), nextArc(NULL) {}
	ArcNode(int a, int w) :adjvex(a), weight(w), nextArc(NULL) {}
};

struct VexNode {
	int data;
	ArcNode* firstArc;
	VexNode() :data(-1), firstArc(NULL) {}
};

class AMGraph {
public:
	int vex_num;
	int arc_num;
	VexNode vertics[MaxSize];
	AMGraph() {
		vex_num = 0;
		arc_num = 0;
	}
	void Init() {
		cin >> vex_num >> arc_num;
		for (int i = 1; i <= vex_num; i++) {
			vertics[i].data = i;
		}
		for (int i = 0; i < arc_num; i++) {
			int u = 0, v = 0, w = 0;
			cin >> u >> v >> w;
			ArcNode* p = new ArcNode(v, w);
			p->nextArc = vertics[u].firstArc;
			vertics[u].firstArc = p;
		}
	}
	void show() {
		for (int i = 1; i <= vex_num; i++) {
			cout << vertics[i].data;
			ArcNode* p = vertics[i].firstArc;
			while (p) {
				cout << "->" << p->adjvex;
				p = p->nextArc;
			}
			cout << endl;
		}
	}
};

void TopologicalOrder(AMGraph& G, int* ve, int* vl, stack<int>& s) {
	int n = G.vex_num;
	queue<int>Q;
	int* indegree = new int[n + 1];
	//初始化度数列
	for (int i = 0; i <= n; i++) {
		indegree[i] = 0;
	}
	for (int i = 1; i <= n; i++) {
		ArcNode* p = G.vertics[i].firstArc;
		while (p) {
			indegree[p->adjvex]++;
			p = p->nextArc;
		}
	}
	for (int i = 1; i <= n; i++) {
		ve[i] = 0;
	}
	//拓扑排序
	while (s.size() != G.vex_num) {
		int index = 0;
		for (int i = 1; i <= n; i++) {
			if (indegree[i] == 0) {
				//cout << i;
				index = i;
				Q.push(i);
				s.push(i);
				indegree[i] = -1;
				break;
			}
		}
		ArcNode* p = G.vertics[index].firstArc;
		while (p) {
			indegree[p->adjvex]--;
			if (ve[p->adjvex] < ve[index] + p->weight) {//更新ve
				ve[p->adjvex] = ve[index] + p->weight;
			}
			p = p->nextArc;
		}
	}

	//初始化vl
	for (int i = 1; i <= n; i++) {
		vl[i] = ve[s.top()];
	}
	//逆拓扑排序
	while (!s.empty()) {
		int index = s.top();
		ArcNode* p = G.vertics[index].firstArc;
		while (p) {
			if (vl[index] > vl[p->adjvex] - p->weight) {
				vl[index] = vl[p->adjvex] - p->weight;
			}
			p = p->nextArc;
		}
		s.pop();
	}
}
void CriticalPath(AMGraph& G) {
	int* ve = new int[G.vex_num + 1];
	int* vl = new int[G.vex_num + 1];
	stack<int> s;
	TopologicalOrder(G, ve, vl, s);
	for (int i = 1; i <= G.vex_num; i++) {
		cout << ve[i] << " " << vl[i] << endl;
	}
	for (int i = 1; i <= G.vex_num; i++) {
		ArcNode* p = G.vertics[i].firstArc;
		while (p) {
			//如果e == l
			if (ve[i] == vl[p->adjvex] - p->weight) {
				cout << i << "->" << p->adjvex << endl;
			}
			p = p->nextArc;
		}
	}
}

int main() {
	AMGraph G;
	G.Init();
	G.show();
	CriticalPath(G);
	system("pause");
	return 0;
}

/*
6 8
1 2 3
2 4 2
3 4 4
4 6 2
5 6 1
1 3 2
2 5 3
3 6 3
*/