#include <cassert>

struct SplayTree
{
    struct node;
    typedef node *tree;
    struct node
    {
        tree ch[2], par;
        int size, val, cnt;
        node(int value, tree fa)
        {
            val = value, par = fa;
            size = 1, cnt = 1;
            ch[0] = ch[1] = nullptr;
        }
    } *root;
    SplayTree() { root = nullptr; }
    inline int size(tree x) { return x ? x->size : 0; }
    inline void pushup(tree x)
    {
        if (x)
            x->size = size(x->ch[0]) + size(x->ch[1]) + x->cnt;
    }
    inline void buildfather(tree son, tree par, bool which)
    {
        if (son)
            son->par = par;
        if (par)
            par->ch[which] = son;
        else
            root = son;
    }
    inline bool wson(tree son, tree par)
    {
        if (!par)
            return 0;
        return par->ch[1] == son;
    }
    inline void rotate(tree x)
    {
        tree p = x->par, g = p->par;
        bool r = wson(x, p);
        buildfather(x, g, wson(p, g));
        buildfather(x->ch[!r], p, r);
        buildfather(p, x, !r);
        pushup(p);
    }
    inline void Splay(tree x, tree y)
    {
        while (x->par != y)
        {
            tree p = x->par, g = p->par;
            if (x->par->par != y)
                wson(x, p) ^ wson(p, g) ? rotate(x) : rotate(p);
            rotate(x);
        }
        pushup(x);
    }
    inline void insert(int val)
    {
        if (!root)
        {
            root = new node(val, nullptr);
            return;
        }
        for (tree x = root; x; x = x->ch[val >= x->val])
        {
            if (x->val == val)
            {
                x->cnt++;
                Splay(x, nullptr);
                return;
            }
            if (!x->ch[val >= x->val])
            {
                x->ch[val >= x->val] = new node(val, x);
                Splay(x->ch[val >= x->val], nullptr);
                return;
            }
        }
    }
    inline void find(int val)
    {
        tree x = root;
        while (x && x->ch[val > x->val] && val != x->val)
            x = x->ch[val > x->val];
        if (x)
            Splay(x, nullptr);
    }
    inline int findkth(int k)
    {
        tree x = root;
        assert(size(x) >= k);
        assert(k);
        while (x)
        {
            if (size(x->ch[0]) + x->cnt >= k && size(x->ch[0]) < k)
                return x->val;
            if (size(x->ch[0]) >= k)
                x = x->ch[0];
            else
                k -= size(x->ch[0]) + x->cnt, x = x->ch[1];
        }
        return -2147483647;
    }
    inline void del(int val)
    {
        find(val);
        if (root->val != val)
            return;
        tree x = root;
        if (x->cnt > 1)
            x->cnt--;
        else if (!x->ch[0])
        {
            root = x->ch[1];
            if (root)
                root->par = nullptr;
            delete x;
        }
        else
        {
            tree k = x->ch[0];
            while (k->ch[1])
                k = k->ch[1];
            Splay(k, x);
            root = k, root->par = nullptr;
            buildfather(x->ch[1], root, 1);
            delete x;
        }
    }
    inline int pre(int val)
    {
        insert(val);
        tree x = root->ch[0];
        while (x->ch[1])
            x = x->ch[1];
        del(val);
        return x->val;
    }
    inline int nxt(int val)
    {
        insert(val);
        tree x = root->ch[1];
        while (x->ch[0])
            x = x->ch[0];
        del(val);
        return x->val;
    }
};