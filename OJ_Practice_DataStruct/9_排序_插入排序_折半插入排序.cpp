#include<iostream>
using namespace std;

void MidInsertSort(int a[],int n) {
	int low = 0, high = 0, mid = 0,temp=0;
	for (int i = 1; i < n; i++) {
		low = 0, high = i - 1,temp=a[i];
		while (low <= high) {
			 mid = (low + high) / 2;
			 if (temp < a[mid]) {
				 high = mid - 1;
			 }
			 else {
				 low = mid + 1;
			 }
		}
		for (int j = i-1; j >=low; j--) {
			a[j + 1] = a[j];
		}
		a[low] = a[i];
	}

}

void print(int a[], int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
}


int main() {
	int a[5] = { 8,5,9,2,3 };
	MidInsertSort(a, 5);
	print(a, 5);

}

