/*
    WA, don't know why
    problem statement is a bit vague
    tried to think about cases of multi edges/ self edges, but cant find what is wrong with the solution
    
    idea : 
    remove edges that are not rewarding since they are never used anyway
    then run bellman ford, if SP after first run = oo, then there is no path, if there is a path
    run bellman ford once more, if sp decrease, then it is unbound
    i am running bellman ford with 2n iterations just as a high safety factor
*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=105;
struct edge{
	int cost,len,to;
	edge(int x,int y,int z){
		cost=x,len=y,to=z;
	}
	bool operator<(const edge & b)const {
		return cost<b.cost;
	}
};
vector<edge> adj[N];
int n,m,a,b;
void work(vector<ii> &dist){
	for(int i=0;i<=2*n;++i)
		for(int j=0;j<n;++j){
			if(dist[j].first==1e9)continue;
			for(int k=0;k<adj[j].size();++k){
				int to=adj[j][k].to;
				int cost=adj[j][k].cost;
				int len=adj[j][k].len;
				dist[to]=min(dist[to],ii(dist[j].first+cost,dist[j].second+len));
			}
		}
}
void bellman(){
	vector<ii> dist(n,ii(1e9,1e9));
	dist[a]=ii(0,0);
	work(dist);
	if(dist[b]==ii(1e9,1e9)){
		puts("VOID");
		return;
	}
	ii cur=dist[b];
	work(dist);
	if(dist[b]!=cur){
		puts("UNBOUND");
	}
	else {
		printf("%d %d\n",dist[b].first,dist[b].second);
	}
}
void init(){
	lop(i,n)adj[i].clear();
}
string x;
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	while(~sc(n)){
		sc(m),sc(a),sc(b);
		init();
		lop(i,m){
			cin>>x;
			lop(i,x.size())if(!isdigit(x[i])&&x[i]!='-')x[i]=' ';
			stringstream ss(x);
			int u,v,cuv,len,cvu;
			ss>>u>>v>>cuv>>len>>cvu;
			adj[u].push_back(edge(cuv,len,v));
			adj[v].push_back(edge(cvu,len,u));


		}
		lop(i,n){
			sort(adj[i].begin(),adj[i].end());
			for(int j=0;j+1<adj[i].size();j++){
				if(adj[i][j].cost!=adj[i][j+1].cost)
					adj[i].erase(adj[i].begin()+j+1,adj[i].end());
			}
		}
		bellman();
	}
}
