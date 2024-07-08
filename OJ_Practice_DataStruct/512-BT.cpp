#include<iostream>
using namespace std;
#define KeyType int
const int m = 512;

#include<vector>
#include<algorithm>
#include<time.h>
#include<windows.h>
#include<ctime>
#include<cstdlib>

typedef struct BTNode {
	int keynum;
	BTNode* parent;
	BTNode* ptr[m + 1];//从0开始
	KeyType key[m + 1];//从1开始
	BTNode() {
		keynum = 0;
		parent = NULL;
		for (int i = 0; i < m + 1; i++) {
			ptr[i] = NULL;
		}
		for (int i = 0; i < m + 1; i++) {
			key[i] = -999;
		}
	}
}*BTree;

struct result {//在pt节点的key[i]处
	BTNode* pt;
	int i;
	bool flag;
	result(BTNode* pt, int i, bool flag) :pt(pt), i(i), flag(flag) {}
};

//查找
int search(BTNode*& p, KeyType  key) {//在p节点中找key
	if (p == NULL) {
		cout << "当前节点为空" << endl;
		return -1;
	}
	int i = 1;
	while (i <= p->keynum && key > p->key[i]) {
		i++;
	}
	return i;
}
result* searchBTree(BTree& t, KeyType key) {//在树t中找key
	if (t == NULL) {
		return new result(NULL, -1, false);
	}
	else {
		int i = 0;
		BTNode* cur = t;
		BTNode* pcur = NULL;
		while (cur) {
			i = search(cur, key);//i是大于等于key的关键字下标
			if (i > cur->keynum && cur->ptr[i - 1] == NULL) {
				return new result(cur, i, false);//未找到(待插入位置)
			}
			if (key == cur->key[i]) {
				return new result(cur, i, true);//已找到
			}
			else if (key < cur->key[i]) {
				pcur = cur;
				cur = cur->ptr[i - 1];//到下一层查询
			}
			else if (i > cur->keynum && cur->ptr[i - 1] != NULL) {
				pcur = cur;
				cur = cur->ptr[i - 1];//到下一层查询
			}
		}
		return new result(pcur, i, false);//未找到(待插入位置)
	}
}

//插入
void split(BTNode* q, int mid, BTNode*& ap) {//把节点p分解成以mid为界的左右节点
	int i = 0, j = 0, leftnum = 0, rightnum = 0;
	//mid = (m + 1) / 2; //⌈m/2⌉提至父节点
	leftnum = mid - 1;
	rightnum = m - mid;
	ap = new BTNode();
	//把右半部分移到ap
	ap->ptr[0] = q->ptr[mid];
	for (i = mid + 1, j = 1; i <= m, j <= rightnum; i++, j++) {
		ap->ptr[j] = q->ptr[i];
		ap->key[j] = q->key[i];
		q->ptr[i] = NULL;
		q->key[i] = -999;
	}
	q->key[mid] = -999;
	q->ptr[mid] = NULL;
	for (j = 0; j <= rightnum; j++) {
		if (ap->ptr[j] != NULL)//叶节点
			ap->ptr[j]->parent = ap;
	}
	ap->parent = q->parent;
	q->keynum = leftnum;
	ap->keynum = rightnum;
}
void newRoot(BTree& t, BTNode*& q, int x, BTNode*& ap) {//把原来的根节点分成以x为父节点的左右节点
	t = new BTNode();
	t->keynum = 1;
	t->key[1] = x;
	t->ptr[0] = q;
	t->ptr[1] = ap;
	if (q != NULL)q->parent = t;
	if (ap != NULL)ap->parent = t;
}
void insert(BTNode* q, KeyType key, int i, BTNode* ap) {//把key插入q的i处,并把节点指针ap也插入
	for (int j = q->keynum + 1; j >= i + 1; j--) {
		q->key[j] = q->key[j - 1];
		q->ptr[j] = q->ptr[j - 1];
	}
	q->key[i] = key;
	q->ptr[i] = ap;
	if (ap != NULL) ap->parent = q;
	q->keynum++;
}
void insertBTree(BTree& t, BTNode* q, int i, KeyType key) {//在树t的q节点的i处插入key
	bool isfinish = false;
	bool neednewRoot = false;
	BTNode* ap = NULL;
	if (q == NULL) {
		neednewRoot = true;
	}
	else {
		while (!isfinish && !neednewRoot) {
			insert(q, key, i, ap);
			if (q->keynum < m) {
				isfinish = true;
			}
			else {
				int mid = (m + 1) / 2; key = q->key[mid];
				split(q, mid, ap);
				if (q->parent != NULL) {
					q = q->parent;
					i = search(q, key);
				}
				else {
					neednewRoot = true;
				}
			}
		}
	}
	if (neednewRoot)
		newRoot(t, q, key, ap);
}

