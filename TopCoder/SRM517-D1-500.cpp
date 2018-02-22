/*
    let's calculate array W where W[i] is the index which the value i should be at in the end, i.e. p[W[i]]=i
    we start with permutation 0,1,...,n-1 and we want to reach p[0],p[1],...,p[n-1]
    and let the current array that we have is v
    when we swap two values at idx & idx+1 , then we must have W[v[idx+1]]<=idx && W[v[idx]]>idx, otherwise
    they will never reach their target location if we make this swap 
    we will use DP[L][R], making a swap will split the range into [L,idx] & [idx+1,R]
    these ranges will look like {Leftvalue,L+1,L+2,...,idx-1,Rightvalue}, i.e. v[i]=i except at terminals 
    if we think about it we dont need use Lv,Rv in state of the dp , they will always be unique for some L,R
    the rest is a combinatorics problem, we have DP[L][idx] ways for first part, each have idx-L swaps,
    and we have DP[idx+1][R] ways for second part, each have R-idx-1 swaps, 
    then total no. of ways is DP[L][idx]*DP[idx+1][R]*nCr[R-L-1][idx-L];
    then we iterate over all possible swapping positions and sum the answer
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=55,mod=1e9+7;
int memo[N][N],W[N];

inline int add(int a,int b){
   a+=b;
   if(a>=mod)a-=mod;
   return a;
}
inline int mul(int a,int b){
   ll ret=1LL*a*b;
   if(ret>=mod)ret%=mod;
   return ret;
}

int nCr[N][N];
void calcnCr(){
   lop(i,N)nCr[i][i]=nCr[i][0]=1;
   for(int i=1;i<N;i++)
      for(int j=1;j<i;j++)
    	  nCr[i][j]=add(nCr[i-1][j],nCr[i-1][j-1]);
}

int solve(int L,int R,int Lv,int Rv,int t){
	if(L+1==R)return (W[Lv]==R&&W[Rv]==L);
	if(L==R)return (W[Lv]==L);
	int &ret=memo[L][R];
	if(~ret)return ret;
	ret=0;
	for(int idx=L;idx<R;idx++){
		int v1=idx;
		if(idx==L)v1=Lv;
		int v2=idx+1;
		if(idx+1==R)v2=Rv;
		if(W[v1]>idx&&W[v2]<=idx){
			int val=mul(solve(L,idx,(idx==L ?v2:Lv ),v2,t+1),solve(idx+1,R,v1,(idx+1==R?v1:Rv),t+1));
			val=mul(val,nCr[R-L-1][idx-L]);
			ret=add(ret,val);
		}
	}
	return ret;
}
class AdjacentSwaps{
public:
	int theCount(vector <int> p){
		int n=p.size();
		lop(i,n)W[p[i]]=i;
		memset(memo,-1,sizeof memo);
		calcnCr();
		return solve(0,n-1,0,n-1,0);
	}
};
