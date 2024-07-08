/*
���ж��������Ϣ�Ƿ�������һ������������������ ��������Ӹ���ʼ��ǰ����������������not a tree��
���룺

��������ڵ����n���ڵ��Ŵ�1��n��Ȼ������n���ڵ���Ϣ����Ϣ�������£��ڵ��� ���ӱ�� �Һ��ӱ�š�������ӽڵ�Ϊ�����ӱ��Ϊ0������ڵ�������ϢΪ5 0 0,�����ڵ���Ϊ5�����Һ��Ӿ�Ϊ�ա�
������Ϣ��Ϊ�������ڵ�����˳����������ǲ���ȱ�����ÿ���ڵ��������һ����ֻ��һ�Ρ�
�����

�����Ϊ�� �����not a tree
���Ϊ������ǰ������Ӹ��ڵ�����ڵ��š����֮��ո���������һ���ڵ����û�пո�

*/

#include<iostream>
#include<map>
#include<algorithm>
using namespace std;

struct Node{
	int data;
	Node* left, * right;
	Node(int e) :data(e), left(NULL), right(NULL) {}
	Node() :data(0), left(NULL), right(NULL) {}
};

struct Tree {
	Node* root;
	Tree() :root(NULL) {};
	//void Init() {
	//	int n;
	//	cin >> n;
	//	int** arr = new int* [n];
	//	for (int i = 0; i < n; i++) {
	//		*(arr + i) = new int[3];
	//	}
	//	for (int i = 0; i < n; i++) {
	//		for (int j = 0; j < 3; j++) {
	//			cout << arr[i][j] << " ";
	//		}
	//		cout << endl;
	//	}

	//}
};

int Init(int** arr, int n) {
	int p = 0, l = 0, r = 0;
	for (int i = 0; i < n; i++) {
		cin >> arr[i][0] >> arr[i][1] >> arr[i][2];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 3; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	int count = 0;
	int* flag = new int[n];
	for (int i = 0; i < n; i++) {
		flag[i] = 1;
	}
	for (int i = 0; i < n; i++) {
		if (arr[i][1]) { flag[arr[i][1] - 1] = 0; count++; }
		if (arr[i][2]) { flag[arr[i][2] - 1] = 0; count++; }
	}

	if (count == n - 1) {
		for (int i = 0; i < n; i++) {
			if (flag[i]) { cout << i + 1; return i + 1; }
		}
	}else {
		return 0;
	}
}

void visit(int a) {
	cout << a;
}
void FirstTraverse(int**arr,int root) {
	if (root == 0) {
		return;
	}
	else {
		visit(arr[root-1][0]);
		FirstTraverse(arr,arr[root-1][1]);
		FirstTraverse(arr,arr[root-1][2]);
	}
}

bool cmp(int*a,int*b) {
	return a[0] < b[0];
}

void func() {
	int n;
	cin >> n;
	int** arr = new int* [n];
	for (int i = 0; i < n; i++) {
		*(arr + i) = new int[3];
	}
	int root = Init(arr, n);
	sort(arr, arr + n, cmp);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 3; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}


	if (root) {
		FirstTraverse(arr,root);
	}
	else {
		cout << "not a tree";
	}
}

int main() {
	func();
	system("pause");
	return 0;
}

/*
����:
7
1 2 3
2 0 0
3 0 4
4 0 5
5 0 0
6 1 7
7 6 0
���:
not a tree

7
3 0 4
1 2 3
2 0 0
4 0 5
6 1 7
5 0 0
7 0 0
���:
6 1 2 3 4 5 7


*/