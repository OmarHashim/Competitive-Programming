/*
    let dp[s][e] be min cost to fix the range s...e, so answer is dp[0][n-1]
    either the range [s,e] forms 1 doll, or we can split it into 2 ranges [s,i],[i+1,e], so lets iterate both in our dp
    but if we form 1 doll with the range[s,e], first we need to make sure that this range have all the numbers
    1,2,3,....,e-s+1. lets precalculate this in array ok[s][e]
    second, we need to know the cost of fixing this range, lets pre calculate this in array cost[s][e]
    but how to calculate it? if s==e, answer is 0 , else we will split the range into [s,i] , [i+1,e]
    , then fix the range [s,i] first then the range [i+1,e], then we merge the 2 resulting dolls, but what is the cost
    of merging the resulting dolls? its the no. of dolls that have to be opened in order to merge them, 
    this value is simply the no. of dolls in the range [s,i] that are greater than the min. value in range [i+1,e]
    + the no. of dolls in range [i+1,e] that are greater than the min. value in range [s,i]
    so lets preprocess 2 more arrays, mn[s][e]: min value in this range, pre[s][e][val], no. of elements in range [s,e]
    that are greater than val, this is a n^3 array and takes about 470mb , we can decrease this if we use short instead of int
    since values dont exceed 500, so this reduces it to about 235mb.
    

*/


#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=503;
int mn[N][N];
short pre[N][N][N];
int cost[N][N];
int dp[N][N];
bool ok[N][N];
int n,arr[N];

int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	sc(n);
	lop(i,n)sc(arr[i]);
	for(int i=0;i<n;i++){
		vector<bool> vec(N,0);
		int mx=0;
		for(int j=i;j<n;j++){
			if(vec[arr[j]])break;
			vec[arr[j]]=1;
			mx=max(mx,arr[j]);
			if(mx==j-i+1)ok[i][j]=1;
		}
	}
	for(int i=0;i<n;i++){
		mn[i][i]=arr[i];
		for(int j=i+1;j<n;j++)
			mn[i][j]=min(arr[j],mn[i][j-1]);
	}
	for(int val=1;val<=n;val++)
		for(int i=0;i<n;i++){
			pre[i][i][val]=(arr[i]>val);
			for(int j=i+1;j<n;j++)
				pre[i][j][val]=(arr[j]>val)+pre[i][j-1][val];
		}
	for(int sz=2;sz<=n;sz++)
		for(int s=0;s+sz<=n;s++){
			int e=s+sz-1;
			cost[s][e]=1e8;
			for(int i=s;i<e;i++)
				cost[s][e]=min(cost[s][e],cost[s][i]+cost[i+1][e]
							+pre[s][i][mn[i+1][e]]+pre[i+1][e][mn[s][i]]);
		}
	lop(i,n)dp[i][i]=1e8*(arr[i]!=1);
	for(int sz=2;sz<=n;sz++)
		for(int s=0;s+sz<=n;s++){
			int e=s+sz-1;
			dp[s][e]=1e8;
			if(ok[s][e])dp[s][e]=cost[s][e];
			for(int i=s;i<e;i++)
				dp[s][e]=min(dp[s][e],dp[s][i]+dp[i+1][e]);
		}
	if(dp[0][n-1]>1e7)puts("impossible");
	else cout<<dp[0][n-1]<<endl;
}
