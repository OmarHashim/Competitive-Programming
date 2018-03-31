/*
    find center of mass of the polygon and area of the polygon,new center of mass will be along the line
    between initial center of mass and point where the load will be (p0)
    let xl=minimum x such that there is a point(x,0)
    let xr=maximum x such that there is a point(x,0)
    the new center of mass must have xl<=x<=xr
    now we have to handle different cases, depending on where the initial center of mass is relative to xl and xr, same with point p0
*/

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
#define sz(v) (int)v.size()
#define PC(x) __builtin_popcount(x)
#define all(v) v.begin(),v.end()
#define CLR(a,v) memset(a,v,sizeof(a))
typedef pair<int, int> ii;
typedef vector<ii> vii;

typedef complex<long double> point;
#define X real()
#define Y imag()
#define cross(a,b) ((conj(a)*(b)).imag())
#define vec(a,b) ((b)-(a))
#define EPS 1e-12

int n;
vector<point> p;

point polygonCentroid(vector<point> &polygon) {
	long double x = 0, y = 0;
	long double a = 0;
	for (int i = 0; i < sz(polygon); ++i) {
		int j = (i + 1) % sz(polygon);
		x += (polygon[i].X + polygon[j].X)
				* (polygon[i].X * polygon[j].Y - polygon[j].X * polygon[i].Y);
		y += (polygon[i].Y + polygon[j].Y)
				* (polygon[i].X * polygon[j].Y - polygon[j].X * polygon[i].Y);
		a += polygon[i].X * polygon[j].Y - polygon[i].Y * polygon[j].X;
	}

	a *= 0.5;
	x /= 6 * a;
	y /= 6 * a;
	return point(x, y);
}

bool intersect(const point&a, const point&b, const point&p, const point&q,
		point&ret) {
	long double d1 = cross(p - a, b - a);
	long double d2 = cross(q - a, b - a);
	ret = (d1 * q - d2 * p) / (d1 - d2);
	if (fabs(d1 - d2) > EPS)
		return 1;
	return 0;
}

vector<point> inter;
point A, B;

long double polygonArea(const vector<point>&p) {
	long double res = 0;
	for (int i = 0; i < sz(p); i++) {
		int j = (i + 1) % sz(p);
		res += cross(p[i], p[j]);
	}
	return fabs(res) / 2;
}
int doubleComp(long double a, long double b) {
	if (fabs(a - b) < EPS)
		return 0;
	return ((a > b) << 1) - 1;
}
bool inside(point P, long double x, long double x2) {
	return doubleComp(P.X, x) >= 0 && doubleComp(P.X, x2) <= 0;
	return P.X >= x && P.X <= x2;
}
bool same(long double x, long double y) {
	if (fabs(x - y) < EPS)
		return 1;
	return 0;
}
long double calcL(point r, long double W) {
	long double x = A.X, y = A.Y;
	long double x2 = B.X, y2 = B.Y;
	long double x3 = r.X, y3 = r.Y;
	//			cout << x3 << ' ' << y3 << endl;
	long double L;
	if (!same(x3, x2))
		L = (W * x - W * x3) / (x3 - x2);
	else
		L = (W * y - W * y3) / (y3 - y2);
	return L;
}

const long double oo = 1e18;
int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	cin >> n;
	long double lx = oo, rx = -oo;
	for (int i = 0; i < n; ++i) {
		long double x, y;
		scanf("%Lf%Lf", &x, &y);
		point P(x, y);
		p.push_back(P);
		if (doubleComp(y,0)==0) {
			lx = min(lx, x);
			rx = max(rx, x);
		}
	}

	point cen = polygonCentroid(p);
	long double W = polygonArea(p);

	A = cen, B = p[0];
	if (inside(A, lx, rx)) {
		point r;
		long double lb = 0, ub = 1e18;
		if (inside(B, lx, rx))
			return puts("0 .. inf");

		if (B.X < lx) {
			point r;
			intersect(A, B, point(lx, 0), point(lx, oo), r);
			ub = calcL(r, W);
		} else {
			point r;
			intersect(A, B, point(rx, 0), point(rx, oo), r);
			ub = calcL(r, W);
		}
		printf("%.0Lf .. %.0Lf\n", floor(lb+EPS), ceil(ub-EPS));
	} else {
		if (A.X < lx) {
			if (doubleComp(B.X,lx)<=0)
				return puts("unstable");
			point rl;
			intersect(A, B, point(lx, 0), point(lx, oo), rl);
			point rr;
			intersect(A, B, point(rx, 0), point(rx, oo), rr);
			long double lb = 0, ub = oo;

			lb = calcL(rl, W);
			bool inf = 1;
			if (B.X > rx+EPS)
				ub = calcL(rr, W), inf = 0;
			if (inf)
				printf("%.0Lf .. inf\n", floor(lb+EPS));
			else
				printf("%.0Lf .. %.0Lf\n", floor(lb+EPS), ceil(ub-EPS));
		} else {
			if (doubleComp(B.X,rx)>=0)
				return puts("unstable");
			point rl;
			intersect(A, B, point(lx, 0), point(lx, oo), rl);
			point rr;
			intersect(A, B, point(rx, 0), point(rx, oo), rr);
			long double lb = 0, ub = oo;

			lb = calcL(rr, W);
			bool inf = 1;
			if (B.X < lx)
				ub = calcL(rl, W), inf = 0;
			if (inf)
				printf("%.0Lf .. inf\n", floor(lb+EPS));
			else
				printf("%.0Lf .. %.0Lf\n", floor(lb+EPS), ceil(ub-EPS));
		}
	}
}
