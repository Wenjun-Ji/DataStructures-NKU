#include<iostream>
#include<iomanip>
using namespace std;
#define Max 10
#define INF 100
struct node {
	int adjvex;
	int lowcost;
};

struct AMGraph {
	int vex_num, arc_num;
	int vexs[Max];
	int arcs[Max][Max];
	AMGraph():vex_num(0),arc_num(0) {
		for (int i = 1; i < Max; i++) {
			vexs[i] = -1;
		}
		for (int i = 1; i < Max; i++) {
			for (int j = 1; j < Max; j++) {
				arcs[i][j] = INF;
			}
		}
	}

	void Init() {
		cin >> vex_num >> arc_num;
		for (int i = 1; i <= vex_num; i++) {
			cin >> vexs[i];
		}
		for (int i = 0; i < arc_num; i++) {
			int u, v, w;
			cin >> u >> v >> w;
			arcs[u][v] = w;
			arcs[v][u] = w;
		}
	}

	void print() {
		for (int i = 1; i < Max; i++) {
			for (int j = 1; j < Max; j++) {
				cout <<setw(4)<<arcs[i][j];
			}
			cout << endl;
		}
	}
};


void Prim(AMGraph& G,int u,node* closeEdge) {
	//初始化closeEdge
	closeEdge = new node[G.vex_num+1];
	for (int i = 1; i <= G.vex_num; i++) {
		closeEdge[i].adjvex = u;
		closeEdge[i].lowcost = G.arcs[i][u];
	}
	closeEdge[u].adjvex = u;
	closeEdge[u].lowcost = 0;

	for (int i = 0; i < G.vex_num-1; i++) {
		int Min = INF, v = -1;	
		//寻找最小的边
		for (int j = 1; j <= G.vex_num; j++) {
			if (closeEdge[j].lowcost != 0 && Min > closeEdge[j].lowcost) {
				Min = closeEdge[j].lowcost;
				v = j;
			}
		}
		//将v点归入已有点集
		closeEdge[v].lowcost = 0;
		//输出选取的边
		cout << closeEdge[v].adjvex << "--" << v << endl;
		//根据新加入点 更新closeEdge
		for (int j = 1; j <= G.vex_num; j++) {
			if (closeEdge[j].lowcost != 0 && closeEdge[j].lowcost > G.arcs[j][v]) {
				closeEdge[j].lowcost = G.arcs[j][v];
				closeEdge[j].adjvex = v;
			}
		}                                                              
	}
}

void func() {
	AMGraph G;
	G.Init();
	G.print();
	node* closeEdge = NULL;
	Prim(G, 1, closeEdge);
}

int main() {
	func();
	system("pause");
	return 0;
}

/*
6 10
1 2 3 4 5 6
1 2 6
1 4 5
1 3 1
2 3 5
3 4 5
2 5 3
3 5 6
4 6 2
3 6 4
5 6 6

*/