#include<iostream>
using namespace std;
struct Node {
	int data;
	Node* next;
	Node():next(NULL) {}
	Node(int e):data(e),next(NULL) {}
	Node(Node* p) :data(p->data), next(NULL) {}
};
struct Stack {
	Node* head;
	Stack() { head = new Node(); }
	bool empty() {
		if (head->next == NULL) return true;
		return false;
	}
	int getnum() {
		if (empty())return 0;
		Node* p = head;
		int j = 0;
		while (p->next!=NULL) {
			p = p->next;
			j++;
		}
		return j;
	}
	void push(Node *node) {
		if (empty()) {head->next = node; return;}
		node->next = head->next;
		head->next = node;
	}
	Node * pop() {
		if (empty()) return NULL;
		Node* p = head->next;
		head->next = head->next->next;
		p->next = NULL;
		return p;
	}
	Node* top() {
		if (empty()) return NULL;
		Node* p = new Node(head->next);
		return p;
	}
	void show() {
		if (empty())return;
		Node* p = head->next;
		while (p != NULL) {
			cout << p->data << " ";	
			p = p->next;
		}
	}
};

Stack* reverse(Stack* s){
	Stack* ss = new Stack();
	while (!s->empty()) {
		ss->push(s->pop());
	}
	return ss;
}
int main() {
	Stack* s=new Stack();
	s->push(new Node(1));
	s->push(new Node(2));
	s->push(new Node(3));
	s->show(); cout << endl;
	Stack* ss = reverse(s);
	ss->show(); cout << endl;
	ss->pop();
	ss->show(); cout << endl;
	cout << ss->top()->data << endl;


	system("pause");
	return 0;
}