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

bool pointOnLine(const point& a, const point& b, const point& p) {
	return fabs(cross(vec(a,b),vec(a,p))) < EPS;
}

inline bool pointOnSegment (point a, point b, point p){
	return dot(vec(a,b),vec(a,p)) > -EPS && pointOnLine(a, b, p)
		&& dot(vec(b,a),vec(b,p)) > -EPS;
}

bool intersect(const point &a, const point &b, const point &p, const point &q, point &ret) {
	//handle degenerate cases
	long double d1 = cross(p - a, b - a);
	long double d2 = cross(q - a, b - a);
	ret = (d1 * q - d2 * p) / (d1 - d2);
	if(fabs(d1-d2)<EPS)
		return pointOnSegment(a,b,p)||pointOnSegment(a,b,q)
				||pointOnSegment(p,q,a)||pointOnSegment(p,q,b);
	return pointOnSegment(a,b,ret)&&pointOnSegment(p,q,ret);
}
bool haveEnd[55];
bool intersected[55];
class RectangleCrossings{
public:
	pair<point,point> get(string str){
		stringstream ss(str);
		int x,y,x2,y2;
		ss>>x>>y>>x2>>y2;
		return make_pair(point(x,y),point(x2,y2));
	}
	vector<pair<point,point>> parse(vector<string> vec){
		vector<pair<point,point>> ret(vec.size());
		lop(i,vec.size())ret[i]=get(vec[i]);
		return ret;
	}
	bool inside(point p,point a,point b){
		return p.X>a.X&&p.Y>a.Y&&p.X<b.X&&p.Y<b.Y;
	}
	vector<int> countAreas(vector<string> rectangles, vector<string> segments){
		vector<pair<point,point>> rec,seg;
		rec=parse(rectangles);
		seg=parse(segments);
		int n=rec.size(),m=seg.size();
		lop(i,n)lop(j,m){
			if(inside(seg[j].first,rec[i].first,rec[i].second))haveEnd[i]=1;
			if(inside(seg[j].second,rec[i].first,rec[i].second))haveEnd[i]=1;
			point dummy;
			if(intersect(seg[j].first,seg[j].second,rec[i].first,point(rec[i].second.X,rec[i].first.Y),dummy))
				intersected[i]=1;
			if(intersect(seg[j].first,seg[j].second,point(rec[i].second.X,rec[i].first.Y),rec[i].second,dummy))
				intersected[i]=1;
			if(intersect(seg[j].first,seg[j].second,rec[i].second,point(rec[i].first.X,rec[i].second.Y),dummy))
				intersected[i]=1;
			if(intersect(seg[j].first,seg[j].second,point(rec[i].first.X,rec[i].second.Y),rec[i].first,dummy))
				intersected[i]=1;
		}
		int area1=0,area2=0;
		lop(i,n){
			if(haveEnd[i])area1+=(rec[i].second.X-rec[i].first.X)*(rec[i].second.Y-rec[i].first.Y);
			else if(intersected[i])area2+=(rec[i].second.X-rec[i].first.X)*(rec[i].second.Y-rec[i].first.Y);
		}
		vector<int> ret;
		ret.push_back(area1);
		ret.push_back(area2);
		return ret;
	}
};
