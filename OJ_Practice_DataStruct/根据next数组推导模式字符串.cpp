#include<iostream>
using namespace std;
#include<string>
char g_start = '0';
char g_end = '0';
int g_len = 0;
int g_next[30];
string S;

//����next�Ƶ�str
//str��ÿһλֻ�����ֿ��� ��Ϊ1��Ϊ0 �ֱ�������ֿ��ܵ��ִ���Ӧ���ǰ��׺ ���Ƿ�����next[i]����
//���������һ���ܶ��� ���ȷ����ǰ�ַ�
//����������Բ��� ˵��next�������� ֱ��return false;

int get_next_i(string s) {
	int len = s.length();
	for (int k = s.length()-1; k >= 1; k--) {
		bool flag = true;
		for (int i = 0, j = len - k; i <= k - 1 && j <= len - 1; i++,j++) {
			if (s[i] != s[j]) {
				flag = false;
				break;
			}
		}
		if (flag == true) {
			return k;
		}
	}
	return 0;
}
bool judge() {
	//��ʼ��
	cin >> g_start >> g_end >> g_len;
	for (int i = 0; i < g_len; i++) {
		cin >> g_next[i];
	}
	S += g_start;
	//for (int i = 0; i < g_len; i++) {
	//	cout << g_next[i]<<" ";
	//}
	//cout << endl;

	int flag = true;
	if (g_next[0] != -1 || g_next[1] != 0)return false;
	for (int i = 2; i < g_len; i++) {
		if (g_next[i] == get_next_i(S + '0')) {
			S += '0';
			//cout <<"S:" << S << endl;
			continue;
		}
		else if (g_next[i] == get_next_i(S + '1')) {
			S += '1';
			//cout << "S:" << S << endl;
			continue;
		}
		else {
			flag = false;
			break;
		}
	}
	if (flag == false) {
		cout << "ERROR";
		return false; 
	}else {
		cout << S+g_end;
		return true;
	}
}


int main() {
	judge();
	system("pause");
	return 0;
}
