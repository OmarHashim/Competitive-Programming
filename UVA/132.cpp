/*
    lets preprocess the polygon, if 3 consecutive points i,j,k are collinear, remove point j.
    now lets choose 2 points A,B and draw a straight line between them, first we need to check that the projection of the center of mass
    on the line lies on the segment AB, then we need to check that the straight line doesnt intersect the polygon (but may touch
    its boundary)
    to do this check, we iterate polygon segments, if the straight line intersects this segment somewhere other than the borders,
    then we know the straight line intersects the polygon, else let the current segment be i,i+1, and the line intersects the segment 
    at i+1, now if i and i+2 lie on different sides of the line, the line intersects the polygon
    last case is when the segment i,i+1 lie entirely on the line, then we need to check points i-1,i+2, if they lie on different sides
    of the line, then the line intersects the polygon, note that this is why we had to remove consecutive collinear points at the 
    beginning.
    

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
bool check(point &a,point &b,point &p,point &q){
	long double v1=cross(vec(a,p),vec(a,b));
	long double v2=cross(vec(a,q),vec(a,b));
	if(v1<-EPS&&v2>EPS)return 1;
	if(v1>EPS&&v2<-EPS)return 1;
	return 0;
}
bool ok(vector<point>& p, point& a, point& b) {
	for (int i = 0; i < sz(p); i++) {
		int j = (i + 1) % sz(p);
		int k = (i + 2) % sz(p);
		int q = (i - 1 + sz(p)) % sz(p);
		point r;
		if(!intersect(a,b,p[i],p[j],r)){
			if(pointOnLine(a,b,p[i])&&pointOnLine(a,b,p[j])&&check(a,b,p[k],p[q]))
				return 0;
			continue;
		}
		if(pointOnSegment(p[i],p[j],r)&&!same(p[i],r)&&!same(p[j],r))
			return 0;
		if(same(p[j],r)&&check(a,b,p[i],p[k]))
			return 0;
	}
	return 1;
}
void rd(point &p ){
	double x,y;
	scanf(" %lf %lf",&x,&y);
	p=point(x,y);
}
vector<point> polygon;
vector<int> ids;
string name;
point center;
int n,id;
bool checkCenter(point a,point b){
	return dot(vec(a,b),vec(a,center)) > -EPS && dot(vec(b,a),vec(b,center)) > -EPS;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	while(cin>>name,name!="#"){
		polygon.clear(),ids.clear(),n=0,id=1;
		rd(center);
		point p;
		while(rd(p),!same(p,point(0,0))){
			if(n>=2&&pointOnLine(polygon[n-1],polygon[n-2],p))
				polygon.pop_back(),ids.pop_back(),n--;
			polygon.push_back(p);
			ids.push_back(id);
			n++;
			id++;
		}
		int out=id;
		for(int i=0;i<n;i++)
			for(int j=i+1;j<n;j++)
				if(ok(polygon,polygon[i],polygon[j])&&checkCenter(polygon[i],polygon[j])){
					int temp=0;
					lop(k,n)if(pointOnLine(polygon[i],polygon[j],polygon[k]))
						temp=max(temp,ids[k]);
					out=min(out,temp);
				}
		name+=string(20-name.size(),' ');
		cout<<name<<" "<<out<<endl;

	}
}
