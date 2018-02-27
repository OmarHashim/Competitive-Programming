//implementation
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

bool read(point & p){
	double x,y;
	if(~scanf(" %lf %lf",&x,&y)){
		p=point(x,y);
		return 1;
	}
	return 0;
}

int n,k;
point arr[110];
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	int t;
	sc(t);
	lop(tc,t){
		sc(n);
		sc(k);
		lop(i,n)read(arr[i]);
		long double sum=0;
		lop(i,n-1)sum+=length(vec(arr[i],arr[i+1]));
		long double d=sum/(k-1);
		long double rem=d;
		point prev=arr[0];
		printf("Road #%d:\n",tc+1);
		printf("%.2Lf %.2Lf\n",prev.X,prev.Y);
		for(int i=0;i<n-1;i++){
			while(length(vec(prev,arr[i+1]))>=rem){
				prev=prev+normalize(vec(prev,arr[i+1]))*rem;
				printf("%.2Lf %.2Lf\n",prev.X,prev.Y);
				rem=d;
			}
			if(i==n-2&&!same(prev,arr[n-1]))printf("%.2Lf %.2Lf\n",arr[n-1].X,arr[n-1].Y);
			rem-=length(vec(prev,arr[i+1]));
			prev=arr[i+1];
		}
		cout<<endl;

	}

}
