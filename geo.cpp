#include<cmath>
#include<algorithm>

constexpr double eps=1e-10;
constexpr int N=1e6;

struct Vector{double x,y;};
using Point=Vector;

bool operator == (const Vector &a, const Vector &b){return !(dcmp(a.x-b.x)&&dcmp(a.y-b.y));}
Vector operator + (const Vector &a,const Vector &b){return {a.x+b.x,a.y+b.y};}
Vector operator - (const Vector &a,const Vector &b){return {a.x-b.x,a.y-b.y};}
template<typename T>
Vector operator * (const Vector &a,const T& b){return {a.x*b,a.y*b};}
template<typename T>
Vector operator / (const Vector &a,const T& b){return {a.x/b,a.y/b};}
double Dot(Vector a,Vector b){return a.x*b.x+a.y*b.y;}
double Length(Vector x){return sqrt(x.x*x.x+x.y*x.y);}
double Cross(Vector x,Vector y){return x.x*y.y-x.y*y.x;}

inline int dcmp(double val){
	if(fabs(val) < eps)return 0;
	else return val > 0 ? 1 : -1;
}

double DisTS(Point P,Point A,Point B){ //Distance_to_Segment
	if(A==B)return Length(P-A);
	Vector V1=B-A,V2=P-A,V3=P-B;
	if(dcmp(Dot(V1,V2))<0) return Length(V2);
	else if(dcmp(Dot(V1,V3))>0) return Length(V3);
	else return fabs(Cross(V1,V2)/Length(V1));
}

inline int ConvexHull(Point A[],int n,Point Ans[]){
	std::sort(A+1,A+n+1);
	int cnt=0;
	for(int i=1;i<=n;++i){
		while(cnt>1 && Cross(Ans[cnt]-Ans[cnt-1],A[i]-Ans[cnt-1])<=0)cnt--;
		Ans[++cnt]=A[i];
	}
	int k=cnt;
	for(int i=n-1;i>=1;--i){
		while(cnt>k && Cross(Ans[cnt]-Ans[cnt-1],A[i]-Ans[cnt-1])<=0)cnt--;
		Ans[++cnt]=A[i];
	}
	return cnt-1;
}

inline double Rotating_Calipers(Point A[],int n,Point Poly[]){
	n=ConvexHull(A,n,Poly);
	Poly[n+1]=Poly[1];
	double ans=0;
	for(int u=1,v=2;u<=n;u++){
		while(true){
			int val=dcmp(Cross(Poly[u+1]-Poly[u],Poly[v+1]-Poly[v]));
			if(val<=0){
				ans=std::max(ans,Length(Poly[u]-Poly[v]));
				if(!val)ans=std::max(ans,Length(Poly[u]-Poly[v+1]));
				break;
			}
			v=v%n+1;
		}
	}
	return ans;
}

inline double area(Point a,Point b,Point c){return fabs(Cross(b-a,c-a));}

struct Line{
	Point P;Vector V;double ang;
	Line(Point a=Point(0,0),Vector b=Vector(0,0)):P(a),V(b){ang=atan2(V.y,V.x);}//极角
	bool operator < (const Line &rhs) const {return ang<rhs.ang;}
};
bool operator < (const Line &a,const Line &b){return a.ang<b.ang;}
inline Point LI(Line a,Line b)
{
	Vector V=a.P-b.P;
	return a.P+a.V*(Cross(b.V,V)/Cross(a.V,b.V));
}

inline bool OnLeft(Line a,Point b){return Cross(b-a.P,a.V)<0;}
int HpI(Line L[],int n,Point Poly[]){
	std::sort(L+1,L+n+1);
	int f,l;
	static Point p[N];static Line q[N];
	q[f=l=1]=L[1];
	for(int i=2;i<=n;++i){
		while(f<l && !OnLeft(L[i],p[l-1]))l--;//如果原来的交点在新加入直线的右边，就没用了。
		while(f<l && !OnLeft(L[i],p[f]))f++;
		q[++l]=L[i];
		if(!dcmp(Cross(q[l].V,q[l-1].V))){//与上一条直线极角相同
			l--;
			if(OnLeft(q[l],L[i].P))q[l]=L[i];
		}
		if(f<l)p[l-1]=LI(q[l],q[l-1]);//新的交点
	}
	while(f<l && !OnLeft(q[f],p[l-1]))l--;
	if(l-f<=1)return 0;
	p[l]=LI(q[l],q[f]);
	int cnt=0;
	for(int i=f;i<=l;i++)Poly[++cnt]=p[i];
	return cnt;
}





inline double sqr(double x){return x*x;}
inline double dist(Point x,Point y)
{
	return sqrt(sqr(y.x-x.x)+sqr(y.y-x.y));
}
Point Center(Point a,Point b,Point c)
{
	double a1=b.x-a.x,b1=b.y-a.y,c1=(sqr(a1)+sqr(b1))/2;
	double a2=c.x-a.x,b2=c.y-a.y,c2=(sqr(a2)+sqr(b2))/2;
	double d=a1*b2-a2*b1;
	return Point{a.x+(c1*b2-c2*b1)/d,a.y+(a1*c2-a2*c1)/d};
}
inline std::pair<Point,double> MCC(Point p[],int n)
{
	std::random_shuffle(p,p+n);
	Point c=p[0];
	double r=0;
	for(int i=1;i<n;++i)
		if(dist(p[i],c)>r+eps)
		{
			c=p[i],r=0;
			for(int j=0;j<i;++j)
				if(dist(p[j],c)>r+eps)
				{
					c=(p[i]+p[j])/2,r=dist(p[j],c);
					for(int k=0;k<j;++k)
						if(dist(p[k],c)>r+eps)
							c=Center(p[i],p[j],p[k]),r=dist(p[j],c);
				}
		}
	return {c,r};
}