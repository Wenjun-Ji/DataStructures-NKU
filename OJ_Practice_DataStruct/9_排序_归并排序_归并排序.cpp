#include<iostream>
using namespace std;

void Merge(int a[],int n, int low, int mid, int high) {
	int *b = new int[n];
	for (int i = 0; i <= n-1; i++) {
		b[i] = a[i];
	}
	int i=0, j=0, k=0;
	for (i = low, j = mid + 1,k=low; i <= mid&&j <= high;k++) {//
		if (b[i] <= b[j]) {
			a[k] = b[i++ ];
		}
		else {
			a[k] = b[j++ ];
		}
	}
	while (i <= mid) { a[k++] = b[i++]; }
	while (j <= high) { a[k++] = b[j++]; }
	delete b;
}
void MergeSort(int a[],int n, int low, int high) {
	if (low < high) {
		int mid = (low + high) / 2;
		MergeSort(a,n, low, mid);
		MergeSort(a,n ,mid + 1, high);
		Merge(a,n, low, mid, high);
	}
}

void print(int a[], int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
}

int main() {
	int a[5] = { 2,3,6,5,1 };
	MergeSort(a,5, 0,4);
	print(a, 5);
	system("pause");
	return 0;
}