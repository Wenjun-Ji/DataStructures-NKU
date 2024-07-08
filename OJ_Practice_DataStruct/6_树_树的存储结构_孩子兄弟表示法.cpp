#include<iostream>
using namespace std;

typedef struct TreeNode {
	int data;
	TreeNode* child;
	TreeNode* brother;
	TreeNode(int _data) :data(_data) {}
}TreeNode,*Tree;

