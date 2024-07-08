#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
vector<vector<int>> resultMerge;
vector<vector<int>> resultInsert;
void print(int a[], int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

void Merge(int a[], int n, int low1, int high1, int low2, int high2) {
	int* b = new int[n];
	for (int i = 0; i < n; i++) {
		b[i] = a[i];
	}
	int i = 0, j = 0, k = 0;
	for (i = low1, j = low2, k = low1; i <= high1 && j <= high2; k++) {
		if (b[i] < b[j]) {
			a[k] = b[i++];
		}
		else {
			a[k] = b[j++];
		}
	}
	while (i <= high1) { a[k++] = b[i++]; }
	while (j <= high2) { a[k++] = b[j++]; }
}
void MergeSort(int a[], int n) {
	int low1 = 0, high1 = 0;
	int low2 = 1, high2 = 1;

	for (int i = 0; pow(2, i) < n; i++) {
		low1 = 0;
		high1 = low1 + (int)pow(2, i) - 1;
		low2 = low1 + pow(2, i);
		high2 = low2 + (int)pow(2, i) - 1;
		if (low2 < n && high2 >= n)
			high2 = n - 1;
		while (high2 < n) {
			//print(a, n);
			Merge(a, n, low1, high1, low2, high2);
			low1 += 2 * (int)pow(2, i);
			high1 = low1 + (int)pow(2, i) - 1;
			low2 += 2 * (int)pow(2, i);
			high2 = low2 + (int)pow(2, i) - 1;
			if (low2 < n && high2 >= n)
				high2 = n - 1;
		}
		//cout << "µÚ" << i << "´Îµü´ú£º";
		//print(a, n);
		vector<int> v;
		for (int i = 0; i < n; i++) {
			v.push_back(a[i]);
		}
		resultMerge.push_back(v);
	}
}
void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void ChooseSort(int a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		int index = i;
		for (int j = i; j < n; j++) {
			if (a[j] < a[index]) {
				index = j;
			}
		}
		swap(a[i], a[index]);
		//print(a, n);
		vector<int> v;
		for (int i = 0; i < n; i++) {
			v.push_back(a[i]);
		}
		resultInsert.push_back(v);
	}
}


void InsertSort(int a[], int n) {
	for (int i = 0; i < n ; i++) {
		int j = 0;
		int temp = a[i];
		for (j = i-1; j >= 0 && a[j] > temp; j--) {
			a[j+1] = a[j];
		}
		a[j+1]=temp;
		//print(a, n);
		vector<int> v;
		for (int i = 0; i < n; i++) {
			v.push_back(a[i]);
		}
		resultInsert.push_back(v);
	}
}

void func() {
	int n = 0;
	cin >> n;
	int* A = new int[n];
	int* a = new int[n];

	for (int i = 0; i < n; i++) {
		cin >> A[i];
		a[i] = A[i];
	}
	vector<int> test;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		test.push_back(x);
	}
	MergeSort(a, n);
	for (int i = 0; i < n; i++) {
		a[i] = A[i];
	}
	InsertSort(a, n);
	//cout << endl;
	//for (vector<vector<int>>::iterator i = resultMerge.begin(); i != resultMerge.end(); i++) {
	//	for (vector<int>::iterator j = (*i).begin(); j != (*i).end(); j++) {
	//		cout << (*j) << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//for (vector<vector<int>>::iterator i = resultInsert.begin(); i != resultInsert.end(); i++) {
	//	for (vector<int>::iterator j = (*i).begin(); j != (*i).end(); j++) {
	//		cout << (*j) << " ";
	//	}
	//	cout << endl;
	//}


	for (vector<vector<int>>::iterator i = resultMerge.begin(); i != resultMerge.end(); i++) {
		if ((*i) == test) {
			cout << "Merge Sort" << endl;
			i++;
			for (vector<int>::iterator j = (*i).begin(); j != (*i).end(); j++){
				cout << (*j) << " ";
			}
			return;
		}
	}
	for (vector<vector<int>>::iterator i = resultInsert.begin(); i != resultInsert.end(); i++) {
		if ((*i) == test) {
			cout << "Insertion Sort"<<endl;
			i++;
			for (vector<int>::iterator j = (*i).begin(); j != (*i).end(); j++) {
				cout << (*j) << " ";
			}
			return;
		}
	}


}


int main() {

	func();

	system("pause");
	return 0;
}