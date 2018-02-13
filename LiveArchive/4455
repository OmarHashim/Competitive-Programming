/*
    for all unique suffixes in input of length 1, consider them as nodes, and add edges from all rules of length 1
    and run floyd algorithm
    for all unique suffixes in input of length 2, consider them as nodes, and add edges from all rules of length 2
    additionally , if 2 suffixes share the first char, add edge between them with cost equals the shortest path
    of the remaining characters
    repeat for len=3,4.... sz(target)
    then sp[source][target] should have the final answer
*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
typedef pair<string,string> pss;

string s,t;
int nr;
set<ii> adj[22];
map<string,int> mp[22];
int getid(string x){
	if(x.size()==1)return 0;
	return mp[x.size()-1][x.substr(1)];
}
ll solve(int len,vector<vector<ll>> sp){
	int n=mp[len].size();
	vector<vector<ll>> nsp(n,vector<ll>(n,1e18));
	for(auto x:mp[len]){
		for(auto y:mp[len]){
			if(x.first[0]==y.first[0])
			nsp[x.second][y.second]=
			sp[getid(x.first)][getid(y.first)];
		}
	}
	for(auto p:adj[len])
		nsp[p.first][p.second]=1;

	lop(i,n)lop(j,n)lop(k,n)
			nsp[j][k]=min(nsp[j][k],nsp[j][i]+nsp[i][k]);
	if(len==s.size())return nsp[mp[len][s]][mp[len][t]];
	return solve(len+1,nsp);

}
void adds(string & x){
	lop(i,x.size()){
		if(!mp[i+1].count(x.substr(x.size()-i-1)))
		mp[i+1][x.substr(x.size()-i-1)]=mp[i+1].size()-1;
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	int tc=1;
	while(cin>>s, s!="."){
		lop(i,22)mp[i].clear(),adj[i].clear();
		cin>>t>>nr;
		adds(s);
		adds(t);
		lop(i,nr){
			string x,y;
			cin>>x>>y;
			if(x==y)continue;
			adds(x),adds(y);
			int len=x.size();
			adj[len].insert(ii(mp[len][x],mp[len][y]));
		}
		ll out=solve(1,vector<vector<ll>>(1,vector<ll>(1,0)));
		if(out<1e18)printf("Case %d: %lld\n",tc++,out);
		else printf("Case %d: No solution\n",tc++);

	}
}
