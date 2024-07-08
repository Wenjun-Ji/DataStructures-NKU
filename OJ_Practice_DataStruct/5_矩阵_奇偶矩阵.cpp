#include<iostream>
#include<vector>
using namespace std;
int main() {
	int m = 0;
	cin >> m;
	int** arr = new int* [m];
	for (int i = 0; i < m; i++) {
		*(arr + i) = new int[m];
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
		}
	}

	bool *row=new bool [m];
	bool *col=new bool [m];
	int rowsum = 0;
	int colsum = 0;

	for (int i = 0; i < m; i++) {
		rowsum = 0;
		for (int j = 0; j < m; j++) {
			rowsum += arr[i][j];
		}
		if (rowsum % 2 == 0) { row[i] = true; }
		else row[i] = false;
	}
	for (int i = 0; i < m; i++) {
		colsum = 0;
		for (int j = 0; j < m; j++) {
			colsum += arr[j][i];
		}
		if (colsum % 2 == 0) { col[i] = true; }
		else col[i] = false;
	}

	vector<int> r;
	vector<int> c;
	int rflag = 0;
	int cflag = 0;

	for (int i = 0; i < m; i++) {
		if (!row[i]) { r.push_back(i); rflag++;}
	}
	for (int i = 0; i < m; i++) {
		if (!col[i]) { c.push_back(i); cflag++;}
	}



	if (rflag == 0 && cflag == 0) {
		cout << "OK";
	}
	else if (rflag == 1 && rflag==1) {
		cout << "Change bit" << " (" << r[0]+1 << "," << c[0]+1 << ")";
	}
	else { 
		cout << "Corrupt"; 
	}




	//system("pause");
	return 0;
}