//TLE
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
#define EPS 1e-9
#define OO 1e9
#define X real()
#define Y imag()
#define vec(a,b) ((b)-(a))
#define polar(r,t) ((r)*exp(point(0,(t))))
#define angle(v) (atan2((v).Y,(v).X))
#define length(v) ((long double)hypot((v).Y,(v).X))
#define length2(v) (sqrt(v.X*v.X+v.Y*v.Y))
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
const long double PI=acos(-1.0);

bool read(point & p){
	double x,y;
	if(~scanf(" %lf %lf",&x,&y)){
		p=point(x,y);
		return 1;
	}
	return 0;
}
const int N=5010;
int n,m;
point arr[N];
point p;
inline long double fix(long double v){
	if(v<-1)return -1;
	if(v>1)return 1;
	return v;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	sc(n);
	lop(i,n)read(arr[i]);
	sc(m);
	lop(i,m){
		read(p);
		long double out=0;
		bool any=0;
		lop(i,n){
			point a=arr[i];
			point b=(i==n-1?arr[0]:arr[i+1]);
			point ab=vec(a,b);
			point pa=vec(p,a);
			point pb=vec(p,b);
			long double lpa=length(pa);
			long double lpb=length(pb);
				if(fabs(length(ab)-lpa-lpb)<EPS){
					any=1;
					break;
				}
			pa=pa/lpa;
			pb=pb/lpb;
			point con=conj(pa)*(pb);
			long double theta=acos(fix(con.X)); // dot product
			if(con.Y>=0)out+=theta; // cross product
			else out-=theta;
		}
		if(any)puts("EDGE");
		else printf("%d\n",int(out/(2*PI)));
	}
}
