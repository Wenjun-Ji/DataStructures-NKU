#include<iostream>
#include<cmath>
#include<iomanip>
#include<string>
#include<vector>
using namespace std;

struct Node {
	char c='#';
	double n=-111;
	Node* next;
	Node() :next(NULL) {}
	Node(char e) :next(NULL),c(e) {}
	Node(double e) :next(NULL), n(e) {}
};

struct Stack {
	Node* head;
	Stack() { head = new Node();}
	void push(Node * p) {
		if (head->next == NULL) {
			head->next = p;
		}else {
			p->next = head->next;
			head->next = p;
		}
	}
	char pop() {
		if (head->next == NULL) {
			return false;
		}
		else {
			Node* p = head->next;
			char temp = p->c;
			head->next = head->next->next;
			delete p;
			return temp;
		}
	}
	double pop(int) {
		if (head->next == NULL) {
			return false;
		}
		else {
			Node* p = head->next;
			double temp = p->n;
			head->next = head->next->next;
			delete p;
			return temp;
		}
	}



	int getnum() {
		if (head->next == NULL) { return 0; }
		Node* p = head;
		int j = -1;
		while (p->next != NULL) {
			p = p->next;
			j++;
		}
		return j + 1;
	}

	void show() {
		Node* p = head;
		while (p->next != NULL) {
			p = p->next;
			if (p->c == '(' || p->c == ')' || p->c == '+' || p->c == '-' || p->c == '*' || p->c == '/' || p->c == '%' || p->c == '^') {
				cout << p->c;
			}
			else {
				cout << p->n;
			}
		}
	}
};

//(��)�� + �� - �� * �� / �� % �� ^ (����)
bool judge(char a, char b) {
	if (a=='(') {
		//return true;//??
	}
	else if (a == '^') {
		return true;
	}
	else if ((a == '*' || a == '/' || a == '%') && (b == '+' || b == '-')) {
		return true;
	}
	else {
		return false;
	}
}


double zhong_hou(string s) {
	Stack stack1;
	Stack stack2;
	bool flag = 0;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] >= '0' && s[i] <= '9') {
			if (i == 0 && s[1] == '(') {
				cout << "ERROR IN INFIX NOTATION";
				return -999;
			}
			if (i == s.length() - 1 && s[i - 1] == ')') {
				cout << "ERROR IN INFIX NOTATION";
				return -999;
			}
			if (s[i + 1] == '(' || s[i - 1] == ')') {
				cout << "ERROR IN INFIX NOTATION";
				return -999;
			}


			flag = 1;
			double sum = s[i]-'0';
			for (int j = i+1; j < s.length(); j++,i++) {
				if (s[j] >= '0' && s[j] <= '9') {
					sum = sum * 10 + s[j] - '0';
				}
				else {
					break;
				}
			}
			//cout << sum << endl;
			Node* p = new Node(sum);
			stack2.push(p);
		}
		else if (s[i] == ')') {
			flag = 0;
			while (1) {
				if (stack1.head->next == NULL) {//������ʽ
					cout << "ERROR IN INFIX NOTATION";
					return -999;
				}else if(stack1.head->next->c != '(') {
					if (stack1.head->next->c != '#') {
						char temp = stack1.pop();
						Node* q = new Node(temp);
						stack2.push(q);
					}
					else {
						double temp = stack1.pop(1);
						Node* q = new Node(temp);
						stack2.push(q);
					}
				}
				else {
					break;
				}
			}
			//cout << "???" << endl;
			stack1.pop();//��(��)ȥ��

		}
		else {
			flag = 0;
			if (stack1.head->next == NULL||judge(s[i], stack1.head->next->c) || s[i] == '('||stack1.head->next->c == '(') {
				Node* p = new Node(s[i]);
				stack1.push(p); 
			}
			else {
				 while (1) {//��ֹ2/5+7������;���� stack1Ϊ��
					 if (stack1.head->next == NULL|| stack1.head->next->c=='(') {
						 break;
					 }
					 else if (!judge(s[i],stack1.head->next->c)) {
						 if (stack1.head->next->c != '#') {
							 char temp = stack1.pop();
							 Node* q = new Node(temp);
							 stack2.push(q);
						 }
						 else {
							 double temp = stack1.pop(1);
							 Node* q = new Node(temp);
							 stack2.push(q);
						 }
					 }
					 else {//���ȼ�����stackջ��
						 break;
					 }

				 }
				Node* p = new Node(s[i]);
				stack1.push(p);
			}
		}
	}
	while (stack1.head->next!=NULL) {
		if (stack1.head->next->c != '#') {
			char temp = stack1.pop();
			Node* q = new Node(temp);
			stack2.push(q);
		}
		else {
			double temp = stack1.pop(1);
			Node* q = new Node(temp);
			stack2.push(q);
		}
	}
	Node* p = stack2.head;
	while (p->next != NULL) {
		p = p->next;
		if (p->c == '(') {
			cout << "ERROR IN INFIX NOTATION";
			return -999;
			//return;
		}
	}	
	//stack2.show();	
	//cout << endl;
	Stack stack22;
	Node* r = stack2.head;
	while(stack2.head->next!=NULL) {
		if (stack2.head->next->c != '#') {
			char temp = stack2.pop();
			Node* q = new Node(temp);
			stack22.push(q);
		}
		else {
			double temp = stack2.pop(1);
			Node* q = new Node(temp);
			stack22.push(q);
		}
	}
	stack22.show();
	//cout << endl;

	//stack3����������  �������������ж����� �ٴ�stack��ȡջ����ջ����һ��Ԫ��
	//�� ��ջ����һ��Ԫ�� ����� ջ��Ԫ�أ���Ϊk ��ѹ��stack3��������������ֱ�� �ַ���ȫ����ȡ���
	Stack stack3;
	double x1=0;
	double x2=0;
	double k=0;
	Node* f = stack22.head;
	while(f->next!=NULL) {
		f = f->next;
		if (f->c=='#') {
			Node* temp = new Node(f->n);
			stack3.push(temp); 
		}
		else {
			x1 = (double)stack3.pop(1);
			x2 = (double)stack3.pop(1);

			switch (f->c){
			case '+':
				//cout <<"x2=" << x2 <<" x1=" << x1 << "x2+x1=" << x2 + x1 << endl;
				k = x2 + x1;
				break;
			case'-':
				//if()
				//cout <<"x2=" << x2 <<" x1=" << x1 <<" x2-x1=" << x2 - x1 << endl;
				k = x2 - x1;
				break;
			case'*':
				//cout <<"x2=" << x2 <<" x1=" << x1 <<" x2*x1=" << x2 * x1 << endl;
				k = x2 * x1;
				break;
			case'/':
				//cout <<"x2=" << x2 <<" x1=" << x1 <<" x2/x1=" << x2 / x1 << endl;
				k = (x2*1.0) / (1.0*x1);
				break;
			case'%':
				//cout << "x2=" << x2 <<" x1="<<x1 << " x2%x1=" << (int)x2%(int)x1<<endl;
				k = (int)x2 % (int)x1;
				break;
			case'^':
				k = pow(x2 , x1);
				break;
			default:
				break;
			}
			//cout << "k=" << k << endl;
			Node* temp = new Node(k);
			stack3.push(temp);
		}
	}
	//// �������Ϊ�̶�С��λ���������ʾС���㼰�������
	cout <<fixed;

	// ����С��λ��Ϊ2
	cout <<setprecision(2);

	// ���double����
	cout << stack3.head->next->n;

	return stack3.head->next->n;


	//stack3.show();

}
/*
(2-4)^3
(3*5*(4+8)%2)
1+2(
*/


