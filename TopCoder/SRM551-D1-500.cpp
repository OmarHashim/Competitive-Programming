/*
    main idea is to put edge cost for edge u->v = no. of edges u->i such that i<v
    then you can find shortest path using floyd
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

const int N=55;
int mat[N][N],n;

class ColorfulWolves{
public:
	int getmin(vector <string> colormap){
		n=colormap.size();
		lop(i,n){
			int c=0;
			lop(j,n)
				if(colormap[i][j]=='Y')
					mat[i][j]=c++;
				else mat[i][j]=1e8*(i!=j);
		}
		lop(i,n)lop(j,n)lop(k,n)mat[j][k]=min(mat[j][k],mat[j][i]+mat[i][k]);
		if(mat[0][n-1]>1e6)return -1;
		return mat[0][n-1];
	}
};
