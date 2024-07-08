#include<iostream>
#include<queue>
#include<utility>
#include<vector>
#include<algorithm>
#include<time.h>
#include<windows.h>
#include<ctime>
#include<cstdlib>
using namespace std;
enum Color { Red, Black };
//template<class int,class int>
struct Node {
	Node* _left;
	Node* _right;
	Node* _parent;
	pair<int, int>_kv;
	Color _col;
	Node(pair<int, int>& e) :
		_left(NULL),
		_right(NULL),
		_parent(NULL),
		_kv(e), _col(Red)
	{}
};

//template<class int, class int>
class RBTree {
public:
	RBTree() :
		_root(NULL),
		size(0)
	{}
	bool init(int* arr, int n) {
		for (int i = 0; i < n; i++) {
			insert(make_pair(arr[i], arr[i]));
		}
		return true;
	}
	int getMax() {
		Node* cur = _root;
		while (cur->_right) {
			cur = cur->_right;
		}
		return cur->_kv.first;
	}
	int getMin() {
		Node* cur = _root;
		while (cur->_left) {
			cur = cur->_left;
		}
		return cur->_kv.first;
	}
	pair<Node*, bool>insert(pair<int, int> kv) {
		//空树直接插入
		if (_root == NULL) {
			_root = new Node(kv);
			_root->_col = Black;//根为黑
			return make_pair(_root, true);
		}
		//1、定位
		Node* cur = _root;
		Node* parent = NULL;
		while (cur) {
			if (kv.first > cur->_kv.first) {
				parent = cur;
				cur = cur->_right;
			}
			else if (kv.first < cur->_kv.first) {
				parent = cur;
				cur = cur->_left;
			}
			else {
				cout << "已经插入过该节点";
				return make_pair(cur, false);
			}
		}
		//2、插入
		cur = new Node(kv);
		if (kv.first < parent->_kv.first) {//在父节点的左边插入
			parent->_left = cur;
			cur->_parent = parent;
		}
		else {//在父节点的右边插入
			parent->_right = cur;
			cur->_parent = parent;
		}


		//3、调整
		Node* grandparent = NULL;
		Node* uncle = NULL;

		while (parent && parent->_col == Red) {
			grandparent = parent->_parent;
			if (parent == grandparent->_left) {//parent是左孩子
				uncle = grandparent->_right;
				if (uncle && uncle->_col == Red) {//红叔-->叔父爷染色，爷变新
					parent->_col = Black;
					uncle->_col = Black;
					grandparent->_col = Red;
					cur = grandparent;//向上回溯
					parent = grandparent->_parent;
				}
				else {//黑叔或者叔叔不存在-->R单旋，父换爷，染色/RL双旋，儿换爷，染色
					if (cur == parent->_left) {//LL
						rightRotate(grandparent);
						parent->_col = Black;
						grandparent->_col = Red;
					}
					else {//LR
						leftRotate(grandparent->_left);
						rightRotate(grandparent);
						cur->_col = Black;
						grandparent->_col = Red;
					}
					break;
				}
			}
			else {//parent是右孩子	
				uncle = grandparent->_left;
				if (uncle && uncle->_col == Red) {//红叔-->叔父爷染色，爷变新
					parent->_col = Black;
					uncle->_col = Black;
					grandparent->_col = Red;
					cur = grandparent;//向上回溯
					parent = grandparent->_parent;
				}
				else {//黑叔或者叔叔不存在-->L单旋，父换爷，染色/LR双旋，儿换爷，染色
					if (parent->_right == cur) {//RR
						leftRotate(grandparent);
						parent->_col = Black;
						grandparent->_col = Red;
					}
					else {//RL
						rightRotate(grandparent->_right);
						leftRotate(grandparent);
						cur->_col = Black;
						grandparent->_col = Red;
					}
					break;
				}

			}
		}
		_root->_col = Black;
		return make_pair(_root, true);
	}
	pair<Node*, bool>Delete(pair<int, int> kv) {
		Node* cur = _root;
		Node* parent = NULL;
		//1、定位待删除节点
		while (cur) {
			if (kv.first > cur->_kv.first) {
				parent = cur;
				cur = cur->_right;
			}
			else if (kv.first < cur->_kv.first) {
				parent = cur;
				cur = cur->_left;
			}
			else {
				break;
			}
		}
		if (cur == NULL) {
			//cout << "RB树不含该节点" << endl;
			return make_pair(_root, false);
		}
		Node* delParentPos = NULL;
		Node* delPos = NULL;
		if (cur->_left == NULL) {
			delPos = cur;
			delParentPos = parent;
		}
		else if (cur->_right == NULL) {
			delPos = cur;
			delParentPos = parent;
		}
		else {
			delParentPos = cur;
			delPos = cur->_right;
			while (delPos->_left) {
				delParentPos = delPos;
				delPos = delPos->_left;
			}
			cur->_kv.first = delPos->_kv.first;
			cur->_kv.second = delPos->_kv.second;
		}
		//delPos认为是双黑节点 且经过寻找后 只有三种情况：叶子节点 只有左子树的节点 只有右子树的节点

		//delPos用于调整 del用于删除
		Node* del = delPos;
		Node* delp = delParentPos;

		//2、调整红黑树（把双黑节点变成普通黑节点）
		if (delPos->_col == Red) {//删除节点为红色，无需旋转染色等调整
			;
		}
		else {//删除节点为黑色 
			if (delPos->_left) {
				delPos->_left->_col = Black;
			}
			else if (delPos->_right) {
				delPos->_right->_col = Black;
			}
			else {
				while (delPos != _root) {
					if (delPos == delParentPos->_left) {//删除节点在父节点的左
						Node* brother = delParentPos->_right;
						if (brother->_col == Red) {//brother为红
							brother->_col = Black;
							delParentPos->_col = Red;
							leftRotate(delParentPos);
							//向上回溯
							brother = delParentPos->_right;
						}
						else if ((brother->_left == NULL || brother->_left->_col == Black)//brother俩黑孩子
							&& (brother->_right == NULL || brother->_right->_col == Black)) {
							brother->_col = Red;
							if (delParentPos->_col == Red) {
								delParentPos->_col = Black;
								break;
							}
							else {
								delPos = delParentPos;
								delParentPos = delParentPos->_parent;
							}
						}
						else {//brother至少一个红孩子
							if (brother->_left && brother->_left->_col == Red) {//RL
								brother->_left->_col = delParentPos->_col;
								delParentPos->_col = Black;
								rightRotate(brother);
								leftRotate(delParentPos);
								break;
							}
							else {//RR
								brother->_right->_col = brother->_col;
								brother->_col = delParentPos->_col;
								delParentPos->_col = Black;
								leftRotate(delParentPos);
								break;
							}

						}
					}
					else {//删除节点在父节点的右
						Node* brother = delParentPos->_left;
						if (brother->_col == Red) {//brother为红
							brother->_col = Black;
							delParentPos->_col = Red;
							rightRotate(delParentPos);
							//向上回溯
							brother = delParentPos->_left;
						}
						else if ((brother->_left == NULL || brother->_left->_col == Black)//brother俩黑孩子
							&& (brother->_right == NULL || brother->_right->_col == Black)) {
							brother->_col = Red;
							if (delParentPos->_col == Red) {
								delParentPos->_col = Black;
								break;
							}
							else {
								delPos = delParentPos;
								delParentPos = delParentPos->_parent;
							}
						}
						else {//brother至少一个红孩子
							if (brother->_right && brother->_right->_col == Red) {//LR
								brother->_right->_col = delParentPos->_col;
								delParentPos->_col = Black;
								leftRotate(brother);
								rightRotate(delParentPos);
								break;
							}
							else {//LL
								brother->_left->_col = brother->_col;
								brother->_col = delParentPos->_col;
								delParentPos->_col = Black;
								rightRotate(delParentPos);
								break;
							}
						}
					}
				}
			}
		}
		//3、做实际删除
		if (del->_left == NULL) {
			if (del == _root) {
				_root = _root->_right;
				if (_root)
					_root->_parent = NULL;
			}
			else {
				if (del == delp->_left) {
					delp->_left = del->_right;
				}
				else {
					delp->_right = del->_right;
				}
				if (del->_right)
					del->_right->_parent = delp;
			}
		}
		else {
			if (del == _root) {
				_root = _root->_left;
				if (_root)
					_root->_parent = NULL;
			}
			else {
				if (del == delp->_left) {
					delp->_left = del->_left;
				}
				else {
					delp->_right = del->_left;
				}
				if (del->_left)
					del->_left->_parent = delp;
			}
		}
		delete del;
		return make_pair(_root, true);
	}
	pair<Node*, bool>Find(pair<int, int> kv) {
		Node* cur = _root;
		while (cur)
		{
			if (kv.first < cur->_kv.first) //key值小于该结点的值
			{
				cur = cur->_left; //在该结点的左子树当中查找
			}
			else if (kv.first > cur->_kv.first) //key值大于该结点的值
			{
				cur = cur->_right; //在该结点的右子树当中查找
			}
			else //找到了目标结点
			{
				return make_pair(cur, true); //返回该结点
			}
		}
		return make_pair(cur, false); //查找失败
	}
	bool isRBTree() {
		if (_root == NULL) {
			return true;
		}
		if (_root->_col == Red) {
			cout << "根节点为红色";
			return false;
		}
		Node* cur = _root;
		int balckcount = 0;
		while (cur) {
			if (cur->_col == Black) {
				balckcount++;
			}
			cur = cur->_left;
		}
		int count = 0;
		return _isRbTree(_root, count, balckcount);
	}
	bool _isRbTree(Node* root, int count, int blackcount) {
		if (root == NULL) {
			if (blackcount == count) {
				return true;
			}
			else {
				cout << "黑高不同" << endl;
				return false;
			}
		}
		if (root->_col == Red && root->_parent->_col == Red) {
			cout << "存在连续红色节点" << endl;
			return false;
		}
		if (root->_col == Black) {
			count++;
		}
		return _isRbTree(root->_left, count, blackcount) && _isRbTree(root->_right, count, blackcount);
	}
	void leftRotate(Node* cur) {
		if (!cur) { return; }
		Node* right = cur->_right;
		Node* right_left = right->_left;
		Node* parent = cur->_parent;
		//把right_left连接到cur的right
		cur->_right = right_left;
		if (right_left)
			right_left->_parent = cur;
		//把cur连接到right的left
		right->_left = cur;
		cur->_parent = right;
		//right连接到parent底下
		right->_parent = parent;
		if (parent) {
			if (cur == parent->_left) {
				parent->_left = right;
			}
			else {
				parent->_right = right;
			}
		}
		else {
			_root = right;
		}
	}
	void rightRotate(Node* cur) {
		if (!cur) { return; }
		Node* left = cur->_left;
		Node* left_right = left->_right;
		Node* parent = cur->_parent;
		//把left_right连接到cur的left
		cur->_left = left_right;
		if (left_right)
			left_right->_parent = cur;
		//把cur连接到left的right
		left->_right = cur;
		cur->_parent = left;
		//把left连接到parent底下
		left->_parent = parent;
		if (parent) {
			if (parent->_left == cur) {
				parent->_left = left;
			}
			else {
				parent->_right = left;
			}
		}
		else {
			_root = left;
		}
	}

public:
	Node* _root;
	int size;
};
void visit(Node* cur) {
	if (cur == NULL)
		return;
	cout << cur->_kv.first;
	if (cur->_col == Red)
		cout << "(R)";
	else
		cout << "(B)";
	cout << " ";
}
void levelTraverse(Node* cur) {
	if (cur == NULL)
		return;
	queue<Node*>q;
	q.push(cur);
	while (!q.empty()) {
		cur = q.front();
		visit(cur);
		q.pop();
		if (cur->_left) {
			q.push(cur->_left);
		}
		if (cur->_right) {
			q.push(cur->_right);
		}
	}
}

