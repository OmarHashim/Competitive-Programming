/*
   answer is sum of MST edges
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

struct edge{
	int u,v,c;
	edge(int x,int y,int z){
		u=x,v=y,c=z;
	}
	bool operator<(const edge & b)const{
		return c<b.c;
	}
};
vector<edge> vec;
int p[1010];
int findSet(int i){
	return (i==p[i]? i:p[i]=findSet(p[i]));
}
class TimeTravellingSalesman{
public:
	long long determineCost(int n, vector <string> roads){
		string x;
		lop(i,roads.size())x+=roads[i];
		stringstream ss(x);
		int u,v,c;
		while(ss>>u){
			ss.ignore();
			ss>>v;
			ss.ignore();
			ss>>c;
			vec.push_back(edge(u,v,c));
		}
		sort(vec.begin(),vec.end());
		lop(i,n)p[i]=i;
		int cnt=0,sum=0;
		lop(i,vec.size()){
			int ru=findSet(vec[i].u);
			int rv=findSet(vec[i].v);
			if(ru!=rv){
				p[ru]=rv;
				cnt++;
				sum+=vec[i].c;
			}
		}
		if(cnt==n-1)return sum;
		return -1;


	}
};
