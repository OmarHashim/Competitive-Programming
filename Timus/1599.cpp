//WA
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
const double PI=acos(-1.0);

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
bool pointOnLine(const point& a, const point& b, const point& p) {
	return fabs(cross(vec(a,b),vec(a,p))) < EPS;
}
bool pointOnSegment(point a,point b,point p){
	return eq(length(vec(a,b)),length(vec(a,p))+length(vec(b,p)));
}

const int N=5010;
int n,m;
point arr[N];
point p;

int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	sc(n);
	lop(i,n)read(arr[i]);
	sc(m);
	lop(i,m){
		read(p);
		double out=0;
		bool any=0;
		lop(i,n){
			point a=arr[i];
			point b=arr[(i+1)%n];
			if(pointOnSegment(a,b,p)){
				any=1;
				continue;
			}
			if(pointOnLine(a,b,p))continue;
			point pa=normalize(vec(p,a));
			point pb=normalize(vec(p,b));
			double theta=acos(dot(pa,pb));
			if(cross(pa,pb)>=0)out+=theta;
			else out-=theta;
		}
		if(any)puts("EDGE");
		else cout<<int(out/(2*PI))<<endl;
	}


}
