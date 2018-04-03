/*
   we only care about edges that are on some shortest path, these edges form a DAG
   if 2 cars have different initial shortest pathes, they will never make congestion, so we can solve for equal shortest path
   cars independantly of other cars. for some cars that all have the same shortest path, we cant use the same edge twice,
   this is a max flow problem, with sink being the target node, and we create a source node with capacitiy to graph nodes equal to
   no. of cars in that node.
   
*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int maxN=25005,maxE=2e5;
const int oo=1e9;
int src,snk,cap[maxE];
int head[maxN],headcpy[maxN],nxt[maxE],to[maxE],edgeCnt;
void init(){
	memset(head,-1,sizeof head);
	edgeCnt=0;
}
void addEdge(int u,int v,int c){
	nxt[edgeCnt]=head[u];
	head[u]=edgeCnt;
	cap[edgeCnt]=c;
	to[edgeCnt++]=v;
}
void addBiEdge(int u,int v,int c){
	addEdge(u,v,c);
	addEdge(v,u,0);
}
int Rank[maxN];
int ddfs(int cur=src,int flow=oo){
	if(cur==snk)return flow;
	for(int &i=headcpy[cur];i!=-1;i=nxt[i]){
		int t=to[i];
		if(!cap[i]||Rank[t]!=Rank[cur]+1)
			continue;
		int f=ddfs(t,min(flow,cap[i]));
		cap[i]-=f;
		cap[i^1]+=f;
		if(f)return f;
	}
	return 0;
}
int Q[maxN];
bool dbfs(){
	memset(Rank,-1,sizeof Rank);
	int Qi=0;
	Q[Qi++]=src;
	Rank[src]=0;
	for(int i=0;i<Qi;i++){
		int cur=Q[i];
		int r=Rank[cur];
		for(int j=head[cur];j!=-1;j=nxt[j]){
			int t=to[j];
			if(!cap[j]||Rank[t]!=-1)
				continue;
			Rank[t]=r+1;
			Q[Qi++]=t;
			if(t==snk)return 1;
		}
	}
	return 0;
}
int dinic(){
	int ret=0,f;
	while(dbfs()){
		memcpy(headcpy,head,sizeof head);
		while(f=ddfs()){
			ret+=f;
		}
	}
	return ret;
}
vector<int> adj[maxN];
vector<int> cost[maxN];
int n,m,c,sp[maxN];
int comm[1005];
bool cmp(int a,int b){
	return sp[a]<sp[b];
}
void dijkstra(){
	priority_queue<ii,vector<ii>,greater<ii>> pq;
	pq.push(ii(0,0));
	lop(i,n)sp[i]=1e9;
	while(pq.size()){
		int cur=pq.top().second;
		int co=pq.top().first;
		pq.pop();
		if(sp[cur]<=co)continue;
		sp[cur]=co;
		lop(i,adj[cur].size()){
			int to=adj[cur][i];
			int e=cost[cur][i];
			if(sp[to]>sp[cur]+e)
				pq.push(ii(sp[cur]+e,to));
		}
	}
}
int cnt[maxN];
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	sc(n),sc(m),sc(c);
	lop(i,m){
		int u,v,co;
		sc(u),sc(v),sc(co);
		u--,v--;
		adj[u].push_back(v);
		cost[u].push_back(co);
		adj[v].push_back(u);
		cost[v].push_back(co);
	}
	dijkstra();
	lop(i,c)sc(comm[i]),comm[i]--;
	sort(comm,comm+c,cmp);
	int out=0;
	lop(i,c){
		int j=i;
		while(j+1<c&&sp[comm[j+1]]==sp[comm[j]])j++;
		memset(cnt,0,sizeof cnt);
		for(int z=i;z<=j;z++)
			++cnt[comm[z]];
		init();
		src=n;
		snk=0;
		lop(cur,n)lop(z,adj[cur].size()){
			int to=adj[cur][z];
			int e=cost[cur][z];
			if(sp[to]==sp[cur]+e){
				addBiEdge(to,cur,1);
			}
		}
		lop(cur,n){
			if(cnt[cur])
				addBiEdge(src,cur,cnt[cur]);
		}
		out+=dinic();
		i=j;
	}
	cout<<out;

}
