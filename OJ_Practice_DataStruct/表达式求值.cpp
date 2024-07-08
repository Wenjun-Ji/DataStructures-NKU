#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<cmath>
#include<iomanip>
//������׺���ʽ ������� ()+-*/%^ �Լ�һλ���֣���λ���֣�С�������������vector
//�ַ�ת��Ϊ����
//����һ��ջһ�����н���׺���ʽת��Ϊ��׺���ʽ
//��׺���ʽ�ļ���

struct Node {
	bool is_num;
	bool is_str;
	char str;
	double num;
	Node(double n) :num(n), str('#'), is_num(true), is_str(false) {}
	Node(char s) :num(999), str(s), is_num(false), is_str(true) {}
};

bool is_num(char c) {
	if (c >= '0' && c <= '9')return true;
	return false;
}
bool is_str(char c) {
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^')return true;
	return false;
}

double string_double(string s) {
	int len = s.length();
	if (len == 1)return s[0] - '0';
	int index = 0;
	double result1 = 0;
	double result2 = 0;
	while (index < len) {
		if (s[index] == '.')break;
		index++;
	}
	for (int i = 0; i <= index - 1; i++) {
		result1 = result1 * 10 + s[i] - '0';
	}
	for (int i = len - 1; i >= index + 1; i--) {
		result2 = result2 * 0.1 + s[i] - '0';
	}
	result2 *= 0.1;
	return result1 + result2;
}
void get_S(string S, vector<Node*>& Mid) {
	//cin >> S;
	int len = S.length();
	int i = 0;
	while (i < len) {
		if (is_num(S[i])) {
			int j = i;
			int num_len = 0;
			while (j < len) {
				if (is_num(S[j]) || S[j] == '.')
					j++;
				else
					break;
			}
			num_len = j - i;
			//cout << S.substr(i, num_len)<<endl;
			Node* p = new Node(string_double(S.substr(i, num_len)));
			Mid.push_back(p);
			i += num_len;
		}
		else {
			if (S[i] == '-' && (i - 1 < 0 || S[i - 1] == '(')) {
				//cout << "0" << endl;
				Node* p = new Node((double)0);
				Mid.push_back(p);
			}
			//cout << S[i] << endl;
			Node* p = new Node(S[i]);
			Mid.push_back(p);
			i += 1;
		}
	}
	//for (int i = 0; i < Mid.size();i++) {
	//	if (Mid[i]->is_num) {
	//		cout << Mid[i]->num;
	//	}
	//	else {
	//		cout << Mid[i]->str;
	//	}
	//}
	//cout << endl;
}


int cmp(char c) {
	if (c == '+' || c == '-')return 1;
	if (c == '*' || c == '/' || c == '%')return 2;
	if (c == '^')return 3;
	if (c == '(' || c == ')')return 0;
}

bool middle_post(vector<Node*>& Mid, stack<Node*>& Stack, vector<Node*>& Post, vector<double>& result) {
	for (int i = 0; i < Mid.size(); i++) {
		if (Mid[i]->is_num)Post.push_back(Mid[i]);
		else {
			if (Mid[i]->str == ')') {
				bool flag = false;
				while (!Stack.empty()) {
					if (Stack.top()->str == '(') {
						Stack.pop();
						flag = true;
						break;
					}
					else {
						Node* p = Stack.top();
						Stack.pop();
						Post.push_back(p);
					}
				}
				if (flag == true)
					continue;
				else {
					cout << "ERROR IN INFIX NOTATION" << endl;
					return false;
				}
				//������ʽ���Ϸ����Ȱѣ�ѹ��ȥ�������post�м���
			}
			if (Stack.empty() || Stack.top()->str == '(') {
				Stack.push(Mid[i]);
				continue;
			}
			if (Mid[i]->str == '(') {
				Stack.push(Mid[i]);
				continue;
			}
			if (cmp(Mid[i]->str) > cmp(Stack.top()->str)) {
				Stack.push(Mid[i]);
				continue;
			}
			else {
				if (Mid[i]->str == '^') {
					Stack.push(Mid[i]);
					continue;
				}
				while (!(Stack.empty()
					|| Stack.top()->str == '('
					|| cmp(Mid[i]->str) > cmp(Stack.top()->str))) {
					Node* p = Stack.top();
					Stack.pop();
					Post.push_back(p);
				}
				Stack.push(Mid[i]);
				continue;
			}
		}
	}
	while (!Stack.empty()) {
		Node* p = Stack.top();
		Stack.pop();
		Post.push_back(p);

	}
	for (int i = 0; i < Post.size(); i++) {
		if (Post[i]->str == '(' || Post[i]->str == ')') {
			cout << "ERROR IN INFIX NOTATION" << endl;
			return false;
		}
		//if (Post[i]->is_num) {
		//	cout << Post[i]->num ;
		//}
		//else {
		//	cout << Post[i]->str;
		//}
	}
	//cout << endl;
	return true;
}
double func(double b, double a, char c) {
	if (c == '+')return b + a;
	if (c == '-')return b - a;
	if (c == '*')return b * a;
	if (c == '/')return (double)b / (double)a;
	if (c == '%') return (int)b % (int)a;
	if (c == '^')return pow(b, a);
}


void post_result(vector<Node*>& Post, stack<double>& f, vector<double>& result) {
	for (int i = 0; i < Post.size(); i++) {
		if (Post[i]->is_num) {
			f.push(Post[i]->num);
		}
		else {
			double a = 0;
			double b = 0;
			if (!f.empty()) {
				a = f.top(); f.pop();
			}
			else {
				cout << "ERROR IN INFIX NOTATION" << endl;
				return;
			}
			if (!f.empty()) {
				b = f.top(); f.pop();
			}
			else {
				cout << "ERROR IN INFIX NOTATION" << endl;
				return;
			}
			f.push(func(b, a, Post[i]->str));
		}
	}
	//cout << endl;

	if (!f.empty() && f.size() == 1) {
		cout << std::fixed << std::setprecision(2) << f.top() << endl;
		f.pop();
	}
	else {
		cout << "ERROR IN INFIX NOTATION" << endl;
	}
}

void func() {
	string S;
	vector<double>result;
	while (getline(cin, S)) {
		vector<Node*>Mid;
		stack<Node*> Stack;
		vector<Node*> Post;

		stack<double>f;
		get_S(S, Mid);
		if (middle_post(Mid, Stack, Post, result))
			post_result(Post, f, result);
		Mid.clear();
		while (!Stack.empty())Stack.pop();
		Post.clear();
	}
	//for (int i = 0; i < result.size(); i++) {
	//	if (result[i] != -999) {
	//		cout << result[i] << endl;
	//	}
	//	else {
	//		cout << "ERROR IN INFIX NOTATION"<<endl;
	//	}
	//}

}





int main() {

	func();
	//	system("pause");
	return 0;

}

/*
�ܽ᣺
Ҫע��һЩ���߽�����
1 �ڴ���ʱ����Ƿ�����ҵ���Ӧ�ģ�
2 �ڵõ���׺���ʽ������ȱ���һ�鿴��û�ж���ģ�
3 Ҫע��double��int��ת������Ҫ������������
4 �����ڼ����׺���ʽ��ʱ��ͨ���пղ�����ȷ����û�ж���������
5 ע�⸺���Ĵ��� �����������λ����ǰΪ���򸺺�ǰ��0
6 ���������ȼ��ȽϺ���
*/