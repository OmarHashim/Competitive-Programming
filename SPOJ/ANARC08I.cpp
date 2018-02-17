#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

int get(int n,ll i,ll j1,ll j2){
	if(n==0)return 1;
	ll v=(1LL<<(n-1));
	if(j1<v&&j2>=v)
		return get(n,i,j1,v-1)+get(n,i,v,j2);
	if(i>=v&&j1>=v)return -get(n-1,i-v,j1-v,j2-v);
	if(i>=v)i-=v;
	if(j1>=v)j1-=v,j2-=v;
	return get(n-1,i,j1,j2);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	int n;
	ll r,s,e;
	while(sc(n),scl(r),scl(s),scl(e),n!=-1){
		int out=0;
			out+=get(n,r,s,e);
		printf("%d\n",out);
	}
}
