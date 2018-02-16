/*
    sum edges not in the maximum spanning tree
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=1e4+10,M=1e5+10;
int n,m;
struct edge{
	int from,to,cost;
	bool operator<(const edge &b)const{
		return cost>b.cost;
	}
} arr[M];
int p[N];
int findSet(int i){
	return (i==p[i]? i:p[i]=findSet(p[i]));
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	int t;
	sc(t);
	while(t--){
		sc(n),sc(m);
		lop(i,m){
			sc(arr[i].from),sc(arr[i].to),sc(arr[i].cost);
			arr[i].from--;
			arr[i].to--;
		}
		sort(arr,arr+m);
		lop(i,n)p[i]=i;
		int out=0;
		lop(i,m){
			int u=findSet(arr[i].from);
			int v=findSet(arr[i].to);
			if(u!=v){
				p[u]=v;
			}
			else out+=arr[i].cost;
		}
		printf("%d\n",out);
	}
}
