#include<iostream>
using namespace std;
struct Node {
	int data;
	Node* next;
	Node(): next(NULL){}
	Node(int e):data (e),next(NULL) {}
	Node(Node* p) :data(p->data), next(NULL) {}
};

struct Queue {
	Node* front;
	Node* rear;
	Queue() { front = rear = NULL; }
	bool empty() {
		if (front == NULL)return true;
		return false;
	}
	void push(Node*node){
		if (empty()) { front = rear = node; return; }
		rear->next = node;
		rear = node;
	}
	Node* pop() {
		if (empty()) {  return NULL; }
		Node* p = front;
		front = front->next;
		p->next = NULL;
		return p;
	}
	void show() {
		if (empty()) return;
		Node* p = front;
		while (p != rear) {
			cout << p->data<<" ";
			p = p->next;
		}
		cout << p->data;
	}
	

};

int main() {
	Queue q;
	q.push(new Node(1));
	q.push(new Node(2));
	q.push(new Node(3));
	q.push(new Node(4));
	q.show();
	q.pop();
	q.show();

	system("pause");
	return 0;
}