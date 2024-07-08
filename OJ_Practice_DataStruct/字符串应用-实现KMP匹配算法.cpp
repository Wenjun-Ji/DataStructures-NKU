#include<iostream>
using namespace std;

void get_next(string P,int* next) {
	int len = P.length()-1;
	int i = 1; int j = 0;
	next[1] = 0;
	while (i<len) {
		if (j == 0 || P[i] == P[j]) {
			i++; j++;
			next[i] = j;
		}
		else {
			j = next[j];
		}
	}
	//for (int i = 1; i <= len; i++) {
	//	cout << next[i] << " ";
	//}
	//cout << endl;
}

int KMP(string S,string P,int* next) {
	int S_len = S.length()-1;
	int P_len = P.length()-1;
	int i = 1,j = 1;
	while (i <= S_len&&j<=P_len) {
		if (j==0||S[i] == P[j]) {
			i++; j++;
		}
		else {
			j = next[j];
		}
	}
	if (j > P_len) {
		return i - j;
	}
	else {
		return -1;
	}
}

void func() {
	string S, P;
	cin >> S >> P;
	//cout << S << endl;
	//cout << P << endl;
	int* next = new int[P.length() + 1];
	get_next('#'+P, next);
	int result = KMP('#'+S, '#'+P, next);
	if (result > 0) {
		cout << result;
	}
	else {
		cout << "no";
	}
}


int main() {
	func();
	system("pause");
	return 0;
}
