#include<iostream>
using namespace std;
#define INF 9999999


void Floyd(int**vertics,int n) {
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (vertics[i][j] > vertics[i][k] + vertics[k][j])
					vertics[i][j] = vertics[i][k] + vertics[k][j];
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (vertics[i][j] == INF)
				vertics[i][j] = -1;
		}
	}

}

void func() {
	int n = 0;
	cin >> n;
	int** vertics = new int* [n];
	for (int i = 0; i < n; i++) {
		*(vertics + i) = new int[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j)
				vertics[i][j] = INF;
			else
				vertics[i][j] = 0;
		}
	}
	int m = 0;
	cin >> m;
	for (int i = 0; i < m; i++) {
		int u = 0, v = 0, w = 0;
		cin >> u >> v >> w;
		vertics[u][v] = w;
	}
	Floyd(vertics, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << vertics[i][j];
			if(j<n-1)cout<<" ";
		}
		if(i<n-1)cout << endl;
	}
}


int main() {
	func();
	system("pause");
	return 0;
}