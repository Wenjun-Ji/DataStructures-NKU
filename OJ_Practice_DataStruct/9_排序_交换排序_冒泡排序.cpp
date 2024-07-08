#include<iostream>
using namespace std;

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void BubbleSort(int a[],int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			if (a[j] > a[j + 1]) {//从小到大
				swap(a[j], a[j + 1]);
			}
		}
	}
}

void print(int a[],int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
}


int main() {
	int a[5] = { 9,4,1,3,5 };
	print(a, 5);
	BubbleSort(a, 5);
	print(a, 5);
	system("pause");
	return 0;
}