#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
enum nodeType // node types
{
    nil,
    leaf,
    twonode,
    threenode
};

template <class T>
struct two3node
{
public:
    nodeType type;
    T val;        // only for leaf node--holds value
    T val1, val2; // it is min1, min2
    two3node<T> *left, *mid, *right;
};

template <class T>
two3node<T> *newnilnode(T zero)
{
    two3node<T> *node = new two3node<T>;
    node->val = node->val1 = node->val2 = 0;
    node->type = nil;
    node->left = node->mid = node->right = NULL;
    return node;
}

template <class T>
two3node<T> *newleaf(T val)
{
    two3node<T> *node = new two3node<T>;
    node->type = leaf;
    node->val = val;
    node->val1 = node->val2 = 0;
    node->left = node->mid = node->right = NULL;
    return node;
}

template <class T>
two3node<T> *newtwonode(T val, two3node<T> *left, two3node<T> *right)
{
    two3node<T> *node = new two3node<T>;
    node->type = twonode;
    node->val1 = val;
    node->val = node->val2 = 1000;
    node->left = left;
    node->mid = NULL;
    node->right = right;
    return node;
}

template <class T>
two3node<T> *newthreenode(T val1, T MinRight, two3node<T> *left, two3node<T> *mid, two3node<T> *right)
{
    two3node<T> *node = new two3node<T>;
    node->type = threenode;
    node->val1 = val1;
    node->val2 = MinRight;
    node->val = 0;
    node->left = left;
    node->mid = mid;
    node->right = right;
    return node;
}

