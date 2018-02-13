/*
    for each bill, force it's value with 0, and see if any assignment of the remaining bills exist that satisfy all conditions,
    repeat check when value is forced to 1, then if any bill cant be 0 and cant be 1 then there is no solution
    
    checking if any assignment exist is done using 2-sat, if we need to satisfy all the remaining conditions of some minister, 
    we add them in the form (A||A)(B||B).. if we need to satisfy atleast n-1 of his conditions, then we add them in the form
    (A||B)(A||C)(A||D)(B||C)(B||D)(C||D) i.e. all pairs
*/


#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int,int> ii;
typedef pair<ll,ll> pll;

const int mM=503,mB=103;
const int N=mB*2;
int vis[N];
vector<int> G[N],Gd[N],topo;
int cId[N],Id;
void init(){
	Id=0;
	lop(i,N)G[i].clear(),Gd[i].clear();
	topo.clear();
	memset(vis,0,sizeof vis);
}
void addOr(int x,int y){
	G[x^1].push_back(y);
	G[y^1].push_back(x);
	Gd[y].push_back(x^1);
	Gd[x].push_back(y^1);
}

void dfs(int cur){
	if(vis[cur]++)return;
	lop(i,Gd[cur].size())
		dfs(Gd[cur][i]);
	topo.push_back(cur);
}
void dfs2(int cur){
	if(vis[cur]++)return ;
	cId[cur]=Id;
	lop(i,G[cur].size())
		dfs2(G[cur][i]);
}

int B,M,k[mM];
vector<ii> votes[mM];
bool ok[mB][2];
int getidx(int i,int j){
	int ret=2*votes[i][j].first;
	if(votes[i][j].second==0)ret^=1;
	return ret;
}
void addallpairs(int i,int z){
		lop(j,k[i]){
			if(z==votes[i][j].first)continue;
			for(int r=j+1;r<k[i];r++){
				if(z==votes[i][r].first)continue;
				addOr(getidx(i,j),getidx(i,r));
			}
		}
}
void addonebyone(int i,int z){
	lop(j,k[i]){
		if(votes[i][j].first==z)continue;
		addOr(getidx(i,j),getidx(i,j));
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif
	int tc=1;
	while(sc(B),sc(M),B||M){
		lop(i,M)votes[i].clear();
		lop(i,M){
			sc(k[i]);
			lop(j,k[i]){
				int idx;
				char v;
				scanf("%d %c",&idx,&v);
				votes[i].push_back(ii(idx-1,(v=='y' ? 1:0)));
			}
		}
		lop(i,B){
			ok[i][0]=ok[i][1]=1;
			lop(j,2){
				init();
				lop(z,M){
					bool in=0,sat=0;
					lop(r,k[z]){
						if(votes[z][r].first==i)
							in=1,sat=(j==votes[z][r].second);
					}
					if(in&&!sat&&k[z]<=2){
						ok[i][j]=0;
						break;
					}
					if(in){
						if(sat){
							if(k[z]>2)addallpairs(z,i);
							else addonebyone(z,i);
						}
						else addonebyone(z,i);

					}
					else {
						if(k[z]<=2)addonebyone(z,-1);
						else addallpairs(z,-1);
					}
				}
				if(!ok[i][j])continue;
				lop(z,2*B) dfs(z);
				memset(vis,0,sizeof vis);
				reverse(topo.begin(),topo.end());
				lop(z,2*B){
					if(!vis[topo[z]]){
						dfs2(topo[z]);
						Id++;
					}
				}
				lop(z,2*B)
				if(cId[z]==cId[z^1])
					ok[i][j]=0;

			}
		}
		bool allok=1;
		lop(i,B)if(!ok[i][0]&&!ok[i][1])allok=0;
		printf("Case %d: ",tc++);
		if(!allok)puts("impossible");
		else {
			lop(i,B){
				if(ok[i][0]&&ok[i][1])printf("?");
				else if(ok[i][0])printf("n");
				else printf("y");
			}
			puts("");
		}

	}
}
