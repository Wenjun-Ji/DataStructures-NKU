#include<iostream>
using namespace std;
#include<stack>


char getchar(int num) {
	if (num >= 0 && num <= 9) {
		return (char)('0' + num);
	}
	else {
		return (char)('A' + num - 10);
	}
}


stack<char>S;
void func() {
	int flag = 0;
	long long num = 0;
	int bit = 0;
	cin >> num >> bit;
	if (num < 0) {
		flag = 1; num = -num;
	}

	long long chushu=num/bit;
	int yushu= num%bit;
	while (chushu!=0) {
		S.push(getchar(yushu));
		yushu = chushu % bit;
		chushu = chushu / bit;
	}	
	if (chushu == 0) {
		S.push(getchar(yushu));
	}

	if (flag == 1) { cout << "-"; }
	while (!S.empty()) {
		cout << S.top();
		S.pop();
	}
}

int main() {
	func();
	system("pause");
	return 0;
}