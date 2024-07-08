#include<iostream>
#include<iostream>
#include<vector>
#include<algorithm>
#include<time.h>
#include<windows.h>
#include<ctime>
#include<cstdlib>
using namespace std;

//�ڵ㶨��
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

//����������
class BSTree
{
	typedef BSTreeNode Node;
public:
	//���������������С�Ҵ�Ĺ���
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

	//���Ҳ���
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
			else//��ʾ�Ѿ��ҵ�������ɾ������
			{
				//��Ϊ�յ����
				if (cur->_left == nullptr)
				{
					if (cur == _root)//Ҫɾ��Ϊ���ڵ�
					{
						_root = cur->_right;
					}
					else
					{
						if (cur == parent->_left)//��Ϊ��һ��Ϊ�գ�Ϊ���ڵ�����������Ұ�߸�������
						{
							parent->_left = cur->_right;
						}
						else//ͬ��Ϊ���ڵ�������Ұ�߸���
						{
							parent->_right = cur->_right;
						}
					}

					delete cur;
				}
				else if (cur->_right == nullptr)//��Ϊ�յ����
				{
					//ͬ����Ϊ��
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
				else//���Ҷ���Ϊ��
				{//����ѡ���Ҹýڵ������������ڵ㣨���ҽڵ㣩��������������С�ڵ㣨����ڵ㣩
					//��������������С�ڵ�(����ڵ�)
					Node* parent = cur;
					Node* subleft = cur->_right;
					while (subleft->_left)
					{
						parent = subleft;
						subleft = subleft->_left;
					}

					swap(cur->_key, subleft->_key);
					//�����ҵ�����������Ĭ����Ϊ��,����ֻ�轫�����Ӹ����ڵ�
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

	void InOrder()//���������������
	{
		_InOrder(_root);
		cout << endl;
	}

	bool FindR(const int& key)//�ݹ���
	{
		return _FindR(_root, key);
	}

	bool InsertR(const int& key)//�ݹ����
	{
		return _InsertR(_root, key);
	}

	bool EraseR(const int& key)//�ݹ�ɾ
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
		else//�ҵ��˿�ʼɾ��
		{
			//ʵ���ϵĲ���ͬ�ǵݹ��࣬��������Ķ�root����������
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
			else//�������������
			{
				Node* subleft = root->_right;
				while (subleft->_left)
				{
					subleft = subleft->_left;

				}
				swap(root->_key, subleft->_key);

				// ת����������ȥ�ݹ�ɾ��
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
			cout << "/**˳�����N���������������1000��������˳��ɾ��**/" << endl;
			cout << "//-------------------------------------------------------------------" << endl;
			flag = 1;
		}
		//���յ���˳�����
		QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ  
		for (vector<int>::iterator i = sortData.begin(); i != sortData.end(); i++) {
			BST.Insert(*i);//...���Դ���
		}
		QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λ
		cout << n * 20000 << "������-" << " BST��������ʱ�䣺" << time * 1000 << "ms" << endl;
		//InOrderTraverse(BT);

		 //�������
		QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ
		for (vector<int>::iterator i = findData.begin(); i != findData.end(); i++) {
			BST.Find(*i);//...���Դ���
		}
		QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λ 
		cout << n * 20000 << "������-" << " BST��������ʱ�䣺" << time * 1000 << "ms" << endl;

		//˳��ɾ��
		QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ 
		for (vector<int>::iterator i = sortData.begin(); i != sortData.end(); i++) {
			BST.Erase(*i);//...���Դ���
		}
		QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λ
		cout << n * 20000 << "������-" << " BSTɾ������ʱ�䣺" << time * 1000 << "ms" << endl;
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
			cout << "/**˳�����N���������������1000������������ɾ��**/" << endl;
			cout << "//-------------------------------------------------------------------" << endl;
			flag = 1;
		}
		//���յ���˳�����
		QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ  
		for (vector<int>::iterator i = sortData.begin(); i != sortData.end(); i++) {
			BST.Insert(*i);//...���Դ���
		}
		QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λ
		cout << n * 20000 << "������-" << " BST��������ʱ�䣺" << time * 1000 << "ms" << endl;
		//InOrderTraverse(BT);

		 //�������
		QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ
		for (vector<int>::iterator i = findData.begin(); i != findData.end(); i++) {
			BST.Find(*i);//...���Դ���
		}
		QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λ 
		cout << n * 20000 << "������-" << " BST��������ʱ�䣺" << time * 1000 << "ms" << endl;

		//����ɾ��
		QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ 
		for (vector<int>::reverse_iterator i = sortData.rbegin(); i != sortData.rend(); i++) {
			BST.Erase(*i);//...���Դ���
		}
		QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λ
		cout << n * 20000 << "������-" << " BSTɾ������ʱ�䣺" << time * 1000 << "ms" << endl;
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
			cout << "/**���˳�����N���������������1000�����������˳��ɾ��**/" << endl;
			cout << "//-------------------------------------------------------------------" << endl;
			flag = 1;
		}
		//���յ���˳�����
		QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ  
		for (vector<int>::iterator i = randomData.begin(); i != randomData.end(); i++) {
			BST.Insert(*i);//...���Դ���
		}
		QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λ
		cout << n * 20000 << "������-" << " BST��������ʱ�䣺" << time * 1000 << "ms" << endl;
		//InOrderTraverse(BT);

		 //�������
		QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ
		for (vector<int>::iterator i = findData.begin(); i != findData.end(); i++) {
			BST.Find(*i);//...���Դ���
		}
		QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λ 
		cout << n * 20000 << "������-" << " BST��������ʱ�䣺" << time * 1000 << "ms" << endl;

		get_data(n, randomData, sortData, findData);
		//���ɾ��
		QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ 
		for (vector<int>::iterator i = randomData.begin(); i != randomData.end(); i++) {
			BST.Erase(*i);//...���Դ���
		}
		QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λ
		cout << n * 20000 << "������-" << " BSTɾ������ʱ�䣺" << time * 1000 << "ms" << endl;
	}
}
int main() {
	//test1();
	//test2();
	test3();

	system("pause");
	return 0;
}