/*
   backtrack, just a bit complicated
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=25;
int dx[]={1,-1,0,0,0,0};
int dy[]={0,0,1,-1,0,0};
int dz[]={0,0,0,0,1,-1};
int sx,sy,sz,sf,tx,ty,tz,tf,mxX,mxY,mxZ;
int vis[N][N][N];
bool valid(int x,int y,int z){
	return x>=1&&y>=1&&z>=1&&x<=mxX&&y<=mxY&&z<=mxZ;
}
void undo(vector<int> &vx,vector<int> &vy,vector<int> &vz){
	lop(i,vx.size())
			vis[vx[i]][vy[i]][vz[i]]=0;
}
bool mark(int dir1,int cnt1,int dir2,int cnt2,int &x,int &y,int &z){
	vector<int> vx,vy,vz;
	lop(i,cnt1){
		x+=dx[dir1];
		y+=dy[dir1];
		z+=dz[dir1];
		if(!valid(x,y,z)||vis[x][y][z]){
			undo(vx,vy,vz);
			return 0;
		}
		vis[x][y][z]=1;
		vx.push_back(x);
		vy.push_back(y);
		vz.push_back(z);
	}
	lop(i,cnt2){
		x+=dx[dir2];
		y+=dy[dir2];
		z+=dz[dir2];
		if(!valid(x,y,z)||vis[x][y][z]){
			undo(vx,vy,vz);
			return 0;
		}
		vis[x][y][z]=1;
		vx.push_back(x);
		vy.push_back(y);
		vz.push_back(z);
	}
	return 1;
}
void unmark(int dir1,int cnt1,int dir2,int cnt2,int &x,int &y,int &z){
	lop(i,cnt1){
		x+=dx[dir1];
		y+=dy[dir1];
		z+=dz[dir1];
		vis[x][y][z]=0;
	}
	lop(i,cnt2){
		x+=dx[dir2];
		y+=dy[dir2];
		z+=dz[dir2];
		vis[x][y][z]=0;
	}

}
int bt(int x,int y,int z,int dir,int used){
	if(x==tx&&y==ty&&z==tz&&dir==tf)return used;
	if(used==6)return 10;
	int ret=10;
	for(int first=2;first<=3;first++){
		for(int newdir= (dir+1+(dir%2==0))%6, cnt=0 ;cnt<4;cnt++,newdir=(newdir+1)%6){
			int nx=x,ny=y,nz=z;
			if(mark(dir,first,newdir,4-first,nx,ny,nz)){
				ret=min(ret,bt(nx,ny,nz,newdir,used+1) );
				nx=x,ny=y,nz=z;
				unmark(dir,first,newdir,4-first,nx,ny,nz);
			}
		}
	}
	return ret;
}
string flow;
int getdir(){
	if(flow=="+x")return 0;
	if(flow=="-x")return 1;
	if(flow=="+y")return 2;
	if(flow=="-y")return 3;
	if(flow=="+z")return 4;
	if(flow=="-z")return 5;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	int tc=1;
	while(sc(mxX),mxX){
		sc(mxY),sc(mxZ);
		sc(sx),sc(sy),sc(sz);
		cin>>flow;
		sf=getdir();
		sx+=dx[sf^1];
		sy+=dy[sf^1];
		sz+=dz[sf^1];
		sc(tx),sc(ty),sc(tz);
		cin>>flow;
		tf=getdir();
		int res=bt(sx,sy,sz,sf,0);
		//int res=0;
		printf("Case %d: ",tc++);
		if(res>6)puts("Impossible");
		else printf("%d\n",res);
	}
}
