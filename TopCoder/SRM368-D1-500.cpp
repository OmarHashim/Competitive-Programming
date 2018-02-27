/*
   if polylines intersect, add edge between them and count components
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

bool eq(long double a,long double b){
	return fabs(a-b)<EPS;
}

bool pointOnSegment(point a,point b,point p){
	// degenrate case already handled
	return eq(length(vec(a,b)),length(vec(a,p))+length(vec(b,p)));
}

//checks whether 2 segments intersect each other
bool intersect(point a,point b,point p,point q){
	// if vec=0, cross=0, so degenarate case is already handled
	long double d=cross(vec(a,b),vec(p,q));
	if(eq(d,0))return pointOnSegment(a,b,p)||pointOnSegment(a,b,q)// case when segments are parallel
			||pointOnSegment(p,q,a)||pointOnSegment(p,q,b);       // or 1 or both of them is a single point
	point r=a+cross(vec(a,p),vec(p,q))/d*(b-a);// intersection point of the 2 straight lines
	return pointOnSegment(a,b,r)&&pointOnSegment(p,q,r);// check the point is on both segments
}

vector<point> arr[3000];
int n,p[3000];
int findSet(int i){
	return (i==p[i] ? i:p[i]=findSet(p[i]));
}
void join(int a,int b){
	p[findSet(a)]=findSet(b);
}
point read(stringstream &ss){
	if(ss.peek()=='-')ss.ignore();
	double x,y;
	ss>>x;
	ss.ignore();
	ss>>y;
	return point(x,y);
}
class
PolylineUnion{
public:
	int countComponents(vector <string> polylines){
		string inp;
		lop(i,polylines.size())inp+=polylines[i];
		stringstream ss(inp);
		while(!ss.eof()){
			while(!ss.eof()&&ss.peek()!=' ')
				arr[n].push_back(read(ss));
			arr[n].push_back(arr[n].back());// to turn points into segments
			n++;
			if(!ss.eof())ss.ignore();
		}
		lop(i,n)p[i]=i;
		lop(i,n)lop(j,n){
			for(int a=0;a+1<arr[i].size();a++)
				for(int b=0;b+1<arr[j].size();b++){
					if(intersect(arr[i][a],arr[i][a+1],arr[j][b],arr[j][b+1]))
						join(i,j);
				}
		}
		int ret=0;
		lop(i,n)if(findSet(i)==i)ret++;
		return ret;

	}
};
