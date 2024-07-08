#include<iostream>
using namespace std;
#define MaxVertexNum 100
#define MaxInt 999
typedef enum { DG, DN, UDG, UDN }GraphKind;//有向图、无向图
typedef int Edgetype;//带权图边上权值的数据类型
typedef char Vextype;//顶点的数据类型

struct AMGraph{//Adjacency matrices
	GraphKind kind;
	Vextype vexs[MaxVertexNum];
	Edgetype arcs[MaxVertexNum][MaxVertexNum];
	int vex_num, arc_num;
	AMGraph(GraphKind k);
	void Create();//创建网or图
	int LocateVex(const Vextype s);//定位邻接矩阵中的1或者权值的位置
	void Printarcs();//打印邻接矩阵
};


AMGraph::AMGraph(GraphKind k)
{
	this->kind = k;
	this->vex_num = 0;
	this->arc_num = 0;
}


void AMGraph::Create()
{
	cout << "输入总顶点数："; cin >> this->vex_num;
	cout << "输入总边数："; cin >> this->arc_num;
	cout << "初始化顶点表！" << endl;  //也就是说输入点的信息
	//初始化一下这个矩阵
	for (int i = 0; i < this->vex_num; i++)
	{
		cout << "请输入第" << i + 1 << "个点的信息:";
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
	//正式构建邻接矩阵
	for (int i = 0; i < this->arc_num; i++)
	{
		Vextype s1, s2;
		int val = 1;
		int locate1 = -1, locate2 = -1;
		cout << "输入第一个点：" << endl; cin >> s1;
		cout << "输入第二个点：" << endl; cin >> s2;
		if (this->kind == 1 || this->kind == 3)
		{
			cout << "输入权值："; cin >> val;
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
			return i;//如果找到喽 就返回在顶点表中的下标
	}
	return -1;//如果没找到，就返回-1
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