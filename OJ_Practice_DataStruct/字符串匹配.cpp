#include<iostream>
using namespace std;
#include<vector>
#include<string>
string S;
string P;
vector<string> p_string;
vector<int> p_string_len;
vector<vector<int>> p_start;
vector<int> p_string_left;



void get_p_string() {
	int P_len = P.length();	int left = 0, right = 0;
	while (left < P_len) {
		//寻找第一个字符串的左侧
		while (left < P_len && P[left] == '%') {
			left++;
		}
		//寻找第一个字符串的右侧
		right = left;
		while (right + 1 < P_len && P[right + 1] != '%') {
			right++;
		}
		int len = right - left + 1;
		if (left < P_len && right < P_len && len > 0) {
			p_string.push_back(P.substr(left, len));
			p_string_len.push_back(len);
			p_string_left.push_back(left);
		}
		left = right + 1;
	}
	//for (int i = 0; i < p_string.size(); i++) {
	//	cout << p_string[i] << " " << p_string_len[i] << endl;
	//}
}

void get_p_start() {
	for (int k = 0; k < p_string.size(); k++) {
		for (int i = 0; i < S.length(); i++) {
			int ii = i; int j = 0;
			while (ii < S.length() && j < p_string[k].length()) {
				if (S[ii] == p_string[k][j] || p_string[k][j] == '?') { ii++; j++; }
				else break;
			}
			if (j >= p_string[k].length()) {
				p_start[k].push_back(i);
			}
		}
	}

	//for (int k = 0; k < p_string.size(); k++) {
	//	for (int i = 0; i < p_start[k].size(); i++) {
	//		cout << p_start[k][i]<<" ";
	//	}
	//	cout << endl;
	//}

}

bool judge() {
	int last = -1, min = 0;
	for (int k = 0; k < p_string.size(); k++) {
		bool flag = false;//第k个串是否有可以匹配的位置
		if (k >= 1) {
			min = last + p_string_len[k - 1];
		}
		for (int i = 0; i < p_start[k].size(); i++) {
			if (p_start[k][i] >= min) {
				//cout << p_start[k][i] << " ";
				last = p_start[k][i];
				flag = true;
				break;
			}
		}
		if (flag == false) {
			return false;
		}
		if (k == p_string.size()-1) {
			if (p_string_left[k]+ p_string_len[k]==P.length()
				&&p_start[k][p_start[k].size() - 1] + p_string_len[k] != S.length()) {
				return false;
			}
			else{
				return true;
			}
		}
	}
	return true;
}


void func() {
	cin >> S >> P;
	get_p_string();
	for (int i = 0; i < p_string.size(); i++) {
		vector<int> temp;
		p_start.push_back(temp);
	}
	get_p_start();
	if (judge()) {
		cout << "true";
	}
	else {
		cout << "false";
	}

}

int main() {
	func();
		//system("pause");
	return 0;
}




