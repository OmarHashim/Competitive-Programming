/*
   split rectangle into 4 segments and find if any of them intersect the given segment
   dont forget case where the segment is inside the rectangle
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

typedef complex<long double> point;
#define sz(a) ((int)(a).size())
#define all(n) (n).begin(),(n).end()
#define EPS 1e-15
#define OO 1e9
#define X real()
#define Y imag()
#define vec(a,b) ((b)-(a))
#define polar(r,t) ((r)*exp(point(0,(t))))
#define angle(v) (atan2((v).Y,(v).X))
#define length(v) ((long double)hypot((v).Y,(v).X))
#define lengthSqr(v) (dot(v,v))
#define dot(a,b) ((conj(a)*(b)).real())
#define cross(a,b) ((conj(a)*(b)).imag())
#define rotate(v,t) (polar(v,t))
#define rotateabout(v,t,a) (rotate(vec(a,v),t)+(a))
#define reflect(p,m) ((conj((p)/(m)))*(m))
#define normalize(p) ((p)/length(p))
#define same(a,b) (lengthSqr(vec(a,b))<EPS)
#define mid(a,b) (((a)+(b))/point(2,0))
#define perp(a) (point(-(a).Y,(a).X))
#define colliner pointOnLine

bool read(point & p){
	double x,y;
	if(~scanf(" %lf %lf",&x,&y)){
		p=point(x,y);
		return 1;
	}
	return 0;
}

bool eq(long double a,long double b){
	return fabs(a-b)<EPS;
}
bool pointOnSegment(point a,point b,point p){
	// degenrate case already handled
	return eq(length(vec(a,b)),length(vec(a,p))+length(vec(b,p)));
}
bool intersect(point a,point b,point p,point q){
	// if vec=0, cross=0, so degenarate case is already handled
	long double d=cross(vec(a,b),vec(p,q));
	if(eq(d,0))return pointOnSegment(a,b,p)||pointOnSegment(a,b,q)
			||pointOnSegment(p,q,a)||pointOnSegment(p,q,b);
	point r=a+cross(vec(a,p),vec(p,q))/d*(b-a);
	return pointOnSegment(a,b,r)&&pointOnSegment(p,q,r);
}

int n;
int xs,ys,x,y;
point p,q;

int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	int t;
	sc(t);
	while(t--){
		read(p);
		read(q);
		sc(xs),sc(y);
		sc(x),sc(ys);
		if(xs>x)swap(xs,x);
		if(ys>y)swap(ys,y);
		bool ok=0;
		ok|=intersect(point(xs,ys),point(x,ys),p,q);
		ok|=intersect(point(x,y),point(x,ys),p,q);
		ok|=intersect(point(x,y),point(xs,y),p,q);
		ok|=intersect(point(xs,ys),point(xs,y),p,q);
		if(p.X>=xs&&q.X>=xs&&p.X<=x&&q.X<=x
		 &&p.Y>=ys&&q.Y>=ys&&p.Y<=y&&q.Y<=y)ok=1;
		if(ok)puts("T");
		else puts("F");
	}
}
