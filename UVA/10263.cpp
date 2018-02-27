/*
   check best point on every segment and minimize answer
   
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

bool read(point & p){
	double x,y;
	if(~scanf(" %lf %lf",&x,&y)){
		p=point(x,y);
		return 1;
	}
	return 0;
}
point m,res;
int n;
void check(point a){
	if(length(vec(a,m))<length(vec(res,m)))res=a;
}
void solve(point a,point b,point p){
	point ab=vec(a,b);
	point ap=vec(a,p);
	point ba=vec(b,a);
	point bp=vec(b,p);
	if(dot(ab,ap)<0)check(a);
	else if(dot(ba,bp)<0)check(b);
	else check(a+normalize(ab)*dot(ab,ap)/length(ab));
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	while(read(m)){
		sc(n);
		vector< point > arr(n+1);
		lop(i,n+1)read(arr[i]);
		lop(i,n)
			solve(arr[i],arr[i+1],m);
		printf("%.4Lf\n%.4Lf\n",res.X,res.Y);
	}


}
