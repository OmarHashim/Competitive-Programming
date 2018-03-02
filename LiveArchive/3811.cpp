/*
    WA so far
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int maxN=100,maxE=1010*2*2;
const ll oo=1e18;
ll src=1,snk=0,cap[maxE];
int head[maxN],headcpy[maxN],nxt[maxE],to[maxE],edgeCnt;

void init(){
	memset(head,-1,sizeof head);
	edgeCnt=0;
}
void addedge(int u,int v,ll c){
	nxt[edgeCnt]=head[u];
	head[u]=edgeCnt;
	cap[edgeCnt]=c;
	to[edgeCnt++]=v;
}
void addbiedge(int u,int v,ll c){
	addedge(u,v,c);
	addedge(v,u,c);// modified
}
int Rank[maxN];

ll ddfs(int cur=src,ll flow=oo){
	if(cur==snk)
		return flow;
	for(int &i=headcpy[cur];i!=-1;i=nxt[i]){
		int t=to[i];
		if(!cap[i]||Rank[t]!=Rank[cur]+1)
			continue;
		ll f=ddfs(t,min(flow,cap[i]));
		cap[i]-=f;
		cap[i^1]+=f;
		if(f)
			return f;
	}
	return 0;
}
int Q[maxN];
bool dbfs(){
	memset(Rank,-1,sizeof Rank);
	int Qi=0;
	Q[Qi++]=src;
	Rank[src]=0;
	for(int i=0;i<Qi;++i){
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

ll dinic(){
	ll ret=0,f;
	while(dbfs()){
		memcpy(headcpy,head,sizeof head);
		while(f=ddfs()){
			ret+=f;
		}
	}
	return ret;
}
int r,t,mf[55],vis[55];
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	int tc=1;
	while(sc(r),sc(t),r||t){
		init();
		lop(i,t){
			int u,v;
			sc(u),sc(v);
			addbiedge(u,v,1);// modified
		}
		for(int i=1;i<=r;i++){
			src=i;
			mf[i]=dinic();
			lop(j,edgeCnt)
				cap[j]=1;
		}
		//for(int i=1;i<=r;i++)printf("%d%c",mf[i]," \n"[i==r]);
		queue<int> q;
		bool f=0;
		q.push(1);
		memset(vis,0,sizeof vis);
		vis[1]=1;
		int out=1e9;
		while(!q.empty()){
			int sz=q.size();
			int mx=0;
			for(int i=0;i<sz;i++){
				int cur=q.front();
				q.pop();
				mx=max(mx,mf[cur]);
				for(int j=head[cur];j!=-1;j=nxt[j]){
					if(!vis[to[j]]){
						vis[to[j]]=1;
						if(to[j]==0)f=1;
						q.push(to[j]);
					}
				}
			}
			out=min(out,mx);
			if(f)break;
		}

		printf("Case %d: %d\n\n",tc++,out);

	}
}
