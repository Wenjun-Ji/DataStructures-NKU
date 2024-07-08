#include<iostream>
using namespace std;
struct Node {
	char data;
	Node *next;
	Node() :next(NULL){}
	Node(char c):data(c),next(NULL) {}
};
struct Stack {
	Node* head=new Node();
	Stack() { }
	void pop(char c) {
		if (head->next == NULL) {
			Node* p = new Node(c);
			head->next = p;
		}
		else {
			Node* p = new Node(c);
			p->next = head->next;
			head->next = p;
		}

	}
	void top() {
		if (head->next == NULL) {
			return;
		}
		else {
			Node* p = head->next;
			head->next = head->next->next;
			delete p;
		}
	}
	bool judge() {
		if (head->next == NULL||head->next->next==NULL) {
			return false;
		}
		if (abs(head->next->data - head->next->next->data) == 32) {
			//cout <<"!!!" << head->next->data << head->next->next->data << endl;
			return true;
		}
		return false;
	}
	void show() {
		cout << "µ±Ç°Õ»Îª£º";
		Node* p = head;
		if (p->next == NULL) { return; }
		while (p->next != NULL) {
			p = p->next;
			cout << p->data;
		}
		cout << endl;
	}
	int getnum() {
		Node* p = head;
		int j = -1;
		while (p->next != NULL) {
			p = p->next;
			j++;
		}
		return j + 1;
	}


	void func() {
		string s;
		cin >> s;
		for (int i = 0; i < s.length(); i++) {
			pop(s[i]);
			//show();
			if (judge()) {
				top();
				top();
			}
		}
		char c[100];
		Node* p = head;
		if (head->next == NULL) {
			cout << -1;
		}
		for (int i = 0; i < getnum(); i++) {
			p = p->next;
			s[i] = p->data;
		}
		for (int i = getnum() - 1; i>=0; i--) {
			cout << s[i];
		}
		cout << endl;
	}

};

int main() {
	Stack stack;
	stack.func();
	return 0;
}