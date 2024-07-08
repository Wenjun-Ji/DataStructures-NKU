#include<iostream>
using namespace std;

struct Node {
	string data="";//以\＋操作字符为一个单位
	Node* next;
	Node() :next(NULL){}
	Node(string e) :data(e), next(NULL) {}
};

struct Stack {
	Node* head;
	Stack() {  head = new Node(); }
	void pop(Node* p) {
		if (head->next == NULL) {
			head->next = p;
		}
		else {
			p->next = head->next;
			head->next = p;
		}
	}
	void top() {
		if (head->next == NULL) {
			cout << "栈空" << endl;
			return;
		}
		else {
			Node* p=head->next;
			head->next = head->next->next;
			delete p;
		}
	}
	int getnum() {
		Node* p = head;
		int j = -1;
		if (p->next == NULL) {
			return 0;
		}
		while (p->next != NULL) {
			p = p->next;
			j++;
		}
		return j + 1;
	}
	void show() {
		Node* p = head;
		if (head->next == NULL) {
			cout << "/";
		}
		string result[100];
		for (int i = 0; i < getnum();i++) {
			p = p->next;
			result[i] = p->data;
		}
		for (int i = getnum()-1; i >=0; i--) {
			cout<<result[i];
		}
	}


};

//路径字符串预处理：1、将连续的\变成一个 2、将最后的\去除
void Processing(string &s) {
	int mark = 0;
	int count = 0;
	if (s[s.length() - 1] == '/')
		s.pop_back();
	//cout << s.length() << endl;
	for (int i = 0; i < s.length(); i++) {
		//cout << "!" << endl;
		if (s[i] == '/') {
			//cout << "!!!!" << endl;
			mark = i;
			count++;
			for (int j = i+1; j < s.length(); j++) {
				if (s[j] == '/') {
					s[j] = '?';
					count++;
				}
				else {
					break;
				}
			}
		}
	}
	//cout << s << endl;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '?') {
			s.erase(i,1);
			i--;
		}
	}
}



int main() {
	Stack stack;
	string s;
	cin >> s;
	Processing(s);
	//cout << s<<endl;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '/') {
			string temp;
			temp += s[i];
			for (int j = i + 1; j < s.length(); j++) {
				if (s[j] != '/') {
					temp += s[j];
				}
				else {
					break;
				}
			}
			Node* p = new Node(temp);
			if (temp == "/..") {
				if(stack.head->next!=NULL)
					stack.top();
			}
			else if (temp == "/.") {
				;
			}else {
				stack.pop(p);
			}
		}
	}
	stack.show();
	//system("pause");
	return 0;
}