int main() {
	vector<double> v;
	string s;
	cin >> s;
	zhong_hou(s);
	//while (getline(cin, s)) {
	//	//cout << s << endl;
	//	v.push_back(zhong_hou(s));
	//}
	//int count = 0;
	//for (vector<double>::iterator i = v.begin(); i != v.end(); i++) {
	//	count++;
	//}

	//for (vector<double>::iterator i = v.begin(); i != v.end(); i++) {
	//	if (*i == -999) {
	//		cout << "ERROR IN INFIX NOTATION" << endl;
	//		if(count>1)
	//			cout<<endl;
	//	}
	//	else {
	//		cout << *i <<endl;
	//		if (count > 1)
	//			cout << endl;
	//	}
	//	count--;
	//}	

	//system("pause");
	return 0;
}

/*
1����ȡ�ַ��������ַ��������жϣ���������ȷ���ʽֱ�ӷ��ء���������Ͳ������ֱ�Ž�FuncStack�С�stack�����ɱ��ʽջ�� +*�� )n �� n( �� )( ����
2����ȡ���ʽջ���ֱ�����stack1��stack2����׺���ʽת��Ϊ��׺���ʽ��ת���������£�
		if FunStack��ǰ�ڵ��ǲ�����
			��ôֱ�ӵ�ǰ�ڵ����stack2
		if FunStack��ǰ�ڵ����������Ϊ��
			��ôֱ�ӽ���ǰ�ڵ���뵽stack1
		else if FunStack��ǰ�ڵ����������Ϊ��
			��ô��Ҫ��ʼ��stack1�е����ڵ�һ�η���stack2��ֱ�������ˣ�Ϊֹ�����δ������stack1�Ϳ��ˣ���ô˵�����ʽ����
		else if FunStack��ǰ�ڵ����������Ϊ+��-��*��/��%��^
			if FunStack��ǰ�ڵ����������ȼ�����stack1ջ���������||��ǰstack1ջ��Ϊ��||��ǰstack1ջ��Ԫ��Ϊ��
				��ôֱ�ӽ���ǰ�ڵ���뵽stack1
			else ��stack1ջ���ڵ㵯������stack2��ֱ����ǰ�ڵ����������ȼ�����stack1ջ���������||��ǰstack1ջ��Ϊ��||��ǰstack1ջ��Ԫ��Ϊ��
		���stack2���򼴿����ɺ�׺���ʽ

3�����ú�׺���ʽ������׺���ʽ�Ľ��������ʹ��stack2��stack3�����ڴ����ֺ��м��������Լ��������ջ��
		˳�����������stack2,�������־ʹ��stack3,�����������ȡstack3ջ�������ڵ㣬���ڶ����ڵ��� ����� ��һ���ڵ��������k
		����k����stack3��ֱ��stack2ȫ�������꣬stack3ֻʣһ���ڵ㣬��Ϊ���ս��
*/