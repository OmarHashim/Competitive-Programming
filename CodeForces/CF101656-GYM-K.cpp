/*
    lets use max flow, add edge from source to each node with letter 'W' with flow 1, add edge from nodes with letter 'N'
    to the sink with flow 1, this way letters 'W' and 'N' wont be used more than once, but to guarantee this for letters 'I'
    we need to use node split trick, so for a W-I neighbours we add edge from node 'W' to the input node of this 'I'
    and for a I-N neighbours we add edge from out node of this 'I' to node 'N', all with flow one,and an edge from the input node
    to the output node for each I and run max flow
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=33;
const int maxN=2*N*N+10;
const int maxE=(N*N+N*N*4+N*N+N*N+10)*2;
const int oo=1e9;
int src,snk,cap[maxE];
int head[maxN],headcpy[maxN],nxt[maxE],to[maxE],edgeCnt;
void init(){
	memset(head,-1,sizeof head);
	edgeCnt=0;
}
void addedge(int u,int v,int c){
	nxt[edgeCnt]=head[u];
	head[u]=edgeCnt;
	cap[edgeCnt]=c;
	to[edgeCnt++]=v;
}
void addbiedge(int u,int v,int c){
	addedge(u,v,c);
	addedge(v,u,0);
}
int Rank[maxN];
int ddfs(int cur=src,int flow=oo){
	if(cur==snk)
		return flow;
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
			if(t==snk)
				return 1;
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
int n,m;
char grid[N][N];
int di[]={0,0,1,-1};
int dj[]={1,-1,0,0};
int id(int i,int j){
	return (i-1)*m+j-1;
}
bool rd(){
	n=0,m=0;
	string x;
	while(getline(cin,x)&&x.size()&&x[0]>='A'){
		m=x.size();
		n++;
		for(int j=1;j<=m;j++)
			grid[n][j]=x[j-1];
		grid[n][m+1]=0;
	}
	for(int j=1;j<=m;j++)
		grid[n+1][j]=0;
	return n;

}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	while(rd()){
		init();
		src=id(2*n,m)+1;
		snk=src+1;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				if(grid[i][j]=='W')
					addbiedge(src,id(i,j),1);
				if(grid[i][j]=='N')
					addbiedge(id(i,j),snk,1);
				if(grid[i][j]=='I')
					addbiedge(id(i,j),id(n+i,j),1);
				lop(z,4){
					int ti=i+di[z];
					int tj=j+dj[z];
					if(grid[i][j]=='W'&&grid[ti][tj]=='I')
						addbiedge(id(i,j),id(ti,tj),1);
					if(grid[i][j]=='I'&&grid[ti][tj]=='N')
						addbiedge(id(n+i,j),id(ti,tj),1);
				}
			}
		printf("%d\n",dinic());
	}

}
