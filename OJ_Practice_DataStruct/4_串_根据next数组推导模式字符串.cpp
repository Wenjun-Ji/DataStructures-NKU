#include<iostream>
using namespace std;
int front, rear;
int num;
bool _KMP(int next[],int result[]) {
	int pm = 0,k=1;
	for (int i = 0; i < num; i++,k++) {
		if (i == 0) { result[i] = front; }
		else if (i == num - 1) { result[i] = rear; }
		else {
			pm = next[k];
			//cout << "???" << (result[0] == 0 ? 1 : 0) << endl;
			if (pm == 0) result[i] = (result[0] == 0 ? 1:0);
			else if (i <= pm - 1) return false;
			else { result[i] = result[pm - 1]; }
		}
		//cout << result[i]<<" ";
	}
	//cout << endl;

	int* re_next = new int[num+1];
	int i = 1, j = 0;
	re_next[1] = 0;
	while (i < num) {
		if (j == 0 || result[i-1] == result[j-1]) {//注意这里的减一 因为在字符串的KMP中result[0]存储的是长度 但在这里的整数型数组result[0]存储的是元素
			i++; j++;
			re_next[i] = j;
		}
		else { j = re_next[j]; }
	}

	for(int i=1;i<=num;i++){
		if (re_next[i] - 1 != next[i-1]) { return false; }
	}

	return true;
}

int main() {

	cin >> front >> rear >> num;
	int* result = new int[num];
	int* next = new int[num];
	for (int i = 0; i < num; i++) { cin >> next[i]; }
	

	if (_KMP(next, result)) {
		for (int i = 0; i < num; i++) { cout << result[i]; }
	}
	else {
		cout << "ERROR";
	}
	return 0;
}