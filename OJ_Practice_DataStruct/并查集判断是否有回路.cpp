#include<iostream>
using namespace std;
#define MaxSize 100

int Set[MaxSize];

void Init(int n) {
	for (int i = 0; i < n; i++) {
		Set[i] = i;
	}
}
int Find(int a) {
	while (Set[a] != a) {
		a = Set[a];
	}
	return a;
}

bool Same(int a,int b) {
	if (Find(a) == Find(b)) return true;
	return false;
}

void Union(int a,int b) {
	Set[Find(a)] = Find(b);
}

void func() {
	int n, m;
	cin >> n >> m;
	int** edge = new int* [m];
	for (int i = 0; i < m; i++) {
		*(edge + i) = new int[2];
	}
	for (int i = 0; i < m; i++) {
		cin >> edge[i][0] >> edge[i][1];
	}
	Init(n);

	for (int i = 0; i < m; i++) {
		if (!Same(edge[i][0], edge[i][1])) {
			Union(edge[i][0], edge[i][1]);
		}else {
			cout << "yes";
			return;
		}
	}
	cout << "no" << endl;

}


int main(){
	func();
	system("pause");
	return 0;
}