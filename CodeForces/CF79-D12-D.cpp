/*
    same as tutorial http://codeforces.com/blog/entry/1839
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=1e4+10,K=12,L=105;
int n,k,l,b[N],a[L];
int sp[2*K][N];
vector<int> vec;
void bfs(int src){
	int id=vec.size();
	lop(i,n+1)sp[id][i]=1e9;
	queue<int> q;
	sp[id][src]=0;
	q.push(src);
	while(q.size()){
		int cur=q.front();
		q.pop();
		lop(i,l){
			if(cur-a[i]>=0&&sp[id][cur-a[i]]==1e9){
				sp[id][cur-a[i]]=sp[id][cur]+1;
				q.push(cur-a[i]);
			}
			if(cur+a[i]<=n&&sp[id][cur+a[i]]==1e9){
				sp[id][cur+a[i]]=sp[id][cur]+1;
				q.push(cur+a[i]);
			}
		}
	}
	vec.push_back(src);
}
int get(int mask,int idx){
	return (mask>>idx)&1;
}
int dp[(1<<20)];
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	sc(n),sc(k),sc(l);
	lop(i,k){
		int x;
		sc(x);
		b[x]^=1;
		b[x-1]^=1;
	}
	lop(i,l)sc(a[i]);
	for(int i=0;i<=n;i++)
		if(b[i])
			bfs(i);
	int m=vec.size();
	for(int mask=1;mask<(1<<m);mask++){
		dp[mask]=1e9;
		int i=0;
		while(!get(mask,i))i++;
		for(int j=i+1;j<m;j++){
			if(get(mask,j))
				dp[mask]=min(dp[mask],sp[i][vec[j]]+dp[mask^(1<<i)^(1<<j)]);
		}
	}
	if(dp[(1<<m)-1]==1e9)return puts("-1");
	printf("%d\n",dp[(1<<m)-1]);

}
