/*
    there are 4^n different patterns , each have a cetrain probability, what we need to do is run huffman coding
    on them to calculate the answer, but given that 4^n is too large, we have to group together identical nodes, 
    since different permutations of the same pattern have the same probability, we can instead add a "cnt" parameter in the
    huffman coding nodes to quickly solve the problem.
*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
#define ld double
typedef pair<ld,ll> pdl;
int n;
ld arr[4];
ll nCr[30][30];

void calcnCr(){
	lop(i,30)nCr[i][0]=nCr[i][i]=1;
	for(int i=1;i<30;i++)
		for(int j=1;j<i;j++)
			nCr[i][j]=nCr[i-1][j]+nCr[i-1][j-1];
}
ld pr[4][22];
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	calcnCr();
	sc(n);
	lop(i,4){
		cin>>arr[i];
		pr[i][0]=1;
		for(int j=1;j<=n;j++)
			pr[i][j]=pr[i][j-1]*arr[i];
	}
	priority_queue<pdl,vector<pdl>,greater<pdl> > pq;
	ld out=0;
	for(int c0=0;c0<=n;c0++)
		for(int c1=0;c0+c1<=n;c1++)
			for(int c2=0;c0+c1+c2<=n;c2++){
				int c3=n-c0-c1-c2;
				ll ways=nCr[n][c0]*nCr[n-c0][c1]*nCr[n-c0-c1][c2];
				ld val=pr[0][c0]*pr[1][c1]*pr[2][c2]*pr[3][c3];
				pq.push(pdl(val,ways));
			}
	while(pq.size()>=2||pq.top().second>1){
		ld p1=pq.top().first;
		ll cnt1=pq.top().second;
		pq.pop();
		if(cnt1>1){
			ll cnt=cnt1/2;
			out+=(2*p1)*cnt;
			pq.push(pdl(2*p1,cnt));
			if(cnt1&1)
				pq.push(pdl(p1,1));
		}
		else {
			ld p2=pq.top().first;
			ll cnt2=pq.top().second;
			pq.pop();
			out+=(p1+p2);
			pq.push(pdl(p1+p2,1));
			if(cnt2>1)
				pq.push(pdl(p2,cnt2-1));

		}
		/*
		pq.push(pdl(p1+p2,min(cnt1,cnt2)));
		out+=(p1+p2)*min(cnt1,cnt2);
		if(cnt1>cnt2)
			pq.push(pdl(p1,cnt1-cnt2));
		else if(cnt2>cnt1)
			pq.push(pdl(p2,cnt2-cnt1));
		 */
	}
	cout<<fixed<<setprecision(6)<<out<<endl;
}
