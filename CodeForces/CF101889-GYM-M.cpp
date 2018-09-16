/*
    if we have just 2 stacks, which one to use first? we find the first index where the values in the stacks are not equal,
    and we take the stack with the smaller value, we take the longer stack if no such value exist
    suppose we sort the stack based on this criteria, when we use some stack we pop the top of that stack, and we want to 
    insert the newly formed stack into our list of stacks, but its just a suffix of the original stack, from here we get the idea of
    using suffix array, we insert all stacks with (301) delimeters between them, now we can find out the order of a suffix of any 
    of the stacks

*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

#define all(c) (c).begin(),(c).end()

const int MX = 500101, alphabetSize = 305;

int str[MX];
int nn;
int bucketID[MX], newbucketID[MX], bucketSt[MX], suf[MX], newSuf[MX];
int head[alphabetSize], nxt[MX], lcp[MX];

void buildSA ( ) {
    memset(head, -1, sizeof head);
    for (nn = 0; !nn || str[nn - 1]; ++nn) {
        nxt[nn] = head[(int) str[nn]];
        head[(int) str[nn]] = nn;
    }
    int ns = 0, ID = 0;
    for (int i = 0; i < alphabetSize; i++) {
        if (head[i] == -1) continue;
        bucketSt[ID] = ns;
        for (int j = head[i]; j != -1; j = nxt[j]) {
            suf[ns++] = j;
            bucketID[j] = ID;
        }
        ID++;
    }

    --ID;
    newSuf[0] = suf[0];
    for (int len = 1; ID != nn - 1; len <<= 1) {

        for (int i = 0; i < nn; i++) {
            int j = suf[i] - len;
            if (j < 0) continue;
            newSuf[bucketSt[bucketID[j]]++] = j;
        }
        ID = 0;
        for (int i = 1; i < nn; i++) {
            ID += (bucketID[newSuf[i - 1]] < bucketID[newSuf[i]]
                    || (bucketID[newSuf[i - 1]] == bucketID[newSuf[i]]
                            && bucketID[newSuf[i - 1] + len] < bucketID[newSuf[i] + len]));
            newbucketID[i] = ID;
            if (newbucketID[i] != newbucketID[i - 1]) bucketSt[ID] = i;
        }
        for (int i = 0; i < nn; i++) {
            suf[i] = newSuf[i];
            bucketID[suf[i]] = newbucketID[i];
        }
    }
}

const int N=1e5+100,mod=1e9+7;
int add(int a,int b){
	a+=b;
	if(a>=mod)a-=mod;
	return a;
}
int mul(ll a,int b){
	a*=b;
	if(a>=mod)a%=mod;
	return a;
}
int pwm(int a,int p){
	int m=a,ret=1;
	while(p){
		if(p&1)ret=mul(ret,m);
		m=mul(m,m);
		p>>=1;
	}
	return ret;
}
vector<int> vec[N];
int n;
int start[N];
int currentIdx[N];

int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	sc(n);
	lop(i,n){
		int k;
		sc(k);
		vec[i].resize(k);
		lop(j,k)
			sc(vec[i][j]);
	}
	int idd=0;
	lop(i,n){
		start[i]=idd;
		lop(j,vec[i].size())str[idd++]=vec[i][j];
		str[idd++]=301;
	}
	buildSA();
	set<ii> st;
	lop(i,n)st.insert(ii(bucketID[start[i]],i));

	int ml=1,inv=pwm(365,mod-2);
	lop(i,n)lop(j,vec[i].size())ml=mul(ml,365);

	int out=0;
	while(st.size()){
		ii cur=*st.begin();
		st.erase(st.begin());
		int i=cur.second;
		out=add(out,mul(ml,vec[i][currentIdx[i]]));
		ml=mul(ml,inv);
		currentIdx[i]++;
		if(currentIdx[i]==vec[i].size())continue;
		st.insert(ii(bucketID[start[i]+currentIdx[i]],i));
	}
	printf("%d\n",out);


}
