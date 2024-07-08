#include<iostream>
using namespace std;
struct SString {
	char* ch;
	void StrAssign(const char* s) {//��ֵ����
		if (ch != NULL) { delete ch; ch = NULL; }
		int len = strlen(s);
		ch = new char[len + 1 + 1]; int i = 0;
		for (; i < len; i++) {
			ch[i + 1] = s[i];
		}
		ch[i + 1] = 0;
		ch[0] = strlen(s);
	}
	void StrAssign(char* s) {//��ֵ����
		if (ch != NULL) { delete ch; ch = NULL; }
		int len = strlen(s);
		ch = new char[len + 1 + 1]; int i = 0;
		for (; i < len; i++) {
			ch[i + 1] = s[i];
		}
		ch[i + 1] = 0;
		ch[0] = strlen(s);
	}
	void show() {
		for (int i = 0; i < ch[0]; i++) {
			cout << ch[1 + i];
		}
		cout << endl;
	}

};
/*
��next������PM���Ƴ����� ����λ��=��ƥ���ַ���-��Ӧ�Ĳ���ƥ��ֵ
Move=(j-1) - PM[j-1] ��P������һλ�õ�
Move=(j-1) - PM[j]
����j=j-Move=j-(j-1)+PM[j]=PM[j]+1
����next����ΪPM������һλ����һ����±�����Ϊ��j��ʧ��Ͱ�j���˵�next[j]�����¿�ʼƥ��

���ٺ������Ƿ���next����ʵ����ǰ��׺������ ֻ��ģʽ�ַ����й� ������ѧ֪ʶ�����Ƶ���next�Ĺ�ʽ

*/
void get_next(SString *T,int next[]) {
	int i = 1, j = 0;
	next[1] = 0;
	while (i < T->ch[0]) {
		if (j == 0 || T->ch[i] == T->ch[j]) {//next�����һ����Ȼ��0 �ڶ�����Ȼ��1
			i++; j++;
			next[i] = j;//next[i]=next[i]+1
		}
		else {
			j = next[j];//�ݹ�
		}
	}
}

//KMP�㷨���Ż�
void get_nextval(SString* T, int nextval[]) {
	int i = 1, j = 0;
	nextval[1] = 0;
	while (i < T->ch[0]) {
		if (j == 0 || T->ch[i] == T->ch[j]) {
			i++, j++;
			if (T->ch[i] != T->ch[j]) nextval[i] = j;
			else nextval[i] = nextval[j];
		}
		else {
			j = nextval[j];
		}
	}
}



int index_KMP(SString* S,SString*T) {
	int* next = new int[T->ch[0]+1];
	get_next(T, next);
	int i = 1, j = 1;
	while (i<=S->ch[0]&&j<=T->ch[0]) {
		if (j == 0 || S->ch[i] == T->ch[j]) {i++; j++;}//j==0�����׸��ַ�����ƥ�䲻�ɹ� ��i++��j->1
		else {
			j = next[j];//jָ����˵�ָ��λ��
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
	SString* s1 = new SString();
	s1->StrAssign("ababcabcacbab");
	s1->show();
	SString* s2 = new SString();
	s2->StrAssign("abcac") ;
	s2->show();
	//int next[5];// = new int[s2->ch[0] + 1];
	//get_next(s2, next);
	//for (int i = 1; i <= s2->ch[0]; i++) {
	//	cout << "i=" << i<<endl;
	//	cout << next[i] << " ";
	//	
	//}
	//cout << endl;
	cout << index_KMP(s1,s2);

	system("pause");
	return 0;

}


//KMP
void get_next(string pattern, int next[]) {
	int i = 0, j = -1;
	next[0] = -1;
	int plen = pattern.length();
	while (i < plen - 1) {
		if (j == -1 || pattern[i] == pattern[j]) {
			i++; j++;
			next[i] = j;
		}
		else {
			j = next[j];
		}
		//KMP_next_count++;
	}
}
int KMP(string target, string pattern) {
	int plen = pattern.length();
	int tlen = target.length();
	int* next = new int[plen];
	get_next(pattern, next);
	int i = 0, j = 0;
	while (i <= tlen - 1 && j <= plen - 1) {
		if (j == -1 || target[i] == pattern[j]) {
			i++;
			j++;
		}
		else {
			j = next[j];
		}
		//KMP_search_count++;
	}
	if (j > plen - 1) {
		return i-plen;
	}
	else {
		return -1;
	}
}