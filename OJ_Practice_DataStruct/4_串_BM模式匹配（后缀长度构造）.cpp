#include<iostream>
using namespace std;
#define ASCII 256

void generateBC(string target,int bc[]) {
	int tlen = target.length();
	for (int i = 0; i < ASCII; i++) {
		bc[i] = -1;
	}
	for (int i = 0; i < tlen; i++) {
		bc[target[i]]=i;
	}
}
void generateGS(string pattern,int suffix[],bool prefix[]) {
	int plen = pattern.length();
	for (int i = 0; i < plen; i++) {
		suffix[i] = -1;
		prefix[i] = false;
	}
	for (int i = 0; i < plen-1; i++) {
		int k = 0;
		int j = i;
		//for (; j >= 0; j--) {//用while循环的话可以省去一些循环次数
		//	if (pattern[j] == pattern[plen - 1 - k]) {
		//		k++;
		//		suffix[k] = j;
		//	}
		//}
		while (j >= 0 && pattern[j] == pattern[plen - 1 - k]) {
			k++;
			j--;
			suffix[k] = j + 1;
		}
		if (j < 0) {
			prefix[k] = true;
		}
	}
}

int getGsMove(int index,int plen,int suffix[],bool prefix[]) {
	int k = plen - index - 1;
	if (suffix[k] != -1) {
		return index + 1 - suffix[k];
	}
	else {
		for (int i = index + 1; i < plen; i++) {
			if (prefix[plen - i - 1] == true) {
				return i;
			}
		}
		
	}
	return 0;
}

int BM(string target,string pattern) {
	int *bc;
	int	* suffix;
	bool * prefix;
	bc = new int[ASCII];
	int tlen = target.length();
	int plen = pattern.length();
	suffix = new int[plen];
	prefix = new bool[plen];
	int BcMove = 0;
	int GsMove = 0;
	int Move=0;
	generateBC(pattern, bc);
	generateGS(pattern, suffix, prefix);
	int i = 0;
	//for (; i <= tlen - plen; i++) {
	//	int j = plen - 1;
	//	for (; j >= 0; j--) {
	//		if (target[i + j] == pattern[j]) {}
	//		else {
	//			BcMove = bc[target[i + j]];
	//			if(j<plen-1)
	//				GsMove = getGsMove(j, plen, suffix, prefix);
	//			Move = BcMove > GsMove ? BcMove : GsMove;
	//			i = i + Move -1;
	//			j = plen-1 +1;
	//			break;
	//		}
	//	}
	//	if (j < 0) {
	//		return i;
	//	}
	//}
	while (i <= tlen - plen) {
		int j = plen - 1;
		for (; j >= 0; j--) {
			if (pattern[j] != target[i + j]) {
				break;
			}
		}
		if (j < 0) {
			return i;
		}
		else {
			BcMove = j - bc[target[i + j]];
			if (j < plen - 1)
				GsMove = getGsMove(j, plen, suffix, prefix);
			Move = BcMove > GsMove ? BcMove : GsMove;
			i = i + Move;
		}
	}

	return -1;
}


int main() {
	cout << BM("ABCDABCDABDE", "DBAEA");
	return 0;
}


//BM
void generateBC(string target, int bc[]) {
	int tlen = target.length();
	for (int i = 0; i < ASCII; i++) {
		bc[i] = -1;
	}
	for (int i = 0; i < tlen; i++) {
		bc[target[i]] = i;
		//BM_BC_count++;
	}
}

void generateGS(string pattern, int suffix[], bool prefix[]) {
	int plen = pattern.length();
	for (int i = 0; i < plen; i++) {
		suffix[i] = -1;
		prefix[i] = false;
	}
	for (int i = 0; i < plen - 1; i++) {
		int k = 0;
		int j = i;
		while (j >= 0 && pattern[j] == pattern[plen - 1 - k]) {
			k++;
			j--;
			suffix[k] = j + 1;
			//BM_GS_count++;
		}
		if (j < 0) {
			prefix[k] = true;
		}
	}
}

int getGsMove(int index, int plen, int suffix[], bool prefix[]) {
	int k = plen - index - 1;
	if (suffix[k] != -1) {
		return index + 1 - suffix[k];
	}
	else {
		for (int i = index + 1; i < plen; i++) {
			if (prefix[plen - i - 1] == true) {
				return i;
			}
			//BM_GSmove_count++;
		}
	}
	return plen;
}

int BM(string target, string pattern) {


	int* bc;
	int* suffix;
	bool* prefix;
	bc = new int[ASCII];
	int tlen = target.length();
	int plen = pattern.length();
	suffix = new int[plen];
	prefix = new bool[plen];
	int BcMove = 0;
	int GsMove = 0;
	int Move = 0;


	generateBC(pattern, bc);
	generateGS(pattern, suffix, prefix);

	int i = 0;
	while (i <= tlen - plen) {
		//cout << i;
		int j = plen - 1;
		for (; j >= 0; j--) {
			if (pattern[j] != target[i + j]) {
				break;
			}
			//BM_search_count++;
		}
		if (j < 0) {
			return i;
		}
		else {
			BcMove = j - bc[target[i + j]];
			GsMove = 0;//这一步是为了清空上一次的Gsmove值
			if (j < plen - 1)
				GsMove = getGsMove(j, plen, suffix, prefix);
			//cout << "BcMove:" << BcMove << " GsMove:" << GsMove << endl;
			Move = BcMove > GsMove ? BcMove : GsMove;
			i = i + Move;
		}
	}

	return -1;



}