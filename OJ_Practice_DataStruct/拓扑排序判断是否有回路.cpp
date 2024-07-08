#include<iostream>
using namespace std;
#define MaxSize 100
#include<queue>
struct ArcNode{
	int adjVex;
	ArcNode* nextArc;
	ArcNode():adjVex(-1),nextArc(NULL) {}
	ArcNode(int a) :adjVex(a), nextArc(NULL) {}
};


struct VexNode {
	int data;
	ArcNode* firstArc;
	VexNode() :data(-1), firstArc(NULL) {}
	VexNode(int d) :data(d), firstArc(NULL) {}
};

struct AdjGraph {
	int vex_num;
	int arc_num;
	VexNode vertics[MaxSize];
	AdjGraph() :vex_num(0), arc_num(0) {}
};


void show(AdjGraph& G) {
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
void Init(AdjGraph& G) {
	cin >> G.vex_num >> G.arc_num;
	for (int i = 0; i < G.vex_num; i++) {
		G.vertics[i].data = i;
	}
	for (int i = 0; i < G.arc_num; i++) {
		int u = 0, v = 0;
		cin >> u >> v;
		ArcNode* p = new ArcNode(v);
		p->nextArc = G.vertics[u].firstArc;
		G.vertics[u].firstArc = p;

		//无向图
		/*ArcNode* q = new ArcNode(u);
		q->nextArc = G.vertics[v].firstArc;
		G.vertics[v].firstArc = q;
	*/
	}
	//	show(G);
}


//无向图
int indegree[MaxSize];
queue<int>Q;
void TopologicSort_judge_circle_undirected(AdjGraph& G) {
	for (int i = 0; i < G.vex_num; i++) {
		ArcNode* p = G.vertics[i].firstArc;
		while (p) {
			indegree[p->adjVex]++;
			p = p->nextArc;
		}
	}


	//找入度为0的点 现找一个来初始化Q
	int index = -1;
	for (int i = 0; i < G.vex_num; i++) {
		if (indegree[i] <= 1) {
			Q.push(i);
			indegree[i] = -1;//visited
			break;
		}
	}

	while (!Q.empty()) {
		//for (int i = 0; i < G.vex_num; i++) {
		//	cout << indegree[i] << " ";
		//}
		//cout << endl;

		int index = Q.front();	Q.pop();
		//更新入度
		ArcNode* p = G.vertics[index].firstArc;
		while (p) {
			indegree[p->adjVex]--;
			p = p->nextArc;
		}
		//把入度<=1的点都入队
		for (int i = 0; i < G.vex_num; i++) {
			if (indegree[i] >= 0 && indegree[i] <= 1) {
				Q.push(i);
				indegree[i] = -1;//visited
			}
		}
	}

	for (int i = 0; i < G.vex_num; i++) {
		if (indegree[i] >= 0) {
			cout << "yes";
			return;
		}
	}
	cout << "no";
}

void TopologicSort_judge_circle_directed(AdjGraph& G) {
	for (int i = 0; i < G.vex_num; i++) {
		ArcNode* p = G.vertics[i].firstArc;
		while (p) {
			indegree[p->adjVex]++;
			p = p->nextArc;
		}
	}


	//找入度为0的点 现找一个来初始化Q
	int index = -1;
	for (int i = 0; i < G.vex_num; i++) {
		if (indegree[i] ==0) {
			Q.push(i);
			indegree[i] = -1;//visited
			break;
		}
	}

	while (!Q.empty()) {
		for (int i = 0; i < G.vex_num; i++) {
			cout << indegree[i] << " ";
		}
		cout << endl;

		int index = Q.front();	Q.pop();
		//更新入度
		ArcNode* p = G.vertics[index].firstArc;
		while (p) {
			indegree[p->adjVex]--;
			p = p->nextArc;
		}
		//把入度<=1的点都入队
		for (int i = 0; i < G.vex_num; i++) {
			if (indegree[i] == 0) {
				Q.push(i);
				indegree[i] = -1;//visited
			}
		}
	}

	for (int i = 0; i < G.vex_num; i++) {
		if (indegree[i] >= 0) {
			cout << "yes";
			return;
		}
	}
	cout << "no";
}



int main() {
	AdjGraph G;
	Init(G);
	//TopologicSort_judge_circle_undirected(G);
	TopologicSort_judge_circle_directed(G);

	system("pause");
	return 0;
}