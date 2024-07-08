#include<iostream>
using namespace std;


void swap(int & a,int & b) {
	int temp = a;
	a = b;
	b = temp;
}


//����ָ�뷨  
int Partition_Hoare(int*a, int left, int right) {
	int i = left;
	int j = right;
	int key = a[left];

	while (i != j) {
		while (i < j && a[j] >= key)      	 //�����ҵ�С�ڻ�׼ֵ��ֵ���±�
			j--;
		while (i < j && a[i] <= key)      	 //�����ҵ����ڻ�׼ֵ��ֵ���±�
			i++;
		swap(a[i], a[j]);
	}
	/*   i����jʱ����ѭ�� ��ǰ��׼ֵ��ʱ���±�Ϊi��λ��(���ʵ�λ��)   */
	swap(a[left], a[i]);	                 //����ߵ�Ԫ�ر�Ϊ���ڵ�ǰ����λ�õ�Ԫ��,�ѻ�׼ֵ���ں���λ��                                                 
	return i;                                  //���غ���λ��(i,j������)
}

int part(int *a,int low,int high){
	int i = low, j = high, pivot = a[low];
	while (i < j) {
		while (i < j && a[j] > pivot) {
			j--;
		}
		if (i < j) {
			swap(a[i++], a[j]);//ע������j�Ӻ���ǰ�ߣ���++����i
		}	
		while (i < j && a[i] < pivot) {
			i++;
		}
		if (i < j) {
			swap(a[i], a[j--]); //ע������i��ǰ�����ߣ���--����j
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