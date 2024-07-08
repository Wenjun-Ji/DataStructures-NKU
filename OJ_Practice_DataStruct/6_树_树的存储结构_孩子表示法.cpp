#include<iostream>
#include<vector>
using namespace std;
struct ListNode {
	int pos;
	ListNode* next;
	ListNode(int _pos) :pos(_pos) {}
};

struct ChildList {
	int data;
	ListNode* node;
	ChildList(int _data) :data(_data) {}
};

class Tree{
public:
	vector<ChildList> t;
};







int main() {



}

