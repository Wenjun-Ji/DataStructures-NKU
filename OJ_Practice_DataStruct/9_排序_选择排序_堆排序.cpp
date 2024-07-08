#include<iostream>
using namespace std;
#define MaxSize 100

struct MaxHeap{
	int size = 0;
	int heap[MaxSize];
	MaxHeap() {
		size = 0;
		for (int i = 0; i < MaxSize; i++) {
			heap[i] = 0;
		}
	}
	void Insert(int e) {
		heap[++size] = e;

	}
	int DeleteMax() {
		int max = heap[1];
		swap(heap[1], heap[size--]);
		Adjust(1);
		return heap[1];
	}
	void CreatMaxHeap(int a[],int n) {
		for (int i = 0; i < n; i++) {
			heap[i + 1] = a[i];
			size++;
		}
		Adjust(size / 2);
	}
	void Adjust(int i) {
		for (int index = i; index >= 1; index--) {
			_Adjust(index);
		}
	}
	void _Adjust(int index) {
		int left = index * 2;
		int right = index * 2 + 1;
		if (left > size) {
			return;
		}
		else if (right <= size) {
			if (heap[left] > heap[right]) {
				if (heap[index] < heap[left]) {
					swap(heap[index], heap[left]);
					_Adjust(left);
				}
			}
			else {
				if (heap[index] < heap[right]) {
					swap(heap[index], heap[right]);
					_Adjust(right);
				}
			}
		}
		else if (left <= size && heap[index] < heap[left]) {
			swap(heap[index], heap[left]);
			_Adjust(left);
		}

	}
	void show() {
		for (int i = 0; i < size; i++) {
			cout << heap[i] << " ";
		}
		cout << endl;
	}
};

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void HeapSort(int a[],int n) {
	MaxHeap h;
	h.CreatMaxHeap(a, n);

	for (int i = 0; i < n - 1; i++) {
		h.DeleteMax();
	}
	for (int i = 0; i < n; i++) {
		a[i] = h.heap[i + 1];
	}
}

void print(int a[],int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
}

int main() {
	int a[4] = { 5,4,9,8 };
	HeapSort(a, 4);
	print(a, 4);
	system("pause");
	return 0;
}