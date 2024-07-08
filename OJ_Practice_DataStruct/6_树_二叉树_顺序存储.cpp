#include<iostream>
using namespace std;
#define MaxSize 1024
typedef char ElemType;
struct TreeNode {
	 ElemType data;
	 bool IsEmpty;
	 TreeNode():IsEmpty(true),data(0) {}
};

struct SeqTree {
	TreeNode* Tree;
	SeqTree() {
		Tree = new TreeNode[MaxSize];
	}
	void CreatSeqTree(int i) {//从第i位开始创造二叉树
		if (i == 0) { cout << "请输入根节点：" << endl; }
		char c;
		c = getchar();
		cin.ignore();
		if (c == '^') {
			Tree[i].data = 0;
			return;
		}
		Tree[i].data = c;
		Tree[i].IsEmpty = false;
		cout << "请输入左子树：" << endl;
		CreatSeqTree(2 * i + 1);
		cout << "请输入右子树：" << endl;
		CreatSeqTree(2 * (i + 1));
	}
	ElemType GetRoot() {
		if (Tree[0].IsEmpty) { cout << "当前树为空" << endl; return 0; }
		return Tree[0].data;
	}
	int GetTreeLength() {
		int count = 0;
		for (int i = 0; i < MaxSize; i++) {
			if (!Tree[i].IsEmpty)count++;
		}
		return count;
	}
	int GetTreeDepth() {//只适用于完全二叉树
		int depth = 0;
		int len = GetTreeLength();
		while (pow(2, depth) - 1 < len) { depth++; }
		return depth;
	}
	void printSeqTree() {
		for (int i = 0; i < MaxSize; i++) {
			if (!Tree[i].IsEmpty) { cout << Tree[i].data << " "; }
		}
	}

};

int main() {
	SeqTree t;
	t.CreatSeqTree(0);
	cout<<t.GetRoot()<<endl;
	cout<<t.GetTreeLength()<<endl;
	cout << t.GetTreeDepth() << endl;
	t.printSeqTree();
}