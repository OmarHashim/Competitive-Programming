/*
    let asp[i][j] = shortest path from node i to node j, where asp[i][i]=0
    let msp[i][j] = shortest path from node i to node j, where you need to take atleast 1 step, so we dont set msp[i][i]=0
    we fill both matrices using floyd
    let sp[i][j][p]=shortest path using exactly 2^p edges from node i to node j
    finally we compute the answer using something like digit dp on k, where answer for pair(i,j) is dp[i][j][30]
    
*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=50,LG=31;
int t,n,l;
ll asp[N][N];
ll msp[N][N];
ll sp[N][N][31];
ll dp[N][N][LG];
int mat[N][N];

int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	sc(t);
	for(int tc=1;tc<=t;tc++){
		sc(l),sc(n);
		lop(i,n)lop(j,n)sc(mat[i][j]),sp[i][j][0]=asp[i][j]=msp[i][j]=mat[i][j];
		lop(i,n)asp[i][i]=0;
		lop(i,n)lop(j,n)lop(k,n)asp[j][k]=min(asp[j][k],asp[j][i]+asp[i][k]);
		lop(i,n)lop(j,n)lop(k,n)msp[j][k]=min(msp[j][k],msp[j][i]+msp[i][k]);
		for(int p=1;p<LG;p++)
			lop(i,n)lop(j,n){
				sp[i][j][p]=1e18;
				lop(k,n)
					sp[i][j][p]=min(sp[i][j][p],sp[i][k][p-1]+sp[k][j][p-1]);
			}
		lop(i,n)lop(j,n){
			if((l&1)==0||i!=j)
				dp[i][j][0]=asp[i][j];
			else dp[i][j][0]=msp[i][j];
		}
		for(int idx=1;idx<LG;idx++)
			lop(i,n)lop(j,n){
				dp[i][j][idx]=1e18;
				if(!(l&(1<<idx))){
					dp[i][j][idx]=dp[i][j][idx-1];
					lop(k,n)dp[i][j][idx]=min(dp[i][j][idx],sp[i][k][idx]+asp[k][j]);
				}
				else {
					lop(k,n)dp[i][j][idx]=min(dp[i][j][idx],sp[i][k][idx]+dp[k][j][idx-1]);
				}
			}
		printf("Region #%d:\n",tc);
		lop(i,n)lop(j,n)printf("%lld%c",dp[i][j][LG-1]," \n"[j+1==n]);
		puts("");

	}
}
