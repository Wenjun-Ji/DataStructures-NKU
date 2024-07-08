#include<iostream>
#include<queue>
#include<cmath>
using namespace std;



struct Node {
	int data;
	Node* next;
	Node() :data(0),next(NULL){}
	Node(int e) :data(e),next(NULL) {}
};
struct Queue {
	Node* head;
	Node* rear;
	Queue():head(NULL),rear(NULL) {}
		
	bool isempty() {
		if (head == NULL) return true;
		return false;
	}
	void push(Node * p) {
		if (isempty()) {
			head = rear = p;
			return;
		}
		else {
			rear->next = p;
			rear = p;
		}
	}
	Node* pop() {
		if (isempty()){
			return NULL;
		}
		else {
			Node* p = head;
			head = head->next;
			p->next = NULL;
			return p;
		}
	}
	int front() {
		if (isempty())return -1;
		return head->data;
	}
};


//求关键字个数（位数）
int MaxBit(int a[],int n) {
	int max = a[0];
	for (int i = 0; i < n; i++) {
		if (max < a[i]) {
			max = a[i];
		}
	}
	int bit = 0;
	while (max) {
		max /= 10;
		bit++;
	}
	return bit;
}

int getbit(int data,int i) {
	int x= (data %(int)pow(10, i)) / (int)pow(10, i - 1);
	return x;
}

//基数为10
queue<Node*> radixQueue[10];
//分配
void distributeRadix(Queue &q,int i) {
	Node* p = q.head;
	Node* pp = q.head;
	while (p) {
		pp = p->next;
		radixQueue[getbit(p->data, i)].push(q.pop());
		p = pp;
	}
}

//收集
void collectRadix(Queue& q) {
	for (int i = 0; i < 10; i++) {
		while (!radixQueue[i].empty()) {
			q.push(radixQueue[i].front());
			radixQueue[i].pop();
		}
	}
}

//基数排序
void RadixSort(int a[],int n) {
	Queue q;
	for (int i = 0; i < n; i++) {
		q.push(new Node(a[i]));
	}
	int k = MaxBit(a, n);
	for (int i = 1; i <=k; i++) {
		distributeRadix(q, i);
		collectRadix(q);
	}
	Node* p = q.head;
	int j = 0;
	while (p) {
		a[j] = p->data;
		p = p->next;
		j++;
	}
}


//关键字个数
int k = 0;

void print(int a[], int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
}


int main() {
	int a [7] = {162,4654,21,483,45,123,984};
	RadixSort(a, 7);
	print(a, 7);
	system("pause");
	return 0;
}