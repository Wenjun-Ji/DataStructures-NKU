#include<iostream>
#include<iomanip>
using namespace std;
#define INF 100
#define MaxVertexNum 4
struct AMGraph {
	int vex_num;
	int arc_num;
	int vexs[MaxVertexNum];
	int arcs[MaxVertexNum][MaxVertexNum];
	AMGraph():vex_num(0),arc_num(0) {
		for (int i = 1; i < MaxVertexNum; i++)
			vexs[i] = -1;
		for (int i = 1; i < MaxVertexNum; i++) {
			for (int j = 1; j < MaxVertexNum; j++) {
				if(i!=j)
					arcs[i][j] =INF;
				else 
					arcs[i][j] = 0;
			}
		}
	}
	void show() {
		for (int i = 1; i < MaxVertexNum; i++) {
			for (int j = 1; j < MaxVertexNum; j++) {
				cout <<setw(4) <<arcs[i][j];
			}
			cout << endl;
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
			//arcs[v][u] = w;
		}
	}
};



void Floyd(AMGraph & G,int** dis,int** path) {
	//≥ı ºªØdis[][]  path[][]
	for (int i = 1; i < MaxVertexNum; i++) {
		for (int j = 1; j < MaxVertexNum; j++) {
			dis[i][j] = G.arcs[i][j];
			if (dis[i][j] != INF) {
				path[i][j] = i;
			}
			else {
				path[i][j] = -1;
			}
		}
	}
	//Floyd
	for (int k = 1; k <= G.vex_num; k++) {
		for (int i = 1; i <= G.vex_num; i++) {
			for (int j = 1; j <= G.vex_num; j++) {
				if (G.arcs[i][j] > G.arcs[i][k] + G.arcs[k][j]) {
					G.arcs[i][j] = G.arcs[i][k] + G.arcs[k][j];
					path[i][j] = k;
				}
			}
		}
		G.show();
		//showPathMatrix(path);
		cout << endl;
	}
}


void func() {
	AMGraph G;
	G.Init();
	G.show();

}


int main() {
	func();
	system("pause");
	return 0;
}
/*
3 5
1 2 3
1 2 6
1 3 13
2 1 10
2 3 4
3 1 5

*/

