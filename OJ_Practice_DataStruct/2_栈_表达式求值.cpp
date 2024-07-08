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

//(，)， + ， - ， * ， / ， % 和 ^ (求幂)
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
				if (stack1.head->next == NULL) {//错误表达式
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
			stack1.pop();//把(和)去除

		}
		else {
			flag = 0;
			if (stack1.head->next == NULL||judge(s[i], stack1.head->next->c) || s[i] == '('||stack1.head->next->c == '(') {
				Node* p = new Node(s[i]);
				stack1.push(p); 
			}
			else {
				 while (1) {//防止2/5+7这种中途出现 stack1为空
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
					 else {//优先级大于stack栈顶
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

	//stack3用来存数字  遇到操作符就判断运算 再从stack从取栈顶和栈顶下一个元素
	//将 （栈顶下一个元素 运算符 栈顶元素）存为k 再压入stack3，依次类推最终直到 字符串全部读取完毕
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
	//// 设置输出为固定小数位数，这会显示小数点及后面的零
	cout <<fixed;

	// 设置小数位数为2
	cout <<setprecision(2);

	// 输出double变量
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
1、读取字符串，对字符串进行判断，若不是正确表达式直接返回、将运算符和操作数分别放进FuncStack中、stack逆序变成表达式栈（ +*、 )n 、 n( 、 )( 、）
2、读取表达式栈，分别利用stack1和stack2将中缀表达式转化为后缀表达式，转化规则如下：
		if FunStack当前节点是操作数
			那么直接当前节点放入stack2
		if FunStack当前节点是运算符且为（
			那么直接将当前节点插入到stack1
		else if FunStack当前节点是运算符且为）
			那么需要开始从stack1中弹出节点一次放入stack2（直到遇到了（为止，如果未遇到（stack1就空了，那么说明表达式有误）
		else if FunStack当前节点是运算符且为+，-，*，/，%和^
			if FunStack当前节点的运算符优先级大于stack1栈顶的运算符||当前stack1栈顶为空||当前stack1栈顶元素为（
				那么直接将当前节点插入到stack1
			else 将stack1栈顶节点弹出插入stack2，直到当前节点的运算符优先级大于stack1栈顶的运算符||当前stack1栈顶为空||当前stack1栈顶元素为（
		最后将stack2逆序即可生成后缀表达式

3、利用后缀表达式生成中缀表达式的结果，这里使用stack2和stack3（用于存数字和中间运算结果以及最后结果的栈）
		顺序遍历逆序后的stack2,遇见数字就存进stack3,遇见运算符就取stack3栈顶两个节点，按第二个节点数 运算符 第一个节点数计算出k
		并将k存入stack3，直到stack2全部遍历完，stack3只剩一个节点，即为最终结果
*/