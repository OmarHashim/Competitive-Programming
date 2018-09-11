/*
    if(k>=log2(h)) answer = log2(h)
    o.w we have k<=60
    if k=1, answer = n
    if k=2, answer= max where x*(x-1)/2+1<=h
    
    otherwise answer<=1000000
    lets find for each k what different values of n the answer change at
    let dp[k][i] = i-th value where answer for k changes at
    then we have dp[k][i]=dp[k][i-1]+dp[k-1][i-1]
    then we can binary search the answer from this table 

*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

ll dp[63][2000010];
void pre(){
	for(int idx=0;idx<=2e6;idx++)
		dp[1][idx]=idx;
	for(int rem=1;rem<63;rem++)
		dp[rem][1]=1;
	for(int rem=2;rem<63;rem++)
		for(int idx=2;idx<=2e6;idx++){
			dp[rem][idx]=dp[rem][idx-1]+dp[rem-1][idx-1];
			if(dp[rem][idx]>1e18)dp[rem][idx]=(2e18);
		}
}
ll lg (ll num) { //floor(log_2(n)) + 1
    return (63 - __builtin_clzll(num)) + 1;
}
ll solve2(ll h,ll rem){
	if(rem>=lg(h)) return lg(h);
	if(rem==1)return h;
	if(rem==2){
		int s=1,e=2e9,md,bst;
		while(s<=e){
			md=s+((e-s)>>1);
			if(1LL*md*(md-1)/2+1<=h)bst=md,s=md+1;
			else e=md-1;
		}
		return bst;
	}
	return upper_bound(dp[rem],dp[rem]+2000000,h)-dp[rem]-1;
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("i.txt", "r", stdin);
#endif
	pre();
	int t;
	sc(t);
	while(t--){
		ll h,rem;
		scl(h),scl(rem);
		printf("%lld\n",solve2(h,rem));
	}

}
