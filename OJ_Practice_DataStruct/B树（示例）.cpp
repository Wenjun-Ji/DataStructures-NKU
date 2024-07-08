
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define KeyType int
#define Record string
const int m = 3;
using namespace std;
typedef struct BTNode {
	int keynum;             //�ڵ㵱ǰ�ؼ��ָ���
	KeyType key[m + 1];       //�ؼ������飬key[0]δ��
	struct BTNode* parent;  //˫�׽��ָ��
	struct BTNode* ptr[m + 1]; //���ӽ��ָ������
	Record* recptr[m + 1];
	BTNode() {
		keynum = 0;
		parent = NULL;
		for (int i = 0; i < m + 1; i++)
		{
			ptr[i] = NULL;
		}
	}
}BTNode, * BTree;
BTree T = NULL;
typedef struct {
	BTree pt;               //ָ���ҵ��Ľ��
	int i;                  //1<=i<=m,�ڽ���еĹؼ���λ��
	int tag;                //1�����ҳɹ���0������ʧ��
}result;                    //B���Ĳ��ҽ������
//3. �㷨���

int Search(BTree p, int k) {  //��p->key[1..p->keynum]��k
	int i = 1;
	while (i <= p->keynum && k > p->key[i]) i++;
	return i;
}
void SearchBTree(BTree t, int k, result& r) {
	//��m��B��t�ϲ��ҹؼ���k����r����(pt,i,tag).
	//�����ҳɹ�������tag=1��ָ��pt��ָ����е�i���ؼ��ֵ���k��
	//����tag=0����Ҫ����ؼ���Ϊk�ļ�¼��Ӧλ��pt����е�i-1���͵�i���ؼ���֮��
	int i = 0, found = 0;
	BTree p = t, q = NULL;//��ʼ��pָ����ڵ㣬p������ָ������ҽ�㣬qָ����˫��
	while (p != NULL && 0 == found) {
		i = Search(p, k);
		if (i <= p->keynum && p->key[i] == k) found = 1;
		else { q = p; p = p->ptr[i - 1]; }//ָ������
	}
	if (1 == found) {//���ҳɹ�������k��λ��p��i
		r = { p,i,1 };
	}
	else {//���Ҳ��ɹ�������k�Ĳ���λ��q��i
		r = { q,i,0 };
	}
}
void split(BTree& q, int s, BTree& ap) {//��q�����ѳ�������㣬ǰһ�뱣����ԭ��㣬��һ������ap��ָ�½��
	int i, j, n = q->keynum;
	ap = (BTNode*)malloc(sizeof(BTNode));//�����½��
	ap->ptr[0] = q->ptr[s];
	for (i = s + 1, j = 1; i <= n; i++, j++) {    //��һ������ap���
		ap->key[j] = q->key[i];
		ap->ptr[j] = q->ptr[i];
	}
	ap->keynum = n - s;
	ap->parent = q->parent;
	for (i = 0; i <= n - s; i++)
		if (ap->ptr[i] != NULL) ap->ptr[i]->parent = ap;
	q->keynum = s - 1;
}
void newRoot(BTree& t, BTree p, int x, BTree ap) {//�����µĸ����
	t = (BTNode*)malloc(sizeof(BTNode));
	t->keynum = 1; t->ptr[0] = p; t->ptr[1] = ap; t->key[1] = x;
	if (p != NULL) p->parent = t;
	if (ap != NULL) ap->parent = t;
	t->parent = NULL;
}
void Insert(BTree& q, int i, int x, BTree ap) {//�ؼ���x���½��ָ��ap�ֱ�嵽q->key[i]��q->ptr[i]
	int j, n = q->keynum;
	for (j = n; j >= i; j--) {
		q->key[j + 1] = q->key[j];
		q->ptr[j + 1] = q->ptr[j];
	}
	q->key[i] = x; q->ptr[i] = ap;
	if (ap != NULL) ap->parent = q;
	q->keynum++;
}
void InsertBTree(BTree& t, int k, BTree q, int i) {
	//��B����q����key[i-1]��key[i]֮�����ؼ���k
	//���������ؼ��ָ�������b���Ľף�������˫��ָ�������н����ѣ�ʹ��t����m��B��
	int x, s, finished = 0, needNewRoot = 0;
	BTree ap;
	if (NULL == q) newRoot(t, NULL, k, NULL);
	else {
		x = k; ap = NULL;
		while (0 == needNewRoot && 0 == finished) {
			Insert(q, i, x, ap);//x��ap�ֱ�嵽q->key[i]��q->ptr[i]
			if (q->keynum < m) finished = 1;//�������
			else {
				s = (m + 1) / 2; split(q, s, ap); x = q->key[s];
				if (q->parent != NULL) {
					q = q->parent; i = Search(q, x);//��˫�׽���в���x�Ĳ���λ��
				}
				else needNewRoot = 1;
			}
		}
		if (1 == needNewRoot)//t�ǿ������߸�����Ѿ����ѳ�Ϊq��ap���
			newRoot(t, q, x, ap);
	}
}
void Remove(BTree& p, int i)
{
	int j, n = p->keynum;
	for (j = i; j < n; j++) {
		p->key[j] = p->key[j + 1];
		p->ptr[j] = p->ptr[j + 1];
	}
	p->keynum--;
}
void Successor(BTree& p, int i) {//�ɺ�����²���ն˽�����С�ؼ��ִ������йؼ���key[i]
	BTree child = p->ptr[i];
	while (child->ptr[0] != NULL) child = child->ptr[0];
	p->key[i] = child->key[1];
	p = child;
}
void Restore(BTree& p, int i, BTree& T) {//��B�����е���
	int j;
	BTree ap = p->parent;
	if (ap == NULL) //����������ֿյĸ���㣬��ɾ���ø���㣬���߼�1
	{
		T = p; //���������
		p = p->parent;
		return;
	}
	BTree lc, rc, pr;
	int finished = 0, r = 0;
	while (!finished)
	{
		r = 0;
		while (ap->ptr[r] != p) r++; //ȷ��p��ap�����е�λ��
		if (r == 0)
		{
			r++;
			lc = NULL, rc = ap->ptr[r];
		}
		else if (r == ap->keynum)
		{
			rc = NULL; lc = ap->ptr[r - 1];
		}
		else
		{
			lc = ap->ptr[r - 1]; rc = ap->ptr[r + 1];
		}
		if (r > 0 && lc != NULL && (lc->keynum > (m - 1) / 2))//�����ֵܽ�ؼ���
		{
			p->keynum++;
			for (j = p->keynum; j > 1; j--)//���ؼ�������
			{
				p->key[j] = p->key[j - 1];
				p->ptr[j] = p->ptr[j - 1];
			}
			p->key[1] = ap->key[r];//���ײ��뵽���
			p->ptr[1] = p->ptr[0];
			p->ptr[0] = lc->ptr[lc->keynum];
			if (NULL != p->ptr[0])//�޸�p�е���Ů�ĸ����Ϊp
			{
				p->ptr[0]->parent = p;
			}
			ap->key[r] = lc->key[lc->keynum];//���ֵ����Ƶ�����λ��
			lc->keynum--;
			finished = 1;
			break;
		}
		else if (ap->keynum > r && rc != NULL && (rc->keynum > (m - 1) / 2)) //�����ֵܽ�ؼ���
		{
			p->keynum++;
			p->key[p->keynum] = ap->key[r]; //���ײ��뵽���
			p->ptr[p->keynum] = rc->ptr[0];
			if (NULL != p->ptr[p->keynum]) //�޸�p�е���Ů�ĸ����Ϊp
				p->ptr[p->keynum]->parent = p;
			ap->key[r] = rc->key[1]; //���ֵ����Ƶ�����λ��
			rc->ptr[0] = rc->ptr[1];
			for (j = 1; j < rc->keynum; j++)  //���ֵܽ��ؼ�������
			{
				rc->key[j] = rc->key[j + 1];
				rc->ptr[j] = rc->ptr[j + 1];
			}
			rc->keynum--;
			finished = 1;
			break;
		}
		r = 0;
		while (ap->ptr[r] != p) //����ȷ��p��ap������λ��
			r++;
		if (r > 0 && (ap->ptr[r - 1]->keynum <= (m - 1) / 2)) //�����ֵܺϲ�
			//if(r>0) //�����ֵܺϲ�
		{
			lc = ap->ptr[r - 1];
			p->keynum++;
			for (j = p->keynum; j > 1; j--) //��p���ؼ��ֺ�ָ������1λ
			{
				p->key[j] = p->key[j - 1];
				p->ptr[j] = p->ptr[j - 1];
			}
			p->key[1] = ap->key[r]; //�����Ĺؼ�����p�ϲ�
			p->ptr[1] = p->ptr[0]; //�����ֵ�����һ��ָ��
			ap->ptr[r] = lc;
			for (j = 1; j <= lc->keynum + p->keynum; j++) //�����p�йؼ��ֺ�ָ���Ƶ�p���ֵ���
			{
				lc->key[lc->keynum + j] = p->key[j];
				lc->ptr[lc->keynum + j] = p->ptr[j];
			}
			if (p->ptr[0]) //�޸�p�е���Ů�ĸ����Ϊlc
			{
				for (j = 1; j <= p->keynum; j++)
					if (p->ptr[p->keynum + j])   p->ptr[p->keynum + j]->parent = lc;
			}
			lc->keynum = lc->keynum + p->keynum;  //�ϲ���ؼ��ֵĸ���
			for (j = r; j < ap->keynum; j++)//��������йؼ��ֺ�ָ������
			{
				ap->key[j] = ap->key[j + 1];
				ap->ptr[j] = ap->ptr[j + 1];
			}
			ap->keynum--;
			pr = p; free(pr);
			pr = NULL;
			p = lc;
		}
		else //�����ֵܺϲ�
		{
			rc = ap->ptr[r + 1];
			if (r == 0)
				r++;
			p->keynum++;
			p->key[p->keynum] = ap->key[r]; //�����Ĺؼ�����p�ϲ�
			p->ptr[p->keynum] = rc->ptr[0]; //�����ֵ�����һ��ָ��
			rc->keynum = p->keynum + rc->keynum;//�ϲ���ؼ��ֵĸ���
			ap->ptr[r - 1] = rc;
			for (j = 1; j <= (rc->keynum - p->keynum); j++)//��p���ֵܹؼ��ֺ�ָ������
			{
				rc->key[p->keynum + j] = rc->key[j];
				rc->ptr[p->keynum + j] = rc->ptr[j];
			}
			for (j = 1; j <= p->keynum; j++)//�����p�йؼ��ֺ�ָ���Ƶ�p���ֵ�
			{
				rc->key[j] = p->key[j];
				rc->ptr[j] = p->ptr[j];
			}
			rc->ptr[0] = p->ptr[0]; //�޸�p�е���Ů�ĸ����Ϊrc
			if (p->ptr[0])
			{
				for (j = 1; j <= p->keynum; j++)
					if (p->ptr[p->keynum + j])    p->ptr[p->keynum + j]->parent = rc;
			}
			for (j = r; j < ap->keynum; j++)//��������йؼ��ֺ�ָ������
			{
				ap->key[j] = ap->key[j + 1];
				ap->ptr[j] = ap->ptr[j + 1];
			}
			ap->keynum--;//�����Ĺؼ��ָ�����1
			pr = p;
			free(pr);
			pr = NULL;
			p = rc;
		}
		ap = ap->parent;
		if (p->parent->keynum >= (m - 1) / 2 || (NULL == ap && p->parent->keynum > 0))
			finished = 1;
		else if (ap == NULL) //����������ֿյĸ���㣬��ɾ���ø���㣬���߼�1
		{
			pr = T;
			T = p; //���������
			free(pr);
			pr = NULL;
			finished = 1;
		}
		p = p->parent;
	}
}
void DeleteBTree(BTree& p, int i, BTree& T) {//ɾ��B����p���ĵ�i���ؼ���
	if (p->ptr[i] != NULL) {//�����������²���ն˽��
		Successor(p, i);//��Ai�������ҳ����²���ն˽�����С�ؼ������ki
		DeleteBTree(p, 1, T);//ת��Ϊɾ�����²���ն˽�����С�ؼ���
	}
	else {//�������²���ն˽��
		Remove(p, i);
		if (p->keynum < (m - 1) / 2)//ɾ����ؼ��ָ���С��(m-1)/2
			Restore(p, i, T);//����B��
	}
}

