/*
    iterate i,j to find dp[1][1][s]
    then to calculate dp[i][j][s] , we either use value dp[i][j-1][s] if j!=1, else we use dp[i-1][j][s], in either case
    we have take value from the other dp entry, add sum of 2 diagonals to it, and remove sum of 2 diagonals, which can be done
    with prefix sum on diagonals

*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=105,mod=1e9+7;
inline int add(int a,int b){
   a+=b;
   if(a>=mod)a-=mod;
   return a;
}

int t,n,m,s,pi,pj;
int dp[N][N][N];
int d1[2*N][N][N];
int d2[2*N][N][N];
int g[N][N];
bool valid(int i,int j){
	return i>=1&&j>=1&&i<=n&&j<=m;
}
int getd1(int iL,int jL,int iR,int jR){
	if(iL<1)jL-=1-iL,iL=1;
	if(jL>m)iL+=jL-m,jL=m;
	if(iR>n)jR+=iR-n,iR=n;
	if(jR<1)iR-=1-jR,jR=1;
	if(valid(iL,jL)&&valid(iR,jR)&&iL<=iR)return add(d1[iL+jL][iR][jR],mod-d1[iL+jL][iL-1][jL+1]);
	return 0;
}
int getd2(int iL,int jL,int iR,int jR){
	if(iL<1)jL+=1-iL,iL=1;
	if(jL<1)iL+=1-jL,jL=1;
	if(iR>n)jR-=iR-n,iR=n;
	if(jR>m)iR-=jR-m,jR=m;
	if(valid(iL,jL)&&valid(iR,jR)&&iL<=iR)return add(d2[iL-jL+N][iR][jR],mod-d2[iL-jL+N][iL-1][jL-1]);
	return 0;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	sc(t);
	for(int tc=1;tc<=t;tc++){
		memset(dp,0,sizeof dp);
		memset(d1,0,sizeof d1);
		memset(d2,0,sizeof d2);
		sc(n),sc(m),sc(s),sc(pi),sc(pj);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				sc(g[i][j]);
				dp[i][j][1]=g[i][j];
			}
		for(int c=1;c<s;c++){
			for(int i=1;i<=n;i++)
				for(int j=1;j<=m;j++){
					d1[i+j][i][j]=add(dp[i][j][c],d1[i+j][i-1][j+1]);
					d2[i-j+N][i][j]=add(dp[i][j][c],d2[i-j+N][i-1][j-1]);
				}
			dp[1][1][c+1]=0;
			for(int i=1;i<=n;i++)
				for(int j=1;j<=m;j++)
					if(i-1+j-1<=c)
						dp[1][1][c+1]=add(dp[1][1][c+1],dp[i][j][c]);
			for(int i=1;i<=n;i++){
				for(int j=1+(i==1);j<=m;j++){
					if(j!=1){
						dp[i][j][c+1]=dp[i][j-1][c+1];
						dp[i][j][c+1]=add(dp[i][j][c+1],mod-getd1(i-c,j-1,i,j-c-1));
						dp[i][j][c+1]=add(dp[i][j][c+1],getd1(i,j+c,i+c,j));
						dp[i][j][c+1]=add(dp[i][j][c+1],mod-getd2(i+1,j-c,i+c,j-1));
						dp[i][j][c+1]=add(dp[i][j][c+1],getd2(i-c,j,i-1,j+c-1));
					}
					else {
						dp[i][j][c+1]=dp[i-1][j][c+1];
						dp[i][j][c+1]=add(dp[i][j][c+1],mod-getd1(i-c-1,j,i-1,j-c));
						dp[i][j][c+1]=add(dp[i][j][c+1],getd1(i,j+c,i+c,j));
						dp[i][j][c+1]=add(dp[i][j][c+1],mod-getd2(i-c,j+1,i-1,j+c));
						dp[i][j][c+1]=add(dp[i][j][c+1],getd2(i,j-c,i+c-1,j-1));

					}
				}
			}
		}
		printf("Case %d: %d\n",tc,dp[pi][pj][s]);

	}

}
