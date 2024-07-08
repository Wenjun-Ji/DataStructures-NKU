#include<iostream>
#include<iostream>
#include<vector>
#include<algorithm>
#include<time.h>
#include<windows.h>
#include<ctime>
#include<cstdlib>
using namespace std;

//节点定义
struct BSTreeNode
{
	BSTreeNode* _left;
	BSTreeNode* _right;
	int _key;

	BSTreeNode(const int& key)
		:_left(nullptr)
		, _right(nullptr)
		, _key(key)
	{}
};

//二叉搜索树
class BSTree
{
	typedef BSTreeNode Node;
public:
	//插入操作，按照左小右大的规则
	bool Insert(const int& key)
	{
		if (_root == nullptr)
		{
			_root = new Node(key);
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			parent = cur;
			if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(key);
		if (parent->_key < key)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}

		return true;
	}

	//查找操作
	bool Find(const int& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else
			{
				return true;
			}
		}
		return false;
	}

	bool Erase(const int& key)
	{
		Node* parent = nullptr;
		Node* cur = _root;

		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else//表示已经找到，进行删除操作
			{
				//左为空的情况
				if (cur->_left == nullptr)
				{
					if (cur == _root)//要删即为根节点
					{
						_root = cur->_right;
					}
					else
					{
						if (cur == parent->_left)//因为左一定为空，为父节点的左子树则将右半边给父即可
						{
							parent->_left = cur->_right;
						}
						else//同理为父节点的右则将右半边给父
						{
							parent->_right = cur->_right;
						}
					}

					delete cur;
				}
				else if (cur->_right == nullptr)//右为空的情况
				{
					//同理左为空
					if (cur == _root)
					{
						_root = cur->_left;
					}
					else
					{
						if (cur == parent->_left)
						{
							parent->_left = cur->_left;
						}
						else
						{
							parent->_right = cur->_left;
						}
					}

					delete cur;
				}
				else//左右都不为空
				{//可以选择找该节点左子树的最大节点（最右节点）或者右子树的最小节点（最左节点）
					//这里找右树的最小节点(最左节点)
					Node* parent = cur;
					Node* subleft = cur->_right;
					while (subleft->_left)
					{
						parent = subleft;
						subleft = subleft->_left;
					}

					swap(cur->_key, subleft->_key);
					//由于找到的是最左，则默认左为空,所以只需将右链接给父节点
					if (subleft == parent->_left)
					{
						parent->_left = subleft->_right;
					}
					else
					{
						parent->_right = subleft->_right;
					}

					delete subleft;

				}

				return true;


			}
		}
		return false;
	}

	void InOrder()//中序遍历即排升序
	{
		_InOrder(_root);
		cout << endl;
	}

	bool FindR(const int& key)//递归找
	{
		return _FindR(_root, key);
	}

	bool InsertR(const int& key)//递归插入
	{
		return _InsertR(_root, key);
	}

	bool EraseR(const int& key)//递归删
	{
		return _EraseR(_root, key);
	}

	BSTree() = default;// C++11

	~BSTree()
	{
		Destroy(_root);
	}

	BSTree(const BSTree& t)
	{
		_root = Copy(t._root);
	}

	// t1 = t3
	BSTree& operator=(BSTree t)
	{
		swap(_root, t._root);
		return *this;
	}

