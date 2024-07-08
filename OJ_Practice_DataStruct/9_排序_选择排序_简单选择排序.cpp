#include<iostream>
using namespace std;
void swap(int &a ,int &b) {
	int temp = a;
	a = b;
	b = temp;
}

void SelectionSort(int a[],int n) {
	for (int i = 0; i < n; i++) {
		int index = i;
		for (int j = i+1; j < n; j++) {
			if (a[j] < a[index]) {
				index = j;
			}
		}	
		swap(a[i],a[index]);
	}
}

void print(int a[], int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
}


int main() {
	int a[5] = { 7,8,2,6,9 };
	SelectionSort(a, 5);
	print(a, 5);


	system("pause");
	return 0;
}