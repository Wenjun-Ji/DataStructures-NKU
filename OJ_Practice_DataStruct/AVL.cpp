#include<iomanip>
#include<queue>
#include<vector>
#include<algorithm>
#include<time.h>
#include<windows.h>
#include<ctime>
#include<cstdlib>
#include<iostream>
using namespace std;

template<class T>
class AVLTreeNode
{
public:
    T key;    // �ؼ��֣���ֵ��
    int height;    // �߶�
    AVLTreeNode* left;    // ����
    AVLTreeNode* right;    // �Һ���

    AVLTreeNode(T value, AVLTreeNode* l, AVLTreeNode* r) :
        key(value), left(l), right(r) {}
};

template<class T>
class AVLTree
{
private:
    AVLTreeNode<T>* root;    // �����

public:
    // �ⲿ�ӿ� 
    AVLTree();
    ~AVLTree();

    // ��ȡ���ĸ߶�
    int height();
    // �Ƚ�����ֵ�Ĵ�С 

    // ǰ�����
    void preOrder();
    // �������
    void inOrder();
    // �������
    void postOrder();

    // ���ݹ�ʵ�֣�����AVL���м�ֵΪkey�Ľ��
    AVLTreeNode<T>* search(T key);
    // ���ǵݹ�ʵ�֣�����AVL���м�ֵΪkey�Ľ��
    AVLTreeNode<T>* iterativeSearch(T key);

    // ������С��㣺������С���ļ�ֵ
    T minimum();
    // ��������㣺���������ļ�ֵ
    T maximum();

    // �������뵽AVL����
    void insert(T key);
    // ɾ�����
    void remove(T key);

    // ����AVL��
    void destroy();

    // ��ӡAVL��
    void print();

private:
    // �ڲ��ӿ� 
    // ��ȡ���ĸ߶�
    int height(AVLTreeNode<T>* tree);

    // ǰ�����
    void preOrder(AVLTreeNode<T>* tree) const;
    // �������
    void inOrder(AVLTreeNode<T>* tree) const;
    // �������
    void postOrder(AVLTreeNode<T>* tree) const;

    // ���ݹ�ʵ�֣�����AVL���м�ֵΪkey�Ľ��
    AVLTreeNode<T>* search(AVLTreeNode<T>* x, T key) const;
    // ���ǵݹ�ʵ�֣�����AVL���м�ֵΪkey�Ľ��
    AVLTreeNode<T>* iterativeSearch(AVLTreeNode<T>* x, T key) const;

    // ������С��� 
    AVLTreeNode<T>* minimum(AVLTreeNode<T>* tree);
    // ��������� 
    AVLTreeNode<T>* maximum(AVLTreeNode<T>* tree);

    // �������뵽AVL����
    AVLTreeNode<T>* insert(AVLTreeNode<T>*& tree, T key);
    // ɾ����㣬�����ر�ɾ���Ľ�� 
    AVLTreeNode<T>* remove(AVLTreeNode<T>*& tree, AVLTreeNode<T>* z);

    // ����AVL��
    void destroy(AVLTreeNode<T>*& tree);

    // ��ӡAVL��
    void print(AVLTreeNode<T>* tree, T key, int direction);

    // LL�������Ӧ�����(����ת)
    AVLTreeNode<T>* leftLeftRotation(AVLTreeNode<T>* k2);
    // RR�����Ҷ�Ӧ�����(�ҵ���ת)
    AVLTreeNode<T>* rightRightRotation(AVLTreeNode<T>* k1);
    // LR�����Ҷ�Ӧ�����(��˫��ת)
    AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* k3);
    // RL�������Ӧ�����(��˫��ת)
    AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* k1);
};

template<class T>
AVLTree<T>::AVLTree() : root(NULL)
{
}

template<class T>
AVLTree<T>::~AVLTree()
{
    destroy(root);
}

template<class T>
int AVLTree<T>::height(AVLTreeNode<T>* tree)
{
    if (tree != NULL)
        return tree->height;
    return 0;
}

