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

const long double pi=acos(-1.0);

bool pointOnLine(const point& a, const point& b, const point& p) {
	return fabs(cross(vec(a,b),vec(a,p))) < EPS;
}

struct cmp {
	point about;
	cmp(point c) {
		about = c;
	}
	bool operator()(const point& p, const point& q) const {
		double cr = cross(vec(about,p), vec(about,q));
		if (fabs(cr) < EPS)
			return make_pair(p.Y, p.X) < make_pair(q.Y, q.X);
		return cr > 0;
	}
};
void sortAntiClockWise(vector<point>& pnts) {
	point mn(1 / 0.0, 1 / 0.0);
	for (int i = 0; i < sz(pnts); i++)
		if (make_pair(pnts[i].Y, pnts[i].X) < make_pair(mn.Y, mn.X))
			mn = pnts[i];
	sort(all(pnts), cmp(mn));
}

void convexHull(vector<point> pnts, vector<point> &convex) {
	sortAntiClockWise(pnts);
	convex.clear();
	convex.push_back(pnts[0]);
	if (sz(pnts) == 1)
		return;
	convex.push_back(pnts[1]);
	for (int i = 2; i <= sz(pnts); i++) {
		point c = pnts[i % sz(pnts)];
		while (sz(convex) > 1) {
			point b = convex.back();
			point a = convex[sz(convex) - 2];
			if (cross(vec(b,a),vec(b,c)) < -EPS)
				break;
			convex.pop_back();
		}
		if (i < sz(pnts))
			convex.push_back(pnts[i]);
	}
}
int n,m;
long double gets(vector<point> pts){
	// if all points collinear ( or there is just 1 or 2 points), return answer
	sortAntiClockWise(pts);
	bool coll=1;
	lop(i,sz(pts)-2){
		if(!colliner(pts[i],pts[i+1],pts[i+2]))coll=0;
	}
	if(coll){
		return length(vec(pts.back(),pts[0]))*2+2*pi*m;
	}
	vector<point> convex;
	convexHull(pts,convex);
	long double ret=0;
	lop(i,convex.size()){
		point a=convex[i];
		point b=convex[(i+1)%convex.size()];
		point c=convex[(i+2)%convex.size()];
		point v1=vec(b,a);
		point v2=vec(b,c);
		long double theta=pi-acos(dot(v1,v2)/(length(v1)*length(v2)));
		ret+=length(v1)+theta*m;
	}
	return ret;

}
const int N=9;
vector<vector<point>> vec;
point arr[N];
long double solve(int cur){
	if(cur==n){
		long double ret=0;
		lop(i,vec.size())
			ret+=gets(vec[i]);
		return ret;
	}
	long double ret=1e18;
	lop(i,vec.size()){
		vec[i].push_back(arr[cur]);
		ret=min(ret,solve(cur+1));
		vec[i].pop_back();
	}
	vec.push_back(vector<point>(1,arr[cur]));
	ret=min(ret,solve(cur+1));
	vec.pop_back();
	return ret;
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("i.txt", "r", stdin);
#endif
	int tc=1;
	while(sc(n),sc(m),n||m){
		lop(i,n){
			long double x,y;
			cin>>x>>y;
			arr[i]=point(x,y);
		}
		vec.clear();
		vec.push_back(vector<point>(1,arr[0]));
		printf("Case %d: length = %.2Lf\n",tc++,solve(1));

	}
}
