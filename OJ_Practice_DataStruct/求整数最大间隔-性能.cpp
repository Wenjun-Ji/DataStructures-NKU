#include<iostream>
using namespace std;
#include<vector>

int  seed;
int rand() { return(((seed = seed * 214013L + 2531011L) >> 16) & 0x7fff); }
int rand32() {
	return ((rand() << 16) + (rand() << 1) + rand() % 2);
}
vector<int> v;
void MinGap() {
	int n = 0;
	cin >> n>>seed;
	for (int i = 0; i < n; i++) {
		v.push_back(rand32());
		//cout << v[i]<<endl;
	}
	int max = -10e9, min = 10e9;
	for (int i = 0; i < n; i++) {
		if (v[i] < min)
			min = v[i];
		if (v[i] > max)
			max = v[i];
	}
	int delta = max - min;
	vector<long long>Max(n,-1e15);
	vector<long long>Min(n, 1e15);
	//cout << Max[1] <<" " << Min[1] << endl;

	double d = (double)(max - min) / (double)n;
	//cout <<"max:" << max<<" min:" << min <<" delta:" << delta <<" d:" << d << endl;
	for (int i = 0; i < n; i++) {
		int k = (v[i] - min) / d;
		if (k == n)k--;
		//cout << k <<endl;
		if (v[i] < Min[k])
			Min[k] = v[i];
		if (v[i] > Max[k])
			Max[k] = v[i];
	}
	int result = 0;
	
	for (int i = 0; i < Min.size()-1;i++) {
		if (Min[i] != 1e15) {
			int j = i+1;
			while (j<Min.size()){
				if (Min[j] != 1e15)
					break;
				else 
					j++;
			}
			if (j != Min.size() - 1 && Min[j] - Max[i] > result) {
				//cout << Min[i] << " " << Max[i] << endl;
				//cout << Min[j] << " " << Max[j] <<endl<< endl;
				result = Min[j] - Max[i];
			}
			if (j != Min.size()) {
				i = j - 1;
			}
		}
	}

	cout << result;
}



int main() {
	MinGap();


	system("pause");
	return 0;
}

/*
�ܽ᣺
����ʹ��ɢ�е�˼��
�����һ�������������ֵ����Сֵ����������������n�ȷ�
������ѧ����ȷ��ÿһ����Ӧ������һ��Ͱ�У�����һ�α�����ֱ��ȷ��Ͱ�����ֵ����Сֵ

�����������Ϊ�������ڣ�ֱ�ӿ��Ը��ſ�Ͱ���ķǿ�Ͱ��ǰһ��Ͱ�����ֵ��ȥ��һ��Ͱ����Сֵ
�������еķǿ�Ͱ�󼴿�ȷ�������

ע�⣺ע��ռ�Ľ�Լ һ�β��������ܽ���������
ע��forѭ����whileѭ�������� �Լ���������



*/