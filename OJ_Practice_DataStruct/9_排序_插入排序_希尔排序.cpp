#include<iostream>
using namespace std;

void InsertionSort(int a[], int len) {
	int i = 0, j = 0, temp = 0;
	for (i = 1; i < len; i++) {
		temp = a[i];
		for (j = i - 1; j >= 0 && a[j] > temp; j--) {
			a[j + 1] = a[j];//前面的覆盖后面的
		}
		a[j + 1] = temp;
	}
}

void ShellSort(int a[], int n) {
	int gap = 1, i = 0, j = 0, temp = 0;
	for (gap = n / 2; gap >= 1; gap /= 2) {
		for (i = gap; i < n; i++) {
			temp = a[i];
			for (j = i - gap; j >= 0 && a[j] > temp; j -= gap) {
				a[j + gap] = a[j];
			}
			a[j + gap] = temp;
		}
	}
}


void print(int a[], int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
}



int main() {

	int a[5] = { 7,8,2,6,9 };
	ShellSort(a, 5);
	print(a, 5);

	system("pause");
	return 0;
}