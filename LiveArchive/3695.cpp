/*
   iterate Ysmall,Ybig (top and bottom borders) , sort all points on x , iterate from left to right and use cumulative sum
   with storing best left border to quickly calculate the answer
*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
#define X first
#define Y second
const int N=105;
ii arr[N];
int n;

int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	int tc=1;
	while(sc(n),n){
		lop(i,n)sc(arr[i].X),sc(arr[i].Y);
		sort(arr,arr+n);
		int out=0;
		lop(i,n)lop(j,n){
			if(arr[i].Y>arr[j].Y)continue;
			int ysum=0,bst=0,ys=arr[i].Y,yb=arr[j].Y;
			lop(k,n){
				int z=k;
				while(z+1<n&&arr[z+1].X==arr[z].X)z++;
				int tmp=0,tmp2=0;
				for(int r=k;r<=z;r++){
					if(arr[r].Y>=ys&&arr[r].Y<=yb)
						tmp++;
					if(arr[r].Y>ys&&arr[r].Y<yb)
						tmp2++;
				}

				out=max(out,tmp+ysum+bst);
				bst=max(bst,tmp2-ysum);
				for(int r=k;r<=z;r++)
					if(arr[r].Y==ys||arr[r].Y==yb)
						ysum++;
				k=z;
			}
		}
		printf("Case %d: %d\n",tc++,out);
	}
}
