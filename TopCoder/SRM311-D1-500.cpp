#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

ll tot[15];
ll solve(ll x){
	if(x<=0)return 0;
	ll ret=0;
	ll ml=1;
	ll v=0;
	ll j=0;
	while(x){
		int val=x%10;
		for(int i=0;i<val;i++)
			ret+=i*ml+tot[j];
		ret+=val*(v+1);
		v+=val*ml;
		ml*=10;
		x/=10;
		j++;
	}
	return ret;
}
class SumThemAll{
public:
	long long getSum(int lowerBound, int upperBound){
		tot[1]=45;
		for(ll i=2,ml=10;i<15;i++,ml*=10)
			tot[i]=10*tot[i-1]+ml*tot[1];
		return solve(upperBound)-solve(lowerBound-1);
	}
};
