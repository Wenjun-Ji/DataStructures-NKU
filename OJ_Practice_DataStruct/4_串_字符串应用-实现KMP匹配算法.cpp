#include<iostream>
#include<cstring>
using namespace std;
struct SString {
	char* ch;
	void StrAssign(const char* s) {//赋值操作
		if (ch != NULL) { delete ch; ch = NULL; }
		int len = strlen(s);
		ch = new  char[len + 1 + 1];
		ch[0] = len;
		for (int i = 0; i < len; i++) { ch[i + 1] = s[i]; }
		ch[len + 1] = 0;
	}
	void StrAssign(char* s) {
		if (ch != NULL) { delete ch; ch = NULL; }
		int len = strlen(s);
		ch = new  char[len + 1 + 1];
		ch[0] = len;
		for (int i = 0; i < len; i++) { ch[i + 1] = s[i]; }
		ch[len + 1] = 0;
	}//赋值操作

	void StrAssign(string s) {//赋值操作
		if (ch != NULL) { delete ch; ch = NULL; }
		int len = s.length();
		ch = new  char[len + 1 + 1];
		ch[0] = len;
		for (int i = 0; i < len; i++) { ch[i + 1] = s[i]; }
		ch[len + 1] = 0;
	}
	void show() {
		if (ch == NULL)return;
		for (int i = 0; i < ch[0]; i++) {
			cout << ch[1 + i];
		}
		cout << endl;
	}
};


void get_next(SString *T,int next[]) {
	int i = 1, j = 0;
	next[1] = 0;
	while (i < T->ch[0]) {
		if (j == 0 || T->ch[i] == T->ch[j]) {
			i++; j++;
			next[i] = j;
		}
		else {
			j = next[j];
		}
	}
}

int index_KMP(SString *S,SString *T,int next[]) {
	int i = 1, j = 1;
	while (i <= S->ch[0] && j <= T->ch[0]) {
		if (j==0||S->ch[i] == T->ch[j]) {
			i++; j++;
		}
		else {
			j = next[j];
		}
	}
	if (j > T->ch[0]) {
		return i - T->ch[0];
	}
	else {
		return 0;
	}
}

int main() {
	SString*S,*T;

	string s,  t;
	S = new SString();
	T = new SString();
	cin >> s >> t;
	S->StrAssign(s);
	T->StrAssign(t);
	//S->show();
	//T->show();

	int* next=new int[T->ch[0]] ;
	get_next(T, next);


	int result=index_KMP(S, T, next);
	if (result != 0) {
		cout << result-1;
	}
	else {
		cout << "no";
	}
	return 0;
}