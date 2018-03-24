/*
    construct the BST , represent nodes by ids that they would have in a segment tree, and represent a tree by a vector of ids 
*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

struct node{
	node * left;
	node * right;
	int val;
	node(int x){
		val=x;
		left=right=0;
	}
};
const int N=55;
int n,k;
int arr[55][55];
vector<int> vec;
node * add(node * root,int val){
	if(root==0){
		root = new node(val);
		return root;
	}
	if(val<root->val) root->left=add(root->left,val);
	else root->right=add(root->right,val);
	return root;
}
void dfs(node * root,int idx){
	if(root==0)return;
	vec.push_back(idx);
	if(root->left)
		dfs(root->left,2*idx+1);
	if(root->right)
		dfs(root->right,2*idx+2);
}
void solve(int idx){
	node * root= new node(arr[idx][0]);
	for(int j=1;j<k;j++)
		root = add(root,arr[idx][j]);
	dfs(root,0);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	cin>>n>>k;
	set<vector<int>> st;
	lop(i,n){
		lop(j,k)sc(arr[i][j]);
		vec.clear();
		solve(i);
		st.insert(vec);
	}
	cout<<st.size()<<endl;

}
