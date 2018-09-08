/*
    consider all pathes in the tree, sum of them have their length increase as k increases, sum of them have their length decrease
    and sum of them don't change, and we want the max path to be as small as possible, then we can use ternary search

*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=3e5+100;

vector<int> to[N],c[N],a[N];
void addedge(int u,int v,int w,int f){
	to[u].push_back(v);
	c[u].push_back(w);
	a[u].push_back(f);
}
pll solve(int cur,int fr,int k){
	pll ret(0,0);
	vector<ll> vec;
	lop(i,to[cur].size()){
		int v=to[cur][i];
		if(v==fr)continue;
		pll res=solve(v,cur,k);
		res.first+=c[cur][i]+1LL*k*a[cur][i];
		vec.push_back(res.first);
		ret.first=max(ret.first,res.first);
		ret.second=max(ret.second,res.second);
	}
	ll mx=0;
	lop(i,vec.size()){
		ret.second=max(ret.second,mx+vec[i]);
		mx=max(mx,vec[i]);
	}
	mx=0;
	for(int i=int(vec.size())-1;i>=0;i--){
		ret.second=max(ret.second,mx+vec[i]);
		mx=max(mx,vec[i]);
	}
	return ret;
}
int n,d;
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	sc(n),sc(d);
	lop(i,n-1){
		int u,v,w,f;
		sc(u),sc(v),sc(w),sc(f);
		u--,v--;
		addedge(u,v,w,f);
		addedge(v,u,w,f);
	}
	int s=0,e=d,md,bst=-1;
	ll vbst=1e18;
	while(s<e){
		md=s+((e-s)>>1);
		ll vmd=solve(0,0,md).second;
		ll vmd2=solve(0,0,md+1).second;
		if(vmd<=vmd2){
			if(vmd<=vbst)bst=md,vbst=vmd;
			e=md-1;
		}
		else {
			if(vmd2<=vbst)bst=md+1,vbst=vmd2;
			s=md+2;
		}

	}
	if(s==e&&(bst==-1||solve(0,0,s).second<solve(0,0,bst).second))
		bst=s;
	cout<<bst<<endl<<solve(0,0,bst).second<<endl;
}
