#include<iostream>
#include<cmath>
#include<iomanip>
#include<string>
#include<vector>
using namespace std;
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


struct Node {
	char c = '#';//存运算符
	double n = -111;//存操作数
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
			return temp;//这里直接返回节点
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

bool JudgeBig(char a,char b) {  //不涉及）（的优先级
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
		// )num( 的情况
		if (i == 0 && (JudgeNum(s[0])||JudgeMark(s[i])) && s[1] == '(')
			return false;
		if (i == len - 1 && JudgeNum(s[len - 1]) && s[len - 2] == ')')
			return false;
		if(JudgeNum(s[i])&&JudgeMark(s[i]) &&(i < len - 1)&&i>=1 && (s[i + 1] == '(' || s[i - 1] == ')'))
			return false;
		// )(的情况
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
		if (JudgeNum(s[i])) {//注意多位数情况
			sum = s[i] - '0';
			for (int j = i + 1; j < s.length(); j++, i++) {//这里保持i也同步增加
				if (s[j] >= '0' && s[j] <= '9')
					sum = sum * 10 + s[j] - '0';
				else
					break;
			}
			//cout << sum << endl;
			//Node* p = new Node(sum);
			//stack2->push(p);
			i++;//为了让下面的s[i]为最后一个整数位的下一位
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
				i++;//为了让下面的s[i]为最后一个小数位的下一位，不要错误的重新识别出一个新的整数位
			}
		}
		

		if (JudgeMark(s[i])) {
			if (stack1->isEmpty())//如果stack1为空，直接插
				stack1->push(new Node(s[i]));
			else if(s[i]=='(') //如果自己是（，直接插
				stack1->push(new Node(s[i]));
			else if (stack1->head->next->c == '(') //栈顶为(，直接插
				stack1->push(new Node(s[i]));
			else if (s[i] == '^'&& stack1->head->next->c == '^')//连续的^为从右往左
				stack1->push(new Node(s[i]));
			else if(JudgeBig(s[i],stack1->head->next->c))//如果stack1栈顶优先级小于s[i]，直接查
				stack1->push(new Node(s[i]));
			else if (s[i] == ')') {//如果s[i]是右括号，开始寻找最近的（
				while (1) {
					if (stack1->isEmpty()) {//找不到）说明表达式有误
						return -999;//此处  比如这种 5+2）*（3*
						break;
					}
					else if (stack1->head->next->c == '(') {//到遇到(结束
						Node*del=stack1->pop();//销毁（
						delete del;//内存管理
						break;
					}
					else
						stack2->push(stack1->pop());//开始把stack1弹栈，压到stack2
				}
			}
			else if (!JudgeBig(s[i], stack1->head->next->c)) {//如果栈顶的优先级大于或等于s[i]，那么
				while (1) {
					if (stack1->isEmpty()) {//到stack1空结束
						stack1->push(new Node(s[i]));
						break;
					}
					else if (stack1->head->next->c == '(') {//到遇到(结束
						stack1->push(new Node(s[i]));
						break;
					}
					else if (JudgeBig(s[i], stack1->head->next->c)) {//到大于栈顶优先级结束
						stack1->push(new Node(s[i]));
						break;
					}
					else {
						stack2->push(stack1->pop());//开始把stack1弹栈，压到stack2
					}
				}
			}

		}
	
	}	
	//最后清空stack1
	while (!stack1->isEmpty())
		stack2->push(stack1->pop());
	//stack2->Show();
	//cout << endl;
	//逆序stack2	
	Stack* stack22;
	stack22 = Reverse(*stack2);
	//展示后缀表达式
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
	//// 设置输出为固定小数位数，这会显示小数点及后面的零
	//cout << fixed;

	// 设置小数位数为2
	//cout << setprecision(2);

	// 输出double变量
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
设计一个表达式求值的程序。该程序必须可以接受包含（，），+，-，*，/，%和^(求幂)的中缀表达式，并求出结果。如果表达式正确，则输出表达式的值，如果表达式非法，则输出错误信息。
注意2^2^3转为后缀应为223^^

操作数均转为double运算。

幂运算可以直接使用pow(a,b)

操作数转为Int再进行计算。

输入要求：
多个表达式，每个表达式占一行。

输出要求：
对每个表达式，如果为正确表达式则输出结果（精确到小数点后两位），如果为错误表达式则输出“ERROR IN INFIX NOTATION”.

样例输入输出
样例1
输入:
(2-4)^3
输出:
-8.00

样例2
输入:
(3*5*(4+8)%2)
输出:
0.00

样例3
输入:
1+2(
输出:
ERROR IN INFIX NOTATION
*/

//if (p->c == '(' || p->c == ')' || p->c == '+' || p->c == '-' || p->c == '*' || p->c == '/' || p->c == '%' || p->c == '^') {
//	cout << p->c;
//}

