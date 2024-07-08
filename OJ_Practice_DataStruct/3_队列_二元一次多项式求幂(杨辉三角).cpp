#include<iostream>
#include<cmath>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
queue<long long> q;
//杨辉三角法求系数
//
void yanghui(int a,int b,int n) {
	long long s = 0, t = 0; //这个地方不可以是int
	q.push(a);//初始化队列
	q.push(b);//相当于给出第一行的 0(s) 1(t) 1   
	for (int i = 1; i < n; i++) { //所以这个地方改为 <=n 靠s就可以输出前9行的杨辉三角
		q.push(0);
		for (int j = 1; j <= i + 2; j++) {
			t = q.front(); q.pop();// 0(s) 1(t) 1  0 —》  1(s) 1(t) 0 1   
			q.push(s*b + t*a);///如果求解（a+b）^n 的系数   就拿  s、t  用后指针s*b 前指针t*a
			s = t;
			if (j != i + 2) {
				//cout << s <<" ";//因为输出的是s 所以实际上最后一行并未输出 程序确实执行了10行 但第一行我们已经初始化了 所以最后一行是第11行
			}
		}
		//cout << endl;
	}

	//这个地方再输出第n行的杨辉三角 
	for (int i = 0; i < q.size(); i++) {
		//cout << q.front() << " ";
		q.push(q.front());
		q.pop();
	}
	//cout << endl;


}

void func(int a, int b, int n) {
	
	if (a == 0 && b == 0) {
		cout << 0;
		return;
	}
	int count = 0;
	vector<long long> K;
	for (int i = 0; i < q.size(); i++) {
		K.push_back(q.front());
		q.push(q.front());
		q.pop();
	}
	//sort(K.begin(), K.end());
	int i = 0;
	for (vector<long long>::iterator j = K.begin(); j != K.end(); j++) {
		//cout << *j << " ";
		long long k;
		k = *j;
		if (k == 0) {
			i++; 
			continue;
		}
		if (count > 0 && k > 0)
			cout << "+";
		if (k != 1 && k != -1)
			cout << k;
		if (k == -1)
			cout << "-";
		if (i != n)
			cout << "x";
		if (i != n && i != n-1)
			cout << "^" << n-i;
		if (i != 0)
			cout << "y";
		if (i != 0 && i != 1)
			cout << "^" << i;
		count++;
		i++;
	}
	


	/*for (int i = n; i >= 0; i--) {
		long long A;
		long long B;
		long long K;
		if (K == 0) { continue; }
		if (count > 0 && K > 0)
			cout << "+";
		if (K != 1 && K != -1)
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
	}*/
}


//int main() {
//	int a, b, n;
//	cin >> a >> b >> n;
//	yanghui(a,b,n);
//	func(a, b, n);
//	//system("pause");
//	return 0;
//}