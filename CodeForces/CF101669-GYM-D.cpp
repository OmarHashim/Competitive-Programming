/*
  since every equation have exactly 2 ones, reduce the problem to a graph where edges repesent equations, 
  for every component, a "tree" repesentation of it is the maximum no. of independant equations, so we sum (component size -1)
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
vector<int> adj[N];
int m,n;
int arr[N],vis[N];
int dfs(int cur){
	if(vis[cur]++)
		return 0;
	int ret=1;
	for(auto v:adj[cur])
		ret+=dfs(v);
	return ret;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	memset(arr,-1,sizeof arr);
	sc(m),sc(n);
	lop(i,m){
		int k;
		sc(k);
		lop(j,k){
			int c;
			sc(c);
			c--;
			if(arr[c]==-1)arr[c]=i;
			else{
				adj[i].push_back(arr[c]);
				adj[arr[c]].push_back(i);
			}
		}
	}
	int out=0;
	lop(i,m)if(!vis[i])
		out+=dfs(i)-1;
	cout<<out;
}
