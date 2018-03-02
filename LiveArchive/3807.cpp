/*
    note that there are atmost 8 marbles, use simple BFS, i represented the state by a mask to tell me which holes are still not filled,
    and the pairs(i,j) where the corresponding marbles currently are, and used a set of vector of pairs to mark visited states
    the code is kind of big but simulate2 is a copy of simulate1 one with just 2 different lines (iterating end to start)
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vector<int>> vvi;
struct node{
	vvi grid;
	vii state;
	int sp,prev;
	node(vvi g,vii s,int a,int b){
		grid=g,state=s,sp=a,prev=b;
	}
};
int di[]={0,0,1,-1};
int dj[]={1,-1,0,0};
int n,m,w;
bool ok[4][4][4];
set<vii> st;
bool valid(int i,int j){
	return i>=0&&j>=0&&i<n&&j<n;
}
void init(){//
	st.clear();
	lop(i,n)lop(j,n)lop(z,4){
		int ti=i+di[z];
		int tj=j+dj[z];
		ok[i][j][z]=valid(ti,tj);
	}

}
vii getState(vvi grid){
	vii ret(1,ii(0,0));
	vector<pair<int,ii>> vec;
	lop(i,n)lop(j,n)if(grid[i][j]<0)ret[0].first|=(1<<(-grid[i][j]));
	else if(grid[i][j]>0)vec.push_back(make_pair(grid[i][j],ii(i,j)));
	sort(vec.begin(),vec.end());
	lop(i,vec.size())ret.push_back(vec[i].second);
	return ret;
}
bool Simulate1(vvi grid,int z,vvi &ret){
	//cout<<"simulating1 "<<di[z]<<" "<<dj[z]<<endl;
	//cout<<"start\n";
	//lop(i,n)lop(j,n)printf("%d%c",grid[i][j]," \n"[j+1==n]);
	//cout<<endl;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
			if(grid[i][j]>0){
				int ci=i,cj=j;
				while(ok[ci][cj][z]){// final ci,cj for this marble
					ci+=di[z];
					cj+=dj[z];
					if(grid[ci][cj]>0){
						ci-=di[z],cj-=dj[z];
						break;
					}
					if(grid[ci][cj]<0)break;
				}
				if(ci==i&&cj==j)continue;
				if(grid[ci][cj]<0){
					if(-grid[ci][cj]!=grid[i][j])return 0;
					grid[ci][cj]=0;
				}
				else grid[ci][cj]=grid[i][j];
				grid[i][j]=0;
			}
		}
	ret=grid;
//	cout<<"end\n";
//	lop(i,n)lop(j,n)printf("%d%c",grid[i][j]," \n"[j+1==n]);
//	cout<<endl;
	return 1;
}
bool Simulate2(vvi grid,int z,vvi &ret){
	//cout<<"simulating2 "<<di[z]<<" "<<dj[z]<<endl;
	//cout<<"start\n";
	//lop(i,n)lop(j,n)printf("%d%c",grid[i][j]," \n"[j+1==n]);
//	cout<<endl;
	for(int i=n-1;i>=0;i--)
			for(int j=n-1;j>=0;j--){
				if(grid[i][j]>0){
					int ci=i,cj=j;
					while(ok[ci][cj][z]){// final ci,cj for this marble
						ci+=di[z];
						cj+=dj[z];
						if(grid[ci][cj]>0){
							ci-=di[z],cj-=dj[z];
							break;
						}
						if(grid[ci][cj]<0)break;
					}
					if(ci==i&&cj==j)continue;
					if(grid[ci][cj]<0){
						if(-grid[ci][cj]!=grid[i][j])return 0;
						grid[ci][cj]=0;
					}
					else grid[ci][cj]=grid[i][j];
					grid[i][j]=0;
				}
			}
		ret=grid;
	//	cout<<"end\n";
	//	lop(i,n)lop(j,n)printf("%d%c",grid[i][j]," \n"[j+1==n]);
	//	cout<<endl;
		return 1;

}
bool Simulate(vvi grid,int z,vvi &ret){
	if(di[z]==-1||dj[z]==-1)return Simulate1(grid,z,ret);
	return Simulate2(grid,z,ret);
}
node read(){
	vvi grid(n,vi(n,0));
	lop(k,m){
		int i,j;
		sc(i),sc(j);
		grid[i][j]=k+1;
	}
	lop(k,m){
		int i,j;
		sc(i),sc(j);
		grid[i][j]=-(k+1);
	}
	//cout<<"inital grid\n";
	//lop(i,n)lop(j,n)printf("%d%c",grid[i][j]," \n"[j+1==n]);
	//cout<<endl;
	lop(k,w){
		int i,j,i2,j2;
		sc(i),sc(j),sc(i2),sc(j2);
		lop(z,4)if(i+di[z]==i2&&j+dj[z]==j2)ok[i][j][z]=0;
		lop(z,4)if(i==i2+di[z]&&j==j2+dj[z])ok[i2][j2][z]=0;
	}
	vii state=getState(grid);
	return node(grid,state,0,-1);
}
int bfs(){
	queue<node> q;
	q.push(read());
	st.insert(q.front().state);
	while(!q.empty()){
		node cur=q.front();
		q.pop();
	//	cout<<"sp : "<<cur.sp<<", state : ";
	//	lop(i,cur.state.size())printf("(%d,%d) ",cur.state[i].first,cur.state[i].second);
	//	cout<<endl;
		if(cur.state.size()==1)return cur.sp;
		lop(z,4){
			if(z==cur.prev)continue;
			vvi newGrid(n,vector<int>(n,0));
			if(Simulate(cur.grid,z,newGrid)){
				vii newState=getState(newGrid);
				if(st.count(newState))continue;
				st.insert(newState);
				if(newState.size()==1)return cur.sp+1;
				q.push(node(newGrid,newState,cur.sp+1,z));
			}
		}
	}
	return -1;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	int tc=1;
	while(sc(n),sc(m),sc(w),n||m||w){
		init();
		int res=bfs();
		printf("Case %d: ",tc++);
		if(res==-1)printf("impossible\n\n");
		else printf("%d moves\n\n",res);
	}
}
