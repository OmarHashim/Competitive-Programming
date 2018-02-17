/*
    dp[mask] = answer if you buy that mask
    iterate which item from the mask you will buy last, and using a precomputed table, find out what it's price will be if
    the remaining of the mask is already bought.
    we store answer as a pair to be able to add to the numerator and the denominator
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int M=15;
int m;
int p[M],a[M];
double arr[M][M];
pair<double,int> dp[(1<<M)];
void check(pair<double,int> &a,pair<double,int> b){
	if(b.first/b.second<a.first/a.second)
		a=b;
}
double pre[(1<<M)][M];
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	while(sc(m),m){
		lop(i,M)lop(j,M)arr[i][j]=1;
		lop(i,m){
			sc(p[i]),sc(a[i]);
			int k;
			sc(k);
			lop(j,k){
				int x,y;
				sc(x),sc(y);
				x--;
				arr[i][x]*=(100-y)/100.0;
			}
		}
		lop(i,m)pre[0][i]=1;
		for(int mask=1;mask<(1<<m);mask++){
			lop(i,m)pre[mask][i]=pre[mask&(mask-1)][i];
			int idx;
			for(idx=0;!(mask&(1<<idx));idx++);
			lop(i,m)pre[mask][i]*=arr[idx][i];

		}
		pair<double,int> ret(1e9,1);
		for(int mask=1;mask<(1<<m);mask++){
			dp[mask]=make_pair(1e9,1);
			lop(i,m){
				if(!(mask&(1<<i)))continue;
				int om=(mask^(1<<i));
				check(dp[mask],make_pair(dp[om].first+pre[om][i]*p[i],dp[om].second+a[i]));
			}
			check(ret,dp[mask]);
		}
		printf("%.4f\n",ret.first/ret.second);
	}
}