template <class T>
class TwoThreeTree
{
public:
    two3node<T> *root;
    two3node<T> *nilnodespl; // acts as special node of type nil in the following functions
    int count = 0;
    class insrtn
    {
    public:
        T val;
        two3node<T> *n1;
        two3node<T> *n2;
        insrtn(two3node<T> *nd1, two3node<T> *nd2, T v)
        {
            n1 = nd1;
            n2 = nd2;
            val = v;
        }
    };

public:
    TwoThreeTree()
    {
        root = newnilnode(0);
        nilnodespl = newnilnode(0);
    }
    ~TwoThreeTree()
    {
        delete root;
    }
    void InsertRoot(T val)
    {
        count++;
        if (root->type == nil)
        {
            // cout << "a00";
            root = newleaf(val);
        }
        else if (root->type == leaf)
        {
            if (root->val > val)
            {
                root = newtwonode(root->val, newleaf(val), root);
                // cout << "a11";
            }
            else if (root->val < val)
            {
                root = newtwonode(val, root, newleaf(val));
                // cout << "a12";
            }
        }
        else
        {
            insrtn rtn = Insert(root, val);
            if (rtn.n2->type == nil)
            {
                root = rtn.n1;
            }
            else
            {
                root = newtwonode(rtn.val, rtn.n1, rtn.n2);
            }
        }
        return;
    }
    insrtn Insert(two3node<T> *&n, T &val)
    {
        // cout << "INS";
        if (n->type == leaf)
        {
            if (n->val == val)
            {
                // cout << "b11";
                return insrtn(n, nilnodespl, 0);
            }
            else if (n->val > val)
            {
                // cout << "b12";
                return insrtn(newleaf(val), n, n->val);
            }
            else if (n->val < val)
            {
                // cout << "b13";
                return insrtn(n, newleaf(val), val);
            }
        }
        else if (n->type == twonode)
        {
            if (val < n->val1)
            {
                insrtn rt = Insert((n->left), val);
                if (rt.n2->type == nil)
                {
                    // cout << "b21";
                    return insrtn(newtwonode(n->val1, rt.n1, n->right), nilnodespl, 0);
                }
                else
                {
                    // cout << "b22";
                    return insrtn(newthreenode(rt.val, n->val1, rt.n1, rt.n2, n->right), nilnodespl, 0);
                }
            }
            else if (val >= n->val1)
            {
                insrtn rt = Insert((n->right), val);
                if (rt.n2->type == nil)
                {
                    // cout << "b23";
                    return insrtn(newtwonode(n->val1, n->left, rt.n1), nilnodespl, 0);
                }
                else
                {
                    // cout << "b24";
                    return insrtn(newthreenode(n->val1, rt.val, n->left, rt.n1, rt.n2), nilnodespl, 0);
                }
            }
        }
        else if (n->type == threenode)
        {
            if (val < n->val1)
            {
                insrtn rt = Insert((n->left), val);
                if (rt.n2->type == nil)
                {
                    // cout << "b31";
                    return insrtn(newthreenode(n->val1, n->val2, rt.n1, n->mid, n->right), nilnodespl, 0);
                }
                else
                {
                    // cout << "b32";
                    return insrtn(newtwonode(rt.val, rt.n1, rt.n2), newtwonode(n->val2, n->mid, n->right), n->val1);
                }
            }
            else if (val >= n->val1 && val < n->val2)
            {
                insrtn rt = Insert((n->mid), val);
                if (rt.n2->type == nil)
                {
                    // cout << "b33";
                    return insrtn(newthreenode(n->val1, n->val2, n->left, rt.n1, n->right), nilnodespl, 0);
                }
                else
                {
                    // cout << "b34";
                    return insrtn(newtwonode(n->val1, n->left, rt.n1), newtwonode(n->val2, rt.n2, n->right), rt.val);
                }
            }
            else if (val >= n->val2)
            {
                insrtn rt = Insert((n->right), val);
                if (rt.n2->type == nil)
                {
                    // cout << "b35";
                    return insrtn(newthreenode(n->val1, n->val2, n->left, n->mid, rt.n1), nilnodespl, 0);
                }
                else
                {
                    // cout << "b36";
                    return insrtn(newtwonode(n->val1, n->left, n->mid), newtwonode(rt.val, rt.n1, rt.n2), n->val2);
                }
            }
        }
        return insrtn(nilnodespl, nilnodespl, 0);
    }
    insrtn InsertRightNode(two3node<T> *r1, two3node<T> *r2, int h1, int h2, int min2)
    {
        if (h1 == h2)
        {
            return insrtn(r1, r2, min2);
        }
        insrtn rn = InsertRightNode(r1->right, r2, h1 - 1, h2, min2);
        if (rn.n2->type == nil)
        {
            r1->right = rn.n1;
            return insrtn(r1, nilnodespl, 0);
        }
        else
        {
            if (r1->type == twonode)
            {
                return insrtn(newthreenode(r1->val1, rn.val, r1->left, rn.n1, rn.n2), nilnodespl, 0);
            }
            else if (r1->type == threenode)
            {
                return insrtn(newtwonode(r1->val1, r1->left, r1->mid), newtwonode(rn.val, rn.n1, rn.n2), r1->val2);
            }
        }
        return insrtn(nilnodespl, nilnodespl, 0);
    }
    insrtn InsertLeftNode(two3node<T> *r1, two3node<T> *r2, int h1, int h2, int min2)
    {
        if (h1 == h2)
        {
            return insrtn(r1, r2, min2);
        }
        insrtn rn = InsertLeftNode(r1, r2->left, h1, h2 - 1, min2);
        if (rn.n2->type == nil)
        {
            r2->left = rn.n1;
            return insrtn(r2, nilnodespl, 0);
        }
        else
        {
            if (r2->type == twonode)
            {
                return insrtn(newthreenode(rn.val, r2->val1, rn.n1, rn.n2, r2->right), nilnodespl, 0);
            }
            else if (r2->type == threenode)
            {
                return insrtn(newtwonode(rn.val, rn.n1, rn.n2), newtwonode(r2->val2, r2->mid, r2->right), r2->val1);
            }
        }
        return insrtn(nilnodespl, nilnodespl, 0);
    }
    void Merge(TwoThreeTree<T> S1, TwoThreeTree<T> S2)
    {
        count = S1.count + S2.count;
        int h1 = 0, h2 = 0;        // heights of tree
        int min1, min2;            // mimimum of both trees
        two3node<T> *yo = S1.root; // dummy pointer to to find height and min
        if (S1.root->type == nil)  // when S1 is empty tree
        {
            root = S2.root;
            return;
        }
        if (S2.root->type == nil) // when S2 is empty tree
        {
            root = S1.root;
            return;
        }
        while (yo->type != leaf)
        {
            yo = yo->left;
            h1++;
        }
        min1 = yo->val;
        yo = S2.root;
        while (yo->type != leaf)
        {
            yo = yo->left;
            h2++;
        }
        min2 = yo->val;
        // cout << min1 << ' ' << min2;
        if (h1 == h2)
        {
            root = newtwonode(min2, S1.root, S2.root);
            return;
        }
        if (h1 > h2) // insert S2 inside S1
        {
            insrtn rn = InsertRightNode(S1.root, S2.root, h1, h2, min2);
            if (rn.n2->type == nil)
            {
                root = rn.n1;
            }
            else
            {
                root = newtwonode(rn.val, rn.n1, rn.n2);
            }
        }
        else if (h1 < h2)
        {
            insrtn rn = InsertLeftNode(S1.root, S2.root, h1, h2, min2);
            if (rn.n2->type == nil)
            {
                root = rn.n1;
            }
            else
            {
                root = newtwonode(rn.val, rn.n1, rn.n2);
            }
        }
    }
    void Extract() // prints elements left to right in O(n) time using queue
    {
        two3node<T> *A[count + 1];
        two3node<T> *temp;
        int f = 0, r = 0;
        A[r] = root;
        r = 1;
        for (int i = 0;; i++)
        {
            temp = A[f];
            if (temp->type == twonode || temp->type == threenode)
            {
                A[r] = temp->left;
                r = (r + 1) % (count + 1);
                if (temp->mid != NULL)
                {
                    A[r] = temp->mid;
                    r = (r + 1) % (count + 1);
                }
                A[r] = temp->right;
                r = (r + 1) % (count + 1);
            }
            else if (temp->type == leaf)
            {
                cout << '|' << temp->val;
            }
            f = (f + 1) % (count + 1);
            if (f == r)
            {
                break;
            }
        }
    }
};
int main()
{
    TwoThreeTree<int> S1, S2, S;
    int p;
    for (int i = 1; i < 90; i++)
    {
        S1.InsertRoot(rand() % 100);
    }
    for (int i = 100; i < 200; i++)
    {
        S2.InsertRoot(100 + rand() % 100);
    }
    S.Merge(S1, S2);
    S.Extract();
    return 0;
};
