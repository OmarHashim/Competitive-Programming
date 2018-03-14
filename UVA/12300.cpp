#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
#define ld long double
const ld PI=acos(-1.0);

int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	int xa,ya,xb,yb,n;
	while(sc(xa),sc(ya),sc(xb),sc(yb),sc(n),n){
		ld len=sqrt((xa-xb)*(xa-xb)+(ya-yb)*(ya-yb));
		ld beta=2*PI/n;
		ld theta=(2*PI-beta)/2;
		ld x;
		if(n%2==0)x=len*cos((n-2)*PI/(n*2));
		else x=len*sin(beta/2)/sin(theta/2);
		printf("%.6Lf\n",0.25*n*x*x/tan(PI/n));
	}
}
