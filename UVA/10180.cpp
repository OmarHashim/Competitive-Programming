/*
    if segment AB doesnt intersect the circle, answer is length of the segment, else we need to find tangent points
    and answer will be length of 2 segments + 1 arc
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
enum STATE {
	IN, OUT, BOUNDRY
};
bool pointOnLine(const point& a, const point& b, const point& p) {
	return fabs(cross(vec(a,b), vec(a,p))) < EPS;
}
inline bool pointOnSegment(point a, point b, point p) {
	return dot(vec(a,b),vec(a,p)) > -EPS && pointOnLine(a, b, p)
			&& dot(vec(b,a),vec(b,p)) > -EPS;
}
int circleSegmentIntersection(const point& p0, const point& p1, point cen,
		long double rad) {
	point r1, r2;
	if (same(p0, p1))
		return 0;
	long double a, b, c, t1, t2;
	a = dot(p1 - p0, p1 - p0);
	b = 2 * dot(p1 - p0, p0 - cen);
	c = dot(p0 - cen, p0 - cen) - rad * rad;
	double det = b * b - 4 * a * c;
	det = sqrt(det);
	t1 = (-b + det) / (2 * a);
	t2 = (-b - det) / (2 * a);
	r1 = p0 + t1 * (p1 - p0);
	r2 = p0 + t2 * (p1 - p0);
	int res = 0;
	if (fabs(length(r2) - rad) < EPS && pointOnSegment(p0, p1, r2))
		res++;
	if (fabs(length(r1) - rad) < EPS && pointOnSegment(p0, p1, r1))
		res++;
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

int tangentPoints(point cen, const long double & r, const point& p, point &r1,
		point &r2) {
	STATE s = circlePoint(cen, r, p);
	if (s != OUT) {
		r1 = r2 = p;
		return s == BOUNDRY;
	}
	point cp = vec(cen, p);
	long double h = length(cp);
	long double a = acos(r / h);
	cp = normalize(cp) * r;
	r1 = rotate(cp,a) + cen;
	r2 = rotate(cp,-a) + cen;
	return 2;
}
void rd(point &p) {
	double x, y;
	scanf(" %lf %lf", &x, &y);
	p = point(x, y);
}
int n;
point A, B;
long double r;
const long double PI = acos(-1.0);
long double solve(point p, point q) {
	long double ret = length(vec(A,p)) + length(vec(q,B));
	ret += r * fabs(atan2(cross(p, q), dot(p, q)));
	return ret;
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("i.txt", "r", stdin);
#endif
	cin >> n;
	while (n--) {
		rd(A), rd(B);
		cin >> r;
		if (circleSegmentIntersection(A, B, point(0, 0), r) < 2) {
			cout << fixed << setprecision(3) << length(vec(A,B)) << endl;
			continue;
		}
		point arr1[2], arr2[2];
		tangentPoints(point(0, 0), r, A, arr1[0], arr1[1]);
		tangentPoints(point(0, 0), r, B, arr2[0], arr2[1]);
		long double res = 1e9;
		lop(i,2)
			lop(j,2)
				res = min(res, solve(arr1[i], arr2[j]));
		cout << fixed << setprecision(3) << res << endl;
	}
}
