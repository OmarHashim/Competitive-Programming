/*
    sort array and take first m values, then u need to swap atmost k values to fix the mod problem, which can be done using dp
    to do so, group values together by their value mod k and sort them 

*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=50010,K=21;

ll dpL[K][K][K];
ll dpR[K][K][K];
int n,m,k,arr[N];
vector<int> L[K],R[K];

void preL(){
	lop(i,k)L[i].clear();
	lop(i,m)L[arr[i]%k].push_back(arr[i]);
	lop(i,k)sort(L[i].rbegin(),L[i].rend());

	lop(i,k+1)lop(j,k)lop(z,k+1)
			dpL[i][j][z]=-1e18;
	dpL[k][0][0]=0;
	for(int idx=k-1;idx>=0;idx--)
		for(int cur=0;cur<k;cur++)
			for(int rem=0;rem<=k;rem++){
				ll sum=0;
				for(int i=0;i<=L[idx].size()&&i<=rem;i++){
					dpL[idx][cur][rem]=max(dpL[idx][cur][rem],
							sum+dpL[idx+1][(cur+sum)%k][rem-i]);
					if(i<L[idx].size())
						sum+=L[idx][i];
				}
			}
}

void preR(){
	lop(i,k)R[i].clear();
	for(int i=m;i<n;i++)
		R[arr[i]%k].push_back(arr[i]);
	lop(i,k)sort(R[i].begin(),R[i].end());

	lop(i,k+1)lop(j,k)lop(z,k+1)
			dpR[i][j][z]=1e18;
	dpR[k][0][0]=0;
	for(int idx=k-1;idx>=0;idx--)
		for(int cur=0;cur<k;cur++)
			for(int rem=0;rem<=k;rem++){
				ll sum=0;
				for(int i=0;i<=R[idx].size()&&i<=rem;i++){
					dpR[idx][cur][rem]=min(dpR[idx][cur][rem],
							sum+dpR[idx+1][(cur+sum)%k][rem-i]);
					if(i<R[idx].size())
						sum+=R[idx][i];
				}
			}
}


int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	int t;
	sc(t);
	while(t--){
		sc(n),sc(m),sc(k);
		lop(i,n)sc(arr[i]);
		sort(arr,arr+n);
		ll sum=0;
		lop(i,m)sum+=arr[i];
		preL();
		preR();
		ll out=1e18;
		lop(x,k+1)
			lop(r,k)
			if(dpR[0][r][x]<1e16&&dpL[0][((-sum+r)%k+k)%k][x]>=0)
				out=min(out,sum+dpR[0][r][x]-dpL[0][((-sum+r)%k+k)%k][x]);

		if(out>1e16)puts("-1");
		else printf("%lld\n",out);


	}
}
