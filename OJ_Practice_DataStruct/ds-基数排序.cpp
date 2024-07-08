#include<iostream>
using namespace std;
#include<vector>
#include<queue>
#include<cmath>
//���������������Ҫ����  d--���λ�������������� n�����ٸ�Ԫ�أ� r������/Ͱ�ĸ�����
//���������ʱ�临��Ϊ O(d(r+n))  ����n����ÿһ�������ռ��ĸ��Ӷȣ� r����ÿһ������Żصĸ��Ӷ�
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
		//�ռ�
		for (int j = 0; j < n; j++) {
			t[get_single(v[j], i)].push(v[j]);
		}
		v.clear();
		//�Ż�
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