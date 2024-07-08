# include <iostream>
# include <algorithm>
# define maxn 101
using namespace std;

int n, m, g; //nΪ������mΪ������gΪͼ�����ͣ�1.����ͼ 2.����ͼ��
int Matrix[maxn][maxn] = { {0} }; //ͼ���ڽӾ���(��ʼ��Ϊ0)(��1��ʼ)
int Path[maxn] = { 0 };          //ŷ����·
int total = 0;                   //����ŷ����·�ĵ�
void Get_Matrix();  //��ͼ���ڽӾ���
void Print_Matrix();     //��ӡͼ���ڽӾ���
bool Judge_Connect();    //�ж�ͼ�Ƿ���ͨ
bool Judge_Path();  //�ж�ͼ�Ƿ���ŷ����·
void Find_Path();   //��ͼ������һ��ŷ����·

int main()
{
	bool temp;
	cout << "ͼ�����ͣ�1.����ͼ 2.����ͼ" << endl;
	cout << "������:";
	cin >> g;
	cout << "�����������Ŀ��";
	cin >> n;
	Get_Matrix();          //��ͼ���ڽӾ���
	Print_Matrix();         //��ӡͼ���ڽӾ���
	temp = Judge_Connect();   //�ж�ͼ�Ƿ���ͨ
	if (temp) {
		temp = Judge_Path();    //�ж�ͼ�Ƿ���ŷ����·
		if (temp) {
			cout << "\n��ͼ�й���" << m << "����" << endl;
			Find_Path();        //��ͼ������һ��ŷ����·
		}
	}
	return 0;
}

void Get_Matrix()  //��ͼ���ڽӾ���
{
	if (g == 1) {
		cout << "����������ͼ�и��������ӵĵ�ı�ţ������رߡ��Ի��������룬����0���������" << endl;
	}
	else {
		cout << "����������ͼ�и�����ָ��ĵ�ı�ţ������ر��������룬����0���������" << endl;
	}
	for (int i = 1; i <= n; i++) {
		int j;
		cout << "v" << i << ":";
		cin >> j;
		while (j != 0) {
			Matrix[i][j]++;
			cin >> j;
		}
	}
}

void Print_Matrix() //��ӡͼ���ڽӾ���
{
	cout << "\n��ͼ���ڽӾ���Ϊ��" << endl;
	cout << "  ";
	for (int i = 1; i <= n; i++) {
		cout << " v" << i;
	}
	cout << endl;
	for (int i = 1; i <= n; i++) {
		cout << "v" << i << " ";
		for (int j = 1; j <= n; j++) {
			cout << Matrix[i][j] << "  ";
		}
		cout << endl;
	}
}

void DFS1(int x, int* p) //�õݹ���Ѱ���㣬�����Ƿ���ͨ
{
	p[x] = 1;
	for (int i = 1; i <= n; i++) {
		if (p[i] == 1) {  //���ѱ���¼��������
			continue;
		}
		if (Matrix[x][i] > 0) {
			DFS1(i, p); //������õ���ͨ��δ��¼����һ����
		}
	}
}

bool Judge_Connect()  //�ж�ͼ�Ƿ���ͨ
{
	int t = 1;
	int Point[maxn] = { 0 }; //�жϵ��Ƿ���ͨ
	DFS1(1, Point); //��ͨ�������еĵ���ᱻ��Ϊ1
	for (int i = 1; i <= n; i++) { //�������Ƿ������¼
		if (!Point[i]) {  //����δ��¼�ĵ㣬˵������ͨ
			t = 0;
			break;
		}
	}
	if (t) {
		cout << "\n��ͨ�ԣ���ͼ��ͨ" << endl;
		return true;
	}
	else {
		if (g == 1) {
			cout << "\n��ͨ�ԣ�������ͼ����ͨ" << endl;
		}
		else {
			cout << "\n��ͨ�ԣ�������ͼ��ǿ��ͨ" << endl;
		}
		return false;
	}
}

bool Judge_Path()   //�ж�ͼ�Ƿ���ŷ����·
{
	int t = 1, sum = 0;
	if (g == 1) { //����ͼ
		int d;
		for (int i = 1; i <= n; i++) {
			d = 0;
			for (int j = 1; j <= n; j++) {
				d += Matrix[i][j]; //�����
			}
			if (d % 2 != 0) { //��������Ƿ�Ϊż��
				t = 0;
				break;
			}
			sum += d;
		}
		m = sum / 2; //����ͼ�ı���
	}
	else {  //����ͼ
		int d1, d2;
		for (int i = 1; i <= n; i++) {
			d1 = 0;
			d2 = 0;
			for (int j = 1; j <= n; j++) {
				d1 += Matrix[i][j];  //�����
			}
			for (int j = 1; j <= n; j++) {
				d2 += Matrix[j][i];  //�����
			}
			if (d1 != d2) { //������Ⱥ�����Ƿ����
				t = 0;
				break;
			}
			sum += d1;
		}
		m = sum; //����ͼ�ı���
	}
	if (t) {
		cout << "\n��ͼ����ŷ����·" << endl;
		return true;
	}
	else {
		cout << "\n��ͼ������ŷ����·" << endl;
		return false;
	}
}

void DFS2(int x) //�õݹ�ͨ������(�����·��)
{
	for (int i = 1; i <= n; i++) {
		if (Matrix[x][i] > 0) { //��x���ڵ���i��ͨ·
			Matrix[x][i]--;     //��ȥ�߹���·
			if (g == 1) {
				Matrix[i][x]--;
			}
			cout << i << " ";
			DFS2(i);         //�������±���
		}
	}
	total++;
	Path[total] = x;  //���ݵ��޷������ߵĵ㣬������·
}

void Find_Path()   //��ͼ������һ��ŷ����·
{
	DFS2(1);
	cout << endl;
	cout << "����һ��ŷ����·Ϊ��";
	int i;
	for (i = m + 1; i > 1; i--) { //�������
		cout << "v" << Path[i] << "->";
	}
	cout << "v" << Path[1];
	cout << endl;
}

/*
2 5 6 3 0
1 5 4 3 0
1 6 4 2 0
2 5 6 3 0
1 2 4 6 0
1 5 4 3 0
*/