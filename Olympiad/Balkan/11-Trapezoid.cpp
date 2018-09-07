/*
    first we need to sort trapezoids by their (a) value. 
    let dp be an array of pairs, where dp[i].first = maximum answer if we last took trapezoid i, dp[i].second= no. of ways
    since last trapezoid we took was i, the next one, let's call it j, must have a[j]>b[i], and since we initially sorted by (a)
    values, we know that valid j's form a suffix of the array.
    but we have one more constraint, c[j]>d[i], to solve this, we can store for each j a segment tree that represents the suffix [j,n+1],
    where leafs are c[j] values, and in each node we store a pair, first is the maximum size and second is the no. of ways,
    but having n segment trees would be too slow, but since segment tree for index j differ from segment tree for
    index j+1 in logn nodes only, we can use persistent segment tree instead.
*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int mod=30013;
int add(int a,int b){
	a+=b;
	if(a>=mod)a-=mod;
	return a;
}

const int N=1e5+100,LG=24;
ii tree[N*LG];
int L[N*LG],R[N*LG],ne;
ii dp[N];
void build(int root,int s,int e){
	if(s==e)return;
	L[root]=ne++;
	R[root]=ne++;
	int m=s+((e-s)>>1);
	build(L[root],s,m);
	build(R[root],m+1,e);
}
ii merge(ii a,ii b){
	if(a.first>b.first)return a;
	if(b.first>a.first)return b;
	return ii(a.first,add(a.second,b.second));

}
void upd(int nroot,int root,int s,int e,int i,ii val){
	if(s==e){
		tree[nroot]=merge(tree[root],val);
		return;
	}
	int m=s+((e-s)>>1);
	if(i<=m){
		L[nroot]=ne++;
		R[nroot]=R[root];
		upd(L[nroot],L[root],s,m,i,val);
	}
	else {
		L[nroot]=L[root];
		R[nroot]=ne++;
		upd(R[nroot],R[root],m+1,e,i,val);
	}
	tree[nroot]=merge(tree[L[nroot]],tree[R[nroot]]);
}
ii get(int root,int s,int e,int l,int r){
	if(e<l||s>r)return ii(0,0);
	if(s>=l&&e<=r)return tree[root];
	int m=s+((e-s)>>1);
	return merge(get(L[root],s,m,l,r),get(R[root],m+1,e,l,r));
}


struct node{
	int a,b,c,d;
	bool operator<(const node &o)const{
		return a<o.a;
	}
}arr[N];
int n;
vector<int> uncom;
int roots[N];

int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	sc(n);
	lop(i,n){
		sc(arr[i].a),sc(arr[i].b);
		sc(arr[i].c),sc(arr[i].d);
		uncom.push_back(arr[i].c);
	}
	uncom.push_back(1e9+1);
	sort(uncom.begin(),uncom.end());
	uncom.erase(unique(uncom.begin(),uncom.end()),uncom.end());
	lop(i,n){
		arr[i].c=lower_bound(uncom.begin(),uncom.end(),arr[i].c)-uncom.begin();
		arr[i].d=upper_bound(uncom.begin(),uncom.end(),arr[i].d)-uncom.begin();
	}
	sort(arr,arr+n);
	roots[n+1]=ne++;
	build(roots[n+1],0,uncom.size()-1);
	arr[n].a=1e9+1;
	upd(roots[n],roots[n+1],0,uncom.size()-1,uncom.size()-1,ii(0,1));
	for(int i=n-1;i>=0;i--){
		node qr;
		qr.a=arr[i].b;
		int start=upper_bound(arr+i+1,arr+n+1,qr)-arr;
		dp[i]=get(roots[start],0,uncom.size()-1,arr[i].d,uncom.size()-1);
		if(!dp[i].first)dp[i].second=1;
		dp[i].first++;
		roots[i]=ne++;
		upd(roots[i],roots[i+1],0,uncom.size()-1,arr[i].c,dp[i]);
	}
	ii out(0,0);
	lop(i,n)
		out=merge(out,dp[i]);
	printf("%d %d\n",out.first,out.second);
}
