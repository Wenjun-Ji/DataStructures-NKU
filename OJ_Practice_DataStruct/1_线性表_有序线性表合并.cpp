#include<iostream>
using namespace std;
int main() {
	int m, n;
	cin >> m >> n;
	int* arr = new int[m+n];
	for (int i = 0; i < m+n; i++) {
		cin >> arr[i];
	}
	int temp = 0;
	for (int i = 0; i < m + n-1; i++) {
		for (int j = 0; j < m + n - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	for (int i = 0; i < m + n; i++) {
		cout << arr[i]<<" ";
	}
	return 0;
}