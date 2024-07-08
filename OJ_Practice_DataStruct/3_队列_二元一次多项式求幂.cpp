#include<iostream>
#include<cmath>
#include<queue>
using namespace std;
queue<long long> q;
long long jiecheng(int a) {
	long long result=1;
	for (int i = 1; i <= a; i++){
		result *= i;
	}
	return result;
}

void func(int a,int b,int n) {
	int count = 0;
	for (int i = n; i >= 0; i--) {
		long long A;
		long long B;
		long long K;
		if (i == 0 || i == n)K = 1;
		else {
			K = jiecheng(n) / (jiecheng(n - i) * jiecheng(i));
		}
			A = pow(a, i);
			B = pow(b, n-i);
			K *= A * B;
			if (K == 0) { continue; }
			if (count>0&&K>0)
				cout << "+";
			if (K != 1&&K!=-1)
				cout << K;
			if (K == -1)
				cout << "-";
			if (i != 0) 
				cout << "x";
			if (i != 1 && i != 0)
				cout << "^" << i;
			if (i != n) 
				cout << "y";
			if (i != n - 1 && i != n)
				cout << "^" << n - i;
			count++;
	}
}

//杨辉三角法求系数
//
void yanghui(int n) {
	int s = 0, t = 0;
	q.push(1);//初始化队列
	q.push(1);//相当于给出第一行的 0(s) 1(t) 1   
	for (int i = 1; i <= n; i++) {
		q.push(0);
		for (int j = 1; j <= i+2; j++) {
			t = q.front(); q.pop();// 0(s) 1(t) 1  0 —》  1(s) 1(t) 0 1   
			q.push(s + t);
			s = t;
			if (j != i + 2) {
				cout << s << " ";
			}
		}
	}
}


int main() {
	int a, b, n;
	cin >> a >> b >> n;
	func(a, b, n);

	//system("pause");
	return 0;
}