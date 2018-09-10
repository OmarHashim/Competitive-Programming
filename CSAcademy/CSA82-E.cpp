/*
    without limitation on number of tanks , we can solve it using something similar to prim
    lets keep an array where arr[i] = min cost to connect water to node i now
    initially arr[i] = f[i] ( putting a tank there)
    we choose an index j that still doesnt have water and provide water with cost arr[j]
    when we connect water to idx j , we can relax all nodes i.e. arr[i]=min(arr[i],c[j][i]);
    when we add a node, check if we have to put a tank there, and find min. no of tanks needed to achieve the solution
    
    if we add some constant value to all tanks prices, as this constant value increase, no. of used tanks decrease, then
    we can binary search the min. constant value to add such that no. of used tanks<=k
    lets this optimal value be b, then we can subtract k*b from answer to obtain the solution.

*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=2010;
int n,k,f[N],c[N][N];
int tf[N];
pll solve(int md){
	lop(i,n)tf[i]=f[i]+md;
	vector<bool> t(n,1);
	vector<bool> d(n,0);
	pll ret(0,0);
	lop(z,n){
		int idx=-1;
		lop(i,n)if(!d[i]&&(idx==-1||tf[idx]>tf[i]))idx=i;
		d[idx]=1;
		ret.first+=tf[idx];
		if(t[idx])ret.second++;
		lop(i,n){
			if(tf[i]>=c[idx][i]){
				tf[i]=c[idx][i];
				t[i]=0;
			}
		}
	}
	return ret;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	int t;
	sc(t);
	while(t--){
		sc(n),sc(k);
		lop(i,n)sc(f[i]);
		lop(i,n)lop(j,n)sc(c[i][j]);
		int s=0,e=1e9,bst=-1;
		while(s<=e){
			int md=s+((e-s)>>1);
			if(solve(md).second<=k)bst=md,e=md-1;
			else s=md+1;
		}
		pll res=solve(bst);
		printf("%lld\n",res.first-bst*k);

	}
}
