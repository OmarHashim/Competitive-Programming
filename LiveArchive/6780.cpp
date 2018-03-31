/*
  if a>b, consider range as [a,b+n], else consider it as 2 ranges [a,b] & [a+n,b+n], now we want minimum no. of ranges that
  cover n consecutive cells
  sort these ranges and remove ranges that are completely covered by other ones 
  note that in the new sorted ranges, a[i]<a[i+1] & b[i]<b[i+1]
  for each range i , let nxt[i] = j such that j>=i is the last node where b[i]+1>=a[j]
  the "nxt" graph form a tree, lets brute force the starting i, set cur=i, and keep moving as cur=nxt[cur] till
  the ranges from i to cur cover n cells, this will give us the answer if we start from i, 
  finally, instead of moving 1 cell at a time (cur=nxt[cur]) lets use sparse table to calculate it in log(n) time
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=2e6+100,LG=21;
int ST[N][LG];
deque<ii> dq,dq2;
int n,k;

bool cover(ii a,ii b){
	return a.first<=b.first&&a.second>=b.second;
}
int out;
int solve(int start){
	if(dq[start].second-dq[start].first+1>=n)return 1;
	int cur=start;
	int ret=1;
	for(int j=LG-1;j>=0;j--){
		int to=ST[cur][j];
		if(dq[to].second-dq[start].first+1<n){
			cur=to;
			ret+=(1<<j);
		}

	}
	cur=ST[cur][0];
	ret++;
	if(dq[cur].second-dq[start].first+1>=n)return ret;
	return k+10;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	sc(n),sc(k);
	lop(i,k){
		int a,b;
		sc(a),sc(b);
		if(a<=b){
			dq2.push_back(ii(a,b));
			dq2.push_back(ii(a+n,b+n));
		}
		else dq2.push_back(ii(a,b+n));
	}
	sort(dq2.begin(),dq2.end());
	lop(i,dq2.size()){
		while(dq.size()&&cover(dq2[i],dq.back()))dq.pop_back();
		if(!dq.size()||!cover(dq.back(),dq2[i]))dq.push_back(dq2[i]);
	}
	int j=int(dq.size())-1;
	for(int i=j;i>=0;i--){
		while(dq[i].second+1<dq[j].first)j--;
		ST[i][0]=j;
		for(int k=1;k<LG;k++)
			ST[i][k]=ST[ST[i][k-1]][k-1];
	}
	out=k+10;
	lop(i,dq.size()){
		out=min(out,solve(i));
	}
	if(out>k)puts("impossible");
	else cout<<out<<endl;


}
