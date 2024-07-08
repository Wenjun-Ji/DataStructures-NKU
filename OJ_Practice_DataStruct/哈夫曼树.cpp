/*
题目描述
合并两个水晶碎块需要的能量是两个水晶碎块的能量和。假设只可以两两合并，请求出一堆水晶碎块合并成一整块水晶需要的最小能量。

题目输入：

第一行输入水晶碎块的个数n(1<=n<100)，随后输入n个整数

题目输出：

合并最小能量（取值在long范围内）



提示：注意题目标题。



附件

样例输入输出
样例1
输入:
6
8282
165
5
7431
9137
3
输出:
48694
*/

#include<iostream>
using namespace std;
struct HFNode{
	int weight;
	int left;
	int right;
	int parent;
	HFNode() :weight(0), left(0), right(0), parent(0) {}
	HFNode(int w,int l,int r,int p) :weight(w), left(l), right(r), parent(p) {}
};

struct HFTree{
	HFNode* HFT;
	int n;
	int m;
	HFTree() : HFT(NULL), n(0) {}
};

void select(HFTree& t,int m, int& a, int& b) {
	for (int i = 1; i < m; i++) {
		if (t.HFT[i].parent == 0) {
			a = i; break;
		}
	}
	for (int i = 1; i < m; i++) {
		if (t.HFT[i].parent == 0&&t.HFT[i].weight<t.HFT[a].weight) {
			a = i;
		}
	}
	for (int i = 1; i < m; i++) {
		if (t.HFT[i].parent == 0 && i != a) {
			b = i; break;
		}
	}
	for (int i = 1; i < m; i++) {
		if (t.HFT[i].parent == 0 && t.HFT[i].weight < t.HFT[b].weight && i != a) {
			b = i;
		}
	}
}


void func(HFTree& hft) {
	cin >> hft.n;
	hft.m = 2 * hft.n - 1;
	hft.HFT = new HFNode[hft.m+1];
	for (int i = 1; i <= hft.n; i++) {
		cin >> hft.HFT[i].weight;
	}
	for (int i = hft.n+1; i <= hft.m; i++) {
		int a=0, b=0;
		select(hft,i ,a, b);
		//cout << a <<" "<< b << endl;
		hft.HFT[i].weight = hft.HFT[a].weight + hft.HFT[b].weight;
		hft.HFT[i].left = a;
		hft.HFT[i].right = b;
		hft.HFT[a].parent = i;
		hft.HFT[b].parent = i;
	}

	int sum = 0;
	for (int i = 1; i <= hft.m; i++) {
		//sum += hft.HFT[i].weight;
		//cout << i << " " 
			//<< hft.HFT[i].weight << " " 
			//<< hft.HFT[i].left << " " 
			//<< hft.HFT[i].right << " " 
			//<< hft.HFT[i].parent << " " 
			//<< endl;
	}


	for (int i = 1; i <= hft.n; i++) {
		int count = 0;
		int p = hft.HFT[i].parent;
		while (p != 0) {
			p = hft.HFT[p].parent;
			count++;
		}
		//cout << count << endl;
		sum += hft.HFT[i].weight * count;
	}
	cout << sum;
}

int main() {
	HFTree t;
	func(t);

	system("pause");
	return 0;
}