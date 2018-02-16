/*
   run MST, the the answer for query u,v is the max edge on the unique path in the tree from u to v
   we can calculate answer in o(log) using sparse table to keep maximum,and use 1 more ST to store the ancestors
*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=50010,M=1e5+10,LG=18;
vector<ii> adj[N];

int ST[N][LG],in[N],out[N],mx[N][LG];

bool isAncestor(int u,int v){
	return in[v]>=in[u]&&out[v]<=out[u];
}
int LCA(int u,int v){
	if(isAncestor(u,v))return u;
	if(isAncestor(v,u))return v;
	for(int j=LG-1;j>=0;--j){
		if(ST[u][j]&&!isAncestor(ST[u][j],v))u=ST[u][j];
	}
	return ST[u][0];
}
int t,vis[N],visID;
void dfs(int cur,int from = 0){// set from=0 initially !!
	vis[cur]=visID;
	in[cur]=t++;

	ST[cur][0]=from;
	for(int j=1;j<LG;++j){
		ST[cur][j]=ST[ST[cur][j-1]][j-1];
		mx[cur][j]=max(mx[cur][j-1],mx[ST[cur][j-1]][j-1]);
	}

	lop(i,adj[cur].size())
	if(adj[cur][i].first!=from){
		mx[adj[cur][i].first][0]=adj[cur][i].second;
		dfs(adj[cur][i].first,cur);
	}

	out[cur]=t++;
}

int solve(int u,int lca){
	if(u==lca)return 0;
	int ret=0;
	for(int i=LG-1;i>=0;i--){
		if(ST[u][i]&&!isAncestor(ST[u][i],lca)){
			ret=max(ret,mx[u][i]);
			u=ST[u][i];
		}
	}
	return max(ret,mx[u][0]);
}
struct edge{
	int u,v,c;
	bool operator<(const edge &b)const{
		return c<b.c;
	}
} edges[M];
int n,m,p[N];
int findSet(int i){
	return (i==p[i]? i:p[i]=findSet(p[i]));
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	int tc=0;
	while(~sc(n)){
		if(tc++)puts("");
		sc(m);
		lop(i,n+1)adj[i].clear();
		lop(i,m)
			sc(edges[i].u),sc(edges[i].v),sc(edges[i].c);
		sort(edges,edges+m);
		for(int i=1;i<=n;i++)p[i]=i;
		lop(i,m){
			int u=findSet(edges[i].u);
			int v=findSet(edges[i].v);
			int c=edges[i].c;
			if(u!=v){
				p[u]=v;
				adj[edges[i].u].push_back(ii(edges[i].v,c));
				adj[edges[i].v].push_back(ii(edges[i].u,c));
			}
		}
		visID++;
		for(int i=1;i<=n;i++)
			if(vis[i]!=visID)
				dfs(i);
		int q;
		sc(q);
		lop(i,q){
			int u,v,lca;
			sc(u),sc(v);
			lca=LCA(u,v);
			printf("%d\n",max(solve(u,lca),solve(v,lca)));
		}

	}
}
