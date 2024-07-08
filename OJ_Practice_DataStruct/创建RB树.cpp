#include<iostream>
#include<queue>
#include<utility>
using namespace std;
enum Color {Red,Black};
//template<class int,class int>
struct Node{
	Node* _left;
	Node* _right;
	Node* _parent;
	pair<int, int>_kv;
	Color _col;
	Node(pair<int,int>&e):
		_left(NULL),
		_right(NULL),
		_parent(NULL),
		_kv(e),_col(Red) 
	{}
};

//template<class int, class int>
class RBTree{
public:
	RBTree():
		_root(NULL),
		size(0)
	{}
	bool init(int* arr, int n) {
		for (int i = 0; i < n; i++) {
			insert(make_pair(arr[i],arr[i]));
		}
		return true;
	}
	int getMax() {
		Node* cur = _root;
		while (cur->_right) {
			cur = cur->_right;
		}
		return cur->_kv.first;
	}
	int getMin() {
		Node* cur = _root;
		while (cur->_left) {
			cur = cur->_left;
		}
		return cur->_kv.first;
	}
	pair<Node*, bool>insert(pair<int, int> kv) {
		//����ֱ�Ӳ���
		if (_root == NULL) {
			_root = new Node(kv);
			_root->_col = Black;//��Ϊ��
			return make_pair(_root, true);
		}
		//1����λ
		Node* cur = _root;
		Node* parent = NULL;
		while (cur) {
			if (kv.first > cur->_kv.first) {
				parent = cur;
				cur = cur->_right;
			}
			else if (kv.first < cur->_kv.first) {
				parent = cur;
				cur = cur->_left;
			}
			else {
				cout << "�Ѿ�������ýڵ�";
				return make_pair(cur, false);
			}
		}
		//2������
		cur = new Node(kv);
		if (kv.first < parent->_kv.first) {//�ڸ��ڵ����߲���
				parent->_left = cur;
				cur->_parent = parent;
			}
			else {//�ڸ��ڵ���ұ߲���
				parent->_right = cur;
				cur->_parent = parent;
		}


		//3������
		Node* grandparent = NULL;
		Node* uncle = NULL;

		while (parent && parent->_col == Red) {
			grandparent = parent->_parent;
			if (parent==grandparent->_left) {//parent������
				uncle = grandparent->_right;
				if (uncle&&uncle->_col==Red) {//����-->�常үȾɫ��ү����
					parent->_col = Black;
					uncle->_col = Black;
					grandparent->_col = Red;
					cur = grandparent;//���ϻ���
					parent = grandparent->_parent;
				}else {//����������岻����-->R����������ү��Ⱦɫ/RL˫��������ү��Ⱦɫ
					if (cur == parent->_left) {//LL
						rightRotate(grandparent);
						parent->_col = Black;
						grandparent->_col = Red;
					}
					else{//LR
						leftRotate(grandparent->_left);
						rightRotate(grandparent);
						cur->_col = Black;
						grandparent->_col = Red;
					}
					break;
				}
			}
			else{//parent���Һ���	
				uncle = grandparent->_left;
				if (uncle&&uncle->_col==Red) {//����-->�常үȾɫ��ү����
					parent->_col = Black;
					uncle->_col = Black;
					grandparent->_col = Red;
					cur = grandparent;//���ϻ���
					parent = grandparent->_parent;
				}
				else {//����������岻����-->L����������ү��Ⱦɫ/LR˫��������ү��Ⱦɫ
					if (parent->_right == cur) {//RR
						leftRotate(grandparent);
						parent->_col = Black;
						grandparent->_col = Red;
					}
					else{//RL
						rightRotate(grandparent->_right);
						leftRotate(grandparent);
						cur->_col = Black;
						grandparent->_col = Red;
					}
					break;
				}
				
			}
		}
		_root->_col = Black;
		return make_pair(_root, true);
	}
	pair<Node*, bool>Delete(pair<int, int> kv) {
		Node* cur = _root;
		Node* parent = NULL;
		//1����λ��ɾ���ڵ�
		while (cur) {
			if (kv.first > cur->_kv.first) {
				parent = cur;
				cur = cur->_right;
			}
			else if (kv.first < cur->_kv.first) {
				parent = cur;
				cur = cur->_left;
			}
			else {
				break;
			}
		}
		if (cur == NULL) {
			//cout << "RB�������ýڵ�" << endl;
			return make_pair(_root, false);
		}
		Node* delParentPos = NULL;
		Node* delPos = NULL;
		if (cur->_left == NULL) {
			delPos = cur;
			delParentPos = parent;
		}
		else if (cur->_right == NULL) {
			delPos = cur;
			delParentPos = parent;
		}
		else {
			delParentPos = cur;
			delPos = cur->_right;
			while (delPos->_left) {
				delParentPos = delPos;
				delPos = delPos->_left;
			}
			cur->_kv.first = delPos->_kv.first;
			cur->_kv.second = delPos->_kv.second;
		}
		//delPos��Ϊ��˫�ڽڵ� �Ҿ���Ѱ�Һ� ֻ�����������Ҷ�ӽڵ� ֻ���������Ľڵ� ֻ���������Ľڵ�

		//delPos���ڵ��� del����ɾ��
		Node* del = delPos;
		Node* delp = delParentPos;

		//2���������������˫�ڽڵ�����ͨ�ڽڵ㣩
		if (delPos->_col == Red) {//ɾ���ڵ�Ϊ��ɫ��������תȾɫ�ȵ���
			;
		}
		else {//ɾ���ڵ�Ϊ��ɫ 
			if (delPos->_left) {
				delPos->_left->_col = Black;
			}else if (delPos->_right) {
				delPos->_right->_col = Black;
			}else {
				while (delPos != _root) {
					if (delPos == delParentPos->_left) {//ɾ���ڵ��ڸ��ڵ����
						Node* brother = delParentPos->_right;
						if (brother->_col == Red) {//brotherΪ��
							brother->_col = Black;
							delParentPos->_col = Red;
							leftRotate(delParentPos);
							//���ϻ���
							brother=delParentPos->_right;
						}
						else if ((brother->_left == NULL || brother->_left->_col == Black)//brother���ں���
							&& (brother->_right == NULL || brother->_right->_col == Black)) {
							brother->_col = Red;
							if (delParentPos->_col == Red) {
								delParentPos->_col = Black;
								break;
							}else {
								delPos = delParentPos;
								delParentPos = delParentPos->_parent;
							}
						}else {//brother����һ���캢��
							if (brother->_left&&brother->_left->_col == Red) {//RL
								brother->_left->_col = delParentPos->_col;
								delParentPos->_col = Black;
								rightRotate(brother);
								leftRotate(delParentPos);
								break;
							}
							else{//RR
								brother->_right->_col = brother->_col;
								brother->_col = delParentPos->_col;
								delParentPos->_col = Black;
								leftRotate(delParentPos);
								break;
							}

						}
					}
					else {//ɾ���ڵ��ڸ��ڵ����
						Node* brother = delParentPos->_left;
						if (brother->_col == Red) {//brotherΪ��
							brother->_col = Black;
							delParentPos->_col = Red;
							rightRotate(delParentPos);
							//���ϻ���
							brother = delParentPos->_left;
						}
						else if ((brother->_left == NULL || brother->_left->_col == Black)//brother���ں���
							&& (brother->_right == NULL || brother->_right->_col == Black)) {
							brother->_col = Red;
							if (delParentPos->_col == Red) {
								delParentPos->_col = Black;
								break;
							}
							else {
								delPos = delParentPos;
								delParentPos = delParentPos->_parent;
							}
						}
						else {//brother����һ���캢��
							if(brother->_left->_col == Red) {//LR
								brother->_right->_col = delParentPos->_col;
								delParentPos->_col = Black;
								leftRotate(brother);
								rightRotate(delParentPos);
								break;
							}
							else {//LL
								brother->_left->_col = brother->_col;
								brother->_col = delParentPos->_col;
								delParentPos->_col = Black;
								rightRotate(delParentPos);
								break;
							}
						}
					}
				}
			}
		}
		//3����ʵ��ɾ��
		if (del->_left == NULL) {
			if (del == _root) {
				_root = _root->_right;
				if (_root)
					_root->_parent = NULL;
			}
			else {
				if (del == delp->_left) {
					delp->_left = del->_right;
				}
				else {
					delp->_right = del->_right;
				}
				if (del->_right)
					del->_right->_parent = delp;
			}
		}
		else {
			if (del == _root) {
				_root = _root->_left;
				if (_root)
					_root->_parent = NULL;
			}
			else {
				if (del == delp->_left) {
					delp->_left = del->_left;
				}
				else {
					delp->_right = del->_left;
				}
				if (del->_left)
					del->_left->_parent = delp;
			}
		}
		delete del;
		return make_pair(_root, true);
	}
	pair<Node*, bool>Find(pair<int, int>& kv) {
		Node* cur = _root;
		while (cur)
		{
			if (kv.first < cur->_kv.first) //keyֵС�ڸý���ֵ
			{
				cur = cur->_left; //�ڸý������������в���
			}
			else if (kv.first > cur->_kv.first) //keyֵ���ڸý���ֵ
			{
				cur = cur->_right; //�ڸý������������в���
			}
			else //�ҵ���Ŀ����
			{
				return make_pair(cur, true); //���ظý��
			}
		}
		return make_pair(cur, false); //����ʧ��
	}
	bool isRBTree() {
		if (_root == NULL) {
			return true;
		}
		if (_root->_col == Red) {
			cout << "���ڵ�Ϊ��ɫ";
			return false;
		}
		Node* cur = _root;
		int balckcount = 0;
		while (cur) {
			if (cur->_col == Black) {
				balckcount++;
			}
			cur = cur->_left;
		}
		int count = 0;
		return _isRbTree(_root,count,balckcount);
	}
	bool _isRbTree(Node* root,int count,int blackcount) {
		if (root == NULL) {
			if (blackcount == count) {
				return true;
			}
			else {
				cout << "�ڸ߲�ͬ" << endl;
				return false;
			}
		}
		if (root->_col == Red && root->_parent->_col == Red) {
			cout << "����������ɫ�ڵ�" << endl;
			return false;
		}
		if (root->_col == Black) {
			count++;
		}
		return _isRbTree(root->_left, count, blackcount) && _isRbTree(root->_right, count, blackcount);
	}
	void leftRotate(Node* cur) {
		if (!cur) { return ; }
		Node* right = cur->_right;
		Node* right_left = right->_left;
		Node* parent = cur->_parent;
		//��right_left���ӵ�cur��right
		cur->_right = right_left;
		if (right_left)
			right_left->_parent = cur;
		//��cur���ӵ�right��left
		right->_left = cur;
		cur->_parent = right;
		//right���ӵ�parent����
		right->_parent = parent;
		if (parent) {	
			if (cur == parent->_left) {
				parent->_left = right;
			}
			else {
				parent->_right = right;
			}
		}else {
			_root = right;
		}
	}
	void rightRotate(Node* cur) {
		if (!cur) { return ; }
		Node* left = cur->_left;
		Node* left_right = left->_right;
		Node* parent = cur->_parent;
		//��left_right���ӵ�cur��left
		cur->_left = left_right;
		if(left_right)
			left_right->_parent = cur;
		//��cur���ӵ�left��right
		left->_right = cur;
		cur->_parent = left;
		//��left���ӵ�parent����
		left->_parent = parent;
		if (parent) {
			if (parent->_left == cur) {
				parent->_left = left;
			}
			else {
				parent->_right = left;
			}
		}
		else {
			_root = left;
		}
	}

public:	
	Node*_root;
	int size;
};
void visit(Node* cur) {
	if (cur == NULL)
		return;
	cout << cur->_kv.first;
	if (cur->_col == Red)
		cout << "(R)";
	else
		cout << "(B)";
	cout << " ";
}
void levelTraverse(Node* cur) {
	if (cur == NULL)
		return;
	queue<Node*>q;
	q.push(cur);
	while(!q.empty()){
		cur = q.front();
		visit(cur);
		q.pop();
		if (cur->_left) {
			q.push(cur->_left);
		}
		if (cur->_right) {
			q.push(cur->_right);
		}
	}
}

void FirstTraverse(Node* cur) {
	if (cur == NULL) {
		return;
	}
	visit(cur);
	FirstTraverse(cur->_left);
	FirstTraverse(cur->_right);
}

void func() {
	int n = 0;
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	int nn = 0;
	cin >> nn;
	int* arrr = new int[nn];
	for (int i = 0; i < nn; i++) {
		cin >> arrr[i];
	}
	RBTree t;
	t.init(arr, n);
	//levelTraverse(t._root);
	//cout << endl;
	if (t._root == NULL) {
		cout << "Null";
	}
	else {
		FirstTraverse(t._root);
	}
	cout << endl;
	cout << t.getMin() << " " << t.getMax() << endl;

	for (int i = 0; i < nn; i++) {
		t.Delete(make_pair(arrr[i], arrr[i]));
	}
	//levelTraverse(t._root);
	//cout << endl;
	if (t._root == NULL) {
		cout << "Null";
	}
	else {
		FirstTraverse(t._root);
	}
	//cout<<t.isRBTree()<<endl;
}

int main() {
	func();
	system("pause"); 
	return 0;
}