//void insert_KeyType(BTree& t) {
//	KeyType temp;
//	cout << "请输入你要插入的元素:";
//	cin >> temp;
//	result* r = searchBTree(t, temp);
//	if (r->flag == false) {
//		if (r->i == -1) {//空树
//			t = new BTNode();
//			insertBTree(t, t, 1, temp);
//		}
//		else {
//			insertBTree(t, r->pt, r->i, temp);
//		}
//	}
//}

//删除
void Remove(BTNode* p, int i) {//把p节点中第i个关键字去除
	for (int j = i + 1; j <= p->keynum; j++) {
		p->key[j - 1] = p->key[j];
		p->ptr[j - 1] = p->ptr[j];
	}
	p->key[p->keynum] = -999;
	p->ptr[p->keynum] = NULL;
	p->keynum--;
}
void Successor(BTNode*& p, int i) {//寻找p节点中第i个关键字的后继 并把p节点指向后继   注意这里的必须传p指针的引用 因为改变了p的指向
	BTNode* cur = p->ptr[i];
	while (cur->ptr[0]) {
		cur = cur->ptr[0];
	}
	p->key[i] = cur->key[1];//交换key
	p = cur;
}
void Restore(BTree& t, BTNode* p, int i) {//p节点不够了 p->keynum<(m-1)/2
	BTNode* ap = NULL, * lt = NULL, * rt = NULL, * del = NULL;
	int r = 0;
	bool isfinish = false;
	while (!isfinish) {
		ap = p->parent;
		r = 0;//r归零
		if (p->keynum >= (m - 1) / 2 || (ap == NULL && p->keynum >= 1)) {
			isfinish = true;
			break;
		}
		if (ap == NULL && p->keynum == 0) {//出现空的根节点
			t = t->ptr[0];
			if (t) t->parent = NULL;
			isfinish = true;
			break;
		}
		//找到p节点的左右兄弟 以及p节点在parent的下标
		while (ap->ptr[r] != p) r++;//key[r]是p左父亲
		if (r == 0) {
			lt = NULL; rt = ap->ptr[r + 1];
		}
		else if (r == ap->keynum) {
			lt = ap->ptr[r - 1]; rt = NULL;
		}
		else {
			lt = ap->ptr[r - 1]; rt = ap->ptr[r + 1];
		}
		//左端点 向右兄弟借
		if (lt == NULL && rt->keynum >= (m + 1) / 2) {
			p->keynum++;
			//右父亲给p一个key 右兄弟给右父亲一个key 再把右兄弟的ptr[0]给p[p->keynum] 
			p->key[p->keynum] = ap->key[r + 1];
			ap->key[r + 1] = rt->key[1];
			p->ptr[p->keynum] = rt->ptr[0];
			if (p->ptr[p->keynum] != NULL)
				p->ptr[p->keynum]->parent = p;
			//把右兄弟的数组向左移一位
			rt->ptr[0] = rt->ptr[1];
			for (int i = 1; i <= rt->keynum - 1; i++) {
				rt->key[i] = rt->key[i + 1];
				rt->ptr[i] = rt->ptr[i + 1];
			}
			rt->key[rt->keynum] = -999;
			rt->ptr[rt->keynum] = NULL;
			rt->keynum--;
			isfinish = true;
			break;
		}
		//左端点 与右兄弟合并
		else if (lt == NULL && rt->keynum < (m + 1) / 2) {
			p->keynum++;
			p->key[p->keynum] = ap->key[r + 1];
			p->ptr[p->keynum] = rt->ptr[0];
			if (p->ptr[p->keynum] != NULL) {
				p->ptr[p->keynum]->parent = p;
			}
			for (int j = 1; j <= rt->keynum; j++) {
				p->key[p->keynum + 1] = rt->key[j];
				p->ptr[p->keynum + 1] = rt->ptr[j];
				rt->key[j] = -999;
				rt->ptr[j] = NULL;
				if (p->ptr[p->keynum + 1] != NULL) {
					p->ptr[p->keynum + 1]->parent = p;
				}
				p->keynum++;
			}
			rt->keynum = 0;
			for (int j = r + 1; j <= ap->keynum; j++) {//抹去r+1 也就是抹去rt
				ap->key[j] = ap->key[j + 1];
				ap->ptr[j] = ap->ptr[j + 1];
			}
			ap->keynum--;
			//isfinish = true;
			p = p->parent;
			ap = p->parent;
		}
		//右端点 向左兄弟借
		else if (rt == NULL && lt->keynum >= (m + 1) / 2) {
			p->keynum++;
			//左父亲给p一个key 左兄弟给左父亲一个key 再把左兄弟的ptr[keynum]给p->ptr[0] 
			for (int j = p->keynum; j >= 2; j--) {
				p->key[j] = p->key[j - 1];
				p->ptr[j] = p->ptr[j - 1];
			}
			p->key[1] = ap->key[r];
			p->ptr[1] = p->ptr[0];
			ap->key[r] = lt->key[lt->keynum];
			p->ptr[0] = lt->ptr[lt->keynum];
			lt->key[lt->keynum] = -999;
			lt->ptr[lt->keynum] = NULL;
			if (p->ptr[0] != NULL)
				p->ptr[0]->parent = p;
			lt->keynum--;
			isfinish = true;
			break;
		}
		//右端点 与左兄弟合并
		else if (rt == NULL && lt->keynum < (m + 1) / 2) {
			lt->keynum++;
			lt->key[lt->keynum] = ap->key[r];
			lt->ptr[lt->keynum] = p->ptr[0];
			if (lt->ptr[lt->keynum] != NULL) {
				lt->ptr[lt->keynum]->parent = lt;
			}
			for (int j = 1; j <= p->keynum; j++) {
				lt->key[lt->keynum + 1] = p->key[j];
				lt->ptr[lt->keynum + 1] = p->ptr[j];
				p->key[j] = -999;
				p->ptr[j] = NULL;
				if (lt->ptr[lt->keynum + 1] != NULL) {
					lt->ptr[lt->keynum + 1]->parent = lt;
				}
				lt->keynum++;
			}
			p->keynum = 0;
			for (int j = r; j <= ap->keynum; j++) {//抹去r+1 也就是抹去rt
				ap->key[j] = ap->key[j + 1];
				ap->ptr[j] = ap->ptr[j + 1];
			}
			ap->keynum--;
			p = lt;
			p = p->parent;
			ap = p->parent;
		}
		//左右兄弟都存在
		else {
			//借
			if (lt->keynum >= (m + 1) / 2 || rt->keynum >= (m + 1) / 2) {
				//向左兄弟借
				if (lt->keynum >= (m + 1) / 2) {
					p->keynum++;
					//左父亲给p一个key 左兄弟给左父亲一个key 再把左兄弟的ptr[keynum]给p->ptr[0] 
					for (int j = p->keynum; j >= 2; j--) {
						p->key[j] = p->key[j - 1];
						p->ptr[j] = p->ptr[j - 1];
					}
					p->key[1] = ap->key[r];
					p->ptr[1] = p->ptr[0];
					ap->key[r] = lt->key[lt->keynum];
					p->ptr[0] = lt->ptr[lt->keynum];
					lt->key[lt->keynum] = -999;
					lt->ptr[lt->keynum] = NULL;
					if (p->ptr[0] != NULL)
						p->ptr[0]->parent = p;
					lt->keynum--;
					isfinish = true;
					break;
				}
				//向右兄弟借
				else {
					p->keynum++;
					//右父亲给p一个key 右兄弟给右父亲一个key 再把右兄弟的ptr[0]给p[p->keynum] 
					p->key[p->keynum] = ap->key[r + 1];
					ap->key[r + 1] = rt->key[1];
					p->ptr[p->keynum] = rt->ptr[0];
					if (p->ptr[p->keynum] != NULL)
						p->ptr[p->keynum]->parent = p;
					//把右兄弟的数组向左移一位
					rt->ptr[0] = rt->ptr[1];
					for (int i = 1; i <= rt->keynum - 1; i++) {
						rt->key[i] = rt->key[i + 1];
						rt->ptr[i] = rt->ptr[i + 1];
					}
					rt->key[rt->keynum] = -999;
					rt->ptr[rt->keynum] = NULL;
					rt->keynum--;
					isfinish = true;
					break;
				}
			}
			//合并（与左兄弟合并）
			else {
				lt->keynum++;
				lt->key[lt->keynum] = ap->key[r];
				lt->ptr[lt->keynum] = p->ptr[0];
				if (lt->ptr[lt->keynum] != NULL) {
					lt->ptr[lt->keynum]->parent = lt;
				}
				for (int j = 1; j <= p->keynum; j++) {
					lt->key[lt->keynum + 1] = p->key[j];
					lt->ptr[lt->keynum + 1] = p->ptr[j];
					p->key[j] = -999;
					p->ptr[j] = NULL;
					if (lt->ptr[lt->keynum + 1] != NULL) {
						lt->ptr[lt->keynum + 1]->parent = lt;
					}
					lt->keynum++;
				}
				p->keynum = 0;
				for (int j = r; j <= ap->keynum; j++) {//抹去r+1 也就是抹去rt
					ap->key[j] = ap->key[j + 1];
					ap->ptr[j] = ap->ptr[j + 1];
				}
				ap->keynum--;
				p = lt;
				p = p->parent;
				ap = p->parent;
			}
		}
	}
}
void DeleteBTree(BTree& t, BTNode* p, int i) {
	if (p->ptr[i] != NULL) {
		Successor(p, i);
		DeleteBTree(t, p, 1);//删除后继
	}
	else {
		Remove(p, i);
		Restore(t, p, i);
	}
}

