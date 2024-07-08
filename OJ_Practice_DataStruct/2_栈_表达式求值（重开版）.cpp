#include<iostream>
#include<cmath>
#include<iomanip>
#include<string>
#include<vector>
using namespace std;
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


struct Node {
	char c = '#';//�������
	double n = -111;//�������
	Node* next;
	Node() :next(NULL) {}
	Node(char e) :next(NULL), c(e) {}
	Node(double e) :next(NULL), n(e) {}
	Node(Node* p) :next(NULL) {
		c = p->c;
		n = p->n;
	}
};

struct Stack {
	Node* head;
	Stack() { head = new Node(); }
	void push(Node* p) {
		if (head->next == NULL) {
			head->next = p;
		}
		else {
			p->next = head->next;
			head->next = p;
		}
	}
	Node* pop() {
		if (head->next == NULL) {
			return NULL;
		}
		else {
			Node* p = head->next;
			Node* temp = new Node(p);
			head->next = head->next->next;
			delete p;
			return temp;//����ֱ�ӷ��ؽڵ�
		}
	}

	bool isEmpty() {
		if (head->next == NULL) {
			return true;
		}
		return false;
	}
	int GetNum() {
		if (head->next == NULL) { return 0; }
		Node* p = head;
		int j = -1;
		while (p->next != NULL) {
			p = p->next;
			j++;
		}
		return j + 1;
	}
	void Show() {
		Node* p = head;
		while (p->next != NULL) {
			p = p->next;
			if (p->c !='#') {
				cout << p->c<<" ";
			}
			else {
				cout << p->n<<" ";
			}
		}
	}
};	

Stack* Reverse(Stack&stack) {
	if (stack.isEmpty()) {
		return &stack;
	}
	Stack* newstack = new Stack();
	while (!stack.isEmpty()) {
		newstack->push(stack.pop());
	}	
	return newstack;
}


bool JudgeNum(char c) {
	if (c >= '0' && c <= '9') {
		return true;
	}
	return false;
}
bool JudgeMark(char c){
	if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^') {
		return true;
	}
	return false;
}

bool JudgeBig(char a,char b) {  //���漰���������ȼ�
	if (a == '^' && b != '^') { 
		return true;
	}
	else if ((a == '*' || a == '/' || a == '%') && (b == '+' || b == '-')) {
		return true;
	}
	else {
		return false;
	}
}


bool Processing(string s) {
	int LeftCount=0;
	int RightCount=0;
	int NumCount = 0;
	int len = s.length();
	if (len == 0) {
		return false;
	}
	for (int i = 0; i < len; i++) {
		if (JudgeNum(s[i]))
			NumCount++;
	}
	if (NumCount == 0) {
		return false;
	}
	for (int i = 0; i < len; i++) {
		// )num( �����
		if (i == 0 && (JudgeNum(s[0])||JudgeMark(s[i])) && s[1] == '(')
			return false;
		if (i == len - 1 && JudgeNum(s[len - 1]) && s[len - 2] == ')')
			return false;
		if(JudgeNum(s[i])&&JudgeMark(s[i]) &&(i < len - 1)&&i>=1 && (s[i + 1] == '(' || s[i - 1] == ')'))
			return false;
		// )(�����
		if (s[i] == ')' && s[i + 1] == '(' && i < len - 1)
			return false;
		if (s[i] == ')')
			LeftCount++;
		if (s[i] == '(')
			RightCount++;
		if (!((s[i] == '+' || s[i] == '-') && (s[i + 1] == '+' || s[i + 1] == '-'))
			&& (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '%' || s[i] == '^')
			&& (s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == '*' || s[i + 1] == '/' || s[i + 1] == '%' || s[i + 1] == '^')
			&& i < len - 1
			)
			return false;
		if (s[i]!='.'&&s[i] != '(' && s[i] != ')' && s[i] != '+' && s[i] != '-' && s[i] != '*' && s[i] != '/' && s[i] != '%' && s[i] != '^' && !(s[i] >= '0' && s[i] <= '9'))
			return false;
	}
	if (LeftCount != RightCount)
		return false;
	return true;
}

