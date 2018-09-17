/*
    (x+1)^2 = x^2 +2*x +1, so if there are x snowballs in some cell and 1 more falls , answer is increased by 2*x+1
    then if we sort blizzards by range, and iterate each snow ball, we can find out expected no. of snowballs in the cell where
    the current snow ball will fall, then answer will be increased by 2 * (cnt/((2*range[i]+1)^2)) + 1
    where cnt is the no. of snowballs so far
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

class MagicBlizzard{
public:
	double expectation(vector <int> range, vector <int> amount){
		vector<ii> vec;
		int n=range.size();
		lop(i,n)vec.push_back(ii(range[i],amount[i]));
		sort(vec.begin(),vec.end());
		int cnt=0;
		double ret=0;
		lop(i,n)
			lop(j,vec[i].second)
				ret+=2.0*cnt++/(vec[i].first+1)/(vec[i].first+1) +1;
		return ret;
	}
};
