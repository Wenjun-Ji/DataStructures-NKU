#include<iostream>
using namespace std;
#include<string>
#include<vector>
string S;
string P;
bool dp[30][40];
bool judge() {
	cin >> S >> P;
	int m = S.length();
	int n = P.length();
	//�߽�����
	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			dp[i][j] = false;
		}
	}
	dp[0][0] = true;
	for (int j = 1; j <= n; j++) {
		if (P[j-1] == '%') {
			dp[0][j] = dp[0][j-1];
		}
	}
	//״̬ת�Ʒ���
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (P[j-1] == S[i-1] || P[j-1] == '?') {//ע���ַ�����һ
				dp[i][j] = dp[i - 1][j - 1];
			}
			else if (P[j-1] == '%') {//ע���ַ�����һ
				dp[i][j] =dp[i][j - 1]||dp[i - 1][j];//%ռ0���ַ�ʱ��ռ1�������ַ�ʱ
			}
		}
	}
	return dp[m][n];
}

int main() {
	if (judge()) {
		cout << "true";
	}
	else {
		cout << "false";
	}
	system("pause");
	return 0;
}