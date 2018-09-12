/*
   we find for each count the minimum cost to make it then we can find how many we can make with b
   let dp[0][i][c] = min cost if to buy c items in subtree of node i if parent of node i is not bought
   and dp[1][i][c] if parent is bought
   we need to use dp to merge children to find costs for node i
   the code looks like its n^3 but if you think about the 2 inner loops they are equivalent to iterating all pairs of nodes
   that have LCA = i, summing over all different values of i we realize its ammortized n^2
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=5010;
int n,b;
int c[N],d[N],sz[N];
vector<int> adj[N];
ll dp[2][N][N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	sc(n),sc(b);
	sc(c[0]),sc(d[0]);
	for(int i=1;i<n;i++){
		int p;
		sc(c[i]),sc(d[i]),sc(p);
		adj[p-1].push_back(i);
	}
	lop(k,2)lop(i,N)lop(j,N)dp[k][i][j]=1e18;
	for(int i=n-1;i>=0;i--){
		sz[i]=1;
		dp[0][i][1]=c[i];
		dp[1][i][1]=c[i]-d[i];
		dp[0][i][0]=0;
		for(auto v:adj[i]){
			vector<ll> t0(dp[0][i],dp[0][i]+sz[i]+sz[v]+1);
			vector<ll> t1(dp[1][i],dp[1][i]+sz[i]+sz[v]+1);
			for(int a=0;a<=sz[i];a++)
				for(int b=0;b<=sz[v];b++){
					t0[a+b]=min(t0[a+b],dp[0][i][a]+dp[0][v][b]);
					t1[a+b]=min(t1[a+b],dp[1][i][a]+min(dp[1][v][b],dp[0][v][b]));
				}
			sz[i]+=sz[v];
			lop(a,t0.size())dp[0][i][a]=t0[a];
			lop(a,t1.size())dp[1][i][a]=t1[a];
		}
	}
	int out=0;
	while(dp[0][0][out+1]<=b||dp[1][0][out+1]<=b)out++;
	printf("%d\n",out);
}
