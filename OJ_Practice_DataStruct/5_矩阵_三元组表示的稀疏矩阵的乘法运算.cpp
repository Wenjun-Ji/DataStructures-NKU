#include<iostream>
using namespace std;
int main() {
	int row1, col1, row2, col2, count1, count2;
	
	cin >> row1 >> col1 >> count1;
	int** arr1 = new int*[row1];
	for (int i = 0; i < row1; i++) {
		*(arr1 + i) = new int[col1];
	}
	for (int i = 0; i < row1; i++) {
		for (int j = 0; j < col1; j++) {
			arr1[i][j] = 0;
		}
	}
	for (int i = 0; i < count1; i++) {
		int row = 0;
		int col = 0;
		int value=0;
		cin >> row >> col >> value;
		arr1[row - 1][col - 1] = value;
	}

	cin >> row2 >> col2 >> count2;	
	int** arr2 = new int* [row2];
	for (int i = 0; i < row2; i++) {
		*(arr2 + i) = new int[col2];
	}
	for (int i = 0; i < row2; i++) {
		for (int j = 0; j < col2; j++) {
			arr2[i][j] = 0;
		}
	}
	for (int i = 0; i < count2; i++) {
		int row = 0;
		int col = 0;
		int value = 0;
		cin >> row >> col >> value;
		arr2[row - 1][col - 1] = value;
	}

	for (int i = 0; i < row1; i++) {
		for (int j = 0; j < col1; j++) {
			//cout << arr1[i][j];
		}
		//cout << endl;
	}
	for (int i = 0; i < row2; i++) {
		for (int j = 0; j < col2; j++) {
			//cout << arr2[i][j];
		}
		//cout << endl;
	}



	int** arr3 = new int* [row1];
	for (int i = 0; i < row1; i++) {
			*(arr3 + i) = new int[col2];
	}
	for (int i = 0; i < row1; i++) {
		for (int j = 0; j < col2; j++) {
			arr3[i][j] = 0;
		}
	}

	if (col1 != row2) {
		cout << "ERROR" << endl;
	}
	else {
		for (int i = 0; i < row1; i++) {
			for(int j = 0; j < col2; j++) {
				for (int k = 0; k < col1; k++) {
					arr3[i][j] += arr1[i][k] * arr2[k][j];
				}
			}
		}
		int count = 0;
		for (int i = 0; i < row1; i++) {
			for (int j = 0; j < col2; j++) {
				if (arr3[i][j] != 0) {
					count++;
					cout << i + 1 <<" " << j + 1<< " " << arr3[i][j] << endl;
				}
			}
		}
		if (count == 0) {
			cout << "The answer is a Zero Matrix" << endl;
		}
	}

	
	



	//system("pause");
	return 0;
}
