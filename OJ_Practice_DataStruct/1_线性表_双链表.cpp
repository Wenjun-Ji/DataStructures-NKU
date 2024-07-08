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
	int Length() {//��ȡ������
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
	bool Empty() {//�п�
		if (head == NULL)return true;
		return false;
	}
	void InsertL(LinkNode<T>* node) {//ͷ�巨����
		if (Empty()) head = tail = node;
		else {
			node->next = head;
			head->front = node;
			head = node;
		}
	}
	void InsertR(LinkNode<T>* node) {//β�巨����
		if (Empty()) head = tail = node;
		else {
			tail->next = node;
			node->front = tail;
			tail = node;
		}
	}
	bool Insert(int i, LinkNode<T>* node) {//��ָ��λ�ò���ڵ㣨�������Ҳ����ַ�����
		if (i < 0)	 return false;
		if (i == 1) { InsertL(node); return true; }
		if (i >= Length()) { InsertR(node); return true; } 
		int j = 1;
		LinkNode<T>* p = head;
		while (j < i - 1) {//�ҵ���i-1���ڵ�
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
		while (j < i - 1) {//�ҵ���i-1���ڵ�
			p = p->next;
			j++;
		}
		LinkNode<T>* q = p->next;//��ɾ���ڵ�
		p->next = p->next->next;
		p->next->next->front = p;
		q->front=q->next = NULL;//�ѽڵ��������
		return q;//Ҳ�����ȸ��ƽڵ��ֵ �ڰѽڵ��ڴ��ͷ� ���շ���ֵ�����ǽڵ�
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
		LinkNode<T>* p, * q;//ע�����ﲻ����*p,q  ����ֻ��p�ᱻ��ֵ
		p = q = head;//ע�����ﲻ����p,q=...  ����ֻ��q�ᱻ��ֵ
		while (p != NULL) {
			p = p->next;
			delete q;
			//q = NULL;
			q = p;
		}
		head = NULL;//ע������Ҫ��head.next������ΪNULL
	}
};


int main() {
	LinkList<int> list;
	list.InsertL(new LinkNode<int>(1));
	list.InsertL(new LinkNode<int>(2));
	list.InsertL(new LinkNode<int>(3));
	cout << "�Ƿ�Ϊ�գ�" << list.Empty() << endl;
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