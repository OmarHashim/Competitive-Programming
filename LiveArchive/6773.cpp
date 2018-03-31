/*
  iterate every goal & run bfs from that goal marking all sets that contains that node, whenever a set is completely marked 
  we can push the source of that set into the queue and set its shortest path
*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=26,MX=1e6+10;;
int n,m[N];
int sz[MX];
vector<int> indices[N];
int rem[MX];
char str[N];
int sp[N][N];
int src[MX];
int id=0;

int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	sc(n);
	lop(i,n){
		sc(m[i]);
		lop(j,m[i]){
			scanf(" %s",str);
			int strl=strlen(str);
			src[id]=i;
			sz[id]=strl;
			lop(k,strl)
				indices[str[k]-'a'].push_back(id);
			id++;
		}
	}
	memset(sp,-1,sizeof sp);
	lop(goal,n){
		lop(i,id)rem[i]=sz[i];
		sp[goal][goal]=0;
		queue<int> q;
		q.push(goal);
		while(q.size()){
			int cur=q.front();
			q.pop();
			lop(i,indices[cur].size()){
				if(--rem[indices[cur][i]]==0){
					int sr=src[indices[cur][i]];
					if(sp[sr][goal]==-1){
						sp[sr][goal]=sp[cur][goal]+1;
						q.push(sr);
					}
				}
			}
		}
	}
	lop(i,n)lop(j,n)printf("%d%c",sp[i][j]," \n"[j+1==n]);

}
