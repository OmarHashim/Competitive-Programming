/*
    let cnt[cur][o][s]= no. of ways node cur returns o (0 or 1 ) when it is supposed to return s (0 or 1)
    then iterating o,s values for both children we can calculate values for parent node
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=1e5+100,mod=1e9+7;
int add(int a,int b){
	a+=b;
	if(a>=mod)a-=mod;
	return a;
}
int mul(ll a,int b){
	a*=b;
	if(a>=mod)a%=mod;
	return a;
}
int n,X[N],Y[N],F[N];
int cnt[N][2][2];
int nand(int in1,int in2){
	return !(in1&&in2);
}
int get(int root,int in1,int in2){
	if(F[root]==-1)return nand(in1,in2);
	return F[root];
}
void solve(int root){
	for(int oa=0;oa<=1;oa++)
		for(int sa=0;sa<=1;sa++)
			for(int ob=0;ob<=1;ob++)
				for(int sb=0;sb<=1;sb++){
					int out=get(root,oa,ob);
					int sh=nand(sa,sb);
					cnt[root][out][sh]=add(cnt[root][out][sh],
							mul(cnt[X[root]][oa][sa],cnt[Y[root]][ob][sb]));
				}
}
void dfs(int cur){
	if(!cur)return ;
	dfs(X[cur]);
	dfs(Y[cur]);
	solve(cur);

}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	sc(n);
	for(int i=1;i<=n;i++)
		sc(X[i]),sc(Y[i]),sc(F[i]);
	cnt[0][0][0]=1;
	cnt[0][1][1]=1;
	dfs(1);
	printf("%d\n",add(cnt[1][0][1],cnt[1][1][0]));
}
