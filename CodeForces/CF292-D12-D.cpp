/*
    connectiving is concerned with atmost n-1 edges, if we know which edges matter, we can use them each query
    to count no. of components, using DSU algorithm
    important edges are edges that connects 2 different components if we consider edges from left to right
    and we need to repeat this from right to left 
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=505,M=1e4+10;
int n,m;
int u[M],v[M];
vector<int> edges;
int p[N];
int findSet(int i){
	return (i==p[i]? i:p[i]=findSet(p[i]));
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	sc(n),sc(m);
	lop(i,m)sc(u[i]),sc(v[i]),u[i]--,v[i]--	;
	lop(i,n)p[i]=i;
	lop(i,m){
		int ru=findSet(u[i]);
		int rv=findSet(v[i]);
		if(ru!=rv){
			p[ru]=rv;
			edges.push_back(i);
		}
	}
	lop(i,n)p[i]=i;
	for(int i=m-1;i>=0;i--){
		int ru=findSet(u[i]);
		int rv=findSet(v[i]);
		if(ru!=rv){
			p[ru]=rv;
			edges.push_back(i);
		}
	}
	int q;
	sc(q);
	while(q--){
		int l,r;
		sc(l),sc(r);
		l--,r--;
		int out=n;
		lop(i,n)p[i]=i;
		lop(i,edges.size()){
			if(l<=edges[i]&&edges[i]<=r)continue;
			int ru=findSet(u[edges[i]]);
			int rv=findSet(v[edges[i]]);
			if(ru!=rv){
				out--;
				p[ru]=rv;
			}
		}
		printf("%d\n",out);
	}

}