double func(string s) {
	Stack* stack1 = new Stack();
	Stack* stack2 = new Stack();

	if (!Processing(s))
		return -999;
	int len = s.length();
	double sum = 0;
	double sum_xiao = 0;
	for (int i = 0; i < len; i++) {
		if (JudgeNum(s[i])) {//ע���λ�����
			sum = s[i] - '0';
			for (int j = i + 1; j < s.length(); j++, i++) {//���ﱣ��iҲͬ������
				if (s[j] >= '0' && s[j] <= '9')
					sum = sum * 10 + s[j] - '0';
				else
					break;
			}
			//cout << sum << endl;
			//Node* p = new Node(sum);
			//stack2->push(p);
			i++;//Ϊ���������s[i]Ϊ���һ������λ����һλ
			if (s[i] != '.')
				stack2->push(new Node(sum));
			else {
				int count = 0;
				for (int j = i + 1; j < s.length(); j++) {
					if (s[j] >= '0' && s[j] <= '9')
						count++;
					else
						break;
				}
				for (int j = count; j > 0; j--)
					sum_xiao = sum_xiao * 0.1 + s[i + j] - '0';
				sum_xiao *= 0.1;
				sum += sum_xiao;
				stack2->push(new Node(sum));
				i += count;
				i++;//Ϊ���������s[i]Ϊ���һ��С��λ����һλ����Ҫ���������ʶ���һ���µ�����λ
			}
		}
		

		if (JudgeMark(s[i])) {
			if (stack1->isEmpty())//���stack1Ϊ�գ�ֱ�Ӳ�
				stack1->push(new Node(s[i]));
			else if(s[i]=='(') //����Լ��ǣ���ֱ�Ӳ�
				stack1->push(new Node(s[i]));
			else if (stack1->head->next->c == '(') //ջ��Ϊ(��ֱ�Ӳ�
				stack1->push(new Node(s[i]));
			else if (s[i] == '^'&& stack1->head->next->c == '^')//������^Ϊ��������
				stack1->push(new Node(s[i]));
			else if(JudgeBig(s[i],stack1->head->next->c))//���stack1ջ�����ȼ�С��s[i]��ֱ�Ӳ�
				stack1->push(new Node(s[i]));
			else if (s[i] == ')') {//���s[i]�������ţ���ʼѰ������ģ�
				while (1) {
					if (stack1->isEmpty()) {//�Ҳ�����˵�����ʽ����
						return -999;//�˴�  �������� 5+2��*��3*
						break;
					}
					else if (stack1->head->next->c == '(') {//������(����
						Node*del=stack1->pop();//���٣�
						delete del;//�ڴ����
						break;
					}
					else
						stack2->push(stack1->pop());//��ʼ��stack1��ջ��ѹ��stack2
				}
			}
			else if (!JudgeBig(s[i], stack1->head->next->c)) {//���ջ�������ȼ����ڻ����s[i]����ô
				while (1) {
					if (stack1->isEmpty()) {//��stack1�ս���
						stack1->push(new Node(s[i]));
						break;
					}
					else if (stack1->head->next->c == '(') {//������(����
						stack1->push(new Node(s[i]));
						break;
					}
					else if (JudgeBig(s[i], stack1->head->next->c)) {//������ջ�����ȼ�����
						stack1->push(new Node(s[i]));
						break;
					}
					else {
						stack2->push(stack1->pop());//��ʼ��stack1��ջ��ѹ��stack2
					}
				}
			}

		}
	
	}	
	//������stack1
	while (!stack1->isEmpty())
		stack2->push(stack1->pop());
	//stack2->Show();
	//cout << endl;
	//����stack2	
	Stack* stack22;
	stack22 = Reverse(*stack2);
	//չʾ��׺���ʽ
	//stack22->Show();
	//cout << endl;

	Stack stack3;
	double x1 = 0;
	double x2 = 0;
	Node* p1;
	Node* p2;
	double k = 0;
	Node* f = stack22->head;
	while (f->next != NULL) {
		f = f->next;
		if (f->c == '#') {
			Node* temp = new Node(f->n);
			stack3.push(temp);
		}
		else {

			p1 = stack3.pop();
			if (p1 != NULL)
				x1 = p1->n;
			else 
				x1 = 0;
			p2 = stack3.pop();
			if (p2 != NULL)
				x2 = p2->n;
			else 
				x2 = 0;

			switch (f->c) {
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
				k = (x2 * 1.0) / (1.0 * x1);
				break;
			case'%':
				//cout << "x2=" << x2 <<" x1="<<x1 << " x2%x1=" << (int)x2%(int)x1<<endl;
				k = (int)x2 % (int)x1;
				break;
			case'^':
				//cout << "x2=" << x2 <<" x1="<<x1 << " x2^x1=" << pow(x2,x1)<<endl;
				k = pow(x2, x1);
				break;
			default:
				break;
			}
			//cout << "k=" << k << endl;
			stack3.push(new Node(k));
		}
	}
	//// �������Ϊ�̶�С��λ���������ʾС���㼰�������
	//cout << fixed;

	// ����С��λ��Ϊ2
	//cout << setprecision(2);

	// ���double����
	//cout << stack3.head->next->n;
	return stack3.head->next->n;

}

