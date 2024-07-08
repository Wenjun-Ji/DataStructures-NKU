#include<iostream>
using namespace std;
#define MaxSize 10
struct VariableString {
	char *ch;
	int length;
	VariableString() { ch = NULL; length = 0; }
	void StrAssign(const char* s) {//��ֵ����
		if (ch != NULL) { delete ch; ch = NULL; }
		int len = strlen(s);
		ch = new char[len + 1]; int i = 0;
		for (; i < len; i++) {
			ch[i] = s[i];
		}
		ch[i] = 0;
		length=strlen(s);
	}
	void StrAssign(char*s) {//��ֵ����
		if (ch != NULL) { delete ch; ch = NULL; }
		int len = strlen(s);
		ch = new char[len + 1]; int i = 0;
		for (; i < len; i++) {
			ch[i] = s[i];
		}
		ch[i] = 0;
		length = strlen(s);
	}
	void StrAssign(string s) {//��ֵ����
		if (ch != NULL) { delete ch; ch = NULL; }
		int len = s.length();
		ch = new char[len+1];int i = 0; 
		for (; i < len; i++) {
			ch[i] = s[i];
		}
		ch[i] = 0;
		length = len;
	}
	void StrCopy(VariableString*s) {//���Ʋ���
		if (ch != NULL) { delete ch; ch = NULL; }
		int len = s->length;
		ch = new char[len];
		for (int i = 0; i < len; i++) {
			ch[i] = s->ch[i];
		}
	}
	bool StrEmpty() {//�пղ���
		if (length == 0)return true;
	}
	int StrCompare(VariableString*s) {//�Ƚϲ���
		int i = 0;
		while (ch[i] != 0 && s->ch[i] != 0) {
			if (ch[i] > s->ch[i])return 1;
			return -1;
			i++;
		}
		if (ch[i] == 0 && s->ch[i] == 0)return 0;
		if (ch[i] == 0 && s->ch[i] != 0) return -1;
		if (ch[i] != 0 && s->ch[i] == 0) return 1;
	}
	int StrLength() {//�󳤶�
		return length;
	}
	VariableString* SubString(int pos,int len) {//��ȡ�Ӵ�
		if (pos + len - 1 > length)return NULL;
		char* s = new char[len+1];
		for (int i = 0; i < len; i++) {
			s[i] = this->ch[i + pos - 1];
		}
		s[len] = 0;
		VariableString* result = new VariableString();
		result->StrAssign(s);
		delete s;
		return result;
	}
	VariableString* Concat(VariableString*s) {//��ƴ��
		VariableString* result = new VariableString();
		result->ch = new char[length + s->length+1];
		result->length = length + s->length;
		for (int i = 0; i < length; i++) { result->ch[i] = ch[i]; }
		for (int i = 0; i < s->length; i++) { result->ch[i + length] = s->ch[i]; }
		result->ch[length + s->length] = 0;
		return result;
	}
	void Index(VariableString*s) {//��λ����
		//ģʽƥ�䣨BF��KMP��BC��
	}
	void ClearString() {//��ղ���
		
	}
	void DestroyString() {//���ٲ���

	}
	void show() {
		cout << ch;
	}
};


int main() {
	VariableString *s1=new VariableString();
	s1->StrAssign("abc");
	s1->show(); cout << endl;

	VariableString *s2 = new VariableString();
	s2->StrAssign("def");
	s2->show(); cout << endl;

	cout << s1->StrCompare(s2) << endl;

	VariableString* s3;
	s3 = s1->Concat(s2);
	s3->show(); cout << endl;

	VariableString* s4;
	s4 = s3->SubString(1, 3);
	s4->show(); cout << endl;
	return 0;
}