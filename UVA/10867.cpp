/*
  very similar to this problem
  https://github.com/OmarHashim/Competitive-Programming/blob/master/LiveArchive/8039.cpp
  with the difference being that we want the segments sum, not the longest segment
  
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
#define EPS 1e-8
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
	if (fabs(d1 - d2) > EPS)
		return 1;
	return 0;
}
bool check(point a,point b,point p,point q){
	long double v1=cross(vec(a,p),vec(a,b));
	long double v2=cross(vec(a,q),vec(a,b));
	if(v1>EPS&&v2<-EPS)return 1;
	if(v1<-EPS&&v2>EPS)return 1;
	return 0;

}
point minp(point a,point b){
	if(a.X<b.X)return a;
	if(fabs(a.X-b.X)<EPS&&a.Y<b.Y)return a;
	return b;
}
bool cmp(pair<point,int> a,pair<point,int > b){
	return same(minp(a.first,b.first),a.first);
}
long double solve(vector<point> & p,point a,point b){
	vector<pair<point,int>> vec;
	for(int i=0;i<sz(p);i++){
		int j=(i+1)%sz(p);
		if(pointOnLine(a,b,p[i])&&pointOnLine(a,b,p[j])){
			vec.push_back({minp(p[i],p[j]),1});
			continue;
		}
		point r;
		if(!intersect(a,b,p[i],p[j],r)||!pointOnSegment(p[i],p[j],r))
			continue;
		if(!same(p[i],r)&&!same(p[j],r)){
			vec.push_back({r,0});
			continue;
		}
		point u,v,w,z;
		if(same(p[i],r)) u=p[j],v=p[i],w=p[(i-1+sz(p))%sz(p)],z=p[(i-2+sz(p))%sz(p)];
		else u=p[i],v=p[j],w=p[(j+1)%sz(p)],z=p[(j+2)%sz(p)];
		if(check(a,b,u,w)){
			if(same(p[j],v))vec.push_back({v,0});
			continue;
		}
		if(!pointOnLine(a,b,w))continue;
		if(same(minp(v,w),v))continue;
		if(check(a,b,z,u))
			vec.push_back({v,3});
		else vec.push_back({v,2});
	}
	sort(vec.begin(),vec.end(),cmp);
	bool cur=0,beforeforce=0;
	long double out=0;
	for(int i=0;i+1<vec.size();i++){
		if(vec[i].second==0)cur^=1;
		else if(vec[i].second==1){
			beforeforce=cur;
			cur=1;
		}
		else if(vec[i].second==2)cur=beforeforce;
		else cur=1-beforeforce;
		if(cur)out+=length(vec[i].first-vec[i+1].first);
	}
	return out;
}
int n,m;
vector<point> polygon;
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	while(sc(n),sc(m),n||m){
		polygon.clear();
		lop(i,n){
			double x,y;
			scanf(" %lf %lf",&x,&y);
			polygon.push_back(point(x,y));
		}
		lop(i,m){
			double x,y;
			scanf(" %lf %lf",&x,&y);
			double x2,y2;
			scanf(" %lf %lf",&x2,&y2);
			cout<<fixed<<setprecision(3)<<solve(polygon,point(x,y),point(x2,y2))<<endl;

		}
	}
}

