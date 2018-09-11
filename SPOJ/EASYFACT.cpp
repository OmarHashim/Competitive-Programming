/*
   we want n!=(a+1) + (a+2) + ... + (a+l)
   n!=a*l +l*(l+1)/2
   2*n!=l*(2*a+l+1)
   let x=l,y=2*a+l+1 then we want to count pairs(x,y) where x>=2,x<y and x,y have different parity
   this is equivalent to counting no. of odd divisors of n!
   let n!=(3^k1)*(5^k2)*(7^k3)*(11^k4)...
   then answer is (k1+1)*(k2+1)*(k3+1)*(k4+1)...
   to count k for some prime p, k=n/p +n/(p*p) +n/(p*p*p) + ... 
   time will fit to do this for first 10^4 primes,after wards we have count(p)<=1000, and for each of these values
   there is a range of consecutive primes that result in them, so we use binary search for each value which also fits the time
   

*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int maxS=1e8+200;
bitset<maxS> ip;
vector<int> primes;
void sieve(){
	ip.set();ip[0] = ip[1] = 0;
	for (int i = 2; i*i < maxS; i++)
	if (ip[i])for (int j = i*i; j < maxS; j+=i)ip[j] = 0;
	for(int i=2;i<=maxS;++i)if(ip[i])primes.push_back(i);
}
// no. of primes to 10^8 = 5761455
int cnt(int n,int p){
	int ret=0;
	n/=p;
	while(n){
		ret+=n;
		n/=p;
	}
	return ret;
}
int n,mod;
int mul(ll a,int b){
	a*=b;
	if(a>=mod)return a%mod;
	return a;
}
inline int pwm(int a,ll p){
   int m=a,ret=1;
   while(p){
      if(p&1)ret=mul(ret,m);
      m=mul(m,m);
      p>>=1;
   }
   return ret;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	sieve();
	int t;
	sc(t);
	while(t--){
		sc(n),sc(mod);
		int out=1;
		for(int i=1;i<10000;i++)
			out=mul(out,(cnt(n,primes[i])+1)%mod);
		int cur=10000;
		while(primes[cur]<=n){
			int val=cnt(n,primes[cur]);
			int s=cur,e=primes.size()-1,bst=cur,md;
			while(s<=e){
				md=s+((e-s)>>1);
				if(cnt(n,primes[md])<val)e=md-1;
				else bst=md,s=md+1;
			}
			out=mul(out,pwm(val+1,bst-cur+1));
			cur=bst+1;
		}
		printf("%d\n",(out+mod-1)%mod);


	}

}
