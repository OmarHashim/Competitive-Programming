#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
#define ld long double
int n;
ld x[105],y[105],sx,sy;
ld calc(ld cx,ld cy){
	ld ret=0;
	lop(i,n)ret+=hypot(cx-x[i],cy-y[i]);
	return ret;
}
int di[]={0,0,1,-1};
int dj[]={1,-1,0,0};
ld solve(ld cx,ld cy){
	ld step=5000,ret=calc(cx,cy);
	while(step>0.01){
		lop(z,4){
			ld temp=calc(cx+di[z]*step,cy+dj[z]*step);
			if(temp<ret)
				ret=temp,cx+=di[z]*step,cy+=dj[z]*step;
		}
		step/=2;
	}
	return ret;

}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	int t;
	sc(t);
	for(int tc=0;tc<t;tc++){
		if(tc)puts("");
		sc(n);
		lop(i,n) cin>>x[i]>>y[i];
		cout<<fixed<<setprecision(0)<<solve(5000,5000)<<endl;
	}
}
