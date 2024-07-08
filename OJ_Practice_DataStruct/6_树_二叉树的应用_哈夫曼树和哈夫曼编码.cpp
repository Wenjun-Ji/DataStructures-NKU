#include<iostream>
#include<algorithm>
#include<string>
#include<stack>
using namespace std;
#define ASCII 256
typedef struct HFNode {
	string name;
	int lchild;
	int rchild;
	int parent;
	float weight;
}HFNode;

struct HFTree {
	HFNode* HFT;
	int n;
	HFTree() :HFT(NULL), n(0) {}
};

struct mychar {
	char ch;
	int n;
};

bool cmp(mychar c1, mychar c2) {
	return c1.n > c2.n;
}

int getN(string text,mychar *&char_table,float*& Weight) {
	int count = 0;
	char_table=new mychar[ASCII];
	for (int i = 0; i < ASCII; i++) {
		char_table[i].ch = i;
		char_table[i].n = 0;
	}
	for (int i = 0; i < text.length(); i++) {
		char_table[text[i]].n++;
	}
	sort(char_table,char_table+ASCII, cmp);
	for (int i = 0; i < ASCII; i++) {
		if (char_table[i].n != 0) {
			count++;
		}
	}
	Weight = new float[count];
	for (int i = 0; i < count; i++) {
		Weight[i] = ((float)char_table[i].n / text.length() * 100);
		//cout <<char_table[i].ch<<" "<<char_table[i].n<<" " << Weight[i] << endl;
	}
	return count;
}


void Select(HFTree T, int n, int& s1, int& s2) {
	for (int i = 0; i < n; i++) {
		if (T.HFT[i].parent == 0) {
			s1 = i;
		}
	}

	for (int i = 0; i < n; i++) {
		if (T.HFT[i].parent == 0 && T.HFT[i].weight < T.HFT[s1].weight) {
			s1 = i;
		}
	}

	for (int i = 0; i < n; i++) {
		if (T.HFT[i].parent == 0 && i != s1) {
			s2 = i;
		}
	}

	for (int i = 0; i < n; i++) {
		if (T.HFT[i].parent == 0 && T.HFT[i].weight < T.HFT[s2].weight && i != s1) {
			s2 = i;
		}
	}
}

void InitHFT(HFTree &T,int n,float* Weight) {
	int m = 2 * n - 1;
	T.HFT = new HFNode[m];
	T.n = n;
	for (int i = 0; i < m; i++) {
		T.HFT[i].parent = 0;
		T.HFT[i].lchild = 0;
		T.HFT[i].rchild = 0;
		if(i<n)
			T.HFT[i].weight = Weight[i];
	}
	for (int i = n; i < m; i++) {
		int s1 = 0;
		int s2 = 0;
		Select(T,i, s1, s2);
		T.HFT[s1].parent = i;
		T.HFT[s2].parent = i;
		T.HFT[i].lchild = s1;
		T.HFT[i].rchild = s2;
		T.HFT[i] .weight = T.HFT[s1].weight + T.HFT[s2].weight;
	}
}

void Show(HFTree T) {
	cout << "showHFT" <<endl;
	int m = 2 * T.n - 1;
	for (int i = 0; i < m; i++) {
		cout << i << " " << T.HFT[i].weight << " " << T.HFT[i].parent<<" "<< T.HFT[i].lchild<<" "<< T.HFT[i].rchild << endl;
	}
}

void HFCode(HFTree &T,string * HC) {
	stack<char> temp;
	int c = 0;
	int father = 0;
	for (int i = 0; i < T.n; i++) {
		c = i;
		father = T.HFT[i].parent;
		while (father != 0) {
			if (T.HFT[father].lchild == c) { temp.push('0'); }
			if (T.HFT[father].rchild == c) { temp.push('1'); }
			c = father;
			father = T.HFT[c].parent;
		}
		while (!temp.empty()) {
			HC[i] += temp.top();
			temp.pop();
		}
	}
}


void ShowHFCode(mychar*&char_table,string* HC,int n) {
	for (int i = 0; i < n; i++) {
		cout << char_table[i].ch << " " << HC[i] << endl;
	}

}




int main(){
	HFTree T;
	string text;
	mychar* char_table=NULL;
	float* Weight=NULL;
	getline( cin,text);
	int n = 0;
	n=getN(text, char_table, Weight);
	cout << "n = " << n << endl;
	InitHFT(T, n, Weight);
	//Show(T);
	string* HC = new string[n];
	HFCode(T, HC);
	ShowHFCode(char_table, HC, n);


	system("pause");
	return 0;
}