void insert_KeyType(BTree& t, KeyType temp) {
	result* r = searchBTree(t, temp);
	if (r->flag == false) {
		if (r->i == -1) {//空树
			t = new BTNode();
			insertBTree(t, t, 1, temp);
		}
		else {
			insertBTree(t, r->pt, r->i, temp);
		}
	}
}


//void delete_KeyType(BTree& t) {
//	KeyType temp;
//	cout << "请输入你要删除的元素:";
//	cin >> temp;
//	result* r = searchBTree(t, temp);
//	if (r->i == -1) {
//		cout << "当前树为空" << endl;
//	}
//	else if (r->flag == true) {
//		DeleteBTree(t, r->pt, r->i);
//	}
//	else {
//		cout << "not find" << endl;
//	}
//}

void delete_KeyType(BTree& t, KeyType temp) {
	result* r = searchBTree(t, temp);
	if (r->i == -1) {
		cout << "当前树为空" << endl;
	}
	else if (r->flag == true) {
		DeleteBTree(t, r->pt, r->i);
	}
	else {
		cout << "not find" << endl;
	}
}

void find_KeyType(BTree& t, KeyType temp) {
	result* r = searchBTree(t, temp);
	if (r->flag == true) {
		//cout << "find" << endl;
	}
	else {
		//cout << "not find" << endl;
	}
}


