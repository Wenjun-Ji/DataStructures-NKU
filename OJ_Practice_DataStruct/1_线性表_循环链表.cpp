#include<iostream>
using namespace std;
template<typename T>
struct LinkNode {
	T data;
	LinkNode<T>* next;
	LinkNode() : next(NULL) {}
	LinkNode(T e) :data(e), next(NULL) {}
};

template<typename T>
struct LinkList {
	LinkNode<T>* head;
	LinkNode<T>* tail;
	LinkList() { head = tail = NULL; }
	int Length() {//获取链表长度
		if (head == NULL)
			return 0;
		else {
			int j = 1;
			LinkNode<T>* p = head;
			while (p != tail) {
				p = p->next;
				j++;
			}
			return j;
		}
	}
	bool Empty() {//判空
		if (head == NULL)return true;
		return false;
	}
	void InsertL(LinkNode<T>* node) {//头插法建立
		if (Empty()) { 
			head = tail = node; 
			head->next = tail;//单节点是是环抱型
			tail->next = head;
		}
		else {
			node->next = head;
			head = node;
			tail->next = head;
		}
	}
	void InsertR(LinkNode<T>* node) {//尾插法建立（含头节点用尾插法较为麻烦，需要每次遍历到链尾）
		if (Empty()) { 
			head = tail = node; 
			head->next = tail;//单节点是是环抱型
			tail->next = head;
		}
		else {
			tail->next = node;
			tail = node;
			tail->next = head;
		}
	}
	bool Insert(int i, LinkNode<T>* node) {//在指定位置插入节点（有左插和右插两种方法）
		if (i < 0)	 return false;
		if (i > Length()+1)   return false; 
		if (i == 1) { InsertL(node); return true; }
		if (i == Length()+1) { InsertR(node); return true; }
		int j = 1;
		LinkNode<T>* p = head;
		while (j < i - 1) {//找到第i-1个节点
			p = p->next;
			j++;
		}
		node->next = p->next;//左插
		p->next = node;
		return true;
	}
	LinkNode<T>* Delete(int i) {
		if (Empty()) return NULL;
		if (i<1||i > Length()) return NULL;
		int j = 1;
		LinkNode<T>* p = head;
		if (i == 1) {//删除首节点
			head = head->next;
			tail->next = head;
			p->next = NULL;
			return p;
		}
		while (j != i - 1) {//找到第i-1个节点
			p = p->next;
			j++;
		}
		if (i == Length()) tail = p;//删除尾节点
		LinkNode<T>* q = p->next;//待删除节点
		p->next = p->next->next;//tail->next = head;
		q->next = NULL;
		return q;//也可以先复制节点的值 在把节点内存释放 最终返回值而不是节点
	}
	void Show() {
		if (Empty()) return;
		LinkNode<T>* p = head;
		while (p != tail) {
			cout << p->data;
			p = p->next;
		}
		cout << p->data;
	}
	void Destroy() {
		if (Empty()) return;
		LinkNode<T>* p,*q;//注意这里不能是*p,q  这样只有p会被赋值
		p = q = head->next;//注意这里不能是p,q=...  这样只有q会被赋值
		while (p != tail) {
			q = q->next;
			delete p;
			p = q;
		}
		delete p;
	}
};


int main() {
	LinkList<int> list;
	list.InsertL(new LinkNode<int>(1));
	list.InsertL(new LinkNode<int>(2));
	list.InsertL(new LinkNode<int>(3));
	cout << "是否为空：" << list.Empty() << endl;
	list.Show(); cout << endl;
	list.Insert(2, new LinkNode<int>(4));
	list.Show(); cout << endl;
	list.Insert(1, new LinkNode<int>(5));
	list.Show(); cout << endl;
	list.Insert(6, new LinkNode<int>(6));
	list.Show(); cout << endl;
	list.Delete(1);
	list.Show(); cout << endl;
	list.Delete(6);
	list.Show(); cout << endl;
	list.Destroy();
	//list.Show(); cout << endl;





}