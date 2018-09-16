/*
    if some a exists where a=x^3, we can factorize x and use just 1 of its prime numbers so instead of trying all values of a
    we just use values of a that are prime number power 3
    we need to count no.s that are divisible by (p1)^3,(p2)^3 ...
    which are n/(p1^3) , n/(p2^3) ...
    but now we count numbers that are divisible by both p1^3 and p2^3 twice
    then we also need to divide by n/((p1)^3 * (p2)^3) , ..
    i.e we need to use inclusion exclusion
    since p^3<=n we have p<=10^6
    after some analysis it turns out that brute forcing all numbers of the form p1^3 * p2^3 * p3^3..<=10^18 is doable,
    we can iterate all such numbers and divide each input by that list
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int maxS=1e6+200;
bitset<maxS+1> ip;
vector<int> primes;
void sieve(){
    ip.set();ip[0] = ip[1] = 0;
    for (int i = 2; i*i <= maxS; i++)
    if (ip[i])for (int j = i*i; j <= maxS; j+=i)ip[j] = 0;
    for(int i=2;i<=maxS;++i)if(ip[i])primes.push_back(i);
}
ll n;
set<ll> st;
ll solve(int idx,ll val,bool p){
    if(val*pow(primes[idx],3)>1e18)
        return 0;
    ll nval=val*primes[idx]*primes[idx]*primes[idx];
    st.insert(nval*(p ? -1:1));
    return solve(idx+1,val,p)+solve(idx+1,nval,p^1);
}
int main(){
#ifndef ONLINE_JUDGE
    //freopen("i.txt","r",stdin);
#endif
    sieve();
    solve(0,1,0);
    int t;
    sc(t);

    while(t--){
        scl(n);
        ll out=0;
        for(auto v:st)
            out+=n/v;
        printf("%lld\n",out);
    }
}
