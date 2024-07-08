#include<iostream>
using namespace std;
#include<string>
#include<stack>
int main() {
	stack<string> s;
	string str = "cat";
	for (int i = 0; i < str.length(); i++)
		s.push(str.substr(i));
	while (!s.empty()) {
		cout << s.top(); s.pop();
	}
	system("pause");
	return 0;
}
