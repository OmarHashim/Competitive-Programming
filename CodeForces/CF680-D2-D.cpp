/*
    find the centroid, make it the root of the tree, then for each node we need to cut some edge that is not in its subtree,
    and connect this edge to it, such that size of remaining nodes(not in this subtree or from newly added edge) have size<=n/2
    among all edges, we choose one with maximal size
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=4e5+100;
vector<int> adj[N];
int n,sz[N];
int get(int cur,int fr){
	sz[cur]=1;
	int ret=0;
	for(auto v:adj[cur]){
		if(v==fr)continue;
		ret|=get(v,cur);
		sz[cur]+=sz[v];
	}
	if(!ret&&sz[cur]>n/2)ret=cur;
	return ret;
}
void dfs(int cur,int fr){
	sz[cur]=1;
	for(auto v:adj[cur]){
		if(v==fr)continue;
		dfs(v,cur);
		sz[cur]+=sz[v];
	}
}
bool can[N];
void solve(int cur,int fr,int mx){
	if(n-sz[cur]-mx<=n/2)can[cur]=1;
	vector<int> pre(1,0),suf(1,0);
	for(auto v:adj[cur])
		if(v!=fr)
			pre.push_back(max(pre.back(),sz[v]));

	for(int i=int(adj[cur].size())-1;i>=0;i--){
		int v=adj[cur][i];
		if(v!=fr)
			suf.push_back(max(suf.back(),sz[v]));
	}
	reverse(suf.begin(),suf.end());
	int j=0;
	lop(i,adj[cur].size()){
		int v=adj[cur][i];
		if(v==fr)
			continue;
		int nmx=max(pre[j],suf[j+1]);
		nmx=max(nmx,mx);
		if(n-sz[v]<=n/2)nmx=max(nmx,n-sz[v]);
		solve(v,cur,nmx);
		j++;
	}

}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	sc(n);
	lop(i,n-1){
		int u,v;
		sc(u),sc(v);
		u--,v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	int root=get(0,0);
	dfs(root,root);
	solve(root,root,0);
	lop(i,n)if(can[i])printf("1 ");
	else printf("0 ");
}
