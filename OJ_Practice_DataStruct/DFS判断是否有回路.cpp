#include<iostream>
using namespace std;
#define MaxSize 100

//邻接表表示图
struct ArcNode {
	int adjVex;
	ArcNode* nextArc;
	ArcNode() :adjVex(-1), nextArc(NULL) {}
	ArcNode(int a) :adjVex(a),nextArc(NULL){}
};

struct VexNode{
	int data;
	ArcNode* firstArc;
	VexNode() :data(-1), firstArc(NULL) {}
	VexNode(int d) :data(d),firstArc(NULL){}
};

struct AdjGraph{
	int vex_num;
	int arc_num;
	VexNode vertics[MaxSize];
	AdjGraph() :vex_num(0),arc_num(0){}
};

void show(AdjGraph&G) {
	for (int i = 0; i < G.vex_num; i++) {
		cout << G.vertics[i].data << ":";
		ArcNode* p = G.vertics[i].firstArc;
		while (p) {
			cout << "->" << p->adjVex;
			p = p->nextArc;
		}
		cout << endl;
	}
}

void Init(AdjGraph&G) {
	cin >> G.vex_num >> G.arc_num;
	for (int i = 0; i < G.vex_num; i++) {
		G.vertics[i].data = i;
	}
	for (int i = 0; i < G.arc_num; i++) {
		int u=0, v=0;
		cin >> u >> v;
		ArcNode* p = new ArcNode(v);
		p->nextArc = G.vertics[u].firstArc;
		G.vertics[u].firstArc = p;

		//无向图
		ArcNode* q = new ArcNode(u);
		q->nextArc = G.vertics[v].firstArc;
		G.vertics[v].firstArc = q;
	}
//	show(G);
}

int FirstNode(AdjGraph&G,int u) {
	if (!(u >= 0 && u < G.vex_num))return -1;	
	if (G.vertics[u].firstArc) 
		return G.vertics[u].firstArc->adjVex;
	else 
		return -1;
}
int NextNode(AdjGraph&G,int u,int w) {
	if (!(u >= 0 && u < G.vex_num))return -1;
	if (!(w >= 0 && w < G.vex_num))return -1;
	ArcNode* p = G.vertics[u].firstArc;
	while (p->adjVex != w) {
		p = p->nextArc;
	}
	if (p->nextArc)
		return p->nextArc->adjVex;
	else
		return -1;
}

//一般的DFS遍历
int visited[MaxSize];
void visit(AdjGraph&G,int i) {
	cout << G.vertics[i].data << " ";
}

void DFS(AdjGraph& G,int u) {
	if (!(u >= 0 && u < G.vex_num))return;
	visit(G, u);
	visited[u] = 1;
	for (int w = FirstNode(G, u); w >= 0; w = NextNode(G, u, w)) {
		if (visited[w] == 0)
			DFS(G, w);
	}
}
void DFSTraverse(AdjGraph&G,int start) {
	if (!(start >= 0 && start < G.vex_num))return;
	DFS(G, start);
	for (int i = 0; i < G.vex_num; i++) {
		if (visited[i] == 0)
			DFS(G, i);
	}
}




/****DFS判断是否有回路****/

//1.1 有向图
//方法一样
//1.2 无向图
int post[MaxSize];
int judge_visit[MaxSize];
void _DFS_judge_circle(AdjGraph&G,int u,int & circle_num) {
	if (!(u >= 0 && u < G.vex_num)) return;
	judge_visit[u]=1;
	for (int w = FirstNode(G, u); w >= 0; w = NextNode(G, u, w)) {
		if (judge_visit[w] ==1 && w != post[u]) {
			//cout <<"产生环路的节点为："<< w << endl;// w即为产生环的节点
			circle_num ++;
		}
		else if(judge_visit[w]==0) {
			post[w] = u;
			_DFS_judge_circle(G, w,circle_num);
		}
	}
	judge_visit[u] = 2;
}

void DFS_judge_circle(AdjGraph& G) {
	for (int i = 0; i < G.vex_num; i++) {
		judge_visit[i] = 0;
		post[i] = -2;
	}
	int circle_num = 0;
	for (int i = 0; i < G.vex_num; i++) {
		if (judge_visit[i]==0) {
			_DFS_judge_circle(G, i, circle_num);
		}
	}
	
	//cout <<"环路数为：" << circle_num << endl;//其实是无法统计精确的环路数的，只能是在程序运行过程中看检测到了几个环
	if (circle_num > 0) {
		cout << "yes";
	}
	else {
		cout << "no";
	}

}


void func() {
	AdjGraph G;
	Init(G);
	//DFSTraverse(G, 0);
	//cout << endl;
	DFS_judge_circle(G);
}

int main() {
	func();

	system("pause");
	return 0;
}