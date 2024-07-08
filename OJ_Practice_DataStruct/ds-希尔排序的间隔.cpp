#include<iostream>
using namespace std;
void func() {
	int n;
	cin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int flagk = 0;
	int flagi = 0;

	for (int k = 1; k <= n; k++) {
		flagk = 1;
		for (int i = 0; i < n; i++) {
			for (int j = i; j+k< n; j += k) {
				if (a[j] > a[j + k]) {
					flagk = 0;
					break;
				}
			}
		}
		if (flagk == 1) {
			cout << k;
			break;
		}
	}
}


int main() {
	func();
	system("pause");
	return 0;
}