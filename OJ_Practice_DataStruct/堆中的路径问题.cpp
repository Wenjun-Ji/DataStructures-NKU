#include<iostream>
using namespace std;
//�����Ա�洢����
//ÿ����һ��Ԫ�ؾ���Ҫ����һ��
//������ָ�����㵽���ڵ��·��
int N[1001];
int M[1001];
void Insert(int data,int index) {
	N[index] = data;
	while (index != 1) {
		if (N[index] > N[index / 2]) {
			int temp = N[index];
			N[index] = N[index / 2];
			N[index / 2] = temp;
			index /= 2;
		}
		else {
			break;
		}
	}
}
void Print(int index) {
	while (index != 0) {
		cout << N[index] << " ";
		index /= 2;
	}
}
void func() {
	int n=0, m=0;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		int data = 0;
		cin >>data;
		Insert(data, i);
	}
	for (int i = 1; i <= n; i++) {
		cout << N[i];
	}
	cout << endl;
	for (int i = 0; i < m; i++) {
		int x = 0;
		cin >> x;
		Print(x);
		cout << endl;
	}
}







int main() {
	func();
	system("pause");
	return 0;
}