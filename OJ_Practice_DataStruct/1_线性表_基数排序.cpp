#include<iostream>
#include<cmath>
using namespace std;
//题目描述
//根据输入，输出基数排序的每趟排序结果。
//
//输入格式：输入数字为正整数，先输入排序数字个数，然后输入需要排序的数字序列。
//
//输出格式：每趟排序结果。行尾无空格。
//
//要求：程序需要实现排序，其他可以使用STL包
//
//样例输入输出
//样例1
//输入 :
//8
//2343
//6
//66
//152310
//5594
//592783
//27
//8
//输出:
//152310 2343 592783 5594 6 66 27 8
//6 8 152310 27 2343 66 592783 5594
//6 8 27 66 152310 2343 5594 592783
//6 8 27 66 152310 2343 592783 5594
//6 8 27 66 2343 5594 152310 592783
//6 8 27 66 2343 5594 152310 592783

void BinSort_Arr(int * arr, int n) {
	//int n = 0;
	//cin >> n;
	//int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	static int bin[10000];
	for (int i = 0; i < n; i++) {
		bin[arr[i]]++;
	}
	for (int i = 0; i < 10000; i++) {
		if (bin[i] != 0) {
			while (bin[i] != 0) {
				cout << i;
				bin[i]--;
			}
		}
	}
}

struct Node {
	int data;
	Node* next;
	Node() :next(NULL) {}
	Node(int e) :data(e),next(NULL) {}
};
struct List {
	Node* head;
	Node* tail;
	List() { tail = head = NULL; }
	void InitList() {
		int n = 0;
		cin >> n;
		for (int i = 0; i < n; i++) {
			int e = 0;
			cin >> e;
			Node* q = new Node(e);
			this->RInsert(q);
		}
	}
	void LInsert(Node* q) {
		if (head == NULL) {
			head = tail = q;
		}
		else {
			q->next = head;
			head = q;
		}
	}
	void RInsert(Node* q) {
		if (head == NULL) {
			head = tail = q;
		}
		else {
			tail->next = q;
			tail = q;
		}
	}

	int Getnum() {
		int j = 1;
		Node* p = head;
		if (head == NULL) {
			return 0;
		}
		else {
			while (p != tail) {
				p = p->next;
				j++;
			}
		}
		return j;
	}

	void BinSort(int range) {
		//初始化箱子
		Node** bottom;
		Node** top;
		bottom = new Node*[range+1];
		top = new Node * [range+1];
		for (int i = 0; i <= range; i++) {
			bottom[i] = top[i] = NULL;
		}
		//把数据放进箱子
		for(; head != NULL; head = head->next) {
			int thebin = head->data;
			if (bottom[thebin] == NULL) {
				bottom[thebin] = top[thebin] = head;
			}
			else {
				top[thebin]->next = head;
				top[thebin] = head;
			}
		}
		//把箱子连接起来并从箱子中取数据
		Node* tail = NULL;
		for (int i = 0; i <= range; i++) {
			if (bottom[i] != NULL) {
				if (head == NULL) {
					head = bottom[i];
				}else {
					tail->next = bottom[i];
				}
				tail = top[i];
			}
		}
		if (tail != NULL) {
			tail->next = NULL;
		}
	}

	void RadixSort(int range) {
		//cout << GetMaxDigit();
		for (int i = 0; i < GetMaxDigit(); i++) {
			//初始化箱子
			Node** bottom;
			Node** top;
			bottom = new Node * [range + 1];
			top = new Node * [range + 1];
			for (int i = 0; i <= range; i++) {
				bottom[i] = top[i] = NULL;
			}
			//把数据放进箱子
			for (; head != NULL; head = head->next) {
				int thebin = (head->data % (int)pow(10, i + 1)) / (int)pow(10, i);
				//cout << thebin<<endl;
				if (bottom[thebin] == NULL) {
					bottom[thebin] = top[thebin] = head;
				}
				else {
					top[thebin]->next = head;
					top[thebin] = head;
				}
			}
			//把箱子连接起来并从箱子中取数据
			Node* tail = NULL;
			for (int i = 0; i <= range; i++) {
				if (bottom[i] != NULL) {
					if (head == NULL) {
						head = bottom[i];
					}
					else {
						tail->next = bottom[i];
					}
					tail = top[i];
				}
			}
			if (tail != NULL) {
				tail->next = NULL;
			}
			Show();
			if(i< GetMaxDigit()-1)
				cout << endl;
		}
	}
	
	
	
	void Show() {
		Node* p = head;
		for (; p != NULL; p = p->next) {
			cout << p->data;
			if(p->next!=NULL)
				cout<<" ";
		}
	}

	int GetMaxDigit() {
		int max = -1;
		Node* p = head;
		for (; p!=NULL; p=p->next) {
			if (max < p->data) {
				max = p->data;
			}
		}
		int count = 0;
		while (max != 0) {
			max /= 10;
			count++;
		}
		return count;
	}
};





int main() {
	int n = 0;
	List l;
	l.InitList();
	l.RadixSort(10);


	return 0;
}