void FirstTraverse(Node* cur) {
	if (cur == NULL) {
		return;
	}
	visit(cur);
	FirstTraverse(cur->_left);
	FirstTraverse(cur->_right);
}

void InTraverse(Node* cur) {
	if (cur == NULL) {
		return;
	}

	InTraverse(cur->_left);
	visit(cur);
	InTraverse(cur->_right);
}

void func() {
	int n = 0;
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	int nn = 0;
	cin >> nn;
	int* arrr = new int[nn];
	for (int i = 0; i < nn; i++) {
		cin >> arrr[i];
	}
	RBTree t;
	t.init(arr, n);
	//levelTraverse(t._root);
	//cout << endl;
	if (t._root == NULL) {
		cout << "Null";
	}
	else {
		FirstTraverse(t._root);
	}
	cout << endl;
	cout << t.getMin() << " " << t.getMax() << endl;

	for (int i = 0; i < nn; i++) {
		t.Delete(make_pair(arrr[i], arrr[i]));
	}
	//levelTraverse(t._root);
	//cout << endl;
	if (t._root == NULL) {
		cout << "Null";
	}
	else {
		FirstTraverse(t._root);
	}
	//cout<<t.isRBTree()<<endl;
}



vector<int> Data;
void initData() {
	for (int i = 1; i <= 400000; i++) {
		Data.push_back(i);
	}
}
int Rand(int i) { return rand() % i; }
int getRand(int min, int max) {
	return (rand() % (max - min + 1)) + min;
}
void generateData(int n, vector<int>& randomData, vector<int>& sortData, vector<int>& findData) {
	vector<int>::iterator start = Data.begin();
	vector<int>::iterator end = Data.begin() + n * 20000;
	sortData.assign(start, end);
	randomData.assign(start, end);
	for (vector<int>::iterator i = sortData.begin(); i != sortData.end(); i++) {
		//cout << *i;
	}
	srand(unsigned(time(0)));
	random_shuffle(randomData.begin(), randomData.end(), Rand);
	for (vector<int>::iterator i = randomData.begin(); i != randomData.end(); i++) {
		//cout << *i;
	}
	for (int i = 0; i < 1000; i++) {
		findData.push_back(getRand(1, n * 10000));
	}
	for (vector<int>::iterator i = findData.begin(); i != findData.end(); i++) {
		//cout << *i << "\n";
	}
}

