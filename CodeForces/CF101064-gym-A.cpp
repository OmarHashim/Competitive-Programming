/*
 	 Yp/H = ( P0P x P0P1 ) / ( Ws Hs)
 	 YpWsHs/H = (Xp-X0,Yp-Y0) x (X01,Y01)
 	          = XpY01 - X0Y01 - YpX01 + Y0X01
 	 YpWsHs/H + YpX01 = XpY01 - X0Y01 + Y0X01
 	 Yp ( WSHS/H + X01) = XpY01 - X0Y01 + Y0X01

 	[ Yp =  (XpY01 - X0Y01 + Y0X01) / ( WSHS/H + X01) ]

 	Xp/W = ( P3P x P3P0 ) / WsHs
 	XpWsHs/W = (Xp-X3,Yp-Y3) x (X30,Y30)
 	         = XpY30 - X3Y30 - YpX30 + Y3X30
 	XpWsHs/W = XpY30 - X3Y30 - [(XpY01 - X0Y01 + Y0X01) / ( WSHS/H + X01)]X30 + Y3X30
*/
#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;


long double x[4],y[4],W,H;
void solve(){
	long double Ws=hypot(x[0]-x[1],y[0]-y[1]);
	long double Hs=hypot(x[0]-x[3],y[0]-y[3]);
	long double y30=y[0]-y[3];
	long double x30=x[0]-x[3];
	long double y01=y[1]-y[0];
	long double x01=x[1]-x[0];
	long double t1=(x[0]*y01-y[0]*x01)/(Ws*Hs/H-x01)*x30;
	long double t2=x30*y01/(Ws*Hs/H - x01);
	long double xp=(t1-y[3]*x30+x[3]*y30)/(Ws*Hs/W+y30+t2);
	long double yp=(x[0]*y01-xp*y01-y[0]*x01)/(Ws*Hs/H-x01);
	cout<<fixed<<setprecision(8)<<xp<<" ";
	cout<<fixed<<setprecision(8)<<yp<<endl;
}
void inverted(){
	long double Ws=hypot(x[0]-x[1],y[0]-y[1]);
	long double Hs=hypot(x[0]-x[3],y[0]-y[3]);
	long double y03=y[3]-y[0];
	long double x03=x[3]-x[0];
	long double y10=y[0]-y[1];
	long double x10=x[0]-x[1];
	long double t1=(x[1]*y10-y[1]*x10)/(Ws*Hs/H-x10)*x03;
	long double t2=x03*y10/(Ws*Hs/H - x10);
	long double xp=(t1-y[0]*x03+x[0]*y03)/(Ws*Hs/W+y03+t2);
	long double yp=(x[1]*y10-xp*y10-y[1]*x10)/(Ws*Hs/H-x10);
	cout<<fixed<<setprecision(8)<<xp<<" ";
	cout<<fixed<<setprecision(8)<<yp<<endl;

}

long double cross(){
	long double x0=x[1]-x[0];
	long double y0=y[1]-y[0];
	long double x1=x[2]-x[0];
	long double y1=y[2]-y[0];
	return x0*y1-x1*y0;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("i.txt","r",stdin);
#endif
	cin>>H>>W;
	lop(i,4)cin>>x[i]>>y[i];
	if(cross()<0)inverted();
	else solve();
}
