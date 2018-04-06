/*
  https://szkopul.edu.pl/portal/
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=5005,V=50005;
int arr[N];
int sp[V];
int vis[V];
int n;

void dijkstra(){
	priority_queue<ii,vector<ii>,greater<ii>> pq;
	pq.push(ii(0,0));
	lop(i,arr[0])sp[i]=1e18;
	sp[0]=0;
	while(pq.size()){
		int cur=pq.top().second;
		int cost=pq.top().first;
		pq.pop();
		if(vis[cur]++)continue;
		lop(i,n){
			int to=(cur+arr[i])%arr[0];
			int nc=cost+arr[i];
			if(nc<=1000000000&&sp[to]>nc){
				sp[to]=nc;
				pq.push(ii(nc,to));
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	//freopen("i.txt","r",stdin);////////////////
#endif
	sc(n);
	lop(i,n)sc(arr[i]);
	sort(arr,arr+n);
	dijkstra();
	int q;
	sc(q);
	while(q--){
		int goal;
		sc(goal);
		if(sp[goal%arr[0]]<=goal)puts("TAK");
		else puts("NIE");
	}

}
