#include<iostream>
#include<cstring>
#include<string>
using namespace std;
#include<stack>

/*
��Ŀ����
����һ���ַ���������ֻ���������ַ�(��)��<��>��^��v��
�ַ����밴��˳��պϣ�����<>��()��^v��<^v>���Ƿ���Ҫ��ģ���^>��<v���ǲ�����Ҫ��ġ�
���룺��һ���ǲ������ݵ�����n(0<n<=100)��֮��ÿһ�ж��ǲ������ݣ�ÿ�����ݳ���<=1000��
����������������Եģ������Yes���������No��

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