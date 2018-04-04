#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
#define ld long double
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	int t;
	sc(t);
	while(t--){
		ld A,B,X,Y;
		cin>>A>>B>>X>>Y;
		if(A<B)swap(A,B);
		if(X<Y)swap(X,Y);
		if(X<A&&Y<B)puts("Escape is possible.");
		else if(Y>=B)puts("Box cannot be dropped.");
		else{
			ld v=1.0*Y/X;
			ld x=(v*B-v*v*A)/(1-v*v);
			ld y=(v*A-v*x);
			ld h1=hypot(x,y);
			ld h2=h1/v;
			if(h1>Y&&h2>X)puts("Escape is possible.");
			else puts("Box cannot be dropped.");
		}

	}
}
