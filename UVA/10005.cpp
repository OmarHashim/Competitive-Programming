/*
  minimum enclosing circle algorithm O(n)
  can be solved using simpler solution since n<=100
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
#define ld long double
typedef complex<ld> point;
#define sz(a) ((int)(a).size())
#define all(n) (n).begin(),(n).end()
#define EPS 1e-9
#define OO 1e9
#define X real()
#define Y imag()
#define vec(a,b) ((b)-(a))
#define polar(r,t) ((r)*exp(point(0,(t))))
#define angle(v) (atan2((v).Y,(v).X))
#define length(v) ((ld)hypot((v).Y,(v).X))
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

enum STATE {
	IN, OUT, BOUNDRY
};
bool read(point & p) {
	double x, y;
	if (~scanf(" %lf %lf", &x, &y)) {
		p = point(x, y);
		return 1;
	}
	return 0;
}
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
const int N = 105;

point p[N], r[3], cen;
int ps, rs;
long double rad;
void mec() {
	if (rs == 3) {
		circle3(r[0], r[1], r[2], cen, rad);
		return;
	}
	if (rs == 2 && ps == 0) {
		circle2(r[0], r[1], cen, rad);
		return;
	}
	if (!ps) {
		cen = r[0];
		rad = 0;
		return;
	}
	ps--;
	mec();
	if (circlePoint(cen, rad, p[ps]) == OUT) {
		r[rs++] = p[ps];
		mec();
		rs--;
	}
	ps++;
}

ld R;

int main() {
#ifndef ONLINE_JUDGE
	freopen("i.txt", "r", stdin);
#endif
	while (sc(ps), ps) {
		rad=0;
		rs = 0;
		lop(i,ps)
			read(p[i]);
		srand(time(0));
		random_shuffle(p,p+ps);
		cin >> R;
		mec();

		if (rad <= R)
			puts("The polygon can be packed in the circle.");
		else
			puts("There is no way of packing that polygon.");
	}
}
