#include<iostream>
using namespace std;
template<typename T>
struct LinkNode {
	T data;
	LinkNode<T>* next;
	LinkNode(): next(NULL){}
	LinkNode(T e):data(e), next(NULL) {}
};

template<typename T>
struct LinkList {
	LinkNode<T>* head;
	LinkList() { head =new LinkNode<T>(); }
	int Length() {//获取链表长度
		if (head->next == NULL)
			return 0;
		else {
			int j = -1;
			LinkNode<T>* p = head;
			while (p!= NULL) {
				p = p->next;
				j++;
			}
			return j;
		}
	}
	bool Empty() {//判空
		if (head->next == NULL)return true;
		return false;
	}
	void InsertL(LinkNode<T>* node) {//头插法建立
		if (Empty()) head->next = node;
		else {
			node->next = head->next;
			head->next = node;
		}
	} 
	void InsertR(LinkNode<T>* node) {//尾插法建立（含头节点用尾插法较为麻烦，需要每次遍历到链尾）
		if (Empty()) head->next = node;
		else {
			LinkNode<T>* tail = head;
			while (tail->next != NULL)tail = tail->next;
			tail->next = node;
		}
	}
	bool Insert(int i,LinkNode<T>* node) {//在指定位置插入节点（有左插和右插两种方法）
		if (i < 0)	 return false;
		if (i > Length()) { InsertR(node); return true; }
		int j = 0;
		LinkNode<T>* p = head;
		while (j != i-1) {//找到第i-1个节点
			p = p->next;
			j++;
		}
		node->next = p->next;//左插
		p->next = node;
		return true;
	}
	LinkNode<T>* Delete(int i) {
		if (Empty()) return NULL;
		if (i > Length()) return NULL;
		int j = 0;
		LinkNode<T>* p = head;
		while (j != i - 1) {//找到第i-1个节点
			p = p->next;
			j++;
		}
		LinkNode<T>* q = p->next;//待删除节点
		p->next = p->next->next;
		q->next = NULL;//把节点孤立起来
		return q;//也可以先复制节点的值 在把节点内存释放 最终返回值而不是节点
	}
	void Show() {
		if (Empty()) return;
		LinkNode<T>* p = head->next;
		while (p != NULL) {
			cout << p->data;
			p = p->next;
		}
	}
	void Destroy() {
		if (Empty()) return;
		LinkNode<T>* p, *q;//注意这里不能是*p,q  这样只有p会被赋值
		p=q = head->next;//注意这里不能是p,q=...  这样只有q会被赋值
		while (p != NULL) {		
			p = p->next;
			delete q;
			//q = NULL;
			q = p;
		}
		head->next = NULL;//注意这里要把head.next重新置为NULL
	}
};


int main() {
	LinkList<int> list;
	list.InsertL(new LinkNode<int>(1));
	list.InsertL(new LinkNode<int>(2));
	list.InsertL(new LinkNode<int>(3));
	cout<<"是否为空："<<list.Empty()<<endl;
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