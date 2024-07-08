#include<iostream>
using namespace std;
int main() {
	int m, n;
	cin >> m >> n;
	int** arr = new int* [m];
	for (int i = 0; i < m; i++) {
		*(arr + i) = new int[n];
	}
	//输入
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
		}
	}
	////输出
	//for (int i = 0; i < m; i++) {
	//	for (int j = 0; j < n; j++) {
	//		cout << arr[i][j]<<" ";
	//	}
	//	cout << endl;
	//}
	//回型输出
	int count = 0, cnt = 1;
	int i = 0;
	if (m == n && m % 2 == 1) {
		while (1) {
			if (cnt == 1) {
				for (int k = i; k < n - i - 1; k++) {
					cout << arr[i][k] << " ";
					count++;
					if (count == m * n-1)break;
				}
				for (int k = i; k < m - i - 1; k++) {
					cout << arr[k][n - i - 1] << " ";
					count++;
					if (count == m * n-1)break;
				}
				for (int k = n - i - 1; k > i; k--) {
					cout << arr[m - i - 1][k] << " ";
					count++;
					if (count == m * n-1)break;
				}
				for (int k = m - i - 1; k > i; k--) {
					cout << arr[k][i] << " ";
					count++;
					if (count == m * n-1)break;
				}
				if (count == m * n - 1) { cout << arr[m / 2][n / 2]; break; }
				cnt *= -1;
			}
			else if (cnt == -1) {
				for (int k = i; k < m - i - 1; k++) {
					cout << arr[k][i] << " ";
					count++;
					if (count == m * n-1)break;
				}
				for (int k = i; k < n - i - 1; k++) {
					cout << arr[m - i - 1][k] << " ";
					count++;
					if (count == m * n-1)break;
				}
				for (int k = m - i - 1; k > i; k--) {
					cout << arr[k][n - i - 1] << " ";
					count++;
					if (count == m * n-1)break;
				}
				for (int k = n - i - 1; k > i; k--) {
					cout << arr[i][k] << " ";
					count++;
					if (count == m * n-1)break;
				}
				if (count == m * n - 1) { cout << arr[m / 2][n / 2]; }
				cnt *= -1;
			}
			i++;
		}
	
	}
	else {
		while (1) {
			if (cnt == 1) {
				for (int k = i; k < n - i - 1; k++) {
					cout << arr[i][k] << " ";
					count++;
					if (count == m * n)break;
				}
				for (int k = i; k < m - i - 1; k++) {
					cout << arr[k][n - i - 1] << " ";
					count++;
					if (count == m * n)break;
				}
				for (int k = n - i - 1; k > i; k--) {
					cout << arr[m - i - 1][k] << " ";
					count++;
					if (count == m * n)break;
				}
				for (int k = m - i - 1; k > i; k--) {
					cout << arr[k][i] << " ";
					count++;
					if (count == m * n)break;
				}
				if (count == m * n)break;
				cnt *= -1;
			}
			else if (cnt == -1) {
				for (int k = i; k < m - i - 1; k++) {
					cout << arr[k][i] << " ";
					count++;
					if (count == m * n)break;
				}
				for (int k = i; k < n - i - 1; k++) {
					cout << arr[m - i - 1][k] << " ";
					count++;
					if (count == m * n)break;
				}
				for (int k = m - i - 1; k > i; k--) {
					cout << arr[k][n - i - 1] << " ";
					count++;
					if (count == m * n)break;
				}
				for (int k = n - i - 1; k > i; k--) {
					cout << arr[i][k] << " ";
					count++;
					if (count == m * n)break;
				}
				if (count == m * n)break;
				cnt *= -1;
			}
			i++;
		}
	}
	//system("pause");
	return 0;
}