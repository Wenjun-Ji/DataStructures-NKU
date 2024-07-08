#include<iostream>
#include<cmath>
#include<queue>
using namespace std;

typedef struct AVLTreeNode {
public:
	int data;
	int h;
	AVLTreeNode* left;
	AVLTreeNode* right;
	AVLTreeNode() :left(NULL), right(NULL), data(-999),h(1){}
	AVLTreeNode(int e) :left(NULL), right(NULL), data(e),h(1){}
}Node;

class AVLTree {
public:
	AVLTree();
	bool init(int *arr,int n);
	bool containValue(int value);
	bool insert(int value);
	Node* add(Node* cur,int value);
	Node* Delete(Node* cur, int value);
	Node* maintain(Node * cur);
	Node* leftRotate(Node *cur);
	Node* rightRotate(Node *cur);
	bool isAVLTree();
	bool isCompleteBinaryTree(); 

public:
	Node* root;
	int  size;
};
int getHeight(Node* cur) {
	if (cur == NULL) {
		return 0;
	}
	int leftHeight = getHeight(cur->left);
	int rightHeight = getHeight(cur->right);
	return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

AVLTree::AVLTree() {
	size = 0;
	root = NULL;
}
bool AVLTree::init(int* arr,int n) {
	for (int i = 0; i < n; i++) {
		insert(arr[i]);
	}
	return true;
}
bool AVLTree::containValue(int value) {
	if (root == NULL) {
		return false;
	}
	Node* cur = root;
	while (cur) {
		if (value > cur->data) {
			cur = cur->right;
		}
		else if (value < cur->data) {
			cur = cur->left;
		}
		else {
			return true;
		}
	}
	return false;
}
bool AVLTree::insert(int value) {
	if (this->containValue(value)) {
		return false;
	}
	else {
		root=add(root, value);
		size++;
		return true;
	}
}
Node* AVLTree::add(Node* cur, int value) {
	if (cur == NULL) {
		cur = new Node(value);
		return cur;
	}
	if (value > cur->data) {
		cur->right=add(cur->right, value);
	}
	else if(value<cur->data) {
		cur->left=add(cur->left, value);
	}
	//更新高度(是add单链路径上的高度，拎一个子树的高度不可见，但由于平衡二叉树，所以平衡因子为 -1 0 1)
	//又因为是增加节点，增加完节点后的子树高度必然大于等于不可见子树的高度
	cur->h = max(cur->left != NULL ? cur->left->h : 0, cur->right != NULL ? cur->right->h : 0) + 1;
	//调整平衡
	return maintain(cur);
}

Node* AVLTree::Delete(Node*cur,int value) {
	if (value > cur->data) {
		cur->right = Delete(cur->right, value);
	}
	else if (value < cur->data) {
		cur->left = Delete(cur->left, value);
	}
	else {
		if (cur->left == NULL && cur->right == NULL) {
			delete cur;
			return NULL;
		}else if (cur->left==NULL&&cur->right!=NULL) {
			Node* des = cur->right;
			delete cur;
			cur= des;
		}
		else if(cur->left!=NULL&&cur->right==NULL){
			Node* des = cur->left;
			delete cur;
			cur= des;
		}
		else {
			Node* successor = cur->right;
			while (successor->left) {
				successor = successor->left;
			}
			cur->data = successor->data;
			cur->right = Delete(cur->right,successor->data);
		}
	}	
	if (cur) {
		cur->h = max(cur->left != NULL ? cur->left->h : 0, cur->right != NULL ? cur->right->h : 0) + 1;
	}
	return maintain(cur);
}

Node* AVLTree::maintain(Node* cur) {
	int k = abs(getHeight(cur->left) - getHeight(cur->right));
	if (k < 2) {
		return cur;
	}
	int leftChildHeight = getHeight(cur->left);
	int rightChildHeight = getHeight(cur->right);
	int leftGrandChildHeight = 0;
	int rightGrandChildHeight = 0;
	if (leftChildHeight > rightChildHeight) {
		leftGrandChildHeight = getHeight(cur->left->left);//左孩子的左孙子
		rightGrandChildHeight = getHeight(cur->left->right);//左孩子的右孙子
		if (leftGrandChildHeight >= rightGrandChildHeight) {//LL旋转  注意等于时只能优右旋
			return rightRotate(cur);
		}
		else if (leftGrandChildHeight < rightGrandChildHeight) {//LR旋转
			cur->left=leftRotate(cur->left);
			return rightRotate(cur);
		}
	}
	else if (leftChildHeight < rightChildHeight) {
		leftGrandChildHeight = getHeight(cur->right->left);//左孩子的左孙子
		rightGrandChildHeight = getHeight(cur->right->right);//左孩子的右孙子
		if (leftGrandChildHeight <= rightGrandChildHeight) {//RR旋转  注意等于时只能左旋
			
			return leftRotate(cur);;
		}
		else if (leftGrandChildHeight > rightGrandChildHeight) {//RL旋转
			cur->right = rightRotate(cur->right);
			return leftRotate(cur);
		}
	}
}
Node* AVLTree::rightRotate(Node* cur){//谁旋转下降 谁做参数
	if (cur == NULL) {
		return NULL;
	}
	Node* root = cur;
	Node* root_leftchild = cur->left;
	Node* root_leftchild_rightchild = cur->left->right;
	root->left = NULL;
	root_leftchild->right = NULL;
	root->left = root_leftchild_rightchild;
	root_leftchild->right = root;

	//因为root下旋 先调整root的高度再调整root_leftchild的高度
	root->h = max(root->left != NULL ? root->left->h : 0,
				  root->right != NULL ? root->right->h : 0
				 ) + 1;
	root_leftchild->h = max(root_leftchild->left != NULL ? root_leftchild->left->h : 0, 
							root_leftchild->right != NULL ? root_leftchild->right->h : 0
						    ) + 1;
	return root_leftchild;
}
Node* AVLTree::leftRotate(Node* cur){
	if (cur == NULL) {
		return NULL;
	}
	Node* root = cur;
	Node* root_rightchild = cur->right;
	Node* root_rightchild_leftchild = cur->right->left;
	root->right = NULL;
	root_rightchild->left = NULL;
	root->right = root_rightchild_leftchild;
	root_rightchild->left = root;

	//因为root下旋 先调整root的高度再调整root_leftchild的高度
	root->h = max(root->left != NULL ? root->left->h : 0,
		root->right != NULL ? root->right->h : 0
	) + 1;
	root_rightchild->h = max(root_rightchild->left != NULL ? root_rightchild->left->h : 0,
		root_rightchild->right != NULL ? root_rightchild->right->h : 0
	) + 1;
	return root_rightchild;
}

bool visit(Node* cur) {
	int leftHeight = cur->left != NULL ? cur->left->h : 0;
	int rightHeight = cur->right != NULL ?  cur->right->h:0;
	int k = abs(leftHeight - rightHeight);
	if (k >= 2) { return false; }
	return true;
}
void InOrder(Node* cur, bool& flag) {
	if (cur == NULL) {
		return;
	}
	InOrder(cur->left, flag);
	if (!visit(cur)) {
		flag = false;
	}
	InOrder(cur->right, flag);
}
bool AVLTree::isAVLTree(){
	if (root == NULL) {
		return true;
	}
	bool flag = true;
	InOrder(root, flag);
	if (flag) {
		return true;
	}
	return false;
}

queue<int>result;
void print(Node*cur) {
	if (cur) {
		cout << "h" << cur->h<<" ";
		result.push(cur->data);
	}
}
void showResult() {
	int count = result.size();
	for (int i = 0; i < count; i++) {
		cout << result.front();
		result.pop();
		if (i < count - 1)
			cout << " ";
	}
}
void LevelTraverse(Node* root) {
	if (root == NULL) { return; }
	queue<Node*>q;
	Node* cur = root;
	q.push(cur);
	while (!q.empty()) {
		cur = q.front();
		print(cur);
		q.pop();
		if (cur->left) {
			q.push(cur->left);
		}
		if (cur->right) {
			q.push(cur->right);
		}
	}
}

bool AVLTree::isCompleteBinaryTree() {
	if (root == NULL) { return true; }
	queue<Node*>q;
	Node* cur = root;
	q.push(cur);
	while (!q.empty()) {
		cur = q.front();
		q.pop();
		if (cur == NULL) { break; }
		//if (cur->left) {
			q.push(cur->left);
		//}
		//if (cur->right) {
			q.push(cur->right);
		//}
	}
	while (!q.empty()) {
		cur = q.front();
		q.pop();
		if (cur != NULL) {
			return false;
		}
	}
	return true;
}

void func() {
	int n = 0;
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	AVLTree t;
	t.init(arr, n);
	LevelTraverse(t.root);
	showResult();
	cout << endl;
	if (t.isCompleteBinaryTree()) {
		cout << "Yes" ;
	}
	else {
		cout << "No";
	}
	cout << endl;
	t.root=t.Delete(t.root, 70);
	LevelTraverse(t.root);
	showResult();
	cout << endl;
	if (t.isCompleteBinaryTree()) {
		cout << "Yes";
	}
	else {
		cout << "No";
	}
}



int main() {

	func();


	system("pause");
	return 0;
}


/*
*/