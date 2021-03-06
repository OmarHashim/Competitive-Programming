/*
  for each matrix run floyd so u have APSP for each car
  let sp[i][j]= min (mat[i][j]) for all matrices
  let dp[s][t][k]=min cost to travel from s to t using atmost k different cars
  then dp[s][t][k]=min sp[s][i] + dp[i][t][k-1]
  complexity n*n*n*n
  important note: we only need atmost n-1 car swaps, this reduces the size of dp
*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=62;
int n,m,r;
int mat[N][N][N];
int sp[N][N];
int dp[N][N][N];

int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	sc(n),sc(m),sc(r);
	lop(z,m)lop(i,n)lop(j,n)sc(mat[z][i][j]);
	lop(z,m)lop(i,n)lop(j,n)lop(k,n)mat[z][j][k]=min(mat[z][j][k],mat[z][j][i]+mat[z][i][k]);
	lop(i,n)lop(j,n)sp[i][j]=mat[0][i][j];
	lop(z,m)lop(i,n)lop(j,n)sp[i][j]=min(sp[i][j],mat[z][i][j]);
	lop(s,n)lop(t,n)dp[s][t][1]=sp[s][t];
	for(int k=2;k<=n;k++)lop(s,n)lop(t,n){
		dp[s][t][k]=dp[s][t][k-1];
		lop(i,n) dp[s][t][k]=min(dp[s][t][k],sp[s][i]+dp[i][t][k-1]);
	}

	lop(i,r){
		int s,t,k;
		sc(s),sc(t),sc(k);
		k=min(k+1,n);
		printf("%d\n",dp[s-1][t-1][k]);

	}

}