void show_Btree(BTree& p)
{
	if (p == NULL) { puts("B tree does not exist"); return; }
	bool have_child = false;
	printf("[");
	for (int i = 1; i <= p->keynum; i++)
	{
		if (i == 1);
		else printf(" ");
		printf("%d", p->key[i]);
	}
	printf("]");
	for (int i = 0; i <= p->keynum; i++)
	{
		if (p->ptr[i] != NULL)
		{
			if (i == 0) printf("<");
			else printf(",");
			show_Btree(p->ptr[i]);
			have_child = true;
		}
	}
	if (have_child) printf(">");
}

void show_Btree2(BTree& p, int deep)
{
	if (p == NULL) { return; }
	int i;
	for (i = 0; i < p->keynum; i++)
	{
		show_Btree2(p->ptr[i], deep + 1);
		for (int i = 0; i < deep; i++)
		{
			printf("\t");
		}
		printf("%d\n", p->key[i + 1]);
	}
	show_Btree2(p->ptr[i], deep + 1);

}
void Destory(BTree& t)
{
	int i = 0;
	if (t != NULL)
	{
		while (i < t->keynum)
		{
			Destory(t->ptr[i]);
			free(t->ptr[i]);
			i++;
		}
	}
	free(t);
	t = NULL;
}
void creat_btree()
{
	T = new BTNode;
	T->keynum = 0;
	puts("New success");
}
void insert_keytype()
{
	puts("Enter an element to be inserted");
	KeyType temp;
	cin >> temp;
	result p;
	SearchBTree(T, temp, p);
	if (p.tag == 0)
	{
		InsertBTree(T, temp, p.pt, p.i);
		puts("Insert success"); show_Btree(T);
		puts("");
	}
	else puts("The element is already in the B tree.");
}
void find_keytype()
{
	puts("Enter an element to find");
	KeyType temp;
	cin >> temp;
	result p;
	SearchBTree(T, temp, p);
	if (p.tag)
	{
		puts("Find success");
	}
	else puts("Lookup failure");
}
void delete_keytype()
{
	puts("Enter an element to be deleted");
	KeyType temp;
	cin >> temp;
	result p;
	SearchBTree(T, temp, p);
	if (p.tag)
	{
		DeleteBTree(p.pt, p.i, T);
		puts("Delete success"); show_Btree(T);
		puts("");
	}
	else puts("The element does not exist in the B tree.");
}


int main()
{


	puts("*************************************************************************");
	puts("> File Name: d.cpp");
	puts("> Author: MentalOmega");
	puts("> Created Time: 2016.11.5 21:23:30");
	puts("> Reference material:");
	puts("http://blog.csdn.net/jesseshen/article/details/6643747");
	puts("http://www.cnblogs.com/vincently/p/4526560.html");
	puts("http://blog.csdn.net/quitepig/article/details/8041308");
	puts("*************************************************************************");
	int order = 0;
	while (order != 7)
	{
		puts("---------------------------------------------------------------------");
		puts("Select menu");
		puts("1:Creat a new 3-B-tree");
		puts("2:Insert element");
		puts("3:Find element");
		puts("4:Delete element");
		puts("5:Print B-tree");
		puts("6:exit");
		cin >> order;
		switch (order)
		{
		case 1: {Destory(T); creat_btree(); break; }
		case 2: {insert_keytype(); break; }
		case 3: {find_keytype(); break; }
		case 4: {delete_keytype(); break; }
		case 5: {show_Btree(T); puts(""); break; }
		case 6: {return 0; }
		}
	}
	return 0;
}