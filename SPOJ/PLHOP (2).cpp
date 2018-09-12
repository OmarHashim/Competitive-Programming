/*
    we can use minimization matrix power, remember not to use identity element

*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=50;
int t,n,k;
ll mat[N][N];

void mmult(ll A[50][50],ll B[50][50],ll C[50][50]){
	lop(i,n)lop(j,n){
		C[i][j]=A[i][0]+B[0][j];
		for(int z=1;z<n;z++)
			C[i][j]=min(C[i][j],A[i][z]+B[z][j]);
	}
}
void pw(ll A[50][50],int p,ll B[50][50]){
	if(p==1){
		lop(i,n)lop(j,n)B[i][j]=A[i][j];
		return;
	}
	ll C[50][50];
	pw(A,p/2,C);
	mmult(C,C,B);
	if(p&1){
		mmult(A,B,C);
		lop(i,n)lop(j,n)B[i][j]=C[i][j];
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	sc(t);
	for(int tc=1;tc<=t;tc++){
		sc(k),sc(n);
		lop(i,n)lop(j,n)scl(mat[i][j]);
		ll X[50][50];
		pw(mat,k,X);
		lop(i,n)mat[i][i]=0;
		lop(i,n)lop(j,n)lop(z,n)mat[j][z]=min(mat[j][z],mat[j][i]+mat[i][z]);
		lop(i,n)lop(j,n)lop(z,n)X[j][z]=min(X[j][z],X[j][i]+mat[i][z]);
		printf("Region #%d:\n",tc);
		lop(i,n)lop(j,n)printf("%lld%c",X[i][j]," \n"[j+1==n]);
		puts("");

	}
}
