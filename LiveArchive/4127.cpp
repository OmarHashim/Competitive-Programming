/*
    find all points of interest,i.e. vertices of the triangles and all the intersection points,there are atmost about 10^4 such points
    sort points according to increasing x, then for each neighbouring points, they are completely covered by some triangles
    find which triangle gives the highest y value and calculate answer
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
#define all(v) v.begin(),v.end()
#define sz(v) (int)v.size()

typedef complex<double> point;
#define X real()
#define Y imag()
#define cross(a,b) ((conj(a)*(b)).imag())
#define dot(a,b) ((conj(a)*(b)).real())
#define vec(a,b) ((b)-(a))
const double EPS = 1e-9, oo = 1e9;

const int MAX = 105;

struct triangle {
	int x, b, h;
	triangle(int x = 0, int b = 0, int h = 0) :
			x(x), b(b), h(h) {
	}

} arr[MAX];

struct line {
	point a, b;
	line(point A, point B) {
		a = A, b = B;
	}

};

int n, tc;
vector<line> v, seg;
vector<point> allPts;
vector<double> mx;

void init() {
	v.clear();
	seg.clear();
	allPts.clear();
	mx.clear();
}

bool pointOnLine(const point& a, const point& b, const point& p) {
	return fabs(cross(vec(a,b), vec(a,p))) < EPS;
}

inline bool pointOnSegment(point a, point b, point p) {
	return dot(vec(a,b),vec(a,p)) > -EPS && pointOnLine(a, b, p)
			&& dot(vec(b,a),vec(b,p)) > -EPS;
}

bool intersect(const point &a, const point &b, const point &p, const point &q,
		point &ret) {
//handle degenerate cases
	double d1 = cross(p - a, b - a);
	double d2 = cross(q - a, b - a);
	ret = (d1 * q - d2 * p) / (d1 - d2);
	if (fabs(d1 - d2) > EPS && pointOnSegment(a, b, ret)
			&& pointOnSegment(p, q, ret))
		return 1;
	return 0;
}

double interPt(point a, point b, point p) {
	return ((a.Y - b.Y) / (a.X - b.X)) * (p.X - b.X) + b.Y;
}


bool dcmp(point p, point p2) {
	if (fabs(p.X - p2.X) < EPS && fabs(p.Y - p2.Y) < EPS)
		return 1;
	return 0;
}

bool intersect(line l, line l2, point& ret) {
	return intersect(l.a, l.b, l2.a, l2.b, ret);
}

bool cmp(point p, point p2) {
	return p.X < p2.X;
}


bool above(line l, point p) {
	return l.a.X <= p.X && l.b.X >= p.X;
}


double calc(double x, double y, double x2, double y2) {
	return sqrt((x - x2)*(x - x2)+(y - y2)*(y - y2));
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif
	while (scanf("%d", &n) == 1 && n) {
		init();
		printf("Case %d: ", ++tc);

		for (int i = 0; i < n; ++i) {
			scanf("%d%d%d", &arr[i].x, &arr[i].h, &arr[i].b);
			v.push_back(
					line(point(arr[i].x - arr[i].b / 2.0, 0),
							point(arr[i].x, arr[i].h)));
			allPts.push_back(point(arr[i].x - arr[i].b / 2.0, 0));

			v.push_back(
					line(point(arr[i].x, arr[i].h),
							point(arr[i].x + arr[i].b / 2.0, 0)));
			allPts.push_back(point(arr[i].x + arr[i].b / 2.0, 0));
		}
		for (int i = 0; i < sz(v); ++i) {
			allPts.push_back(v[i].a);
			allPts.push_back(v[i].b);
			for (int j = i+1; j < sz(v); ++j) {
				point r;
				if (intersect(v[i], v[j], r))
					allPts.push_back(r);
			}
		}
		sort(all(allPts), cmp);
		allPts.erase(unique(all(allPts), dcmp), allPts.end());
		mx.resize(sz(allPts),0);
		for (int j = 0; j < sz(allPts); ++j)
			for (int i = 0; i < sz(v); ++i)
				if (above(v[i], allPts[j]))
					mx[j] = max(mx[j], interPt(v[i].a, v[i].b, allPts[j]));

		double ans = 0;
		for (int i = 1; i < sz(allPts); ++i) {
			if((!dcmp(mx[i-1],0.0))||(!dcmp(mx[i],0.0)))
			ans += calc(allPts[i - 1].X, mx[i - 1], allPts[i].X, mx[i]);
		}
		cout<<fixed<<setprecision(0)<<ans<<endl<<endl;
	}
}
