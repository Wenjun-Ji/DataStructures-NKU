#include<iostream>
#include<vector>
using namespace std;
struct Node {
	int row;
	int col;
	int data;
	Node() :row(0),col(0){ data = -999;}
	Node(int row,int col,int e) :row(row),col(col),data(e) {}
};

struct SparseMatrix {
	int rows;
	int cols;
	int terms;
	vector<Node*> smArray;
	SparseMatrix(int rows,int cols) {
		this->rows = rows;
		this->cols = cols;
		terms = 0;
	}
	void Append(int row,int col,int value) {

		Node* node = new Node(row, col, value);
		smArray.push_back(node);
	}
	void print() {
		if (smArray.empty()) {
			cout << "The answer is a Zero Matrix" << endl ;
		}else{
			for (vector<Node*>::iterator k = smArray.begin(); k != smArray.end(); k++) {
				cout << (*k)->row << " " << (*k)->col << " " << (*k)->data<<endl;
			}
		}
	}

	/*
1 3 3
1 1 1
1 2 2
1 3 3

3 1 3
1 1 -1
2 1 -1
3 1 1

3 3 9
1 1 1
1 2 2
1 3 3
2 1 1
2 2 2
2 3 3
3 1 1
3 2 2
3 3 3

3 3 9
1 1 1
1 2 2
1 3 3
2 1 1
2 2 2
2 3 3
3 1 1
3 2 2
3 3 3
	*/
	SparseMatrix* operator*(SparseMatrix&m2) {
		if (cols != m2.rows) { cout << "ERROR"<<endl; return NULL; }
		SparseMatrix* result = new SparseMatrix(rows,m2.cols);
		for (int i = 0; i < smArray.size(); i++) {
			for (int j = 0; j < m2.smArray.size(); j++) {
				if (smArray[i]->col == m2.smArray[j]->row) {
					int flag = 1;
					for (vector<Node*>::iterator k=result->smArray.begin(); k != result->smArray.end(); k++) {
						if ((*k)->row == smArray[i]->row && (*k)->col == m2.smArray[j]->col) {
							(*k)->data += smArray[i]->data * m2.smArray[j]->data;
							flag = 0;
							break;
							//if ((*k)->data == 0) {
							//	//result->smArray.erase(k);
							//}
						}
					}
					if (flag == 1) {
						result->Append(smArray[i]->row, m2.smArray[j]->col, smArray[i]->data * m2.smArray[j]->data);
					}
				}
			}
		}
		//result->print();
		SparseMatrix* reresult = new SparseMatrix(rows, m2.cols);

		for (vector<Node*>::iterator k = result->smArray.begin(); k != result->smArray.end(); k++) {
			if ((*k)->data != 0) {
				reresult->smArray.push_back(*k);
			}
		}

		return reresult;
	}
};





int main() {
	int row1, col1,row2,col2,count1,count2;
	cin >> row1 >> col1 >> count1;
	SparseMatrix* m1 = new SparseMatrix(row1,col1);
	for (int i = 0; i < count1; i++) {
		int row = 0;
		int col = 0;
		int value = 0;
		cin >> row >> col >> value;
		m1->Append(row, col, value);
	}
	cin >> row2 >> col2 >> count2;
	SparseMatrix* m2 = new SparseMatrix(row2, col2);
	for (int i = 0; i < count2; i++) {
		int row = 0;
		int col = 0;
		int value = 0;
		cin >> row >> col >> value;
		m2->Append(row, col, value);
	}
	//m1->print();

	//m2->print();
	SparseMatrix* m3 = (*m1)*(*m2);
	//cout<<m3->terms<<endl;
	if (m3) { 
		m3->print(); 
	}



	//system("pause");
	return 0;
}


/*
3 3 9
1 1 1
1 2 2
1 3 3
2 1 1
2 2 2
2 3 3
3 1 1
3 2 2
3 3 3

3 3 9
1 1 1
1 2 2
1 3 3
2 1 1
2 2 2
2 3 3
3 1 1
3 2 2
3 3 3
*/