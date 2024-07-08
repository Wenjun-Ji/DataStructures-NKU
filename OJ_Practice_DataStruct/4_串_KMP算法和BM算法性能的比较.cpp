#include<iostream>
#include<cstring>
#include<time.h>
#include<windows.h>
#include<ctime>
#include<cstdlib>
using namespace std;

#define ASCII 256
int KMP_next_count = 0;
int KMP_search_count = 0;
int BM_BC_count = 0;
int BM_GS_count = 0;
int BM_GSmove_count = 0;
int BM_search_count = 0;
enum LongType {Short,Middle,Long};
enum ComplexType {Easy,Normal,Hard};
enum Place {qian,zhong,hou};
//KMP
void get_next(string pattern,int next[]) {
	int i = 0, j = -1;
	next[0] = -1;
	int plen = pattern.length();
	while (i < plen-1) {
		if (j == -1 || pattern[i] == pattern[j]) {
			i++; j++;
			next[i] = j;
		}
		else {
			j = next[j];
		}
		KMP_next_count++;
	}
}

int KMP(string target, string pattern) {
	int plen = pattern.length();
	int tlen = target.length();
	int* next = new int[plen];
	get_next(pattern, next);
	int i = 0, j = 0;
	while (i <= tlen - 1 && j <= plen - 1) {
		if (j == -1 || target[i] == pattern[j]) {
			i++;
			j++;
		}
		else {
			j = next[j];
		}
		KMP_search_count++;
	}
	if (j > plen - 1) {
		return i - plen;
	}
	else {
		return -1;
	}
}

int KMP_N(string target,string pattern) {
	int plen = pattern.length();
	int tlen = target.length();
	int* next = new int[plen];
	get_next(pattern, next);
	int i = 0, j = 0;
	int temp = i;
	while (i <= tlen-1 && j <= plen-1) {
		if (j==-1||target[i] == pattern[j]) {
			i++;
			j++;
		}
		else {
			j = next[j];
		}
		KMP_search_count++;
		if (j > plen - 1) {
			//cout<<"i=" << i-plen << " ";
			i=i-j+1;
			j = 0;
		}
	}
	return -1;
}


//BM
void generateBC(string target, int bc[]) {
	int tlen = target.length();
	for (int i = 0; i < ASCII; i++) {
		bc[i] = -1;
	}
	for (int i = 0; i < tlen; i++) {
		bc[target[i]] = i;
		BM_BC_count++;
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
		//for (; j >= 0; j--) {//��whileѭ���Ļ�����ʡȥһЩѭ������
		//	if (pattern[j] == pattern[plen - 1 - k]) {
		//		k++;
		//		suffix[k] = j;
		//	}
		//}
		while (j >= 0 && pattern[j] == pattern[plen - 1 - k]) {
			k++;
			j--;
			suffix[k] = j + 1;
			BM_GS_count++;
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
			BM_GSmove_count++;
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
			BM_search_count++;
		}
		if (j < 0) {
			return i;
		}
		else {
			BcMove = j - bc[target[i + j]];
			GsMove = 0;//��һ����Ϊ�������һ�ε�Gsmoveֵ
			if (j < plen - 1)
				GsMove = getGsMove(j, plen, suffix, prefix);
			cout << "BcMove:" << BcMove << " GsMove:" << GsMove << endl;
			Move = BcMove > GsMove ? BcMove : GsMove;
			i = i + Move;
		}
	}
	return -1;
}

