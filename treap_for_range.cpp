#include<cstdio>
#include<algorithm>

struct Node
{
    int val,size=1,pri=rand();
    bool rev=0;
    Node *lc=nullptr,*rc=nullptr;

    explicit Node(int v):
        val(v)
    {}

    void push_down()
    {
        if(!rev)return;
        if(lc)lc->rev^=1;
        if(rc)rc->rev^=1;
        rev=0;
        std::swap(lc,rc);
    }
    void maintain()
    {
        size=1;
        if(lc)size+=lc->size;
        if(rc)size+=rc->size;
    }
};

Node *root=nullptr;

Node *merge(Node *l,Node *r)
{
    if(!l)return r;
    if(!r)return l;
    if(l->pri<r->pri)
    {
        l->push_down();
        l->rc=merge(l->rc,r);
        l->maintain();
        return l;
    }
    else
    {
        r->push_down();
        r->lc=merge(l,r->lc);
        r->maintain();
        return r;
    }
}

void split(Node *rt,int k,Node *&l,Node *&r)
{
    if(!rt)
    {
        l=r=nullptr;
        return;
    }
    rt->push_down();
    int s=0;
    if(rt->lc)s=rt->lc->size;
    if(s+1<k)
    {
        l=rt;
        split(l->rc,k-s-1,l->rc,r);
    }
    else
    {
        r=rt;
        split(r->lc,k,l,r->lc);
    }
    rt->maintain();
}

void reverse(int l,int r)
{
    Node *p1,*p2,*p3;
    split(root,r+1,p2,p3);
    split(p2,l,p1,p2);
    p2->rev^=1;
    root=merge(merge(p1,p2),p3);
}

void dfs(Node *p)
{
    if(!p)return;
    p->push_down();
    dfs(p->lc);
    printf("%d ",p->val);
    dfs(p->rc);
}

int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    while(n--)
    {
        root=merge(new Node(n+1),root);
    }
    while(m--)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        reverse(l,r);
    }
    dfs(root);
}
