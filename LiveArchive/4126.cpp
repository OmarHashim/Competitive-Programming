/*
   we want to make a dp where state is which strings have we already finished (a mask), an index in the big string,
   and for each unfinished string how many characters in it have we matched so far, this will be (2^10)*25*(10^10), but key is that
   we only need to use the string with the maximal match in the state, this reduces the dp to (2^10)*25*10*10 
   then inside the dp we iterate which character we add next and count the answer.
*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=26,M=11;
string arr[M];
int pre[M][M][26];
int n,m;
vector<string> out;
ll memo[(1<<10)][25][10][10];
string bt;
ll solve(int mask,int idx,int id,int match,vector<int> vec){
	if(idx==n){
		if(mask==(1<<m)-1){
			if(out.size()<42)out.push_back(bt);
			return 1;
		}
		return 0;
	}
	ll &ret=memo[mask][idx][id][match];
	if((~ret)&&(!ret||out.size()>=42))return ret;
	ret=0;
	lop(k,26){
		vector<int> nv(m);
		int nmask=mask;
		int nid=0,mx=0;
		lop(i,m){
			nv[i]=pre[i][vec[i]][k];
			if(nv[i]==arr[i].size())nv[i]=0,nmask|=(1<<i);
			if(nv[i]>mx)nid=i,mx=nv[i];
		}
		bt+=string(1,k+'a');
		ret+=solve(nmask,idx+1,nid,mx,nv);
		bt.pop_back();
	}
	return ret;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	int tc=1;
	while(sc(n),sc(m),n||m){
		out.clear();
		memset(memo,-1,sizeof memo);

		lop(i,m)cin>>arr[i];
		lop(i,m)lop(j,arr[i].size())lop(k,26){
			string nw=arr[i].substr(0,j)+string(1,k+'a');
			pre[i][j][k]=0;
			for(int z=j+1;z>=1;z--){
				if(arr[i].substr(0,z)==nw.substr(j+1-z)){
					pre[i][j][k]=z;
					break;
				}
			}
		}
		ll ret=solve(0,0,0,0,vector<int>(m,0));
		printf("Case %d: %lld suspects\n",tc++,ret);
		if(ret<=42){
			lop(i,out.size())cout<<out[i]<<endl;
		}

	}


}
