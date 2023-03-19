namespace LCT
{
#define ls(x) (c[x][0])
#define rs(x) (c[x][1])
#define s(x, k) (c[x][k])
    int val[N], f[N], siz[N], si[N];
    long long siz2[N], si2[N]; // si 轻儿子
    int c[N][2];
    inline long long sqr(int x) { return 1ll * x * x; }
    inline bool ws(int x, int p) { return ls(p) ^ x; }
    inline bool nroot(int x) { return ls(f[x]) == x || rs(f[x]) == x; }

    inline void pushup(int x)
    {
        siz[x] = siz[ls(x)] + siz[rs(x)] + si[x] + 1;
        siz2[x] = sqr(siz[ls(x)]) + sqr(siz[rs(x)]) + si2[x];
    }

    inline void rotate(int x)
    {
        int p = f[x], g = f[p];
        int t = ws(x, p), w = s(x, !t);
        if (nroot(p))
            s(g, ws(p, g)) = x;
        s(x, !t) = p;
        s(p, t) = w;
        if (w)
            f[w] = p;
        f[p] = x;
        f[x] = g;
        pushup(p);
    }
    inline void Splay(int x)
    {
        while (nroot(x))
        {
            int p = f[x], g = f[p];
            if (nroot(p))
                rotate(ws(x, p) ^ ws(p, g) ? x : p);
            rotate(x);
        }
        pushup(x);
    }
    inline void access(int x)
    {
        for (int y = 0; x; x = f[y = x])
            Splay(x), si[x] += siz[rs(x)] - siz[y], si2[x] += sqr(siz[rs(x)]) - sqr(siz[y]), rs(x) = y, pushup(x);
    }
    inline int findroot(int x)
    {
        access(x), Splay(x);
        while (ls(x))
            x = ls(x);
        return Splay(x), x;
    }
    inline void link(int u, int v)
    {
        access(v), Splay(v);
        Splay(u);
        si[v] += siz[u], si2[v] += sqr(siz[u]);
        pushup(f[u] = v);
    }
    inline void cut(int u, int v)
    {
        access(v), Splay(v);
        Splay(u);
        si[v] -= siz[u], si2[v] -= sqr(siz[u]), f[u] = 0;
        pushup(v);
    }
}
using namespace LCT;