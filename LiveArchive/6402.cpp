/*
   we use an algorithm similar to one that calculates area of a polygon, but each time we only calculate the area inside the circle.
   we have to handle few cases, for some segment, if both points lie inside, we just add area of a triangle as in the normal polygon
   area algorithm, if 1 point inside and 1 outisde, we add area of a triagle + area of a sector, if both points outside then there are 
   two cases, if the line between them doesnt intersect the circle, then we just add area of a sector, else we have to
   add area of a triangle + 2 sectors
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
#define angle(v) (atan2((v).Y,(v).X))
#define cross(a,b) ((conj(a)*(b)).imag())
typedef complex<long double> point;
#define X real()
#define Y imag()
#define dot(a,b) ((conj(a)*(b)).real())
#define length(v) ((long double)hypot((v).Y,(v).X))
#define vec(a,b) ((b)-(a))
#define EPS 1e-9
int n, r;
vector<point> p;

int doubleComp(long double x, long double y) {
	if (fabs(x - y) < EPS)
		return 0;
	return ((x > y) << 1) - 1;
}

bool outside(point x) {
	return x.X * x.X + x.Y * x.Y <= r * r;
}

bool pointOnLine(const point& a, const point& b, const point& p) {
	return fabs(cross(vec(a,b), vec(a,p))) < EPS;
}

bool pointOnRay(const point& a, const point& b, const point& p) {
	return dot(vec(a,p), vec(a,b)) > -EPS;
}

bool pointOnSegment(const point& a, const point& b, const point& p) {
	if (!pointOnLine(a, b, p))
		return 0;
	return pointOnRay(a, b, p) && pointOnRay(b, a, p);
}

int circleLineIntersection(const point& p0, const point& p1, const point cen,
		long double rad, point& r1, point & r2) {

	// handle degenerate case if p0 == p1
	long double a, b, c, t1, t2;
	a = dot(p1 - p0, p1 - p0);
	b = 2 * dot(p1 - p0, p0 - cen);
	c = dot(p0 - cen, p0 - cen) - rad * rad;
	double det = b * b - 4 * a * c;
	int res;
	if (fabs(det) < EPS)
		det = 0, res = 1;
	else if (det < 0)
		res = 0;
	else
		res = 2;
	det = sqrt(det);
	t1 = (-b + det) / (2 * a);
	t2 = (-b - det) / (2 * a);
	r1 = p0 + t1 * (p1 - p0);
	r2 = p0 + t2 * (p1 - p0);

	if (res > 0) {
		if (!pointOnSegment(p0, p1, r1)) {
			--res;
			r1 = r2;
			if (!pointOnSegment(p0, p1, r1))
				--res;
			return res;
		}
		if (!pointOnSegment(p0, p1, r2))
			--res;
		return res;
	}
	if (pointOnSegment(p0, p1, r2))
		swap(r1, r2);
	return res;
}
long double triArea(point a, point b) {
	return cross(a,b) / 2;
}
long double secArea(point a, point b) {
//return r*r*angle(vec(a,b))/2.0;
	return r * r * atan2(cross(a, b), dot(a, b)) / 2.0;
}
long double calc(point a, point b, point in1, point in2) {
	long double ret = 0;
	if (length(vec(a,in1)) < length(vec(a,in2))) {
		ret += secArea(a, in1) + triArea(in1, in2) + secArea(in2, b);
	} else
		ret += secArea(a, in2) + triArea(in2, in1) + secArea(in1, b);
	return ret;
}
bool inside(point a) {
	return length(a) - EPS <= r;
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif
	cin >> n >> r;
	for (int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		p.push_back(point(x, y));
	}

	long double area = 0;
	for (int j = n - 1, i = 0; i < n; j = i++) {
		point in1, in2;
		int in = circleLineIntersection(p[j], p[i], point(0, 0), r, in1, in2);
		if (inside(p[j])) {
			if (inside(p[i])) {
				area += triArea(p[j], p[i]);
			} else {
				area += triArea(p[j], in1);
				area += secArea(in1, p[i]);
			}
		} else {
			if (inside(p[i])) {
				area += triArea(in1, p[i]);
//				if (i == 4)
//					cout << in2.X << ' ' << in2.Y << endl;
				area += secArea(p[j], in1);
			} else {
				if (in < 2) {
					area += secArea(p[j], p[i]);
				} else {
//					cout << i << " HERE\n";
//					cout << in1 << ' ' << in2 << endl;
					area += calc(p[j], p[i], in1, in2);
				}
			}
		}
//		cout << i << " " << area << endl;
	}
	printf("%.9Lf", area);
}