string format(string str) {
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '-') {
			if (i == 0) {
				str.insert(0, 1, '0');
			}
			else if (str[i - 1] == '(') {
				str.insert(i, 1, '0');
			}
		}

	}
	//cout << str << endl;
	return str;
}


int main() {
	//cout << pow(0, 0) << endl;
	string s;
	int count = 0;
	while (getline(cin, s)) {
		if (func(format(s)) == -999)
			cout << "ERROR IN INFIX NOTATION" << endl;
		else {
			cout << fixed;
			cout << setprecision(2);
			cout << func(format(s)) << endl;
		}
	}
	//system("pause");
	return 0;
}



/*
2.5+2^3/2%3
9+(3-1)*3+10/2
5.2*5.8/3)+2
9.235+3.2246/2.3
5+15*23+(235*2+6)*11
2^2^3
45#-5
2*2-3+(3*5
1/2-1
3e*2
3+5*(5+2+3*(5/5+2/(3-2)+5)%2)-2
3+/2-5%3
5-2
While
5/0
1+1
ERROR IN INFIX NOTATION
ERROR IN INFIX NOTATION
2.00

*/


/*
���һ�����ʽ��ֵ�ĳ��򡣸ó��������Խ��ܰ�����������+��-��*��/��%��^(����)����׺���ʽ������������������ʽ��ȷ����������ʽ��ֵ��������ʽ�Ƿ��������������Ϣ��
ע��2^2^3תΪ��׺ӦΪ223^^

��������תΪdouble���㡣

���������ֱ��ʹ��pow(a,b)

������תΪInt�ٽ��м��㡣

����Ҫ��
������ʽ��ÿ�����ʽռһ�С�

���Ҫ��
��ÿ�����ʽ�����Ϊ��ȷ���ʽ������������ȷ��С�������λ�������Ϊ������ʽ�������ERROR IN INFIX NOTATION��.

�����������
����1
����:
(2-4)^3
���:
-8.00

����2
����:
(3*5*(4+8)%2)
���:
0.00

����3
����:
1+2(
���:
ERROR IN INFIX NOTATION
*/

//if (p->c == '(' || p->c == ')' || p->c == '+' || p->c == '-' || p->c == '*' || p->c == '/' || p->c == '%' || p->c == '^') {
//	cout << p->c;
//}

