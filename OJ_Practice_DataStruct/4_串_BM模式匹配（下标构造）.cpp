#include<iostream>
#include<vector>
using namespace std;
#define ASCII 256


void get_BC_table(string & Pattern,vector<int>& BC_table) {
	int plen = Pattern.length();
	for (int i = 0; i < plen; i++) {
		BC_table[Pattern[i]] = i;
	}
}

void get_suffix(string & Pattern,vector<int> &suffix) {
	int plen = Pattern.length();
	int i = 0;
	int j = 0;
	for (int i = 0; i < plen - 1;i++) {
		for (int j = 0; Pattern[i - j] == Pattern[plen - 1 - j]; j++) { ; }
		suffix[i] = j;
	}
	suffix[plen - 1] = plen;
	for (int i = 0; i < plen; i++) {
		cout << suffix[i] << " ";
	}
	cout << endl;
}


void get_GS_table(vector<int> &suffix,vector<int>&GS_table) {
	int plen = suffix.size();
	for (int i = plen - 1; i >= 0; i--) {
		if (suffix[i] == i + 1) {
			for (int j = 0; j < plen - 1 - i; j++) {
				GS_table[j] = plen - 1 - i;
			}
		}
	}
	for(int i=0;i<plen-1;i++){
		GS_table[plen - 1 - suffix[i]] = plen - 1 - i;
	}

	for (int i = 0; i < plen; i++) {
		cout << GS_table[i]<<" ";
	}
	cout << endl;
}

int BM(string & Target,string & Pattern) {
	int plen = Pattern.length();
	int tlen = Target.length();
	int i = 0, j = plen-1;
	int BCmove = 0;
	int GSmove = 0;
	vector<int>BC_table(ASCII,-1);
	vector<int>GS_table(plen,plen);
	vector<int>suffix(plen,0);
	get_suffix(Pattern,suffix);
	get_BC_table(Pattern, BC_table);
	get_GS_table(suffix, GS_table);
	while (i <= tlen - plen ) {
		if (Target[i + j] == Pattern[j]) { j--; }
		else {
			BCmove = j-BC_table[Target[i + j]];
			GSmove = GS_table[j];
			i += BCmove > GSmove ? BCmove : GSmove;
			j = plen - 1;
		}
		if (j < 0) { return i; }
	}
	return -1;
}


int main() {
	string Pattern, Target;
	cin >> Target >> Pattern;
	cout<<BM(Target,Pattern);
	return 0;
}