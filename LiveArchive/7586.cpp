/*
  use dp where state is current index in array, remaining value in this index, 'k' : the no. of quotes needed to close the latest term,
  last : what was the last thing i did ( close a term or opened a new one) , and can_leave, because when u open a term
  you have to keep opening smaller ones till u open a '1' till u can start closing
  transition is u either open a term or close one if possible
  bruteforce the answer in main and use this dp 
  complexity is 4*10^8 if all states are being visited but its unlikely, the solution passed in 32ms
*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=102;
int n,arr[N];
int gk;
int memo[N][N][N][2][2];// 0 -> closed 1-> opened
int vis[N][N][N][2][2];

int solve(int idx,int rem,int k,bool last,bool can_leave){
	if(rem<0)return 0;
	if(idx<n&&!rem)return solve(idx+1,arr[idx+1],k,last,can_leave);
	if(idx==n)
		return !last&&k==gk+1;
	if(k==gk+1)return 0;
	int &ret=memo[idx][rem][k][last][can_leave];
	if(vis[idx][rem][k][last][can_leave]==gk)
		return ret;
	vis[idx][rem][k][last][can_leave]=gk;
	ret=0;
	if(k>1){
		ret=solve(idx,rem-(k-1),k-1,1,k-1==1);
	}
	if(can_leave)ret|=solve(idx,rem-k,k+1,0,1);
	return ret;


}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	sc(n);
	lop(i,n)sc(arr[i]);
	memset(memo,-1,sizeof memo);
	for(gk=arr[0];gk>=1;gk--){
		if(solve(0,arr[0]-gk,gk,1,(gk==1))){
			cout<<gk;
			return 0;
		}
	}
	puts("no quotation");

}
