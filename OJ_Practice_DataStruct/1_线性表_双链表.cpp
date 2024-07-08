#include<iostream>
using namespace std;

template<typename T>
struct LinkNode {
	T data;
	LinkNode<T>* next;
	LinkNode<T>* front;
	LinkNode() : next(NULL),front(NULL) {}
	LinkNode(T e) :data(e), next(NULL),front(NULL) {}
};

template<typename T>
struct LinkList {
	LinkNode<T>* head;
	LinkNode<T>* tail;
	LinkList() { head = tail = NULL; }
	int Length() {//获取链表长度
		if (head->next == NULL)
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
		if (Empty()) head = tail = node;
		else {
			node->next = head;
			head->front = node;
			head = node;
		}
	}
	void InsertR(LinkNode<T>* node) {//尾插法建立
		if (Empty()) head = tail = node;
		else {
			tail->next = node;
			node->front = tail;
			tail = node;
		}
	}
	bool Insert(int i, LinkNode<T>* node) {//在指定位置插入节点（有左插和右插两种方法）
		if (i < 0)	 return false;
		if (i == 1) { InsertL(node); return true; }
		if (i >= Length()) { InsertR(node); return true; } 
		int j = 1;
		LinkNode<T>* p = head;
		while (j < i - 1) {//找到第i-1个节点
			p = p->next;
			j++;
		}
		node->next = p->next;
		p->next = node;
		node->next->front = node;
		node->front = p;

		/*
				node->next = p->next;
		p->next->front = node;
		node->front = p;
		p->next = node;
		*/
		
		return true;
	}
	LinkNode<T>* Delete(int i) {
		if (Empty()) return NULL;
		if (i > Length()) return NULL;
		int j = 1;
		LinkNode<T>* p = head;
		if (i == 1) {
			head = head->next;
			p->next = NULL; head->front = NULL;
			return p;
		}
		if (i == Length()) {
			p = tail;
			tail = tail->front;
			p->front = NULL; tail->next = NULL;
			return p;
		}
		while (j < i - 1) {//找到第i-1个节点
			p = p->next;
			j++;
		}
		LinkNode<T>* q = p->next;//待删除节点
		p->next = p->next->next;
		p->next->next->front = p;
		q->front=q->next = NULL;//把节点孤立起来
		return q;//也可以先复制节点的值 在把节点内存释放 最终返回值而不是节点
	}
	void Show() {
		if (Empty()) return;
		LinkNode<T>* p = head;
		while (p != NULL) {
			cout << p->data;
			p = p->next;
		}
	}
	void Destroy() {
		if (Empty()) return;
		LinkNode<T>* p, * q;//注意这里不能是*p,q  这样只有p会被赋值
		p = q = head;//注意这里不能是p,q=...  这样只有q会被赋值
		while (p != NULL) {
			p = p->next;
			delete q;
			//q = NULL;
			q = p;
		}
		head = NULL;//注意这里要把head.next重新置为NULL
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
	list.Show(); cout << endl;





}