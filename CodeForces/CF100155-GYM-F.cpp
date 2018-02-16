/*
   dp[l][x][y][mask]
   l: remaining length
   x,y: coordinates of last used point
   mask: which points have i used so far
   answer = sum over dp[l][x][y][(1<<id(x,y))] for all x,y that are not forbidden
*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

bool isvalid(int x,int y){
	return x>=1&&y>=1&&x<=3&&y<=4;
}

int dx[]={1,1,1,-1,-1,-1,0,0};
int dy[]={0,1,-1,0,1,-1,1,-1};
vector<ii> passes[5][5][5][5];
int state[5][5];
int memo[100][5][5][(1<<12)];
int getid(int x,int y){
	return (y-1)*3+x-1;
}
int n,l;
int solve(int x,int y,int mask){
	if(l==0)return 1;
	if(l<0)return 0;
	int &ret=memo[l][x][y][mask];
	if(~ret)return ret;
	ret=0;
	for(int i=1;i<=3;i++)
		for(int j=1;j<=4;j++){
			if(state[i][j])continue;
			bool ok=1;
			lop(k,passes[x][y][i][j].size()){
				int a=passes[x][y][i][j][k].first;
				int b=passes[x][y][i][j][k].second;
				if(state[a][b]!=1)ok=0;
			}
			if(ok){
				state[i][j]=1;
				l-=abs(x-i)+abs(y-j);
				ret+=solve(i,j,mask|(1<<(getid(i,j))));
				l+=abs(x-i)+abs(y-j);
				state[i][j]=0;
			}
		}
	return ret;
}
void pr(int x,int y,int ii,int jj,int i,int j){
	for(int a=1;a<=3;a++){
		for(int b=1;b<=4;b++){
			if(a==x&&b==y)cout<<"S ";
			else if(a==ii&&b==jj)cout<<"T ";
			else if(a==i&&b==j)cout<<"X ";
			else cout<<". ";
		}
		cout<<endl;
	}
	cout<<endl;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	for(int x=1;x<=3;x++)
		for(int y=1;y<=4;y++){
		//	cout<<getid(x,y)<<endl;
			lop(z,8)
				for(int i=x+dx[z],j=y+dy[z];isvalid(i,j);i+=dx[z],j+=dy[z])
					for(int ii=i+dx[z],jj=j+dy[z];isvalid(ii,jj);ii+=dx[z],jj+=dy[z]){
					//	pr(x,y,ii,jj,i,j);
						passes[x][y][ii][jj].push_back(make_pair(i,j));
					}
		}

	sc(l),sc(n);
	if(l>=100)return puts("BAD MEMORY");
	lop(i,n){
		int x,y;
		sc(x),sc(y);
		state[x][y]=2;
	}
	memset(memo,-1,sizeof memo);
	int out=0;
	for(int x=1;x<=3;x++)
		for(int y=1;y<=4;y++){
			if(!state[x][y]){
				state[x][y]=1;
				out+=solve(x,y,(1<<getid(x,y)));
				state[x][y]=0;
			}
		}
	if(out)
	cout<<out;
	else cout<<"BAD MEMORY";

}
