/*
    direct Welzl's algorithm
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
STATE circlePoint(const point & cen, const long double & r, const point& p) {
	long double lensqr = lengthSqr(vec(cen,p));
	if (fabs(lensqr - r * r) < EPS)
		return BOUNDRY;
	if (lensqr < r * r)
		return IN;
	return OUT;
}

const int N = 1e5 + 10;

int n;
point arr[N];
vector<point> r;
long double rd;
point cen;

void mec() {
	if (!n || r.size() == 3) {
		if (r.size() == 1) {
			cen = r[0];
			rd = 0;
		} else if (r.size() == 2) {
			circle2(r[0],r[1],cen,rd);
		} else if(r.size()==3){
			circle3(r[0],r[1],r[2],cen,rd);
		}
		return;
	}
	n--;
	mec();
	if (circlePoint(cen, rd, arr[n]) == OUT) {
		r.push_back(arr[n]);
		mec();
		r.pop_back();
	}
	n++;

}
int main() {
#ifndef ONLINE_JUDGE
	freopen("i.txt", "r", stdin);
#endif
	int t;
	sc(t);
	while (t--) {
		rd=0;
		sc(n);
		lop(i,n){
			long double x,y;
			scanf("%Lf %Lf", &x, &y);
			arr[i]=point(x,y);
		}
		srand(time(0));
		random_shuffle(arr, arr + n);
		mec();
		printf("%.2LF\n%.2LF %.2LF\n",rd,cen.X,cen.Y);

	}

}
