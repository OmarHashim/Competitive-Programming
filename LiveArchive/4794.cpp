/*
      dp state x,mask where x is one dimension of the current chocolate bar, the second dimension is sum of mask divided by x
      iterate submasks whose sum are either divisible by x or y ( the second dimension), and split the chocolate bar accordingly
*/

#include<bits/stdc++.h>
using namespace std;

#define scl(x) scanf("%lld",&x)
#define sc(x)  scanf("%d",&x)
#define ll long long
#define lop(i,n) for(int i=0;i<n;++i)
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
#define CLR(a,v) memset(a,v,sizeof(a))
#define PC(a) __builtin_popcount(a)

const int MAX = 105;
int n, X, Y, parts[MAX], memo[MAX][1 << 15], TC, sum[1 << 15];

void init() {
	CLR(memo, -1);
	CLR(sum, 0);
}

int rem(int x, int y) {
	return (x & ~y);
}

int solve(int x, int MSK) {
	int unserved = ((1 << n) - 1) ^ MSK;
	int y = sum[unserved] / x;
	if (PC(unserved) == 1)
		return 1;
	int &ret = memo[x][MSK];
//	cout << x << ' ' << unserved << endl;
	if (~ret)
		return ret;
	ret = 0;
	int msk = (unserved - 1) & unserved;
	for (; !ret; msk = (msk - 1) & unserved) {
		int other = unserved ^ msk;
		if (other > msk)
			break;
		if (sum[msk] % y == 0 && sum[other] % y == 0 && sum[msk] / y <= 100
				&& sum[other] / y <= 100)
			ret |= (solve(sum[msk] / y, MSK | other)
					&& solve(sum[other] / y, MSK | msk));
		if (sum[msk] % x == 0 && sum[other] % x == 0 && sum[msk] / x <= 100
				&& sum[other] / x <= 100)
			ret |= (solve(x, MSK | other) && solve(x, MSK | msk));
	}

	return ret;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("i.txt", "r", stdin);
#endif
	while (scanf("%d", &n) == 1 && n) {
		printf("Case %d: ", ++TC);
		init();
		scanf("%d%d", &X, &Y);
		int tot = 0;
		for (int i = 0; i < n; ++i)
			scanf("%d", &parts[i]), tot += parts[i];
		if (tot != X * Y) {
			puts("No");
			continue;
		}
		for (int i = 0; i < (1 << n); ++i) {
			for (int j = 0; j < n; ++j)
				if ((i >> j) & 1)
					sum[i] += parts[j];
		}

		puts(solve(min(X, Y), 0) ? "Yes" : "No");
	}
}