template<class T>
int AVLTree<T>::height()
{
    return height(root);
}


template<class T>
AVLTreeNode<T>* AVLTree<T>::leftLeftRotation(AVLTreeNode<T>* k2)
{
    AVLTreeNode<T>* k1;

    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;

    return k1;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::rightRightRotation(AVLTreeNode<T>* k1)
{
    AVLTreeNode<T>* k2;

    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(k1->height, height(k2->right)) + 1;

    return k2;
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>* k3)
{
    k3->left = rightRightRotation(k3->left);

    return leftLeftRotation(k3);
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* k1)
{
    k1->right = leftLeftRotation(k1->right);

    return rightRightRotation(k1);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>*& tree, T key)
{
    if (tree == NULL)
    {
        // �½���� 
        tree = new AVLTreeNode<T>(key, NULL, NULL);
        if (tree == NULL)
        {
            cout << "ERROR: create avltree node failed!" << endl;
            return NULL;
        }
    }
    else if (key < tree->key)
    {
        tree->left = insert(tree->left, key);
        // ���������AVL��ʧȥƽ�⣬�������Ӧ�ĵ���
        if (height(tree->left) - height(tree->right) == 2)
        {
            if (key < tree->left->key)
                tree = leftLeftRotation(tree);
            else
                tree = leftRightRotation(tree);
        }
    }
    else
    {
        tree->right = insert(tree->right, key);
        // ���������AVL��ʧȥƽ�⣬�������Ӧ�ĵ���
        if (height(tree->right) - height(tree->left) == 2)
        {
            if (key > tree->right->key)
                tree = rightRightRotation(tree);
            else
                tree = rightLeftRotation(tree);
        }
    }

    tree->height = max(height(tree->left), height(tree->right)) + 1;

    return tree;
}

template<class T>
void AVLTree<T>::insert(T key)
{
    insert(root, key);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>*& tree, AVLTreeNode<T>* z)
{
    // ��Ϊ�� ���� û��Ҫɾ���Ľ��
    if (tree == NULL || z == NULL)
        return NULL;
    if (z->key < tree->key)
    {
        tree->left = remove(tree->left, z);
        // ɾ��������AVL��ʧȥƽ�⣬�������Ӧ����
        if (height(tree->right) - height(tree->left) == 2)
        {
            AVLTreeNode<T>* r = tree->right;
            if (height(r->left) > height(r->right))
                tree = rightLeftRotation(tree);
            else
                tree = rightRightRotation(tree);
        }
    }
    else if (z->key > tree->key)
    {
        tree->right = remove(tree->right, z);
        if (height(tree->left) - height(tree->right) == 2)
        {
            AVLTreeNode<T>* r = tree->left;
            if (height(r->left) < height(r->right))
                tree = leftRightRotation(tree);
            else
                tree = leftLeftRotation(tree);
        }
    }
    else    // tree�Ƕ�ӦҪɾ���Ľ�� 
    {
        // tree�����Һ��Ӷ��ǿ� 
        if ((tree->left != NULL) && (tree->right != NULL))
        {
            if (height(tree->left) > height(tree->right))
            {
                // ���tree�����������������ߣ�
                // ��(01)�ҳ�tree���������е����ڵ�
                //   (02)�������ڵ��ֵ��ֵ��tree��
                //   (03)ɾ�������ڵ㡣
                // ����������"tree�������������ڵ�"��"tree"������
                // �������ַ�ʽ�ĺô��ǣ�ɾ��"tree�������������ڵ�"֮��AVL����Ȼ��ƽ��ġ�
                AVLTreeNode<T>* max = maximum(tree->left);
                tree->key = max->key;
                tree->left = remove(tree->left, max);
            }
            else
            {
                // ���tree��������������������(��������ȣ�������������������1)
                // ��(01)�ҳ�tree���������е���С�ڵ�
                //   (02)������С�ڵ��ֵ��ֵ��tree��
                //   (03)ɾ������С�ڵ㡣
                // ����������"tree������������С�ڵ�"��"tree"������
                // �������ַ�ʽ�ĺô��ǣ�ɾ��"tree������������С�ڵ�"֮��AVL����Ȼ��ƽ��ġ�
                AVLTreeNode<T>* min = minimum(tree->right);
                tree->key = min->key;
                tree->right = remove(tree->right, min);
            }
        }
        else
        {
            AVLTreeNode<T>* tmp = tree;
            tree = (tree->left != NULL) ? tree->left : tree->right;
            delete tmp;
        }
    }

    return tree;
}

template<class T>
void AVLTree<T>::remove(T key)
{
    AVLTreeNode<T>* z;
    if ((z = search(root, key)) != NULL)
        root = remove(root, z);
}

template<class T>
void AVLTree<T>::preOrder(AVLTreeNode<T>* tree) const
{
    if (tree != NULL)
    {
        cout << tree->key << " ";
        preOrder(tree->left);
        preOrder(tree->right);
    }
}

template<class T>
void AVLTree<T>::preOrder()
{
    preOrder(root);
}

template<class T>
void AVLTree<T>::inOrder(AVLTreeNode<T>* tree) const
{
    if (tree != NULL)
    {
        inOrder(tree->left);
        cout << tree->key << " ";
        inOrder(tree->right);
    }
}

template<class T>
void AVLTree<T>::inOrder()
{
    inOrder(root);
}

template<class T>
void AVLTree<T>::postOrder(AVLTreeNode<T>* tree) const
{
    if (tree != NULL)
    {
        postOrder(tree->left);
        postOrder(tree->right);
        cout << tree->key << " ";
    }
}

template<class T>
void AVLTree<T>::postOrder()
{
    postOrder(root);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::search(AVLTreeNode<T>* x, T key) const
{
    if (x == NULL || x->key == key)
        return x;
    if (key < x->key)
        return search(x->left, key);
    else
        return search(x->right, key);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::search(T key)
{
    return search(root, key);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::iterativeSearch(AVLTreeNode<T>* x, T key) const
{
    while (x != NULL && x->key != key)
    {
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::iterativeSearch(T key)
{
    return iterativeSearch(root, key);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T>* tree)
{
    if (tree == NULL)
        return NULL;
    while (tree->left != NULL)
        tree = tree->left;
    return tree;
}

template<class T>
T AVLTree<T>::minimum()
{
    AVLTreeNode<T>* p = minimum(root);
    if (p != NULL)
        return p->key;
    return (T)NULL;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T>* tree)
{
    if (tree == NULL)
        return NULL;
    while (tree->right != NULL)
        tree = tree->right;
    return tree;
}

template<class T>
T AVLTree<T>::maximum()
{
    AVLTreeNode<T>* p = maximum(root);
    if (p != NULL)
        return p->key;
    return (T)NULL;
}

template<class T>
void AVLTree<T>::destroy(AVLTreeNode<T>*& tree)
{
    if (tree == NULL)
        return;
    if (tree->left != NULL)
        destroy(tree->left);
    if (tree->right != NULL)
        destroy(tree->right);
    delete tree;
}

template<class T>
void AVLTree<T>::destroy()
{
    destroy(root);
}

template<class T>
void AVLTree<T>::print(AVLTreeNode<T>* tree, T key, int direction)
{
    if (tree != NULL)
    {
        if (direction == 0)
            cout << setw(2) << tree->key << "is root" << endl;
        else
            cout << setw(2) << tree->key << "is" << setw(2) << key << "'s" << setw(12) << (direction == 1 ? "right child" : "left child") << endl;
        print(tree->left, tree->key, -1);
        print(tree->right, tree->key, 1);
    }
}

template<class T>
void AVLTree<T>::print()
{
    if (root != NULL)
        print(root, root->key, 0);
}



void func() {
    int n = 0;
    cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    AVLTree<int> t;
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

        AVLTree<int> AVL;


        if (flag == 0) {
            cout << "//-------------------------------------------------------------------" << endl;
            cout << "/**˳�����N���������������1000��������˳��ɾ��**/" << endl;
            cout << "//-------------------------------------------------------------------" << endl;
            flag = 1;
        }

        //���յ���˳�����
        QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ  
        for (vector<int>::iterator i = sortData.begin(); i != sortData.end(); i++) {
            AVL.insert(*i);//...���Դ���
        }
        QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
        time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λ
        cout << n * 20000 << "������-" << " AVL��������ʱ�䣺" << time * 1000 << "ms" << endl;
        // BST.Output();

         //�������
        QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ
        for (vector<int>::iterator i = findData.begin(); i != findData.end(); i++) {
            AVL.search(*i);//...���Դ���
        }
        QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
        time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λ 
        cout << n * 20000 << "������-" << " AVL��������ʱ�䣺" << time * 1000 << "ms" << endl;

        //˳��ɾ��
        QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ 
        for (vector<int>::iterator i = sortData.begin(); i != sortData.end(); i++) {
            AVL.remove(*i);//...���Դ���
        }
        QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
        time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λ
        cout << n * 20000 << "������-" << " AVLɾ������ʱ�䣺" << time * 1000 << "ms" << endl;
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

        AVLTree<int> AVL;


        if (flag == 0) {
            cout << "//-------------------------------------------------------------------" << endl;
            cout << "/**˳�����N���������������1000������������ɾ��**/" << endl;
            cout << "//-------------------------------------------------------------------" << endl;
            flag = 1;
        }

        //���յ���˳�����
        QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ  
        for (vector<int>::iterator i = sortData.begin(); i != sortData.end(); i++) {
            AVL.insert(*i);//...���Դ���
        }
        QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
        time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λ
        cout << n * 20000 << "������-" << " AVL��������ʱ�䣺" << time * 1000 << "ms" << endl;
        // BST.Output();

         //�������
        QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ
        for (vector<int>::iterator i = findData.begin(); i != findData.end(); i++) {
            AVL.search(*i);//...���Դ���
        }
        QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
        time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λ 
        cout << n * 20000 << "������-" << " AVL��������ʱ�䣺" << time * 1000 << "ms" << endl;

        //˳��ɾ��
        QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ 
        for (vector<int>::reverse_iterator i = sortData.rbegin(); i != sortData.rend(); i++) {
            AVL.remove(*i);//...���Դ���
        }
        QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
        time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λ
        cout << n * 20000 << "������-" << " AVLɾ������ʱ�䣺" << time * 1000 << "ms" << endl;
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

        AVLTree<int> AVL;


        if (flag == 0) {
            cout << "//-------------------------------------------------------------------" << endl;
            cout << "/**�������N���������������1000�����������ɾ��**/" << endl;
            cout << "//-------------------------------------------------------------------" << endl;
            flag = 1;
        }

        //���յ���˳�����
        QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ  
        for (vector<int>::iterator i = randomData.begin(); i != randomData.end(); i++) {
            AVL.insert(*i);//...���Դ���
        }
        QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
        time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λ
        cout << n * 20000 << "������-" << " AVL��������ʱ�䣺" << time * 1000 << "ms" << endl;
        // BST.Output();

         //�������
        QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ
        for (vector<int>::iterator i = findData.begin(); i != findData.end(); i++) {
            AVL.search(*i);//...���Դ���
        }
        QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
        time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λ 
        cout << n * 20000 << "������-" << " AVL��������ʱ�䣺" << time * 1000 << "ms" << endl;

        //ɾ��
        get_data(n, randomData, sortData, findData);
        QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ 
        for (vector<int>::iterator i = randomData.begin(); i != randomData.end(); i++) {
            AVL.remove(*i);//...���Դ���
        }
        QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
        time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λ
        cout << n * 20000 << "������-" << " AVLɾ������ʱ�䣺" << time * 1000 << "ms" << endl;
    }
}


int main() {

    //test1();
    //test2();
    test3();


    system("pause");
    return 0;
}