//void find_KeyType(BTree& t) {
//	KeyType temp;
//	cout << "请输入你要查找的元素:";
//	cin >> temp;
//	result* r = searchBTree(t, temp);
//	if (r->flag == true) {
//		cout << "find" << endl;
//	}
//	else {
//		cout << "not find" << endl;
//	}
//}


//中序遍历为升序
void InOrderTraverse(BTree& t) {
	if (t != NULL) {
		InOrderTraverse(t->ptr[0]);
		for (int i = 1; i <= t->keynum; i++) {
			cout << t->key[i] << " ";
			InOrderTraverse(t->ptr[i]);
		}
	}
}



//
//10 13 12 5
//5 10 15 20 25 30 12 14 13
void func() {
	BTree t = NULL;
	int choice = -1;
	int arr[9] = { 14,10,20,5,12,13,15,30,25 };
	for (int i = 0; i < 9; i++) {
		insert_KeyType(t, arr[i]);
	}
	InOrderTraverse(t);
	cout << endl;
	while (1) {
		cout << "1:插入：\n" << "2:删除\n" << "3:查找\n";
		cout << "请输入你的选择：";
		cin >> choice;
		if (choice == 1) {
			//insert_KeyType(t);
			InOrderTraverse(t);
			cout << endl;
		}
		else if (choice == 2) {
			//delete_KeyType(t);
			InOrderTraverse(t);
			cout << endl;
		}
		else if (choice == 3) {
			//find_KeyType(t);
			InOrderTraverse(t);
			cout << endl;
		}
		else if (choice == 0) {
			break;
		}
		else {
			cout << "输入有误,再输入一次" << endl;
		}
	}
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

		BTree BT = NULL;


		if (flag == 0) {
			cout << "//-------------------------------------------------------------------" << endl;
			cout << "/**顺序插入N个整数，随机查找1000个数，按顺序删除**/" << endl;
			cout << "//-------------------------------------------------------------------" << endl;
			flag = 1;
		}

		//按照递增顺序插入
		QueryPerformanceCounter(&nBeginTime);//开始计时  
		for (vector<int>::iterator i = sortData.begin(); i != sortData.end(); i++) {
			insert_KeyType(BT, *i);//...测试代码
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位
		cout << n * 20000 << "个数据-" << " BT插入运行时间：" << time * 1000 << "ms" << endl;
		//InOrderTraverse(BT);

		 //随机查找
		QueryPerformanceCounter(&nBeginTime);//开始计时
		for (vector<int>::iterator i = findData.begin(); i != findData.end(); i++) {
			find_KeyType(BT, *i);//...测试代码
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位 
		cout << n * 20000 << "个数据-" << " BT查找运行时间：" << time * 1000 << "ms" << endl;

		//顺序删除
		QueryPerformanceCounter(&nBeginTime);//开始计时 
		for (vector<int>::iterator i = sortData.begin(); i != sortData.end(); i++) {
			delete_KeyType(BT, *i);//...测试代码
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位
		cout << n * 20000 << "个数据-" << " BT删除运行时间：" << time * 1000 << "ms" << endl;
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

		BTree BT = NULL;


		if (flag == 0) {
			cout << "//-------------------------------------------------------------------" << endl;
			cout << "/**顺序插入N个整数，随机查找1000个数，按逆序删除**/" << endl;
			cout << "//-------------------------------------------------------------------" << endl;
			flag = 1;
		}

		//按照递增顺序插入
		QueryPerformanceCounter(&nBeginTime);//开始计时  
		for (vector<int>::iterator i = sortData.begin(); i != sortData.end(); i++) {
			insert_KeyType(BT, *i);//...测试代码
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位
		cout << n * 20000 << "个数据-" << " BT插入运行时间：" << time * 1000 << "ms" << endl;
		//InOrderTraverse(BT);

		 //随机查找
		QueryPerformanceCounter(&nBeginTime);//开始计时
		for (vector<int>::iterator i = findData.begin(); i != findData.end(); i++) {
			find_KeyType(BT, *i);//...测试代码
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位 
		cout << n * 20000 << "个数据-" << " BT查找运行时间：" << time * 1000 << "ms" << endl;

		//顺序删除
		QueryPerformanceCounter(&nBeginTime);//开始计时 
		for (vector<int>::reverse_iterator i = sortData.rbegin(); i != sortData.rend(); i++) {
			delete_KeyType(BT, *i);//...测试代码
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位
		cout << n * 20000 << "个数据-" << " BT删除运行时间：" << time * 1000 << "ms" << endl;
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

		BTree BT = NULL;


		if (flag == 0) {
			cout << "//-------------------------------------------------------------------" << endl;
			cout << "/**随机插入N个整数，随机查找1000个数，按随机删除**/" << endl;
			cout << "//-------------------------------------------------------------------" << endl;
			flag = 1;
		}

		//按照递增顺序插入
		QueryPerformanceCounter(&nBeginTime);//开始计时  
		for (vector<int>::iterator i = randomData.begin(); i != randomData.end(); i++) {
			insert_KeyType(BT, *i);//...测试代码
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位
		cout << n * 20000 << "个数据-" << " BT插入运行时间：" << time * 1000 << "ms" << endl;
		//InOrderTraverse(BT);

		 //随机查找
		QueryPerformanceCounter(&nBeginTime);//开始计时
		for (vector<int>::iterator i = findData.begin(); i != findData.end(); i++) {
			find_KeyType(BT, *i);//...测试代码
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位 
		cout << n * 20000 << "个数据-" << " BT查找运行时间：" << time * 1000 << "ms" << endl;

		//顺序删除
		get_data(n, randomData, sortData, findData);
		QueryPerformanceCounter(&nBeginTime);//开始计时 
		for (vector<int>::iterator i = randomData.begin(); i != randomData.end(); i++) {
			delete_KeyType(BT, *i);//...测试代码
		}
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位
		cout << n * 20000 << "个数据-" << " BT删除运行时间：" << time * 1000 << "ms" << endl;
	}
}


int main() {
	//func();
	//test1();
	//test2();
	test3();

	system("pause");
	return 0;
}