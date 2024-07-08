#include<iostream>
using namespace std;

struct BSTreeNode
{
    BSTreeNode* lchild_; //left child;
    BSTreeNode* rchild_; //right child;
    int key_;              //key
    int value_;            //value

    BSTreeNode(const int& key, const int& value) //init
        :lchild_(NULL)
        , rchild_(NULL)
        , key_(key)
        , value_(value)
    {}

};



class BSTree
{
    typedef BSTreeNode Node;

public:
    BSTree()
        :root_(NULL)
    {}

    //BST Find
    Node* Find(const int& key)
    {
        return Find_(root_, key);
    }

    Node* Find_(Node* root, const int& key)
    {
        if (root == NULL)
        {
            return NULL;
        }

        if (root->key_ > key) //find in leftchild
        {
            return Find_(root->lchild_, key);
        }
        else if (root->key_ < key)//find in rightchild
        {
            return Find_(root->rchild_, key);
        }
        else
        {
            return root;
        }
    }



    //BST Insert
    //Find the node and Insert
    bool Insert(const int& key, const int& value)
    {
        return Insert_(root_, key, value);
    }

    bool Insert_(Node*& root, const int& key, const int& value)
    {
        if (root == NULL)
        {
            root = new Node(key, value);
            return true;
        }

        if (root->key_ > key)
        {
            return Insert_(root->lchild_, key, value);
        }
        else if (root->key_ < key)
        {
            return Insert_(root->rchild_, key, value);
        }
        else
        {
            return false;
        }
    }



    //BST remove
    bool Remove(const int& key)
    {
        return Remove_(root_, key);
    }

    bool Remove_(Node*& root, const int& key)
    {
        //There is no such node
        if (root == NULL)
        {
            return false;
        }
        //only one node
        if (root->lchild_ == NULL && root->rchild_ == NULL)
        {
            if (root->key_ == key)
            {
                delete root;
                root = NULL;
                return true;
            }
            else
            {
                return false;
            }

        }


        if (root->key_ > key)
        {
            Remove_(root->lchild_, key);
        }
        else if (root->key_ < key)
        {
            Remove_(root->rchild_, key);
        }
        else
        {
            Node* del = NULL;

            if (root->lchild_ == NULL)      //just has rightchild
            {
                del = root;
                root = root->rchild_;
                delete del;
                del = NULL;
                return true;
            }
            else if (root->rchild_ == NULL) //just has leftchild
            {
                del = root;
                root = root->lchild_;
                delete del;
                del = NULL;
                return true;
            }
            else
            {
                Node* RightFirst = root->rchild_;
                //find the first In order node
                while (RightFirst->lchild_)
                {
                    RightFirst = RightFirst->lchild_;
                }

                //swap RightFirst node with cur node
                swap(root->key_, RightFirst->key_);
                swap(root->value_, RightFirst->value_);


                Remove_(root->rchild_, key);
                return true;
            }
        }
    }


    //BST print In Order
    void Output()
    {
        Output_(root_);
        cout << endl;
    }

    void Output_(Node* root)
    {
        if (root == NULL)
        {
            return;
        }

        Output_(root->lchild_);
        cout << root->key_ << " ";
        Output_(root->rchild_);
    }


    Node* self()
    {
        return root_;
    }

private:
    Node* root_;
};


void Test()
{
    BSTree  s;

    //测试插入
    s.Insert(5, 1);
    s.Insert(4, 1);
    s.Insert(3, 1);
    s.Insert(6, 1);
    s.Insert(1, 1);
    s.Insert(2, 1);
    s.Insert(0, 1);
    s.Insert(9, 1);
    s.Insert(8, 1);
    s.Insert(7, 1);

    //二叉搜索树按中序输出是有序的
    s.Output();

    //测试查找
    cout << s.Find(6)->key_ << endl;

    //测试删除
    s.Remove(4);
    s.Remove(6);
    s.Remove(3);
    s.Remove(1);
    s.Remove(2);

    //再次打印删除后的结果
    s.Output();

}

int main()
{
    Test();
    return 0;
}