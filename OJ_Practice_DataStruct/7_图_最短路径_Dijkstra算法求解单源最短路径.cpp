#include<iostream>
#include<iomanip>
#define MaxVertexNum 10
#define INF 999
using namespace std;


struct AMGragh{
	int vex_num, arc_num;
	int vexs[MaxVertexNum];
	int arcs[MaxVertexNum][MaxVertexNum];
	AMGragh():vex_num(0),arc_num(0) {
		for (int i = 1; i < MaxVertexNum; i++) {
			vexs[i] = -1;
		}
		for (int i = 1; i < MaxVertexNum; i++) {
			for (int j = 1; j < MaxVertexNum; j++) {
				if (i == j)
					arcs[i][j] = 0;
				else
					arcs[i][j] = INF;
			}
		}
	}
	void show() {
		for (int i = 1; i < MaxVertexNum; i++) {
			for (int j = 1; j < MaxVertexNum; j++) {
				cout.setf(ios::left);
				cout <<setw(4)<<arcs[i][j];
			}
			cout << endl;
		}
	}
	void InitAMGraph() {
		cout << "请输入节点数和边数" << endl;
		cin >> vex_num >> arc_num;
		for (int i = 1; i <= vex_num; i++) {
			cin >> vexs[i];
		}
		for(int i=1;i<=arc_num;i++){
			int u=0, v=0,w=0;
			cin >> u >> v >> w;
			arcs[u][v] = w;
			arcs[v][u] = w;//无向图
		}
	}
};

void Dijkstra(AMGragh& G, int start,int dis[], int path[],int visit[]) {
	//初始化dis 和 path数组
	for (int i = 1; i <= G.vex_num; i++) {
		dis[i] = G.arcs[1][i];
		path[i] = dis[i] != INF ? 1 : -1;
		visit[i] = false;
	}
	dis[start] = 0;
	visit[start] = true;
	int min=INF;
	int post = 1;	
	//进行vex_num-1次循环
	for (int i = 1; i <= G.vex_num - 1;i++) {
		min = INF, post = 1;
		//for循环寻找下一个最近节点
		for (int j = 1;j <= G.vex_num; j++) {
			if (!visit[j] && min > dis[j]) {
				min = dis[j];
				post = j;
			}
		}
		visit[post] = true;
		//for循环更新dis和path
		for (int j = 1; j < G.vex_num; j++) {
			if (!visit[j] && dis[j] > dis[post] + G.arcs[post][j]) {
				dis[j] = dis[post] + G.arcs[post][j];
				path[j] = post;
			}
		}
	}
}
/*
8 10
1 2 3 4 5 6 7 8
1 6 10
1 5 5
6 3 1
6 5 2
3 4 4
4 1 7
4 3 6
5 6 3
5 3 9
5 4 2
*/
void showPath(int path[], int x) {
	if (path[x] == -1) {
		cout << "不存在从1到"<<x<<"的最短路径";
		return;
	}
	if (x == 1) {
		cout << "1";
		return;
	}
	else {
		showPath(path, path[x]);
	}
	cout << "->" << x;
}


void func() {
	AMGragh G;
	G.InitAMGraph();
	//G.show();
	int dis[MaxVertexNum];
	int path[MaxVertexNum];
	int visit[MaxVertexNum];
	Dijkstra(G,1,dis,path,visit);
	for (int i = 1; i <= G.vex_num; i++) {
		showPath(path, i);
		cout << endl;
	}
}




int main() {
	func();




	system("pause");
	return 0;
}