/*
    let the base values be stored in an array arr with size n (baseLength)
    the "top" value is calculated as summation (nCr[n-1][i]*arr[i])
    but nCr[30][15]=1.5*10^8, and since arr is positive, if n is 30 or more the top value will definitely be more than 10^6
    so we need only consider cases where n<30, lets use dp[idx][any][rem], where idx is arr index, and 'any' tells us whether we put any
    value in idx already or not, and rem is the remaining value in top element,
    then dp[idx][any][rem] = dp[idx][1][rem-nCr[n-1][idx] ] + any*dp[idx+1][0][rem];
    since memory limit is 64mb we need to use rolling table on idx
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

int mod=1e9+9;

ll nCr[30][30];
ll dp[2][2][1000100];
void calcnCr(){
   lop(i,30)nCr[i][i]=nCr[i][0]=1;
   for(int i=1;i<30;i++)
      for(int j=1;j<i;j++)
	nCr[i][j]=nCr[i-1][j]+nCr[i-1][j-1];
}

class NumberPyramids{
public:
	int count(int n, int top){
		if(n>=30)return 0;
		calcnCr();
		dp[1][0][0]=1;
		int p=0;
		for(int idx=n-1;idx>=0;idx--,p^=1)
			for(int rem=0;rem<=top;rem++)
				for(int any=0;any<2;any++){
					dp[p][any][rem]=0;
					if(nCr[n-1][idx]<=rem)dp[p][any][rem]=dp[p][1][rem-nCr[n-1][idx]];
					if(any)dp[p][any][rem]=(dp[p][any][rem]+dp[p^1][0][rem])%mod;
				}
		return dp[p^1][0][top];
	}
};
