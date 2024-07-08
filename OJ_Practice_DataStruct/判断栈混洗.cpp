#include<iostream>
#include<stack>
using namespace std;
stack<int>A;
stack<int>B;
stack<int>T;

bool judge() {
	int n = 0;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		A.push(i);
	}
	for (int i = 1; i <= n; i++) {
		int m = 0;
		cin >> m;
		B.push(m);
	}
	T.push(B.top());
	B.pop();
	while (!(B.empty()&&T.empty())) {
		if(T.empty()||T.top()!=A.top()){
			if (!B.empty()) {
				T.push(B.top());
				B.pop();
			}
			else {
				return false;
			}
		}else if (T.top() == A.top()) {
			T.pop();
			A.pop();
		}
	}
	return true;
}




int main() {
	cout << judge();
	
	system("pause");
	return 0;
}