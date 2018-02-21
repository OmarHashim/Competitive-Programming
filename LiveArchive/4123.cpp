/*
    there can't be neighbouring O's, and there must be exactly 4 neighbouring R's, and remember that first and last characters
    in the string are neighbours, then count the answer using dp
    i think it can also be solved using combinatorics
*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

ll memo[5][2][2][1010];
ll solve(int crr,int fc,int lc,int len){
	if(crr>4)return 0;
	if(!len){
		if(fc&&fc==lc)return 0;
		if(fc==lc)crr++;
		return (crr==4);
	}
	ll &ret=memo[crr][fc][lc][len];
	if(~ret)return ret;
	ret=solve(crr+(!lc),fc,0,len-1);
	if(!lc)ret+=solve(crr,fc,1,len-1);
	return ret;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	memset(memo,-1,sizeof memo);
	int len,tc=1;
	while(sc(len),len){
		printf("Case %d: %lld\n",tc++,solve(0,0,0,len-1)+solve(0,1,1,len-1));
	}
}
