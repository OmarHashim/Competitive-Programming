/*
   find the right point of the seesaw before it is moved and after it is moved, find distance between the 2 points and hence find
   the angle moved, now find the left point of the seesaw and rotate it by that angle
*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
const long double PI=acos(-1.0);

typedef complex<long double> point;
#define X real()
#define Y imag()
#define polar(r,t) ((r)*exp(point(0,(t))))
#define rotate(v,t) (polar(v,t))

int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	int t;
	sc(t);
	for(int tc=1;tc<=t;tc++){
		long double r,d,h1;
		cin>>r>>d>>h1;
		printf("Case %d: ",tc);
		if(d==r){
			cout<<fixed<<setprecision(4)<<r+(r-h1)<<endl;
			continue;
		}
		long double u=sqrt(r*r-(r-d)*(r-d));
		long double v=sqrt(r*r-(r-h1)*(r-h1));
		long double len=hypot(u-v,(r-d)-(r-h1));
		long double theta=acos((2*r*r-len*len)/(2*r*r));
		point p(-u,-(r-d));
		p=rotate(p,2*PI-theta);
		cout<<fixed<<setprecision(4)<<p.Y+r<<endl;
	}
}
