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
	int Length() {//��ȡ������
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
	bool Empty() {//�п�
		if (head->next == NULL)return true;
		return false;
	}
	void InsertL(LinkNode<T>* node) {//ͷ�巨����
		if (Empty()) head->next = node;
		else {
			node->next = head->next;
			head->next = node;
		}
	} 
	void InsertR(LinkNode<T>* node) {//β�巨��������ͷ�ڵ���β�巨��Ϊ�鷳����Ҫÿ�α�������β��
		if (Empty()) head->next = node;
		else {
			LinkNode<T>* tail = head;
			while (tail->next != NULL)tail = tail->next;
			tail->next = node;
		}
	}
	bool Insert(int i,LinkNode<T>* node) {//��ָ��λ�ò���ڵ㣨�������Ҳ����ַ�����
		if (i < 0)	 return false;
		if (i > Length()) { InsertR(node); return true; }
		int j = 0;
		LinkNode<T>* p = head;
		while (j != i-1) {//�ҵ���i-1���ڵ�
			p = p->next;
			j++;
		}
		node->next = p->next;//���
		p->next = node;
		return true;
	}
	LinkNode<T>* Delete(int i) {
		if (Empty()) return NULL;
		if (i > Length()) return NULL;
		int j = 0;
		LinkNode<T>* p = head;
		while (j != i - 1) {//�ҵ���i-1���ڵ�
			p = p->next;
			j++;
		}
		LinkNode<T>* q = p->next;//��ɾ���ڵ�
		p->next = p->next->next;
		q->next = NULL;//�ѽڵ��������
		return q;//Ҳ�����ȸ��ƽڵ��ֵ �ڰѽڵ��ڴ��ͷ� ���շ���ֵ�����ǽڵ�
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
		LinkNode<T>* p, *q;//ע�����ﲻ����*p,q  ����ֻ��p�ᱻ��ֵ
		p=q = head->next;//ע�����ﲻ����p,q=...  ����ֻ��q�ᱻ��ֵ
		while (p != NULL) {		
			p = p->next;
			delete q;
			//q = NULL;
			q = p;
		}
		head->next = NULL;//ע������Ҫ��head.next������ΪNULL
	}
};


int main() {
	LinkList<int> list;
	list.InsertL(new LinkNode<int>(1));
	list.InsertL(new LinkNode<int>(2));
	list.InsertL(new LinkNode<int>(3));
	cout<<"�Ƿ�Ϊ�գ�"<<list.Empty()<<endl;
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