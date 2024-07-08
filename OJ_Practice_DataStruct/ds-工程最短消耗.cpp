#include<iostream>
#include<string>
#include<vector>
#include<stack>
using namespace std;
#define MaxSize 25

struct ArcNode{
	int weight;
	ArcNode* nextArc;
	int adjVex;
	ArcNode() :weight(0), adjVex(0), nextArc(NULL) {}
	ArcNode(int w,int a) :weight(w), adjVex(a), nextArc(NULL) {}

};
struct VexNode{
	int data;
	ArcNode* firstArc;
	VexNode() :data(-1),firstArc(NULL){}
};

struct AdGraph{
	VexNode vertics[MaxSize];
	int vex_num;
	int arc_num;
	AdGraph():vex_num(0),arc_num(0) {}
};

void show(AdGraph&G) {
	for (int i = 1; i <= G.vex_num; i++) {
		cout << i << ":";
		ArcNode* p = G.vertics[i].firstArc;
		while (p) {
			cout << "->" << p->adjVex;
			p = p->nextArc;
		}
		cout << endl;
	}
}

void Init(AdGraph&G) {
	int n = 0;
	cin >> n;
	G.vex_num = n;
	cin.ignore();
	for(int i=1;i<=n;i++){
		//输入节点编号
		int start;
		cin >> start;
		//输入权重
		int weight;
		cin >> weight;
		G.vertics[i].data = weight;
		//输入前驱节点
		string s;
		getline(cin,s);
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == ';') {
				int post=0;
				int j = i-1;
				while (j>0&&s[j] >= '0' && s[j] <= '9') {
					post = post * 10 + s[j] - '0';
					j--;
				}
				ArcNode* p = new ArcNode(0, start); G.arc_num++;
				p->nextArc = G.vertics[post].firstArc;
				G.vertics[post].firstArc = p;
			}
		}
	}
}

stack<int> tp;
int AOV(AdGraph&G) {
	int Flag = 0;
	//初始化
	int *InDegree=new int[G.vex_num+1];
	for (int i = 0; i <= G.vex_num; i++) {
		InDegree[i] = 0;
	}
	int* visit = new int[G.vex_num + 1];
	for (int i = 0; i <= G.vex_num; i++) {
		visit[i] = 0;
	}
	for (int i = 1; i <= G.vex_num; i++) {
		ArcNode* p = G.vertics[i].firstArc;
		while (p) {
			InDegree[p->adjVex]++;
			p = p->nextArc;
		}
	}
	//拓扑排序
	stack<int>s;
	for (int i = 1; i <= G.vex_num; i++) {
		if (InDegree[i] == 0) {
			s.push(i);
			tp.push(i);
			visit[i] = 1;
		}
	}
	while (!s.empty()) {
		int root = s.top();
		s.pop();
		ArcNode* p = G.vertics[root].firstArc;
		while (p) {
			InDegree[p->adjVex]--;
			p = p->nextArc;
		}
		for (int i = 1; i <= G.vex_num; i++) {
			if (visit[i]==0&&InDegree[i] == 0) {
				s.push(i);
				tp.push(i);
				visit[i] = 1;
			}
		}
	}
	for (int i = 1; i <= G.vex_num; i++) {
		if (InDegree[i] != 0) {
			return false;
		}
	}
	
	//初始化
	int* OutDegree = new int[G.vex_num + 1];
	for (int i = 0; i <= G.vex_num; i++) {
		OutDegree[i] = 0;
	}
	int* result = new int[G.vex_num];
	for (int i = 1; i <= G.vex_num; i++) {
		result[i] = G.vertics[i].data;
	}
	for (int i = 1; i <= G.vex_num; i++) {
		ArcNode* p = G.vertics[i].firstArc;
		while (p) {
			OutDegree[i]++;
			p = p->nextArc;
		}
	}
	//贪心算法计算最长路径
	while (!tp.empty()) {
		int top = tp.top();
		tp.pop();
		//cout << top << endl;
		ArcNode* p = G.vertics[top].firstArc;
		int vexdata = result[top];
		while (p) {
			if (result[top] < vexdata + result[p->adjVex]) {
				result[top] = vexdata + result[p->adjVex];
			}
			p = p->nextArc;
		}
	}
	int Max=-1;
	for (int i = 1; i <= G.vex_num; i++) {
		if (Max < result[i])Max = result[i];
	}
	return Max;
}

/*
8
1 5
2 4 1;
3 1 1;
4 9 3;
5 10 4;
6 3 5;
7 7 5;
8 5 6;
*/

int main() {
	AdGraph G;
	Init(G);
	int result = AOV(G);
	if (result) {
		cout << result;
	}
	else {
		cout << "error";
	}
	system("pause");
	return 0;
}