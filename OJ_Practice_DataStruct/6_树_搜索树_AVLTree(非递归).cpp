#pragma once
using namespace std;
#include <iostream>
#include<queue>
template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode(const pair<K, V>& kv = pair<K, V>())
		: _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _bf(0)
		, _kv(kv)
	{}
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	int _bf;//balance factor ƽ������

	pair<K, V> _kv;
};

template<class K, class V>
class AVLTree
{
public:
	typedef struct AVLTreeNode<K, V>  Node;
	//�ҵ���
	void RotateR(Node* parent)
	{
		Node* cur = parent->_left;
		Node* curR = cur->_right;//cur��������
		Node* pparent = parent->_parent;//����parent�ĸ��׽ڵ�

		//��cur���������ӵ�parent�����
		parent->_left = curR;
		if (curR)
			curR->_parent = parent;

		//��parent���ӵ�cur���Ҳ�
		cur->_right = parent;
		parent->_parent = cur;

		//��cur��pparent��������
		if (pparent == nullptr)//cur����µĸ�
		{
			_root = cur;
			cur->_parent = nullptr;
		}
		else//pparent��Ϊ��
		{
			cur->_parent = pparent;
			if (parent == pparent->_left)//parent�ڸ��׽ڵ�����
			{
				pparent->_left = cur;
			}
			else
			{
				pparent->_right = cur;
			}
		}

		//ƽ�����Ӹ���
		parent->_bf = 0;
		cur->_bf = 0;

	}
	//����
	void RotateL(Node* parent)//����
	{
		Node* cur = parent->_right;//�ұ�ߣ�������Ϊ��
		Node* curL = cur->_left;
		Node* pprent = parent->_parent;

		//curL���ӵ�parent��
		parent->_right = curL;
		if (curL)
			curL->_parent = parent;

		//parent���ӵ�cur��
		cur->_left = parent;
		parent->_parent = cur;

		//cur���ӵ�pprent��
		if (pprent == nullptr)//��
		{
			_root = cur;
			cur->_parent = nullptr;
		}
		else//��Ϊ��
		{
			cur->_parent = pprent;
			//�ж���������һ��
			if (pprent->_left == parent)
			{
				pprent->_left = cur;
			}
			else
			{
				pprent->_right = cur;
			}
		}

		//ƽ�����ӵĸ���
		parent->_bf = 0;
		cur->_bf = 0;
	}

