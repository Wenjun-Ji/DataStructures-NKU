
#include<iostream>
#include<iomanip>
using namespace std;
#define MaxSize 22
#define INF 999
struct AMGraph {
	int vex_num;
	int arc_num;
	int arcs[MaxSize][MaxSize];
	AMGraph() {
		vex_num = 0;
		arc_num = 0;
		for (int i = 1; i < MaxSize; i++) {
			for (int j = 1; j < MaxSize; j++) {
				if (i == j)
					arcs[i][j] = 1;
				else
					arcs[i][j] = INF;
			}
		}
	}
	void Init() {
		cin >> vex_num;
		cin >> arc_num;
		for (int i = 0; i < arc_num; i++) {
			int u=0, v=0, w=1;
			cin >> u>>v;
			arcs[u + 1][v + 1] = w;
			arcs[v + 1][u + 1] = w;
		}
	}
	void show() {
		for (int i = 1; i < MaxSize; i++) {
			for (int j = 1; j < MaxSize; j++) {
				cout << setw(4) << arcs[i][j];
			}
			cout << endl;
		}
	}

};

//  A(k)[i][j] = ( A(k - 1)[i][k]∧A(k - 1)[k][j] ) ∨ A(k - 1)[i][j];
void warshell(AMGraph& G,bool** A) {
	for (int i = 1; i <= G.vex_num; i++) {
		for (int j = 1; j <= G.vex_num; j++) {
			if (G.arcs[i][j] == INF) {
				A[i][j] = false;
			}
			else {
				A[i][j] = true;
			}
		}
	}
	for (int j = 1; j <= G.vex_num; j++) {//j<=col//中转点
		for (int i = 1; i <= G.vex_num; i++) {//i<=row
			if (A[i][j]) {
				for (int k = 1; k <= G.vex_num; k++) {//k<=col
					A[i][k] = A[i][k] || A[j][k];
				}
			}
		}
	}
	for (int i = 1; i <= G.vex_num; i++) {
		for (int j = 1; j <= G.vex_num; j++) {
			//cout << A[i][j] << " ";
		}
		//cout << endl;
	}
}
bool judge(int i,int j,bool**A) {
	return A[i][j] ? true : false;
}

void func() {
	AMGraph G;
	G.Init();
	//G.show();
	//cout << endl;
	bool** A = new bool* [G.vex_num+1];
	for (int i = 0; i < G.vex_num+1; i++) {
		*(i + A) = new bool[G.vex_num+1];
	}
	warshell(G, A);
	int n = 0;
	cin >> n;
	pair<int, int>* p = new pair<int, int>[n];
	for (int i = 0; i < n; i++) {
		cin >> p[i].first >> p[i].second;
	}
	for (int i = 0; i < n; i++) {
		if (judge(p[i].first+1, p[i].second+1, A)) {
			cout << "true" << endl;
		}
		else {
			cout << "false" << endl;
		}
	}
}

int main() {
	func();
	
	

	//system("pause");
	return 0;
	
}




/*
5
4
1 5
3 5
1 3
2 4

2
4 5
3 5
*/


/*
#include<iostream>
using namespace std;
#define MaxSize 20
int UFSets[MaxSize];
int n;

int FindRoot(int a) {
	while (UFSets[a] != a) {
		a = UFSets[a];
	}
	return a;
}
bool SameRoot(int a,int b) {
	if (FindRoot(a) == FindRoot(b)) return true;
	return false;
}
void Union(int a,int b) {
	if (SameRoot(a,b)) {
		return;
	}
	else {
		UFSets[FindRoot(b)] = FindRoot(a);//注意两个集合的合并是对根节点进行操作的,如果是UFSets[b]=a;这样会是的b上面的节点全部丢失
	}
}
void Initial() {
	for (int i = 0; i < MaxSize; i++) {
		UFSets[i] = i;
	}
	int  m;
	cin >> n;
	cin >> m;
	for (int i = 0; i < m; i++) {
		int a=0, b=0;
		cin >> a >> b;
		Union(a, b);
	}
}
void func() {
	Initial();
	int s = 0;
	cin >> s;
	//pair<int, int>* p = new pair<int, int>[s];
	//for (int i = 0; i < s; i++) {
	//	cin >> p[i].first >> p[i].second;
	//}
	//for (int i = 0; i < s; i++) {
	//	if (SameRoot(p[i].first, p[i].second)) {
	//		cout << "true"<<endl;
	//	}
	//	else {
	//		cout << "false" << endl;;
	//	}
	//}

	//pair<int, int>* p = new pair<int, int>[s];
	//for (int i = 0; i < s; i++) {
		//cin >> p[i].first >> p[i].second;
	//}
	for (int i = 0; i < s; i++) {
		int a = 0, b = 0;
		cin >> a >> b;
		if (SameRoot(a,b)) {
			cout << "true" << endl;
		}
		else {
			cout << "false" << endl;;
		}
	}
}

int main() {
	func();
	//system("pause");
	return 0;
}
*/