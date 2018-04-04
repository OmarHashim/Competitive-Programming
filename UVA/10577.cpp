/*
    find center of the circle using the 3 points, then start at 1 point and rotate it about center by 360/n,2*360/n... to get
    the rest of the point, find min x,max x,min y,max y to find the area of the rectangle
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
const long double PI=acos(-1.0);

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

int main() {
#ifndef ONLINE_JUDGE
	freopen("i.txt", "r", stdin);
#endif
	int n,tc=1;
	while(sc(n),n){
		vector<point> vec;
		lop(i,3){
			double x,y;
			scanf(" %lf %lf",&x,&y);
			vec.push_back(point(x,y));
		}
		point cen;
		long double r;
		circle3(vec[0],vec[1],vec[2],cen,r);
		long double mnx=1e18,mxx=-1e18;
		long double mny=1e18,mxy=-1e18;
		lop(i,n){
			point res=rotateabout(vec[0],i*2*PI/n,cen);
			mnx=min(mnx,res.X);
			mxx=max(mxx,res.X);
			mny=min(mny,res.Y);
			mxy=max(mxy,res.Y);
		}
		printf("Polygon %d: ",tc++);
		cout<<fixed<<setprecision(3)<<(mxx-mnx)*(mxy-mny)<<endl;
	}
}
