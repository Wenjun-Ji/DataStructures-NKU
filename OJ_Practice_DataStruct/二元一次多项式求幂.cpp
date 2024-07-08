#include<iostream>
using namespace std;
#include<queue>
queue<long>Q;
void YangHui(int a,int b,int N) {
	Q.push(0); Q.push(a); Q.push(b); Q.push(0);
	for (int n = 0; n < N; n++) {
		for (int i = 0; i < Q.size() - 1; i++) {
			long top1 = Q.front()*b; Q.pop();
			long top2 = Q.front()*a;
			//cout << top1 + top2 << " ";
			Q.push(top1 + top2);
		}
		//cout << endl;
		if(n<N-1)
			Q.push(0);
	}
}


int main() {
	int a = 0; int b = 0; int N = 0;
	cin >> a >> b >> N;
	YangHui(a,b,N-1);
	Q.pop();
	for (int i = 0; i < N + 1; i++) {
		long k = Q.front(); Q.pop();
		long x_k = N - i;
		long y_k = i;
		if (k > 0 && i != 0)cout << "+";
		if (k != 0) {
			if (k == 1) {
				;
			}
			else if (k == -1) {
				cout << "-";
			}
			else {
				cout << k;
			}
			if (x_k == 0) {
			
			}
			else if (x_k == 1) {
				cout << "x";
			}
			else {
				cout << "x^";
				cout << x_k;
			}
			if (y_k == 0) {
				;
			}
			else if (y_k == 1) {
				cout << "y";
			}
			else {
				cout << "y^";
				cout << y_k;
			}
		}
	}
	if (a == 0 && b == 0) {
		cout << 0;
	}
	system("pause");
	return 0;
}