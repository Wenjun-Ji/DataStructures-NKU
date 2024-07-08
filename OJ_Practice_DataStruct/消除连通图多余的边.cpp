#include<iostream>
#include<vector>
#include<algorithm>
#define MaxSize 100
using namespace std;

struct Edge{
	int start;
	int end;
	int weight;
	Edge(int s,int e,int w) :start(s), end(e), weight(w) {}
};

int vex_num = 0;
int arc_num = 0;
vector<Edge*>q;
int Set[MaxSize];
bool cmp(Edge*e1,Edge*e2) {
	return e1->weight < e2->weight;
}

void Init() {
	cin >> vex_num >> arc_num;
	for (int i = 0; i < arc_num; i++) {
		int s, e, w;
		cin >> s >> e >> w;
		q.push_back(new Edge(s, e, w));
	}
	sort(q.begin(), q.end(), cmp);
	for(int i=1;i<=vex_num;i++){
		Set[i] = i;
	}
	for (vector<Edge*>::iterator i = q.begin(); i != q.end(); i++) {
		cout << (*i)->weight << " ";
	}
}

int findRoot(int x) {
	while (x != Set[x]) {
		x = Set[x];
	}
	return x;
}

bool sameRoot(int a,int b) {
	if (findRoot(a) == findRoot(b)) return true;
	return false;
}
void Union(int a,int b) {
	Set[findRoot(b)] = a;
}

void Kruskal() {
	int count=0;
	for (int i = 0; i < arc_num; i++) {
		if (!sameRoot(q[i]->start, q[i]->end)) {
			Union(q[i]->start,q[i]->end);
			q[i]->weight = 0;
			count++;
			if (count == vex_num - 1) {
				break;
			}
		}
	}
	for(int i=0;i<arc_num;i++){
		if (q[i]->weight != 0) {
			cout << q[i]->weight << " ";
		}
	}
}



int main() {
	Init();
	Kruskal();
	system("pause");
	return 0;
}
