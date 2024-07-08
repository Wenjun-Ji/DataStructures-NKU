#include<iostream>
#include<stack>
using namespace std;
#define INF 999999999
void Dijkstra(int start,int **vertics,int n,int path[],int dis[],int visit[]) {
	//初始化
	for (int i = 1; i <= n; i++) {
		dis[i] = vertics[start][i];
	}
	for (int i = 1; i <= n; i++) {
		if (dis[i] < INF)path[i] = start;
		else path[i] = -1;
	}
	path[start] = -1;
	for (int i = 1; i <= n; i++) {
		visit[i] = 0;
	}
	visit[start] = 1;
	int count = 0;
	for (int i = 1; i <= n; i++) {
		//寻找最近的点
		int min = INF, index = 0;
		for (int j = 1; j <= n; j++) {
			if (visit[j] == 0 && dis[j] < min) {
				min = dis[j];
				index = j;
			}
		}
		if (index == 0)continue;
		count++;
		//标记最近的点
		visit[index] = 1;
		//cout << index << " " << dis[index]<<endl;
		int x = index;
		stack<int>s;
		while (x != -1) {
			s.push(x);
			x = path[x];
		}
		cout << "No." << i << " :";
		while (!s.empty()) {
			cout <<" "<< s.top() <<" ";
			if (s.size() != 1)cout << "->";
			s.pop();
		}
		cout << ", d = " << dis[index]<<endl;

		//更新距离
		for (int j = 1; j <= n; j++) {
			if (visit[j] == 0 && dis[j]>dis[index]+vertics[index][j]) {
				dis[j] = dis[index] + vertics[index][j];
				path[j] = index;
			}
		}
	}
	//cout << count << endl;
	if (count+1 < n) {//这里很关键
		cout << "No." << count + 1 << " : No Path to";
		for (int i = 1; i <= n; i++) {
			if (dis[i] == INF) {
				cout << " " << i;
			}
		}
	}
}
void func() {
	int n = 0, m = 0;
	cin >> n>>m;
	int** vertics = new int*[n+1];
	for (int i = 0; i < n+1 ; i++) {
		*(vertics + i) = new int[n+1];
	}
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			if (i != j)
				vertics[i][j] = INF;
			else
				vertics[i][j] = 0;
		}
	}
	for (int i = 0; i < m; i++) {
		int u = 0, v = 0, w = 0;
		cin >> u >> v >> w;
		vertics[u][v] = w;
	}

	int* path = new int[n];
	int* dis = new int[n];
	int* visit = new int[n];
	int start;
	cin >> start;
	Dijkstra(start,vertics,n, path, dis,visit);


}

int main() {
	func();

	system("pause");
	return 0;
}


/*
8 10
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
1

No.1 : 1 -> 5 , d = 5
No.2 : 1 -> 5 -> 4 , d = 7
No.3 : 1 -> 5 -> 6 , d = 8
No.4 : 1 -> 5 -> 6 -> 3 , d = 9
No.5 : No Path to 2 7 8
*/