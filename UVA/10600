/*
    run MST algorithm and construct the tree which gives u the first output
    to get second MST, iterate unused edges u->v, find max edge on path from u->v
    then adding the new edge will add edgecost-maxedge to the sum, minimize this value
*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=105,M=10005,LG=7;
int p[N],n,m;
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
int t;
void dfs(int cur,int ec,int from = 0){
	in[cur]=t++;

	ST[cur][0]=from;
	mx[cur][0]=ec;
	for(int j=1;j<LG;++j){
		ST[cur][j]=ST[ST[cur][j-1]][j-1];
		mx[cur][j]=max(mx[cur][j-1],mx[ST[cur][j-1]][j-1]);
	}

	lop(i,adj[cur].size())
	if(adj[cur][i].first!=from)
		dfs(adj[cur][i].first,adj[cur][i].second,cur);

	out[cur]=t++;
}


struct edge{
	int from,to,cost;
	bool operator<(const edge & b)const{
		return cost<b.cost;
	}
}edges[M];
int findSet(int i){
	return (i==p[i] ? i : p[i]=findSet(p[i]));
}
int sum;
bool taken[M];

int gets(int u,int lca){
	int ret=0;
	for(int j=LG-1;j>=0;j--){
		if(!isAncestor(ST[u][j],lca)||ST[u][j]==lca){
			ret=max(ret,mx[u][j]);
			u=ST[u][j];
		}
	}
	return ret;
}
int solve(int u,int v){
	int lca=LCA(u,v);
	return max(gets(u,lca),gets(v,lca));
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	int tc;
	sc(tc);
	while(tc--){
		sc(n),sc(m);

		lop(i,n)adj[i].clear();
		memset(taken,0,sizeof taken);
		t=0;

		lop(i,m){
			sc(edges[i].from),sc(edges[i].to),sc(edges[i].cost);
			edges[i].from--;
			edges[i].to--;
		}
		sort(edges,edges+m);
		lop(i,n)p[i]=i;
		sum=0;
		lop(i,m){
			int ru=findSet(edges[i].from);
			int rv=findSet(edges[i].to);
			if(ru!=rv){
				taken[i]=1;
				p[ru]=rv;
				sum+=edges[i].cost;
				adj[edges[i].from].push_back(ii(edges[i].to,edges[i].cost));
				adj[edges[i].to].push_back(ii(edges[i].from,edges[i].cost));
			}
		}
		dfs(0,0);
		int delta=1e9;
		lop(i,m){
			if(taken[i])continue;
			delta=min(delta,edges[i].cost-solve(edges[i].from,edges[i].to));
		}
		cout<<sum<<" "<<delta+sum<<endl;

	}
}
