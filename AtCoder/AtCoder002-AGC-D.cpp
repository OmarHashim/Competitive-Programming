/*
      we can binary search for each query, and check validity using dsu, which would be mlogm per query, 
      but what if we solve for first iteration of binary search for all query, then second iteration and so on
      we can build just 1 dsu and every time we are at the middle element of some query we will do the check for this query
      for this iteration, then overall complexity is mlogm

*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=1e5+100;
int n,m,q,u[N],v[N],x[N],y[N],z[N],s[N],e[N],bst[N];
int p[N],sz[N];
vector<int> qr[2][N];

int findSet(int i){
	return (p[i]==i ? i:p[i]=findSet(p[i]) );
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	sc(n),sc(m);
	lop(i,m)sc(u[i]),sc(v[i]),u[i]--,v[i]--;
	sc(q);
	lop(i,q)sc(x[i]),sc(y[i]),sc(z[i]),x[i]--,y[i]--;
	lop(i,q){
		s[i]=0,e[i]=m-1,bst[i]=-1;
		qr[0][s[i]+((e[i]-s[i])>>1)].push_back(i);
	}
	lop(k,20){
		lop(i,n)p[i]=i,sz[i]=1;
		lop(i,m)qr[(k+1)&1][i].clear();
		lop(i,m){
			int ru=findSet(u[i]);
			int rv=findSet(v[i]);
			if(ru!=rv){
				p[ru]=rv;
				sz[rv]+=sz[ru];
			}
			lop(j,qr[k&1][i].size()){
				int qidx=qr[k&1][i][j];
				int rx=findSet(x[qidx]);
				int ry=findSet(y[qidx]);
				int csz=sz[rx];
				if(rx!=ry)csz+=sz[ry];
				if(csz>=z[qidx])bst[qidx]=i, e[qidx]=i-1;
				else s[qidx]=i+1;
				if(s[qidx]<=e[qidx])
					qr[(k+1)&1][s[qidx]+((e[qidx]-s[qidx])>>1)].push_back(qidx);
			}
		}
	}
	lop(i,q)printf("%d\n",bst[i]+1);

}
