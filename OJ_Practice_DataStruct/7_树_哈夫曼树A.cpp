#include<iostream>
using namespace std;

struct HFNode{
	long weight;
	int lchild;
	int rchild;
	int parent;
};

struct HFTree{
	HFNode* HFT;
	int n;
	HFTree():HFT(NULL),n(0) {}
};

void select(HFTree& t,int m,int &s1,int&s2) {
	for (int i = 0; i < m; i++) {
		if (t.HFT[i].parent == 0) {
			s1 = i;
		}
	}
	for (int i = 0; i < m; i++) {
		if (t.HFT[i].parent == 0 && t.HFT[i].weight < t.HFT[s1].weight) {
			s1 = i;
		}
	}
	for (int i = 0; i < m; i++) {
		if (t.HFT[i].parent == 0&&i!=s1) {
			s2 = i;
		}
	}
	for (int i = 0; i < m; i++) {
		if (t.HFT[i].parent == 0 && t.HFT[i].weight < t.HFT[s2].weight&& i != s1) {
			s2 = i;
		}
	}
}
void InitHFTree(HFTree & t,long a[],int n) {
	t.n = n;
	int m = 2 * n - 1;
	t.HFT = new HFNode[m];
	for (int i = 0; i < m; i++) {
		t.HFT[i].lchild = 0;
		t.HFT[i].rchild = 0;
		t.HFT[i].parent = 0;
		if (i < n) {
			t.HFT[i].weight = a[i];
		}
	}
	int s1=0, s2=0;
	for (int i = n; i < m; i++) {
		select(t,i, s1, s2);
		t.HFT[i].lchild = s1;
		t.HFT[i].rchild = s2;
		t.HFT[i].weight = t.HFT[s1].weight + t.HFT[s2].weight;
		t.HFT[s1].parent = i;
		t.HFT[s2].parent = i;
	}
}
void show(HFTree& t,string HF[]) {
	int m = 2 * t.n - 1;
	for (int i = 0; i < m; i++) {
		cout << i << " "
			<< t.HFT[i].weight << " "
			<< t.HFT[i].lchild << " "
			<< t.HFT[i].rchild << " "
			<< t.HFT[i].parent << " ";
		if(i<t.n)cout<< HF[i];
		cout << endl;
	}
}

void getHF(string HF [],int n,HFTree&t) {
	for (int i = 0; i < n; i++) {
		int parent = t.HFT[i].parent;
		int child = i;
		while (parent!=0) {
			if (t.HFT[parent].lchild == child) {
				HF[i] += '0';
			}
			else if (t.HFT[parent].rchild == child) {
				HF[i] += '1';
			}
			child = parent;
			parent = t.HFT[child].parent;
		}
	}
}

long getsum(HFTree& t,string HF[]) {
	long sum=0;
	for (int i = 0; i < t.n; i++) {
		sum += t.HFT[i].weight * HF[i].length();
	}
	return sum;
}

void func() {
	int n = 0;
	cin >> n;
	long *a = new long[n];
	string* HF = new string[n];
	HFTree t;
	for (int i = 0; i < n; i++)cin >> a[i];

	InitHFTree(t, a, n);
	getHF(HF, n, t);
	//show(t,HF);

	cout << getsum(t,HF)<<endl;
}


int main() {

	func();

	//system("pause");
	return 0;
}
