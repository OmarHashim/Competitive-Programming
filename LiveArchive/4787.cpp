/*
     grid compression and dfs
*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=1e6+10,W=1010;

vector<int> uncomx,uncomy;
int comx(int v){
	return lower_bound(uncomx.begin(),uncomx.end(),v)-uncomx.begin();
}
int comy(int v){
	return lower_bound(uncomy.begin(),uncomy.end(),v)-uncomy.begin();

}
bool isW[2*W][2*W];
int memo[2*W][2*W];
int n,m,w;
bool solve(int i,int j){
	if(i<0||j+1==uncomy.size()||isW[i][j])return 0;
	if(i==0&&j+2==uncomy.size())return 1;
	int &ret=memo[i][j];
	if(~ret)return ret;
	return ret=solve(i,j+1)||solve(i-1,j);
}
int x1[W],x2[W],y11[W],y2[W];

int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	int tc=1;
	while(sc(n),sc(m),sc(w),n||m||w){
		memset(isW,0,sizeof isW);
		memset(memo,-1,sizeof memo);
		uncomx.clear(),uncomy.clear();
		uncomx.push_back(0);
		uncomx.push_back(n);
		uncomy.push_back(0);
		uncomy.push_back(m);
		lop(i,w){
			sc(y11[i]),sc(x1[i]),sc(y2[i]),sc(x2[i]);
			x1[i]=x2[i]=n-1-x1[i];
			uncomx.push_back(x1[i]);
			uncomx.push_back(x2[i]+1);
			uncomy.push_back(y11[i]);
			uncomy.push_back(y2[i]+1);
		}
		sort(uncomx.begin(),uncomx.end());
		uncomx.erase(unique(uncomx.begin(),uncomx.end()),uncomx.end());
		sort(uncomy.begin(),uncomy.end());
		uncomy.erase(unique(uncomy.begin(),uncomy.end()),uncomy.end());

		lop(k,w)
			for(int j=comy(y11[k]);uncomy[j]<=y2[k];j++)
				isW[comx(x1[k])][j]=1;
		ll out=0;
	//	lop(i,uncomx.size()-1){
	//		cout<<i<<": "<<uncomx[i]<<" "<<uncomx[i+1]-1<<", ";
	//	}
	//	cout<<endl;
	//	lop(j,uncomy.size()-1){
	//		cout<<j<<": "<<uncomy[j]<<" "<<uncomy[j+1]-1<<", ";
	//	}
		//cout<<endl;
		lop(i,uncomx.size()-1){// -1 because we dont wanna start at n or m
			lop(j,uncomy.size()-1){
				if(!isW[i][j]&&!solve(i,j)){
				//	cout<<uncomx[i]<<" "<<uncomy[j]<<" ";
					//cout<<uncomx[i+1]-1<<" "<<uncomy[j+1]-1<<" ";
					//cout<<isW[i][j]<<endl;
					out+=(uncomx[i+1]-uncomx[i])*1LL*(uncomy[j+1]-uncomy[j]);
				}
			}
		}
		printf("Case %d: %lld\n",tc++,out);
	}

}
