/*
    it can be solved using divide and conquer dp or convex hull trick, memory and time limits are very strict
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=1e5+10,K=202;
ll dp[N][2],p[N];
int cut[N][K];
int n,k;
void solve(int s,int e,int l,int r,int rem){
	if(e<s)return;
	int m=s+((e-s)>>1);
	int opt=m;
	dp[m][rem&1]=-1e18;
	for(int i=max(l,m);i<=r;i++){
		ll res=(p[i]-p[m-1])*p[m-1]+dp[i+1][(rem-1)&1];
		if(res>dp[m][rem&1]){
			dp[m][rem&1]=res;
			opt=i;
		}
	}
	cut[m][rem]=opt;
	solve(s,m-1,l,opt,rem);
	solve(m+1,e,opt,r,rem);
}
int main(){
	sc(n),sc(k);k++;
	for(int i=1;i<=n;i++)
		scl(p[i]),p[i]+=p[i-1];
	for(int i=0;i<=n;i++)
		dp[i][0]=-1e18;

	dp[n+1][0]=0;
	for(int rem=1;rem<=k;rem++)
		solve(1,n,1,n,rem);

	printf("%lld\n",dp[1][k&1]);
	int cur=1,rem=k;
	while(cur<=n&&cut[cur][rem]!=n){
		printf("%d",cut[cur][rem]);
		cur=cut[cur][rem]+1;
		rem--;
		if(cur<=n)printf(" ");
	}
	puts("");

}