public:

	Node* Copy(Node* root)
	{
		if (root == nullptr)
			return nullptr;

		Node* newRoot = new Node(root->_key);
		newRoot->_left = Copy(root->_left);
		newRoot->_right = Copy(root->_right);

		return newRoot;
	}

	void Destroy(Node*& root)
	{
		if (root == nullptr)
			return;

		Destroy(root->_left);
		Destroy(root->_right);
		delete root;
		root = nullptr;
	}

	bool _EraseR(Node*& root, const int& key)
	{
		if (root == nullptr)
			return false;

		if (root->_key < key)
		{
			return _EraseR(root->_right, key);
		}
		else if (root->_key > key)
		{
			return _EraseR(root->_left, key);
		}
		else//找到了开始删除
		{
			//实际上的操作同非递归差不多，这里巧妙的对root运用了引用
			if (root->_left == nullptr)
			{
				Node* del = root;
				root = root->_right;
				delete del;

				return true;
			}
			else if (root->_right == nullptr)
			{
				Node* del = root;
				root = root->_left;
				delete del;

				return true;
			}
			else//找右子树的最大
			{
				Node* subleft = root->_right;
				while (subleft->_left)
				{
					subleft = subleft->_left;

				}
				swap(root->_key, subleft->_key);

				// 转换成在子树去递归删除
				return _EraseR(root->_right, key);
			}
		}
	}

	bool _InsertR(Node*& root, const int& key)
	{
		if (root == nullptr)
		{
			root = new Node(key);
			return true;
		}

		if (root->_key < key)
			return _InsertR(root->_right, key);
		else if (root->_key > key)
			return _InsertR(root->_left, key);
		else
			return false;
	}

	bool _FindR(Node* root, const int& key)
	{
		if (root == nullptr)
		{
			return false;
		}

		if (root->_key < key)
		{
			return _FindR(root->_right, key);
		}
		else if (root->_key > key)
		{
			return _FindR(root->_left, key);
		}
		else
		{
			return true;
		}
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;

		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}
	Node* _root = nullptr;
};



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

		BSTree BST;

		if (flag == 0) {
			cout << "//-------------------------------------------------------------------" << endl;
			cout << "/**顺序插入N个整数，随机查找1000个数，按顺序删除**/" << endl;
			cout << "//-------------------------------------------------------------------" << endl;
			flag = 1;
		}
		//按照递增顺序插入
		QueryPerformanceCounter(&nBeginTime);//开始计时  
		for (vector<int>::iterator i = sortData.begin(); i != sortData.end(); i++) {
			BST.Insert(*i);//...测试代码
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位
		cout << n * 20000 << "个数据-" << " BST插入运行时间：" << time * 1000 << "ms" << endl;
		//InOrderTraverse(BT);

		 //随机查找
		QueryPerformanceCounter(&nBeginTime);//开始计时
		for (vector<int>::iterator i = findData.begin(); i != findData.end(); i++) {
			BST.Find(*i);//...测试代码
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位 
		cout << n * 20000 << "个数据-" << " BST查找运行时间：" << time * 1000 << "ms" << endl;

		//顺序删除
		QueryPerformanceCounter(&nBeginTime);//开始计时 
		for (vector<int>::iterator i = sortData.begin(); i != sortData.end(); i++) {
			BST.Erase(*i);//...测试代码
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位
		cout << n * 20000 << "个数据-" << " BST删除运行时间：" << time * 1000 << "ms" << endl;
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

		BSTree BST;

		if (flag == 0) {
			cout << "//-------------------------------------------------------------------" << endl;
			cout << "/**顺序插入N个整数，随机查找1000个数，按逆序删除**/" << endl;
			cout << "//-------------------------------------------------------------------" << endl;
			flag = 1;
		}
		//按照递增顺序插入
		QueryPerformanceCounter(&nBeginTime);//开始计时  
		for (vector<int>::iterator i = sortData.begin(); i != sortData.end(); i++) {
			BST.Insert(*i);//...测试代码
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位
		cout << n * 20000 << "个数据-" << " BST插入运行时间：" << time * 1000 << "ms" << endl;
		//InOrderTraverse(BT);

		 //随机查找
		QueryPerformanceCounter(&nBeginTime);//开始计时
		for (vector<int>::iterator i = findData.begin(); i != findData.end(); i++) {
			BST.Find(*i);//...测试代码
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位 
		cout << n * 20000 << "个数据-" << " BST查找运行时间：" << time * 1000 << "ms" << endl;

		//逆序删除
		QueryPerformanceCounter(&nBeginTime);//开始计时 
		for (vector<int>::reverse_iterator i = sortData.rbegin(); i != sortData.rend(); i++) {
			BST.Erase(*i);//...测试代码
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位
		cout << n * 20000 << "个数据-" << " BST删除运行时间：" << time * 1000 << "ms" << endl;
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

		BSTree BST;

		if (flag == 0) {
			cout << "//-------------------------------------------------------------------" << endl;
			cout << "/**随机顺序插入N个整数，随机查找1000个数，按随机顺序删除**/" << endl;
			cout << "//-------------------------------------------------------------------" << endl;
			flag = 1;
		}
		//按照递增顺序插入
		QueryPerformanceCounter(&nBeginTime);//开始计时  
		for (vector<int>::iterator i = randomData.begin(); i != randomData.end(); i++) {
			BST.Insert(*i);//...测试代码
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位
		cout << n * 20000 << "个数据-" << " BST插入运行时间：" << time * 1000 << "ms" << endl;
		//InOrderTraverse(BT);

		 //随机查找
		QueryPerformanceCounter(&nBeginTime);//开始计时
		for (vector<int>::iterator i = findData.begin(); i != findData.end(); i++) {
			BST.Find(*i);//...测试代码
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位 
		cout << n * 20000 << "个数据-" << " BST查找运行时间：" << time * 1000 << "ms" << endl;

		get_data(n, randomData, sortData, findData);
		//随机删除
		QueryPerformanceCounter(&nBeginTime);//开始计时 
		for (vector<int>::iterator i = randomData.begin(); i != randomData.end(); i++) {
			BST.Erase(*i);//...测试代码
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位
		cout << n * 20000 << "个数据-" << " BST删除运行时间：" << time * 1000 << "ms" << endl;
	}
}
int main() {
	//test1();
	//test2();
	test3();

	system("pause");
	return 0;
}