/*
    brute force 2 points or 3 non-collinear points and find the circle they define and check if
    any of the produced circles provide the correct result
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
#define colliner pointOnLine

enum STATE {
	IN, OUT, BOUNDRY
};

bool intersect(const point &a, const point &b, const point &p, const point &q,
		point &ret) {
//handle degenerate cases
	long double d1 = cross(p - a, b - a);
	long double d2 = cross(q - a, b - a);
	ret = (d1 * q - d2 * p) / (d1 - d2);
	if (fabs(d1 - d2) > EPS)
		return 1;
	return 0;
}

void circle2(const point& p1, const point& p2, point& cen, long double& r) {
	cen = mid(p1, p2);
	r = length(vec(p1,p2)) / 2;
}

bool circle3(const point& p1, const point& p2, const point& p3, point& cen,
		long double& r) {
	point m1 = mid(p1, p2);
	point m2 = mid(p2, p3);
	point perp1 = perp(vec(p1,p2));
	point perp2 = perp(vec(p2,p3));
	bool res = intersect(m1, m1 + perp1, m2, m2 + perp2, cen);
	r = length(vec(cen,p1));
	return res;
}
const int N = 110;

int n;
point arr[N];
long double rd;
point cen;
char state[N];

int main() {
#ifndef ONLINE_JUDGE
	freopen("i.txt", "r", stdin);
#endif
	sc(n);
	lop(i,n){
		long double x,y;
		scanf("%Lf %Lf", &x, &y);
		arr[i]=point(x,y);
		cin>>state[i];
	}
	if(n<3)return puts("No");
	bool ok=0;
	lop(i,n)for(int j=i+1;j<n;j++){
		circle2(arr[i],arr[j],cen,rd);
		bool tmp=1;
		for(int z=0;z<n;z++){
			if(state[z]=='I'&&length(arr[z]-cen)-EPS>rd)tmp=0;
			if(state[z]=='N'&&length(arr[z]-cen)+EPS<rd)tmp=0;
		}
		ok|=tmp;
	}
	lop(i,n)for(int j=i+1;j<n;j++)
		for(int k=j+1;k<n;k++){
			if(!circle3(arr[i],arr[j],arr[k],cen,rd))continue;
			bool tmp=1;
			for(int z=0;z<n;z++){
				if(state[z]=='I'&&length(arr[z]-cen)-EPS>rd)tmp=0;
				if(state[z]=='N'&&length(arr[z]-cen)+EPS<rd)tmp=0;
			}
			ok|=tmp;
		}
	if(ok)puts("No");
	else puts("Yes");

}
