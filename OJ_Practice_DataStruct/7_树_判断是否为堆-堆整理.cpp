#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
struct Con{
	vector<int> SeqCon;
	int n;
};
bool JudgeMaxCon(Con&con) {
	int index = (con.SeqCon.size()-1) / 2;
	for (int i = index; i >= 1; i--) {
		if (2 * i < con.SeqCon.size() && 2 * i + 1 < con.SeqCon.size()) {
			if (con.SeqCon[2 * i] <= con.SeqCon[i] && con.SeqCon[2 * i + 1] <= con.SeqCon[i]) {}
			else { return false; }
		}
		else if (2 * i < con.SeqCon.size() && 2 * i + 1 >= con.SeqCon.size()) {
			if (con.SeqCon[2 * i] <= con.SeqCon[i] ) {}
			else { return false; }
		}
	}
	return true;
}
bool JudgeMinCon(Con&con) {
	int index = (con.SeqCon.size() - 1) / 2;
	for (int i = index; i >= 1; i--) {
		if (2 * i < con.SeqCon.size() && 2 * i + 1 < con.SeqCon.size()) {
			if (con.SeqCon[2 * i] >= con.SeqCon[i] && con.SeqCon[2 * i + 1] >= con.SeqCon[i]) {}
			else { return false; }
		}
		else if (2 * i < con.SeqCon.size() && 2 * i + 1 >= con.SeqCon.size()) {
			if (con.SeqCon[2 * i] >= con.SeqCon[i]) {}
			else { return false; }
		}
	}
	return true;
}
void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void AdjustSubMaxTree(Con& con, int i) {
	if (i <= con.SeqCon.size() - 1) {
		if (2 * i < con.SeqCon.size() && 2 * i + 1 < con.SeqCon.size()) {
			if (con.SeqCon[2 * i] <= con.SeqCon[i] && con.SeqCon[2 * i + 1] <= con.SeqCon[i]) {}
			else {
				if (con.SeqCon[2 * i] > con.SeqCon[2 * i + 1]) {
					swap(con.SeqCon[2 * i], con.SeqCon[i]);
					AdjustSubMaxTree(con, 2 * i);
				}
				else if (con.SeqCon[2 * i + 1] >= con.SeqCon[2 * i]) {
					swap(con.SeqCon[2 * i + 1], con.SeqCon[i]);
					AdjustSubMaxTree(con, 2 * i + 1);
				}
			}
		}
		else if (2 * i < con.SeqCon.size() && 2 * i + 1 >= con.SeqCon.size()) {
			if (con.SeqCon[2 * i] <= con.SeqCon[i]) {}
			else {
				swap(con.SeqCon[2 * i], con.SeqCon[i]);
				AdjustSubMaxTree(con, 2 * i);
			}
		}
	}
}

void AdjustSubMinTree(Con& con, int i) {
	if (i <= con.SeqCon.size() - 1) {
		if (2 * i < con.SeqCon.size() && 2 * i + 1 < con.SeqCon.size()) {
			if (con.SeqCon[2 * i] >= con.SeqCon[i] && con.SeqCon[2 * i + 1] >= con.SeqCon[i]) {}
			else {
				if (con.SeqCon[2 * i] < con.SeqCon[2 * i + 1]) {
					swap(con.SeqCon[2 * i], con.SeqCon[i]);
					AdjustSubMinTree(con, 2 * i);
				}
				else if (con.SeqCon[2 * i + 1] <= con.SeqCon[2 * i]) {
					swap(con.SeqCon[2 * i + 1], con.SeqCon[i]);
					AdjustSubMinTree(con, 2 * i + 1);
				}
			}
		}
		else if (2 * i < con.SeqCon.size() && 2 * i + 1 >= con.SeqCon.size()) {
			if (con.SeqCon[2 * i] >= con.SeqCon[i]) {}
			else {
				swap(con.SeqCon[2 * i], con.SeqCon[i]);
				AdjustSubMaxTree(con, 2 * i);
			}
		}
	}
}

void getMax(Con&con) {
	int index = (con.SeqCon.size() - 1) / 2;
	for (int i = index; i >= 1; i--) {
		AdjustSubMaxTree(con, i);
	}
}
void getMin(Con&con) {
	int index = (con.SeqCon.size() - 1) / 2;
	for (int i = index; i >= 1; i--) {
		AdjustSubMinTree(con, i);
	}
}
void show(Con&con) {
	for (int i = 1; i <con.SeqCon.size(); i++) {
		cout << con.SeqCon[i];
		if (i < con.SeqCon.size()-1) { cout << " "; }
	}
}
void func() {
	int n = 0;
	cin >> n;
	Con con;
	con.SeqCon.push_back(-999);
	int e;
	for (int i = 0; i < n; i++) {	
		cin >> e;
		con.SeqCon.push_back(e);
	}
//	show(con);
	if (JudgeMaxCon(con) && JudgeMinCon(con)) {
		cout << "max min ";
	}else if (JudgeMaxCon(con)) {
		cout << "max ";
		getMin(con);
		show(con);
	}
	else if (JudgeMinCon(con)) {
		cout << "min ";
		getMax(con);
		show(con);
	}
	else {
		getMax(con);
		show(con);
	}



}
int main() {
	func();
	//system("pause");
	return 0;
}
