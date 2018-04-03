/*
    binary search the answer, lets check if we can make answer (d)
    when we decide on the min values for a new machine we take an adjacet pair of values, after that we can skip up to 2*k-2 values
    so we iterate left from right maintaining how many values we can skip, if the next pair have difference<=d , always take it
    else decrement the no. of values you can skip, if this value go below 0 then we cant make answer (d)
*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=1e6+10;
int n,k,tot,arr[N];

bool ok(int d){
	ll skipcnt=0;
	lop(i,tot-1){
		if(arr[i+1]-arr[i]>d){
			if(!skipcnt)return 0;
			skipcnt--;
		}
		else {
			i++;
			skipcnt+=2*k-2;
		}
	}
	return 1;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	sc(n),sc(k);
	tot=2*n*k;
	lop(i,tot)sc(arr[i]);
	sort(arr,arr+tot);
	int s=0,e=1e9+10,md,bst=-1;
	while(s<=e){
		md=s+((e-s)>>1);
		if(ok(md))bst=md,e=md-1;
		else s=md+1;
	}
	cout<<bst<<endl;

}
