/*
    each ship blocks a range of time where the ferry cant start in this range,lets add 2 more ranges (-oo,t1) and (t2,oo)
    for the ferry constraint. lets merge all the ranges and sort them, now we can find the gap between 2 consecutive ranges.
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
#define ld long double
typedef pair<ld,ld> pld;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
const int N=1e5+10;
int n,w,u,v,m1,m2;
char dir[N];
set<pld> st;
void insert(ld a,ld b){
	while(1){
		auto it=st.lower_bound(pld(a,-1e18));
		if(it==st.end())break;
		if(it->first>b)break;
		b=max(b,it->second);
		st.erase(it);
	}
	while(1){
		auto it=st.lower_bound(pld(a,-1e18));
		if(it==st.begin())break;
		it--;
		if(it->second<a)break;
		a=min(a,it->first);
		b=max(b,it->second);
		st.erase(it);
	}
	st.insert(pld(a,b));
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	cin>>n>>w>>u>>v>>m1>>m2;
	lop(i,n){
		cin>>dir[i];
		int k;
		sc(k);
		lop(j,k){
			int len,pos;
			sc(len),sc(pos);
			ld t1,t2,d1,d2;
			if(dir[i]=='E'){
				if(pos-len>=0)continue;
				if(pos<0)d1=-pos,d2=-pos+len;
				else d1=0,d2=-pos+len;
			}
			else {
				if(pos+len<=0)continue;
				if(pos>0)d1=pos,d2=pos+len;
				else d1=0,d2=len+pos;
			}
			//cout<<d1<<" "<<d2<<endl;
			t1=d1/u,t2=d2/u;
			t1-=1.0*(i+1)*w/v;
			t2-=1.0*i*w/v;
			//cout<<t1<<" "<<t2<<endl;
			insert(t1,t2);
		}
	}
	insert(-1e18,m1); //
	insert(m2,1e18); //
	auto it2=st.begin();
	ld out=0;
	for(auto it=it2++;it2!=st.end();it++,it2++){
		out=max(out,it2->first-it->second);
	}
	//for(auto v:st){
		//cout<<v.first<<" "<<v.second<<endl;
	//}
	cout<<fixed<<setprecision(8)<<out;

}