int BM_N(string target, string pattern) {
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
			BM_search_count++;
		}
		if (j < 0) {
			//cout<<"i="<< i<<" ";
			j = plen - 1;
			i++;
		}
		else {
			BcMove = j - bc[target[i + j]];
			GsMove = 0;//��һ����Ϊ�������һ�ε�Gsmoveֵ
			if (j < plen - 1)
				GsMove = getGsMove(j, plen, suffix, prefix);
			cout << "BcMove:" << BcMove << " GsMove:" << GsMove << endl;
			Move = BcMove > GsMove ? BcMove : GsMove;
			i = i + Move;
		}
	}
	return -1;
}


	// �涨����Ϊ
	// 20-100��Ϊ���ַ��� 100-10000Ϊ���ַ��� 10000-1000000Ϊ���ַ��� 
	// ����2���ַ��ļ��ַ��� ����10���ַ�(0-9)��Ϊ��ͨ�ַ��� ����95���ַ���Ϊ�����ַ����� ASCII  32~126(��95��)�ַ�(32�ǿո�)��
	// ���о������� �ֱ���KMP�㷨��BM�㷨��ƥ��ģʽ��  
	// Ϊ�˷�������涨ģʽ������Ϊ5�����������к��ж��ģʽ�������Σ���ȡƥ���ÿһ��������ģʽ��Ϊֹ �����ܴ�������ʱ����Ϊ���ܴ���
	//ģʽ�����췽ʽΪ�˷��������ȡ�������������ȡ������5���ķ�ʽ

string& generate_Target(LongType L,ComplexType C,string &s) {
	int max,min;
	int Long;
	if (L == 0 ) {Long = 50;}
	if (L == 1) { Long = 5000; }
	if (L == 2) { Long = 500000; }
	if (C == 0) {max = 1; min = 0;}
	if (C == 1) { max = 9; min = 0; }
	if (C == 2) { max = 78; min = -16; }
	for (int i = 0; i < Long; i++) {
		s += (char)('0' + rand() % (max - min + 1) + min);
	}
	//cout <<"Target_str: " << s << endl;
	return s;
}
string& generate_Patter(LongType L,string& target,string& s,int i) {
	int start = i*target.length() / 4;
	int n = 0;
	if (L == 0) { n = 5; }
	if (L == 1) { n = 50; }
	if (L == 2) { n = 500; }
	s = target.substr(start, n);
	//cout <<"Pattern_str: " << s << endl;
	return s;
}


//abbabababbabababbabbbabbaaabababbababbababb
int main() {
	srand(time(0));
	//for (int i = 1; i <= 3; i++) {
		//for (int j = 1; j <= 3; j++) {
			string Target, Pattern;
			Target = "0002010101";
				//= generate_Target(Long, Hard, Target);
			Pattern = "0001";
				//= generate_Patter(Short, Target, Pattern, 1);

			double time = 0;
			double counts = 0;
			LARGE_INTEGER nFreq;
			LARGE_INTEGER nBeginTime;
			LARGE_INTEGER nEndTime;
			QueryPerformanceFrequency(&nFreq);

			int resultKMP = 0, resultBM = 0;
			cout << endl;
			cout << "KMP�㷨���ܲ��ԣ�" << endl;
			//KMP
			QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ  
			//...���Դ���
			resultKMP = KMP(Target, Pattern);
			QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
			time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λ  
			//cout << "\nresult:" << resultKMP;
				cout<< " ����ʱ�䣺" << time * 1000 << "ms" << endl;
			cout << "KMP_next_count:" << KMP_next_count << "\nKMP_search_count:" << KMP_search_count << "\nSUM_KMP_count:" << KMP_next_count + KMP_search_count << endl;

			cout << endl;
			cout << "BM�㷨���ܲ��ԣ�" << endl;

			//BM
			QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ  
			//...���Դ���
			resultBM = BM(Target, Pattern);
			QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
			time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs
			cout << "\nresult:" << resultBM;
				cout<< " ����ʱ�䣺" << time * 1000 << "ms" << endl;
			cout << "BM_BC_count:" << BM_BC_count << "\nBM_GS_count:" << BM_GS_count << "\nBM_GSmove_count:" << BM_GSmove_count << "\nBM_search_count:" << BM_search_count << "\nSUM_BM_count:" << BM_BC_count + BM_GS_count + BM_GSmove_count + BM_search_count << endl;
			cout << endl;
		//}
	//}


	system("pause");
	return 0;

}