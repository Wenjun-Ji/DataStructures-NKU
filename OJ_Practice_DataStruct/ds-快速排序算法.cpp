#include<iostream>
using namespace std;

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void print(int a[],int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}






int getIndex(int a[], int n, int low, int high) {
	int pivot = a[high];
	int i = 0, j = high;//注意这里的j不可以是high-1,否则会造成单个元素时 错误交换
	while (i < j) {
		while (i < j && a[i] <= pivot) {
			i++;
		}
		while (i < j && a[j]>=pivot) {
			j--;
		}
		if (i < j) {
			swap(a[i], a[j]);
		}
	}

	swap(a[high], a[i]);
	return i;
}

void QuickSort(int a[],int n,int low,int high) {
	if (low < high) {
		int index = getIndex(a, n, low, high);
		print(a, n);
		QuickSort(a,n,low,index-1);
		QuickSort(a,n,index+1,high);
	}
}


void func() {
	int n = 0;
	cin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
	QuickSort(a, n, 0, n - 1);

}



int main() {
	func();

	system("pause");
	return 0;
}