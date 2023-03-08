#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int n;
double ans;
struct point
{
    double x,y;
};
point g[10005],s[10005];
double vecmul(point a1,point a2,point b1,point b2)
{
    return (a2.x-a1.x)*(b2.y-b1.y)-(b2.x-b1.x)*(a2.y-a1.y);
}
double abs(point x)
{
    return sqrt(x.x*x.x+x.y*x.y);
}
double dis(point a,point b)
{
    return sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y));
}
bool cmp(const point& p1,const point& p2)
{
    double t=vecmul(g[1],p1,g[1],p2);
    if(t>0)return 1;
    if(t==0&&abs(p1)<abs(p2))return 1;
    return 0;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lf%lf",&g[i].x,&g[i].y);
        if(i!=0&&g[i].y<g[1].y)
        {
            swap(g[1],g[i]);
        }
    }
    sort(g+2,g+n+1,cmp);
    s[1]=g[1];
    int tot=1;
    for(int i=2;i<=n;i++)
    {
        while(tot>1&&vecmul(s[tot-1],s[tot],s[tot],g[i])<=0)--tot;
        s[++tot]=g[i];
    }
    s[tot+1]=g[1];
    for(int i=1;i<=tot;i++) ans+=dis(s[i],s[i+1]);
    printf("%.2lf\n",ans);
}