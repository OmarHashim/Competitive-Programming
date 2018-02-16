/*
    for all pairs i,j
    if for some k mat[i][k]+mat[k][j] <mat[i][j], then measurements are incorrect
    if for some k mat[i][k]+mat[k][j]==mat[i][j], then there is no need for and edge between i and j
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=105;
int mat[N][N],n;

int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	int t;
	sc(t);
	lop(tc,t){
		sc(n);
		for(int i=1;i<n;i++){
			for(int j=0;j<i;j++){
				sc(mat[i][j]);
				mat[j][i]=mat[i][j];
			}
		}
		int ok=1;
		vector<ii> out;
		lop(i,n){
			for(int j=i+1;j<n;j++){
				bool ise=1;
				lop(k,n){
					if(k==i||k==j)continue;
					if(mat[i][k]+mat[k][j]<mat[i][j])ok=0;
					if(mat[i][k]+mat[k][j]==mat[i][j])ise=0;
				}
				if(ise)out.push_back(ii(i,j));
			}
		}
		printf("Case #%d:\n",tc+1);
		if(!ok)puts("Need better measurements.");
		else{
			cout<<out.size()<<endl;
			lop(i,out.size())
			printf("%d %d %d\n",out[i].first+1,out[i].second+1,mat[out[i].first][out[i].second]);
		}
		puts("");

	}
}
