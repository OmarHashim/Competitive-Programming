#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

class GridCut{
public:
	int solve(int w,int h,int n){
		if(w*h==n||w*h==0)return 0;
		int out=1e9;
		for(int i=1;i<=n&&i<=w;i++)
			for(int j=1;i*j<=n&&j<=h;j++){
				int rem=n-i*j;
				if(!rem){
					int temp=0;
					if(j<h)temp+=i;
					if(i<w)temp+=j;
					out=min(out,temp);
				}
				else {
					if(rem<j&&i<w){
						int temp=0;
						if(j<h)temp+=i;
						temp+=j-rem+1;
						if(i+1<w)temp+=rem;
						out=min(out,temp);
					}
					if(rem<i&&j<h){
						int temp=0;
						if(i<w)temp+=j;
						temp+=i-rem+1;
						if(j+1<h)temp+=rem;
						out=min(out,temp);
					}
				}
			}
		return out;
	}
	int cutLength(int w, int h, int n){
		return min(solve(w,h,n),solve(w,h,w*h-n));

	}
};
