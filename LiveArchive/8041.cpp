/*
  the maximum in each row and in each column should stay the same, also some cells must have 0 and some must have +ve value
  (from top view), if in some row i and some column j the max value is equal, we can use cell i,j to put this value once and cover
  both the row and the column, however this is impossible if cell i,j is initially 0 , so among all rows and columns that share the same
  value, some can be matched together and some cant, so we have to use maximum matching algorithm to solve this.
  what's left is just to find how many more cells we have to use to satisfy the top view and calculate the answer
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
const int maxN=2*N,maxE=(N+N*N+N)*2;
const int oo=1e9;
int src=maxN-1,snk=maxN-2,cap[maxE];
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
		while(f=ddfs())
			ret+=f;
	}
	return ret;
}

int arr[N][N];
int n,m;
int rmx[N],cmx[N];

int MF(int val){
	vector<int> rows,cols;
	lop(i,n)if(rmx[i]==val)rows.push_back(i);
	lop(j,m)if(cmx[j]==val)cols.push_back(j);
	if(!cols.size())return 0;
	init();
	lop(i,rows.size())addbiedge(src,rows[i],1);
	lop(i,cols.size())addbiedge(n+cols[i],snk,1);
	lop(i,rows.size())lop(j,cols.size())
			if(arr[rows[i]][cols[j]])
			addbiedge(rows[i],n+cols[j],1);
	return dinic();

}



int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	sc(n),sc(m);
	ll tot=0,nonzero=0;//ok
	lop(i,n)lop(j,m){//ok
		sc(arr[i][j]);
		rmx[i]=max(rmx[i],arr[i][j]);
		cmx[j]=max(cmx[j],arr[i][j]);
		tot+=arr[i][j];
		if(arr[i][j])nonzero++;
	}
	ll used=0,cellcnt=0;
	lop(i,n){
		used+=rmx[i];
		if(rmx[i])cellcnt++;
	}
	lop(j,m){
		used+=cmx[j];
		if(cmx[j])cellcnt++;
	}
	vector<int> vec(rmx,rmx+n);
	sort(vec.begin(),vec.end());
	vec.erase(unique(vec.begin(),vec.end()),vec.end());
	lop(i,vec.size()){
		int res=MF(vec[i]);
		used-=1LL*vec[i]*res;
		cellcnt-=res;
	}
	used+=nonzero-cellcnt;
	cout<<tot-used;



}
