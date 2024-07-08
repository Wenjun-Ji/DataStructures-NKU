#include<iostream>
#include<cstring>
#include<string>
using namespace std;
#include<stack>

/*
题目描述
输入一段字符串，里面只包含下列字符(、)、<、>、^、v。
字符必须按照顺序闭合，比如<>、()、^v、<^v>都是符合要求的，而^>、<v就是不符合要求的。
输入：第一行是测试数据的组数n(0<n<=100)，之后每一行都是测试数据，每组数据长度<=1000。
输出：如果符号是配对的，就输出Yes，否则输出No。

4
<>^v
(^v)
<()^v>
()v<>^

*/
//( ) < > ^ v
stack<char> Stack;
bool judge(string &s) {
	int len = 0;
	len = s.length();
	for (int i = 0; i < len; i++) {
		char x = s[i];
		if (x == '('||x=='<'||x=='^') {
			Stack.push(x);
		}
		else{
			if (x == ')') {
				if (!Stack.empty()&&Stack.top() == '(') Stack.pop();
				else Stack.push(x);
			}
			else if (x == '>') {
				if (!Stack.empty()&&Stack.top() == '<')Stack.pop();
				else Stack.push(x);
			}
			else {
				if (!Stack.empty()&&Stack.top() == '^')Stack.pop();
				else Stack.push(x);
			}
		}
	}
	if (Stack.empty()) return true;
	else return false;
}

int main(){
	int n = 0;
	cin >> n;
	string *ss=new string[n];
	cin.ignore();
	for (int i = 0; i < n; i++) {
		getline(cin, ss[i]);
	}
	for (int i = 0; i < n; i++) {
		cout << ss[i] << endl;
	}
	for (int i = 0; i < n; i++) {
		cout << judge(ss[i]);
	}
	system("pause");
	return 0;
}


/*
<>^v
(^v)
<()^v>
()v<>^
*/