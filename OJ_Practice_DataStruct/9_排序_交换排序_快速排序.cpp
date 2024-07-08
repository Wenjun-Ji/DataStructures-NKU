#include<iostream>
using namespace std;


void swap(int & a,int & b) {
	int temp = a;
	a = b;
	b = temp;
}


//左右指针法  
int Partition_Hoare(int*a, int left, int right) {
	int i = left;
	int j = right;
	int key = a[left];

	while (i != j) {
		while (i < j && a[j] >= key)      	 //向左找到小于基准值的值的下标
			j--;
		while (i < j && a[i] <= key)      	 //向右找到大于基准值的值的下标
			i++;
		swap(a[i], a[j]);
	}
	/*   i等于j时跳出循环 当前基准值此时在下标为i的位置(合适的位置)   */
	swap(a[left], a[i]);	                 //最左边的元素变为处于当前合适位置的元素,把基准值放在合适位置                                                 
	return i;                                  //返回合适位置(i,j都可以)
}

int part(int *a,int low,int high){
	int i = low, j = high, pivot = a[low];
	while (i < j) {
		while (i < j && a[j] > pivot) {
			j--;
		}
		if (i < j) {
			swap(a[i++], a[j]);//注意这里j从后往前走，但++的是i
		}	
		while (i < j && a[i] < pivot) {
			i++;
		}
		if (i < j) {
			swap(a[i], a[j--]); //注意这里i从前往后走，但--的是j
		}
	}
	return i;
}

void quickSort(int *a,int low,int high) {
	if (low < high) {
		int mid = part(a, low, high);
		quickSort(a,low, mid - 1);
		quickSort(a, mid + 1, high);
	}
}

void print(int a[], int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
}




int main() {

	int a[5] = { 5 ,4 ,9 , 4 , 3 };
	quickSort(a, 0, 4);
	print(a,5);

	system("pause");
	return 0;
}