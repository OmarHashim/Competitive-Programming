/*
    calculate allpair shortest path, then the second path will consist of sp[from][i]+mat[i][j]+sp[j][to]
    i.e. force 1 bad edge, or sp[from][i]+sp[i][to], force no edges but force a node to be visited,
    1 more case when from=to and it contains a positive self edge
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=55;
int mat[N][N];
int sp[N][N];
int n;
class
Paths{
public:
	int secondBest(vector <string> graph, int from, int to){
		n=graph.size();
		lop(i,n)lop(j,n)if(!isdigit(graph[i][j]))
			sp[i][j]=mat[i][j]=1e8;
		else sp[i][j]=mat[i][j]=graph[i][j]-'0';
		lop(i,n)sp[i][i]=0;
		lop(i,n)lop(j,n)lop(k,n)sp[j][k]=min(sp[j][k],sp[j][i]+sp[i][k]);
		int bst=sp[from][to];
		int ret=1e8;
		lop(i,n)lop(j,n){
			int v=sp[from][i]+mat[i][j]+sp[j][to];
			if(v>bst)ret=min(ret,v);
		}
		lop(i,n){
			int v=sp[from][i]+sp[i][to];
			if(v>bst)ret=min(ret,v);
		}
		if(mat[from][to]>bst)ret=min(ret,mat[from][to]);
		if(ret!=1e8)return ret;
		return -1;
	}
};