void get_data(int n, vector<int>& randomData, vector<int>& sortData, vector<int>& findData) {
	initData();
	generateData(n, randomData, sortData, findData);
}

void test1() {
	int flag = 0;
	for (int n = 1; n <= 20; n++) {
		vector<int> randomData;
		vector<int> sortData;
		vector<int> findData;
		get_data(n, randomData, sortData, findData);

		double time = 0;
		double counts = 0;
		LARGE_INTEGER nFreq;
		LARGE_INTEGER nBeginTime;
		LARGE_INTEGER nEndTime;
		QueryPerformanceFrequency(&nFreq);

		RBTree RBT;

		if (flag == 0) {
			cout << "//-------------------------------------------------------------------" << endl;
			cout << "/**递增顺序插入N个整数，随机查找1000个数，按相同顺序删除**/" << endl;
			cout << "//-------------------------------------------------------------------" << endl;
			flag = 1;
		}

		//按照递增顺序插入
		QueryPerformanceCounter(&nBeginTime);//开始计时  
		for (vector<int>::iterator i = sortData.begin(); i != sortData.end(); i++) {
			RBT.insert(make_pair(*i, 1));//...测试代码
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位
		cout << n * 20000 << "个数据-" << " RBT插入运行时间：" << time * 1000 << "ms" << endl;
		//InTraverse(RBT._root);

		 //随机查找
		QueryPerformanceCounter(&nBeginTime);//开始计时
		for (vector<int>::iterator i = findData.begin(); i != findData.end(); i++) {
			//BST.Find(*i);//...测试代码
			RBT.Find(make_pair(*i, 1));
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位 
		cout << n * 20000 << "个数据-" << " RBT查找运行时间：" << time * 1000 << "ms" << endl;

		//顺序删除
		QueryPerformanceCounter(&nBeginTime);//开始计时 
		for (vector<int>::iterator i = sortData.begin(); i != sortData.end(); i++) {
			RBT.Delete(make_pair(*i, 1));//...测试代码
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位
		cout << n * 20000 << "个数据-" << " RBT删除运行时间：" << time * 1000 << "ms" << endl;
	}
}


void test2() {
	int flag = 0;
	for (int n = 1; n <= 20; n++) {
		vector<int> randomData;
		vector<int> sortData;
		vector<int> findData;
		get_data(n, randomData, sortData, findData);

		double time = 0;
		double counts = 0;
		LARGE_INTEGER nFreq;
		LARGE_INTEGER nBeginTime;
		LARGE_INTEGER nEndTime;
		QueryPerformanceFrequency(&nFreq);

		RBTree RBT;


		if (flag == 0) {
			cout << "//-------------------------------------------------------------------" << endl;
			cout << "/**递增顺序插入N个整数，随机查找1000个数，按相反顺序删除**/" << endl;
			cout << "//-------------------------------------------------------------------" << endl;
			flag = 1;
		}

		//按照递增顺序插入
		QueryPerformanceCounter(&nBeginTime);//开始计时  
		for (vector<int>::iterator i = sortData.begin(); i != sortData.end(); i++) {
			RBT.insert(make_pair(*i, 1));//...测试代码
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位
		cout << n * 20000 << "个数据-" << " RBT插入运行时间：" << time * 1000 << "ms" << endl;
		//InTraverse(RBT._root);

		 //随机查找
		QueryPerformanceCounter(&nBeginTime);//开始计时
		for (vector<int>::iterator i = findData.begin(); i != findData.end(); i++) {
			//BST.Find(*i);//...测试代码
			RBT.Find(make_pair(*i, 1));
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位 
		cout << n * 20000 << "个数据-" << " RBT查找运行时间：" << time * 1000 << "ms" << endl;

		//顺序删除
		QueryPerformanceCounter(&nBeginTime);//开始计时 
		for (vector<int>::reverse_iterator i = sortData.rbegin(); i != sortData.rend(); i++) {
			RBT.Delete(make_pair(*i, 1));//...测试代码
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位
		cout << n * 20000 << "个数据-" << " RBT删除运行时间：" << time * 1000 << "ms" << endl;
	}
}


void test3() {
	int flag = 0;
	for (int n = 1; n <= 20; n++) {
		vector<int> randomData;
		vector<int> sortData;
		vector<int> findData;
		get_data(n, randomData, sortData, findData);

		double time = 0;
		double counts = 0;
		LARGE_INTEGER nFreq;
		LARGE_INTEGER nBeginTime;
		LARGE_INTEGER nEndTime;
		QueryPerformanceFrequency(&nFreq);

		RBTree RBT;

		if (flag == 0) {
			cout << "//-------------------------------------------------------------------" << endl;
			cout << "/**随机顺序插入N个整数，随机查找1000个数，按随机顺序删除**/" << endl;
			cout << "//-------------------------------------------------------------------" << endl;
			flag = 1;
		}

		//按照递增顺序插入
		QueryPerformanceCounter(&nBeginTime);//开始计时  
		for (vector<int>::iterator i = randomData.begin(); i != randomData.end(); i++) {
			RBT.insert(make_pair(*i, 1));//...测试代码
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位
		cout << n * 20000 << "个数据-" << " RBT插入运行时间：" << time * 1000 << "ms" << endl;
		//InTraverse(RBT._root);

		 //随机查找
		QueryPerformanceCounter(&nBeginTime);//开始计时
		for (vector<int>::iterator i = findData.begin(); i != findData.end(); i++) {
			//BST.Find(*i);//...测试代码
			RBT.Find(make_pair(*i, 1));
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位 
		cout << n * 20000 << "个数据-" << " RBT查找运行时间：" << time * 1000 << "ms" << endl;

		//随机删除
		get_data(n, randomData, sortData, findData);
		QueryPerformanceCounter(&nBeginTime);//开始计时 
		for (vector<int>::iterator i = randomData.begin(); i != randomData.end(); i++) {
			RBT.Delete(make_pair(*i, 1));//...测试代码
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位
		cout << n * 20000 << "个数据-" << " RBT删除运行时间：" << time * 1000 << "ms" << endl;
	}
}

int main() {
	//test1();
	//test2();
	test3();
	system("pause");
	return 0;
}