#include <cstdio>
#include <vector>
#include <algorithm>

struct Node
{
    int sum;
    Node *lc;
    Node *rc;
    static int _sum(Node *ptr) { return ptr == NULL ? 0 : ptr->sum; }
    Node(int s = 0) : sum(s), lc(NULL), rc(NULL) {}
};

std::vector<Node *> Root;

Node *build(int l, int r)
{
    Node *ptr = new Node;
    if (l >= r)
        return ptr;
    int mid = (l + r) >> 1;
    ptr->lc = build(l, mid);
    ptr->rc = build(mid + 1, r);
    return ptr;
}

Node *modify(int l, int r, int x, Node *nroot)
{
    Node *ptr = new Node(Node::_sum(nroot) + 1);
    ptr->lc = nroot->lc;
    ptr->rc = nroot->rc;
    if (l >= r)
        return ptr;
    int mid = (l + r) >> 1;
    if (x <= mid)
        ptr->lc = modify(l, mid, x, nroot->lc);
    else
        ptr->rc = modify(mid + 1, r, x, nroot->rc);
    return ptr;
}

int query(int l, int r, int q, Node *nl, Node *nr)
{
    if (l >= r)
        return l;
    int x = Node::_sum(nr->lc) - Node::_sum(nl->lc);
    int mid = (l + r) >> 1;
    if (q <= x)
        return query(l, mid, q, nl->lc, nr->lc);
    else
        return query(mid + 1, r, q - x, nl->rc, nr->rc);
}

int a[200050], b[200050];
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", a + i), b[i] = a[i];
    std::sort(b + 1, b + n + 1);
    int len = std::unique(b + 1, b + n + 1) - b - 1;
    Root.push_back(nullptr);
    Root[0] = build(1, len);
    for (int i = 1; i <= n; ++i)
    {
        int p = std::lower_bound(b + 1, b + len + 1, a[i]) - b;
        Root.push_back(modify(1, len, p, Root[i - 1]));
    }
    for (int i = 0; i < m; ++i)
    {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        int ans = query(1, len, k, Root[l - 1], Root[r]);
        printf("%d\n", b[ans]);
    }
}