/*
    construct graph where nodes are triangle points, connect points of same triangle or identical points of different triangles,
    also connect A to all points in triangle or triangles that it lies in, same for B, then run dijkstra which minimizes maximum Z
*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
typedef pair<ii,int> point;
#define X first.first
#define Y first.second
#define Z second

point vec(point a,point b){
	return point(ii(b.X-a.X,b.Y-a.Y),b.Z-a.Z);
}
int cross(point a,point b){
	if(1LL*a.X*b.Y==1LL*a.Y*b.X)return 0;
	return ((1LL*a.X*b.Y>1LL*a.Y*b.X)<<1)-1;
}
int calc(point &a,point &b,point &p){
	return cross(vec(a,b),vec(a,p));
}
bool inTriangle(point &a,point &b,point &c,point &p){
	int res=calc(a,b,p);
	int res2=calc(b,c,p);
	int res3=calc(c,a,p);
	return (res<=0&&res2<=0&&res3<=0) || (res>=0&&res2>=0&&res3>=0);
}
const int N=2005;
int n;
vector<int> adj[3*N];
void pr(point & P){
	printf("%d %d %d\n",P.X,P.Y,P.Z);
}
void rd(point & P){
	scanf("%d %d %d",&P.X,&P.Y,&P.Z);
}
struct node{
	int i,prev,height;
	node(int _i,int _prev,int _height){
		i=_i;
		prev=_prev;
		height=_height;
	}
	bool operator<(const node & b)const{
		return height>b.height;
	}
};
int previ[3*N];
int sh[3*N],A,B;
point points[3*N];

int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	freopen("hiking.in","r",stdin);
	freopen("hiking.out","w",stdout);
	sc(n);
	lop(i,n)lop(j,3)rd(points[3*i+j]);
	lop(i,2)rd(points[3*n+i]);
	A=3*n,B=3*n+1;
	lop(i,n){
		if(inTriangle(points[i*3],points[i*3+1],points[i*3+2],points[A]))
			lop(j,3)adj[A].push_back(i*3+j);
		if(inTriangle(points[i*3],points[i*3+1],points[i*3+2],points[B]))
			lop(j,3)adj[i*3+j].push_back(B);
	}
	lop(i,n)for(int j=i+1;j<n;j++)
		lop(k,3)lop(z,3)
			if(points[3*i+k]==points[3*j+z]){
				adj[3*i+k].push_back(3*j+z);
				adj[3*j+z].push_back(3*i+k);
			}
	lop(i,n)lop(j,3)for(int k=j+1;k<3;k++){
		adj[3*i+j].push_back(3*i+k);
		adj[3*i+k].push_back(3*i+j);
	}

	priority_queue<node> pq;
	pq.push(node(A,A,points[A].Z));
	lop(i,3*n+2)sh[i]=1e9;
	memset(previ,-1,sizeof previ);
	while(!pq.empty()){
		int i=pq.top().i;
		int prev=pq.top().prev;
		int height=pq.top().height;
		pq.pop();
		if(~previ[i])continue;
		sh[i]=height;
		previ[i]=prev;
		if(i==B)break;
		lop(z,adj[i].size()){
			int to=adj[i][z];
			int nheight=max(height,points[to].Z);
			if(sh[to]>nheight){
				sh[to]=nheight;
				pq.push(node(to,i,nheight));
			}
		}
	}
	stack<point> st;
	st.push(points[B]);
	int cur=B;
	while(cur!=A){
		cur=previ[cur];
		if(st.top()!=points[cur])
			st.push(points[cur]);
	}
	cout<<st.size()<<endl;
	while(st.size()){
		pr(st.top());
		st.pop();
	}

}