	//����˫��
	void RotateLR(Node* parent)
	{
		Node* cur = parent->_left;
		Node* curR = cur->_right;//��ʱ������Ϊ�գ���Ϊ��������

		int bf = curR->_bf;//����һ��ƽ������

		RotateL(cur);//������
		RotateR(parent);//������

		//�����������Ὣƽ������ȫ�������0�����Ҫ��ƽ�����ӽ��и���

		if (bf == 1)//��curR���Ҳ����
		{
			curR->_bf = 0;
			cur->_bf = -1;
			parent->_bf = 0;
		}
		else if (bf == -1)//��curR������
		{
			curR->_bf = 0;
			cur->_bf = 0;
			parent->_bf = 1;
		}
	}
	//����˫��
	void RotateRL(Node* parent)
	{
		Node* cur = parent->_right;
		Node* curL = cur->_left;

		int bf = curL->_bf;

		RotateR(cur);//������
		RotateL(parent);//������

		//ƽ�����ӳ���

		if (bf == 1)//��subRL�Ҳ����ʱ
		{
			curL->_bf = 0;
			parent->_bf = -1;
			cur->_bf = 0;
		}
		else if (bf == -1)//��������ʱ
		{
			curL->_bf = 0;
			parent->_bf = 0;
			cur->_bf = 1;
		}
	}
	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}

		//�и��ˣ�����ƽ��������ķ������в���
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (kv.first < cur->_kv.first)//Kֵ�Ƚϣ�С���������
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (kv.first > cur->_kv.first)//������
			{
				parent = cur;
				cur = cur->_right;
			}
			else//��ȣ������в���
			{
				return false;
			}
		}

		//��ʱ�Ѿ��ҵ������λ����,�жϲ�����parent����߻����ұ�
		cur = new Node(kv);
		if (parent->_kv.first > kv.first)//�������
		{
			parent->_left = cur;
			cur->_parent = parent;//��������cur��ָ���ָ
		}
		else//�����ұ�
		{
			parent->_right = cur;
			cur->_parent = parent;//��������cur��ָ���ָ
		}


		//����ƽ������
		while (parent)//��Ϊ��
		{
			if (parent->_left == cur)//cur��parent���
			{
				parent->_bf--;
			}
			else//cur��parent�Ҳ�
			{
				parent->_bf++;
			}

			if (parent->_bf == 0)//��ǰ����ƽ��ģ�ֹͣ����
				break;
			else if (parent->_bf == 1 || parent->_bf == -1)//������������
			{
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)//��Ҫ������ת����
			{
				if (parent->_bf == -2)//��߸�
				{
					if (cur->_bf == -1)//���ڵ�ǰ�ڵ���������˽ڵ� ->�ҵ���
					{
						RotateR(parent);
					}
					else//cur->_bf=1 ->����Ӱ��,��Ҫ��������˫��
					{
						RotateLR(parent);
					}
				}
				else//�ұ߸�
				{
					if (cur->_bf == 1)//�ڵ�ǰ�ڵ���Ҳ�����˽ڵ� ->  ����
					{
						RotateL(parent);
					}
					else//cur->_bf=-1 ����Ӱ��
					{
						RotateRL(parent);
					}
				}
				break;//��ת����ǰ��������ƽ����ˣ��˳�
			}
			else//0 1 2 -> �������ߵ���һ�����ߵ�����˵���������߼�����
			{
				exit(-1);
			}
		}
		return true;
	}

	//ɾ������
	bool Erase(const K& key)
	{
		//���ڱ���������
		Node* parent = nullptr;
		Node* cur = _root;
		//���ڱ��ʵ�ʵ�ɾ����㼰�丸���
		Node* delParentPos = nullptr;
		Node* delPos = nullptr;
		while (cur)
		{
			if (key < cur->_kv.first) //����keyֵС�ڵ�ǰ����keyֵ
			{
				//���ý�����������
				parent = cur;
				cur = cur->_left;
			}
			if (key > cur->_kv.first) //����keyֵС�ڵ�ǰ����keyֵ
			{
				//���ý�����������
				parent = cur;
				cur = cur->_right;
			}
			else //�ҵ��˴�ɾ�����
			{
				if (cur->_left == nullptr) //��ɾ������������Ϊ��
				{
					if (cur == _root) //��ɾ������Ǹ����
					{
						_root = _root->_right; //�ø�������������Ϊ�µĸ����
						//�����ʱ_rootΪ�գ���ʱѰ��ȥ����ָ���Կ�ָ������ö����������Ҫ�ж�
						if (_root)
							_root->_parent = nullptr;
						delete cur; //ɾ��ԭ�����
						return true; //����������Ƚ�㣬�������ƽ�����ӵĸ��²���
					}
					else
					{
						delParentPos = parent; //���ʵ��ɾ�����ĸ����
						delPos = cur; //���ʵ��ɾ���Ľ��
					}
					break; //ɾ����������Ƚ�㣬�����ƽ������
				}
				else if (cur->_right == nullptr) //��ɾ������������Ϊ��
				{
					if (cur == _root) //��ɾ������Ǹ����
					{
						_root = _root->_left; //�ø�������������Ϊ�µĸ����
						//�����ʱ_rootΪ�գ���ʱѰ��ȥ����ָ���Կ�ָ������ö����������Ҫ�ж�
						if (_root)
							_root->_parent = nullptr;
						delete cur; //ɾ��ԭ�����
						return true; //����������Ƚ�㣬�������ƽ�����ӵĸ��²���
					}
					else
					{
						delParentPos = parent; //���ʵ��ɾ�����ĸ����
						delPos = cur; //���ʵ��ɾ���Ľ��
					}
					break; //ɾ����������Ƚ�㣬�����ƽ������
				}
				else //��ɾ������������������Ϊ��
				{
					//�滻��ɾ��
					//Ѱ�Ҵ�ɾ���������������keyֵ��С�Ľ����Ϊʵ��ɾ�����
					Node* minParent = cur;
					Node* minRight = cur->_right;
					while (minRight->_left)
					{
						minParent = minRight;
						minRight = minRight->_left;
					}
					cur->_kv.first = minRight->_kv.first; //����ɾ������key��ΪminRight��key
					cur->_kv.second = minRight->_kv.second; //����ɾ������value��ΪminRight��value
					delParentPos = minParent; //���ʵ��ɾ�����ĸ����
					delPos = minRight; //���ʵ��ɾ���Ľ��
					break; //ɾ����������Ƚ�㣬�����ƽ������
				}
			}
		}
		if (delParentPos == nullptr) //delParentPosû�б��޸Ĺ���˵��û���ҵ���ɾ�����
		{
			return false;
		}

		//��¼��ɾ����㼰�丸���
		Node* del = delPos;
		Node* delP = delParentPos;

		//����ƽ������
		while (delPos != _root)
		{
			//�ж�ɾ�������ڸ��׵���һ�ߣ�Ȼ�����ƽ������
			if (delPos == delParentPos->_left)
			{
				delParentPos->_bf++;
			}
			else if (delPos == delParentPos->_right)
			{
				delParentPos->_bf--;
			}
			//��ǰ����ƽ��ģ�ֹͣ����
			if (delParentPos->_bf == -1 || delParentPos->_bf == 1)
			{
				break; //delParent���ĸ߶�û�з����仯������Ӱ���丸��㼰���Ͻ���ƽ������
			}
			else if (delParentPos->_bf == 0)//��Ҫ�������ϸ���ƽ������
			{
				//delParentPos���ĸ߶ȱ仯����Ӱ���丸����ƽ�����ӣ���Ҫ�������ϸ���ƽ������
				delPos = delParentPos;
				delParentPos = delParentPos->_parent;
			}

			else if (delParentPos->_bf == -2 || delParentPos->_bf == 2) //��Ҫ������ת����
			{
				if (delParentPos->_bf == -2)//��߸�
				{
					if (delParentPos->_left->_bf == -1)//��߸ߣ������ҵ���
					{
						Node* tmp = delParentPos->_left; //��¼delParentPos����ת���µĸ����
						RotateR(delParentPos); //�ҵ���
						delParentPos = tmp; //���¸����
					}
					else if (delParentPos->_left->_bf == 1)//����Ӱ��,��Ҫ��������˫��
					{
						Node* tmp = delParentPos->_left->_right; //��¼delParentPos������ת���µĸ����
						RotateLR(delParentPos); //����˫��
						delParentPos = tmp; //���¸����
					}
					else //delParentPos->_left->_bf == 0
					{
						Node* tmp = delParentPos->_left; //��¼delParentPos����ת���µĸ����
						RotateR(delParentPos); //�ҵ���
						delParentPos = tmp; //���¸����
						//ƽ�����ӵ���
						delParentPos->_bf = 1;
						delParentPos->_right->_bf = -1;
						break;
					}
				}
				else //delParentPos->_bf == 2
				{
					if (delParentPos->_right->_bf == -1)
					{
						Node* tmp = delParentPos->_right->_left; //��¼delParentPos������ת���µĸ����
						RotateRL(delParentPos); //����˫��
						delParentPos = tmp; //���¸����
					}
					else if (delParentPos->_right->_bf == 1)//����Ӱ��,��Ҫ��������˫��
					{
						Node* tmp = delParentPos->_right; //��¼delParentPos����ת���µĸ����
						RotateL(delParentPos); //����
						delParentPos = tmp; //���¸����
					}
					else //delParentPos->_right->_bf == 0
					{
						Node* tmp = delParentPos->_right; //��¼delParentPos����ת���µĸ����
						RotateL(delParentPos); //����
						delParentPos = tmp; //���¸����
						//ƽ�����ӵ���
						delParentPos->_bf = -1;
						delParentPos->_left->_bf = 1;
						break;
					}
				}
				//�������ϸ���ƽ������
				delPos = delParentPos;
				delParentPos = delParentPos->_parent;
			}
			else
			{
				exit(-1); //���ᵽ���������˵�������˴���
			}
		}
		//����ʵ��ɾ��
		if (del->_left == nullptr) //ʵ��ɾ������������Ϊ��
		{
			if (del == delP->_left) //ʵ��ɾ��������丸��������
			{
				delP->_left = del->_right;
				if (del->_right)
					del->_right->_parent = parent;
			}
			else //ʵ��ɾ��������丸�����Һ���
			{
				delP->_right = del->_right;
				if (del->_right)
					del->_right->_parent = parent;
			}
		}
		else //ʵ��ɾ������������Ϊ��
		{
			if (del == delP->_left) //ʵ��ɾ��������丸��������
			{
				delP->_left = del->_left;
				if (del->_left)
					del->_left->_parent = parent;
			}
			else //ʵ��ɾ��������丸�����Һ���
			{
				delP->_right = del->_left;
				if (del->_left)
					del->_left->_parent = parent;
			}
		}
		delete del; //ʵ��ɾ�����
		return true;
	}

	//������ʱ�� rootΪprivate�����޷��õ�
	//�����Ҫ��װһ��
	void _Inorder(Node* root)
	{
		if (root == nullptr)
			return;
		_Inorder(root->_left);
		cout << root->_kv.first << " ";
		_Inorder(root->_right);
	}
	//�������
	void Inorder()
	{
		_Inorder(_root);
	}

	Node* Find(const K& k)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first > k)
				cur = cur->_left;
			else if (cur->_kv.first < k)
				cur = cur->_right;
			else
				return cur;
		}
		return false;
	}


	//���������
	int maxDepth(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}
		int leftDepth = maxDepth(root->_left);
		int rightDepth = maxDepth(root->_right);
		return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
	}
	bool _isBalanced(Node* root)
	{
		if (root == nullptr)
		{
			return true;
		}
		int leftHight = maxDepth(root->_left);
		int rightHight = maxDepth(root->_right);
		return abs(leftHight - rightHight) < 2
			&& _isBalanced(root->_left)
			&& _isBalanced(root->_right);

	}
	bool isBalanced()
	{
		return _isBalanced(_root);

	}
private:
	Node* _root = nullptr;
};



int main() {
	//func();
	system("pause");
	return 0;
}