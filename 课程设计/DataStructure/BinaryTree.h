#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
using namespace std;

template <typename Comparable>
class BinarySearchTree
{
public:
    BinarySearchTree() : root(nullptr) {}
    BinarySearchTree(const BinarySearchTree& rhs) : root(rhs) {}
    ~BinarySearchTree()
    {
        makeEmpty(root);
    }

    const Comparable& findMin() const            //��ѯ������СԪ��
    {
        return findMin(root)->element;
    }
    const Comparable& findMax() const            //��ѯ�������Ԫ��
    {
        return findMax(root)->element;
    }
    bool contains(const Comparable& x) const     //�ж������Ƿ������֪Ԫ��
    {
        contains(x, root);
    }
    bool isEmpty() const      //�ж����Ƿ�Ϊ��
    {
        return root == nullptr;
    }

    int depth()               //�����������㷨
    {
        return depth(root);
    }
    int nodecount()           //��������������㷨
    {
        return nodecount(root);
    }
    int leafcount()           //�������Ҷ�ӽڵ�����㷨
    {
        return leafcount(root);
    }

    void creatTree(istream& in)   //����
    {
        creatTree(root, in);
    }
    void printTree(ostream& out)  //�������
    {
        if (root == nullptr)
        {
            out << "empty tree";
        }
        else
        {
            printTree(root, out);
        }
     
    }
    

    void makeEmpty()             //�����������Ԫ��
    {
        if (root == nullptr)
        {
            cout << "empty tree";
        }
        else
        {
            makeEmpty(root);
            root = nullptr;
        }
    }
    void insert(const Comparable& x)     //�����в���ָ��Ԫ��
    {
        insert(x, root);
    }
    void remove(const Comparable& x)     //ɾ������ָ��Ԫ��
    {
        remove(x, root);
    }

    //���ֱ��������������,����ʵ���������ܿ����뺯��ָ��ʵ��

    void pre_order() //ǰ�����
    {
        pre_order(root);
    }
    void in_order() //�������
    {
        in_order(root);
    }
    void post_order() //�������
    {
        post_order(root);
    }

    const BinarySearchTree& operator=(const BinarySearchTree& rhs)
    {
        if (this != &rhs)
        {
            makeEmpty();
            root = clone(rhs.root);
        }
        return *this;
    }

    //������������������

    friend istream& operator>>(istream& in, BinarySearchTree<Comparable>& rhs)
    {
        rhs.creatTree(in);
        return in;
    }
    friend ostream& operator<<(ostream& out, BinarySearchTree<Comparable>& rhs)
    {
        rhs.printTree(out);
        return out;
    }

private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(const Comparable& theElement, BinaryNode* lt, BinaryNode* rt)
            : element(theElement), left(lt), right(rt) {}
    };

    BinaryNode* root;

    void insert(const Comparable& x, BinaryNode*& t) const
    {
        if (t == nullptr)
        {
            t = new BinaryNode(x, nullptr, nullptr);
        }
        else if (x < t->element)
        {
            insert(x, t->left);
        }
        else if (x > t->element)
        {
            insert(x, t->right);
        }
    }
    void remove(const Comparable& x, BinaryNode*& t) const
    {
        if (t == nullptr)
        {
            cout << "NULL";
        }
        else if (x < t->element)
        {
            remove(x, t->left);
        }
        else if (x > t->element)
        {
            remove(x, t->right);
        }
        else if (t->left != nullptr && t->right != nullptr)
        {
            t->element = findMin(t->right)->element;
            romove(t->element, t->right);
        }
        else
        {
            BinaryNode* OldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete OldNode;
        }
    }
    BinaryNode* findMin(BinaryNode* t) const
    {
        if (t == nullptr)
        {
            return 0;
        }
        else if (t->left == nullptr)
        {
            return t;
        }
        return findMin(t->left);
    }
    BinaryNode* findMax(BinaryNode* t) const
    {
        if (t == nullptr)
        {
            return 0;
        }
        else if (t->right == nullptr)
        {
            return t;
        }
        return findMax(t->right);
    }
    bool contains(const Comparable& x, BinaryNode* t) const
    {
        if (t == nullptr)
        {
            return false;
        }
        else if (x < t->element)
        {
            contains(x, t->left);
        }
        else if (x > t->element)
        {
            contains(x, x->right);
        }
        else
        {
            return true;
        }
    }
    void makeEmpty(BinaryNode*& t)
    {
        if(t!=nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
    }

    int depth(BinaryNode*& t)
    {
        if (t == nullptr)
            return 0;

        int depth_l = depth(t->left);
        int depth_r = depth(t->right);

        return depth_l > depth_r ? depth_l + 1 : depth_r + 1;
    }
    int nodecount(BinaryNode*& t)
    {
        if (t == nullptr)
            return 0;

        int count_l = nodecount(t->left);
        int count_r = nodecount(t->right);

        return 1 + count_l + count_r;

    }
    int leafcount(BinaryNode*& t)
    {
        if (t == nullptr)
            return 0;
        else if (t->left == 0 && t->right == 0)
            return 1;

        return leafcount(t->right) + leafcount(t->left);
    }

    void creatTree(BinaryNode* t, istream& in)
    {
        Comparable stop, item;

        cout << "�������������һ��Ԫ��" << endl;
        in >> stop;
        cout << "����������Ԫ��" << endl;
        in >> item;
        while (item != stop)
        {
            insert(item);
            cout << "����������Ԫ��" << endl;
            in >> item;
        }
        insert(stop);
    }
    void printTree(BinaryNode* t, ostream& out)
    {
        if (t != nullptr)
        {
            out << (t->element) << " ";
            printTree(t->right, out);
            printTree(t->left, out);
        }
    }

    BinaryNode* clone(BinaryNode* t) const
    {
        if (t == nullptr)
        {
            return nullptr;
        }
        else
        {
            return BinaryNode(t->element, clone(t->left), clone(t - right));
        }
    }

    void pre_order(BinaryNode* t) //ǰ�����
    {
        if (t != nullptr)
        {
            cout << t->element << " ";
            pre_order(t->left);
            pre_order(t->right);
        }
    }
    void in_order(BinaryNode* t) //�������
    {
        if (t != nullptr)
        {
            in_order(t->left);
            cout << t->element << " ";
            in_order(t->right);
        }
    }
    void post_order(BinaryNode* t) //�������
    {
        if (t != nullptr)
        {
            post_order(t->left);
            post_order(t->right);
            cout << t->element << " ";
        }
    }
};



#endif 
