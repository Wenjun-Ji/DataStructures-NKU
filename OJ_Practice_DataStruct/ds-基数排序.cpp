#include<iostream>
using namespace std;
#include<vector>
#include<queue>
#include<cmath>
//基数排序的三个重要变量  d--最大位数（排序轮数） n（多少个元素） r（基数/桶的个数）
//基数排序的时间复度为 O(d(r+n))  其中n代表每一轮排序收集的复杂度， r代表每一轮排序放回的复杂度
int d;
int r=10;
int n;
vector<int> v;
vector<queue<int>> t;

int get_bit(int a) {
	int count = 0;
	while (a != 0) {
		a /= 10;
		count++;
	}
	return count;
}

void get_b() {
	int max = -1e9;
	for (int i = 0; i < n; i++) {
		if (v[i] > max)
			max = v[i];
	}
	//cout <<"max:" << max << endl;
	d = get_bit(max);
	//cout <<"d:" << d << endl;
}

void Init_v() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		v.push_back(temp);

	}
	for (int i = 0; i < r; i++) {
		queue<int> q;
		t.push_back(q);
	}
}

int get_single(int num,int k) {
	for (int i = 1; i < k; i++) {
		num /= 10;
	}
	return num % 10;
}

void Sort() {
	for (int i = 1; i <= d; i++) {
		//收集
		for (int j = 0; j < n; j++) {
			t[get_single(v[j], i)].push(v[j]);
		}
		v.clear();
		//放回
		for (int j = 0; j < r; j++) {
			while (!t[j].empty()) {
				v.push_back(t[j].front());
				t[j].pop();
			}
		}
		for (int j = 0; j < n; j++) {
			cout << v[j];
			if(j<n-1)cout<<" ";
		}
		cout << endl;
	}
}



int main() {
	//cout << get_single(12345, 3) << endl;

	Init_v();
	get_b();
	Sort();
	system("pause");
	return 0;
}