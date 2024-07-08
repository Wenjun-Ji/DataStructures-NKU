#include<iostream>
using namespace std;
struct SString{
	char* ch;
	void StrAssign(const char* s) {//赋值操作
		if (ch != NULL) { delete ch; ch = NULL; }
		int len = strlen(s);
		ch = new char[len + 1 + 1]; int i = 0;
		for (; i < len; i++) {
			ch[i+1] = s[i];
		}
		ch[i+1] = 0;
		ch[0] = strlen(s);
	}
	void StrAssign(char* s) {//赋值操作
		if (ch != NULL) { delete ch; ch = NULL; }
		int len = strlen(s);
		ch = new char[len + 1 + 1]; int i = 0;
		for (; i < len; i++) {
			ch[i+1] = s[i];
		}
		ch[i+1] = 0;
		ch[0] = strlen(s);
	}
	void show() {
		for (int i = 0; i < ch[0]; i++) {
			cout << ch[1 + i];
		}
		cout << endl;
	}

};

int index_BF(SString*S,SString*T) {
	int i = 1, j = 1;
	//while (i < S->ch[0]) {
	//	cout << i <<":" << S->ch[i + j - 1] << " " << j <<":" << T->ch[j] << endl;
	//	if (S->ch[i+j-1] == T->ch[j]) { j++; }
	//	else { j = 1; i++;}
	//	if (j == T->ch[0]+1) { return i; }
	//}
	//return -1;
	while (i <= S->ch[0] && j <= T->ch[0]) {
		if (S->ch[i] == T->ch[j]) { i++; j++; }
		else {
			i = i - j + 2;//指针回退到匹配起始点的下一位
			j = 1;
		}
	}
	if (j > T->ch[0]) { return i - T->ch[0]; }
	else { return 0; }



}

int main() {
	SString* s1 = new SString();
	s1->StrAssign("ababcabcacbab");
	s1->show();
	SString* s2 = new SString();
	s2->StrAssign("abcac");
	s2->show();
	cout<<index_BF(s1, s2);

	system("pause");
	return 0;

}


int match(const char* P, const char* T) {
	int n = strlen(T); int m = strlen(P); int i = 0; int j = 0;
	while (j < m && i < n)
	{
		if (T[i] == P[j]) {
			i++; j++;
		}
		else {
			i -= (j - 1);
		}
	}
	return i - j;
}
