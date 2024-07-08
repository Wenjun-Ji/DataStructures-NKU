#include<iostream>
using namespace std;
struct LinkNode {
	int num;
	LinkNode* next;
	LinkNode() { next = NULL; }
	LinkNode(int e) :num(e) { next = NULL; }
};

struct LinkList {
	LinkNode* head;
	LinkNode* tail;
	LinkList() { head = tail = NULL; }
	void Generate_Circle_List(int n) {
		for (int i = 0; i < n; i++) {
			LinkNode* p = new LinkNode(i + 1);
			this->RInsert(p);
		}
		tail->next = head;
	}
	void RInsert(LinkNode* p) {
		if (head == NULL) {
			head = tail = p;
		}
		else {
			tail->next = p;
			tail = p;
		}
	}
	int getnum() {
		int j = 1;
		LinkNode* p = head;
		if (head == NULL) {
			return 0;
		}
		else if (head == tail) {
			return 1;
		}
		else {
			while (p != tail) {
				p = p->next;
				j++;
			}
			return j;
		}
	}
	void DeleteN(int n) {
		if (n == 1) {
			tail->next = head->next;
			head = head->next;
		}
		else {
			int j = 1;
			LinkNode* p = head;
			while (j != n - 1) {
				p = p->next;
				j++;
			}
			LinkNode* q = p->next;
			p->next = q->next;
			delete q;
		}
	}
	LinkNode* DeleteP(LinkNode* q) {
		if (q == head) {
			//cout << "!!!" << endl;
			tail->next = head->next;
			head = head->next;
			//cout << q->num << endl;
			delete q;
			return head;
		}
		else if (head->next == tail) {
			if (q == head) {
				head = tail;
				//cout << q->num << endl;
				delete q;
				return head;
			}
			else if(q==tail){
				tail = head;
				//cout << q->num << endl;
				delete q;
				return head;
			}
		}
		else {
			int j = 1;
			LinkNode* p = head;
			while (p->next != q) {
				p = p->next;
				j++;
			}
			p->next = q->next;
			//cout << q->num << endl;
			if (q == tail) {
				tail = p;
			}
			delete q;
			//cout << p->next->num << endl;
			return p->next;
		}
	}
	void josephus() {
		int n = 0;
		int k = 0;
		cin >> n >> k;
		Generate_Circle_List(n);
		int j = 1;
		LinkNode* p = head;
		while (1) {
			//cout <<"!!!" << p->num << endl;
			if (head == tail) {
				cout << head->num;
				return;
			}
			if (j == k) {
				cout << p->num<<"->";
				p=DeleteP(p);
				//show();
				j = 1;
			}
			p = p->next;
			j++;
		}
	}
	void show() {
		LinkNode* p=head;
		if (head == NULL) {
			return;
		}
		if (head == tail) {
			cout << head->num<<endl;
			return;
		}
		while (p->next != head) {
			cout << p->num << " ";
			p = p->next;
		}
		cout << p->num;
		cout << endl;
	}
};




int main() {
	LinkList l;
	l.josephus();
	system("pause");
	return 0;
}