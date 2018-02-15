/*
    let A be set of nodes u where any path from source to u have the same cost
    let B be set of nodes u where any path from u to target have the same cost
    if a node is not in A and also not in B then there is no solution
    otherwise a solution always exist by changing edges that connect a node in set A but not in set B, with a node in set B
    we can check whether a node is in set B or not by calculating shortest path and longest path from each node to target
    then if shortest path=longest path then it is in set B
    it can be done easily since the graph is a DAG
    we can check for set A in the same way, we can run same algorithm on the reversed graph to find this

*/


#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=50010;
vector<int> adj[N],Gd[N];
int from[N],to[N],c[N];
int mns[N],mxs[N],mnt[N],mxt[N];
int n,m,vis[N];
bool changed[N];
int added[N];
void dfs(int cur){
	if(vis[cur]++)return;
	if(cur==n-1){
		mnt[cur]=mxt[cur]=0;
		return;
	}
	mnt[cur]=1e9;
	mxt[cur]=-1e9;
	lop(i,adj[cur].size()){
		int eid=adj[cur][i];
		int v=to[eid];
		dfs(v);
		mnt[cur]=min(mnt[cur],mnt[v]+c[eid]);
		mxt[cur]=max(mxt[cur],mxt[v]+c[eid]);
	}
}
void dfs2(int cur){
	if(vis[cur]++)return;
	if(cur==0){
		mns[cur]=mxs[cur]=0;
		return;
	}
	mns[cur]=1e9;
	mxs[cur]=-1e9;
	lop(i,Gd[cur].size()){
		int eid=Gd[cur][i];
		int v=from[eid];
		dfs2(v);
		mns[cur]=min(mns[cur],mns[v]+c[eid]);
		mxs[cur]=max(mxs[cur],mxs[v]+c[eid]);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	int tc=1;
	while(sc(n),sc(m),n||m){
		lop(i,n)adj[i].clear(),Gd[i].clear();
		memset(changed,0,sizeof changed);
		memset(added,0,sizeof added);
		lop(i,m){
			sc(from[i]),sc(to[i]),sc(c[i]);
			--from[i],--to[i];
			adj[from[i]].push_back(i);
			Gd[to[i]].push_back(i);
		}
		memset(vis,0,sizeof vis);
		dfs(0);
		memset(vis,0,sizeof vis);
		dfs2(n-1);
		bool ok=1;
		lop(i,n)if(mns[i]!=mxs[i]&&mnt[i]!=mxt[i])ok=0;
		printf("Case %d: ",tc++);
		if(!ok)puts("No solution");
		else {
			int cnt=0,p=mxt[0];
			lop(i,m){
				int u=from[i];
				int v=to[i];
				if(mns[u]==mxs[u]&&mnt[u]!=mxt[u]&&mnt[v]==mxt[v]
					&&mns[u]+mnt[v]+c[i]!=p){
					cnt++;
					changed[i]=1;
					added[i]=p-mns[u]-mnt[v]-c[i];
				}
			}
			printf("%d %d\n",cnt,p);
			lop(i,m){
				if(changed[i])
					printf("%d %d\n",i+1,added[i]);
			}
		}
	//	lop(i,n)cout<<"i="<<i+1<<" mns="<<mns[i]<<" mxs="<<mxs[i]<<" mnt="<<mnt[i]
		//			<<" mxt="<<mxt[i]<<endl;
	}
}
