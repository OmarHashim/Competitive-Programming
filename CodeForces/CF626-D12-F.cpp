/*
    first we sort the array, then we use dp maintaining how many groups we have opened but not closed yet,
    as we transition, we know how many groups will still be open, then for each of these group cost is
    increased by arr[idx+1]-arr[idx], then we can maintain remaining k and count the answer

*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=205,K=1005,mod=1e9+7;
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
int n,k,arr[N];
int memo[N][N][K];
int solve(int idx,int cnt,int rem){
	if(rem<0)return 0;
	if(idx==n)return !cnt;
	int &ret=memo[idx][cnt][rem];
	if(~ret)return ret;
	ret=0;
	if(cnt)ret=mul(solve(idx+1,cnt-1,rem-(arr[idx+1]-arr[idx])*(cnt-1)),cnt); // add and close
	if(cnt)ret=add(ret,mul(solve(idx+1,cnt,rem-(arr[idx+1]-arr[idx])*(cnt)),cnt)); // add and dont close
	ret=add(ret,solve(idx+1,cnt+1,rem-(arr[idx+1]-arr[idx])*(cnt+1)));      // open new one
	ret=add(ret,solve(idx+1,cnt,rem-(arr[idx+1]-arr[idx])*(cnt)));                                      // open and close
	return ret;

}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	sc(n),sc(k);
	lop(i,n)sc(arr[i]);
	sort(arr,arr+n);
	memset(memo,-1,sizeof memo);
	cout<<solve(0,0,k);
}
