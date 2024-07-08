
#include<iostream>
#include<stack>
#include<vector>
using namespace std;
/*
ʹ�ò��鼯��ʼ����������
�����������㵽����·���洢�����У�ջ����
���ջ��Ԫ����ͬ��ջ����ͬ�Ļ�������һ����ջ��Ԫ�ؼ�ΪLCA
*/

//ʹ�ò��鼯��ʼ����������
int Set[10001];
void Init(int n) {
	for (int i = 0; i <= n; i++) {
		Set[i] = i;
	}
}
int find(int a) {
	while (Set[a] != a) {
		a = Set[a];
	}
	return a;
}
bool Same(int a,int b) {
	if (find(a) == find(b)) {
		return true;
	}
	return false;
}
void Union(int a,int b) {
	Set[b] = a;
}

vector<int>L;
void LCA(int n) {
	for (int i = 0; i < n - 1; i++) {
		int a=0, b=0;
		cin >> a >> b;
		Union(a, b);
	}
	int x=0,y=0;
	cin >> x >> y;
	stack<int>a;
	stack<int>b;
	a.push(x);
	while (Set[x] != x) {
		x = Set[x];
		a.push(x);
	}
	b.push(y);
	while (Set[y] != y) {
		y = Set[y];
		b.push(y);
	}
	int lca;
	while (!a.empty()&&!b.empty()&&a.top() == b.top()) {
		lca = a.top();
		a.pop();
		b.pop();
	}
	//cout << lca<<endl;
	L.push_back(lca);
}


void func() {
	int T;
	cin >> T;
	for (int i = 0; i < T; i++) {
		int n = 0;
		cin >> n;
		Init(n);
		LCA(n);
	}
	for (int i = 0; i < T; i++) {
		cout << L[i] << endl;
	}
}



int main() {


	func();

	system("pause");
	return 0;
}