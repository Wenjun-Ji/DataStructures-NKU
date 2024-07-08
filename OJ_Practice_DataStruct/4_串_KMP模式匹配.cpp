#include<iostream>
using namespace std;
struct SString {
	char* ch;
	void StrAssign(const char* s) {//赋值操作
		if (ch != NULL) { delete ch; ch = NULL; }
		int len = strlen(s);
		ch = new char[len + 1 + 1]; int i = 0;
		for (; i < len; i++) {
			ch[i + 1] = s[i];
		}
		ch[i + 1] = 0;
		ch[0] = strlen(s);
	}
	void StrAssign(char* s) {//赋值操作
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
·next数组由PM表推出，由 右移位数=已匹配字符数-对应的部分匹配值
Move=(j-1) - PM[j-1] 将P表右移一位得到
Move=(j-1) - PM[j]
又有j=j-Move=j-(j-1)+PM[j]=PM[j]+1
定义next数组为PM表右移一位并加一后的新表，含义为在j处失配就把j回退到next[j]处重新开始匹配

·再后来我们发现next数组实际是前后缀的特性 只与模式字符串有关 利用数学知识我们推导出next的公式

*/
void get_next(SString *T,int next[]) {
	int i = 1, j = 0;
	next[1] = 0;
	while (i < T->ch[0]) {
		if (j == 0 || T->ch[i] == T->ch[j]) {//next数组第一个必然是0 第二个必然是1
			i++; j++;
			next[i] = j;//next[i]=next[i]+1
		}
		else {
			j = next[j];//递归
		}
	}
}

//KMP算法的优化
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
		if (j == 0 || S->ch[i] == T->ch[j]) {i++; j++;}//j==0代表首个字符串就匹配不成功 则i++，j->1
		else {
			j = next[j];//j指针回退到指定位置
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