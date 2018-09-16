/*
  suppose we buy sword at shop i, sell at shop j, with i<=j, how much do we sell it for?
  we sell it for q[i]-d[i]*(j-i)-r[j]
  we can rewrite it as such : price = q[i]+d[i]*i -d[i]*j-r[j]
  we can sell that the part q[i]+d[i]*i is added anyway whenever u r selling a sword bought from shop i
  but the part -d[i]*j-r[j] depends on the shop u r selling at, let d[i]=x, j=m, -r[j]=c
  then we can rewrite it as m*x+c, i.e a line equation , then we can use convex hull trick to find optimal shop to sell at
  (optimal j) if you buy the sword from shop i
  but how many swords to buy from shop i ? the k-th sword costs a[i]+b[i]*k , so if we have a[i]+b[i]*k <= sell price, we will make profit
  i.e k<=(sell price-a[i])/b[i]
  so k = floor((sell price-a[i])/b[i]) is the no. of swords we should buy

*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=3e5+100,mod=1e9+7;
inline int add(int a,int b){
   a+=b;
   if(a>=mod)a-=mod;
   return a;
}
inline int mul(int a,int b){
   ll ret=1LL*a*b;
   if(ret>=mod)ret%=mod;
   return ret;
}

ll a[N],b[N],q[N],r[N],d[N];
int n;
deque<pll> dq;
deque<double> start;
double inter(pll a,pll b){
    return (1.0*b.second-a.second)/(a.first-b.first);
}
bool maloshlazma(pll a,pll b,pll c){
    return inter(a,c)<=inter(a,b);
}
void chtAdd(ll m,ll c){
    if(!dq.size()){
        dq.push_back(pll(m,c));
        start.push_back(-1e18);
        return;
    }
    while(dq.size()>1&&maloshlazma(dq[dq.size()-2],dq[dq.size()-1],pll(m,c))){
        dq.pop_back();
        start.pop_back();
    }
    start.push_back(inter(pll(m,c),dq.back()));
    dq.push_back(pll(m,c));
}
ll chtGet(ll x){
    int j=upper_bound(start.begin(),start.end(),double(x))-start.begin()-1;
    return dq[j].first*x+dq[j].second;
}

const int inv2=500000004;
int main(){
#ifndef ONLINE_JUDGE
    //freopen("i.txt","r",stdin);
#endif
    sc(n);
    for(int i=1;i<=n;i++)
        scl(q[i]),scl(a[i]),scl(b[i]),scl(r[i]),scl(d[i]);
    int out=0;
    for(int i=n;i>=1;i--){
        chtAdd(-i,-r[i]); // increasing slopes
        ll price=q[i]+i*d[i]+chtGet(d[i]);
        if(price-a[i]<b[i])
            continue;
        ll k=(price-a[i])/b[i];
        k%=mod;
        price%=mod;
        out=add(out,mul(k,price));
        a[i]%=mod;
        b[i]%=mod;
        int pay=mul(k,k+1);
        pay=mul(pay,inv2);
        pay=mul(pay,b[i]);
        pay=add(pay,mul(a[i],k));
        out=add(out,mod-pay);
    }
    printf("%d\n",out);

}
