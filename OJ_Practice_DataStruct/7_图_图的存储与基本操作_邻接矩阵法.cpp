#include<iostream>
using namespace std;
#define MaxVertexNum 100
#define MaxInt 999
typedef enum { DG, DN, UDG, UDN }GraphKind;//����ͼ������ͼ
typedef int Edgetype;//��Ȩͼ����Ȩֵ����������
typedef char Vextype;//�������������

struct AMGraph{//Adjacency matrices
	GraphKind kind;
	Vextype vexs[MaxVertexNum];
	Edgetype arcs[MaxVertexNum][MaxVertexNum];
	int vex_num, arc_num;
	AMGraph(GraphKind k);
	void Create();//������orͼ
	int LocateVex(const Vextype s);//��λ�ڽӾ����е�1����Ȩֵ��λ��
	void Printarcs();//��ӡ�ڽӾ���
};


AMGraph::AMGraph(GraphKind k)
{
	this->kind = k;
	this->vex_num = 0;
	this->arc_num = 0;
}


void AMGraph::Create()
{
	cout << "�����ܶ�������"; cin >> this->vex_num;
	cout << "�����ܱ�����"; cin >> this->arc_num;
	cout << "��ʼ�������" << endl;  //Ҳ����˵��������Ϣ
	//��ʼ��һ���������
	for (int i = 0; i < this->vex_num; i++)
	{
		cout << "�������" << i + 1 << "�������Ϣ:";
		cin >> vexs[i];
	}
	for (int i = 0; i < this->vex_num; i++)
	{
		for (int j = 0; j < this->vex_num; j++)
		{
			if (this->kind == 0 || this->kind == 2)
				this->arcs[i][j] = 0;
			else
				this->arcs[i][j] = MaxInt;
		}
	}
	//��ʽ�����ڽӾ���
	for (int i = 0; i < this->arc_num; i++)
	{
		Vextype s1, s2;
		int val = 1;
		int locate1 = -1, locate2 = -1;
		cout << "�����һ���㣺" << endl; cin >> s1;
		cout << "����ڶ����㣺" << endl; cin >> s2;
		if (this->kind == 1 || this->kind == 3)
		{
			cout << "����Ȩֵ��"; cin >> val;
		}
		locate1 = this->LocateVex(s1);
		locate2 = this->LocateVex(s2);
		if (locate1 == -1 || locate2 == -1)
			return;
		switch (this->kind)
		{
		case  DG:
			this->arcs[locate1][locate2] = 1;
			break;
		case DN:
			this->arcs[locate1][locate2] = val;
			break;
		case UDG:
			this->arcs[locate1][locate2] = 1;
			this->arcs[locate2][locate1] = 1;
			break;
		case UDN:
			this->arcs[locate1][locate2] = val;
			this->arcs[locate2][locate1] = val;
			break;
		default:
			break;
		}
	}
}



int AMGraph::LocateVex(const Vextype s)
{
	/*cout << typeid(this->vexs[0]).name() << endl;
	cout << typeid(s).name() << endl;*/
	for (int i = 0; i < this->vex_num; i++)
	{
		if (s == this->vexs[i])
			return i;//����ҵ�� �ͷ����ڶ�����е��±�
	}
	return -1;//���û�ҵ����ͷ���-1
}

void AMGraph::Printarcs()
{
	for (int i = 0; i < this->vex_num; i++)
	{
		for (int j = 0; j < this->vex_num; j++)
		{
			cout <<vexs[i]<<" " << vexs[j] <<" " << this->arcs[i][j] << "\n";
		}
		cout << endl;
	}
}



int main() {


	system("pause");
	return 0;
}