/*
    we use a map<int,int> and for each pair(i,j) that satisfy the conditions bj>ai && gcd(bj,ai)>1 , increment mp[gcd(bj,ai)] by one
    lets do the same thing for pairs (p,q) but count in a different map
    then we need to match values from first map with values from 2nd map such that their gcd>1.
    since we care only that gcd is greater than 1, we can reduce the problem by reducing each value a[i] to multiplication of its
    distinct prime factors only, but lets also keep a copy from original array for the comparisons needed (bj>ai),
    then any gcd calculated is a submask of the primes of one of the values ai or bi, then we can quickly find its distinct prime
    divisors aswell. now we can just build a graph to match between the 2 maps quickly, for some value V than occured C times in first map
    we create a node in the graph, connect it with the source node with capacity = C, we connect it with its corresponding prime node with
    the same cost. we do the same thing with the other map but instead connect to the sink, then running dinic max flow will be able
    to find the solution fast enough.


*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;


const int maxN=4e5+100,maxE=8e6;
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

const int N=410;
int n,a[N],ra[N],b[N],rb[N];
map<int,int> smp,pid;
void work(int &x){
	if(x==1)return;
	vector<int> primes;
	for(int i=2;i*i<=x;i++){
		if(x%i==0)primes.push_back(i);
		while(x%i==0)x/=i;
	}
	if(x>1)primes.push_back(x);
	x=1;
	lop(i,primes.size()){
		x*=primes[i];
		if(!pid.count(primes[i])){
			int sz=pid.size();
			pid[primes[i]]=sz;
		}
	}
	for(int mask=1;mask<(1<<primes.size());mask++){
		int val=1,sm;
		for(int i=primes.size()-1;i>=0;i--)
			if(mask&(1<<i))
				val*=primes[i],sm=primes[i];
		smp[val]=sm;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	int t;
	sc(t);
	while(t--){
		smp.clear();
		pid.clear();
		sc(n);
		lop(i,n){
			sc(a[i]);
			ra[i]=a[i];
			work(ra[i]);
		}
		lop(i,n){
			sc(b[i]);
			rb[i]=b[i];
			work(rb[i]);
		}
		map<int,int> mp,mp2;
		lop(i,n)lop(j,n){
			if(a[i]>=b[j])continue;
			int g=__gcd(ra[i],rb[j]);
			if(g>1)
				++mp[g];
		}
		lop(p,n)lop(q,n){
			if(b[p]>=a[q])continue;
			int g=__gcd(rb[p],ra[q]);
			if(g>1)
				++mp2[g];
		}
		init();
		src=pid.size(),snk=pid.size()+1;
		int id=pid.size()+2;
		for(auto p:mp){
			addbiedge(src,id,p.second);
			int v=p.first;
			while(v>1){
				addbiedge(id,pid[smp[v]],p.second);
				v/=smp[v];
			}
			id++;
		}
		for(auto p:mp2){
			addbiedge(id,snk,p.second);
			int v=p.first;
			while(v>1){
				addbiedge(pid[smp[v]],id,p.second);
				v/=smp[v];
			}
			id++;
		}
		printf("%d\n",dinic());



	}


}
