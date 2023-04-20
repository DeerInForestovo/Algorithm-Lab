#include <bits/stdc++.h>
using namespace std;
#define For(_,l,r) for(int _ = l; _ <= r; ++_)
#define _For(_,r,l) for(int _ = r; _ >= l; --_)
template <class R> inline bool Checkmax(R &A, R B) {
	return A < B ? A = B, 1 : 0;
}
template <class R> inline bool Checkmin(R &A, R B) {
	return A > B ? A = B, 1 : 0;
}
const int MaxN = 1000000 + 10;
int N, M, T, C;
int Del[MaxN], Time[MaxN], Val[MaxN];
priority_queue<int> Q, D;
int Top() {
	while(!Q.empty() && !D.empty() && Q.top() == D.top())
		Q.pop(), D.pop();
	return Q.empty() ? 0 : Q.top();
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M >> T;
	For(i, 1, M) {
		if(Del[i]) {
			D.push(-i);
			Val[Del[i]] = 0;
			Time[Del[i]] = 0;
			Del[i] = 0;
			--C;
		}
		int op, k, v;
		cin >> op;
		if(op == 1) {
			cin >> k;
			if(Val[k]) {
				printf("%d\n", Val[k]);
				Del[Time[k]] = 0;
				D.push(-Time[k]);
				Del[Time[k] = i + T + 1] = k;
				Q.push(-Time[k]);
			} else printf("-1\n");
		} else {
			cin >> k >> v;
			if(Val[k]) {
				Val[k] = v;
				Del[Time[k]] = 0;
				D.push(-Time[k]);
				Del[Time[k] = i + T + 1] = k;
				Q.push(-Time[k]);
			} else {
				if(C == N) {
					int t = Del[-Top()];
					Q.pop();
					Del[Time[t]] = 0;
					Time[t] = 0;
					Val[t] = 0;
				} else ++C;
				Del[Time[k] = i + T + 1] = k;
				Val[k] = v;
				Q.push(-Time[k]);
			}
		}
	}
	int t;
	while(t = -Top())
		printf("%d ", Val[Del[t]]), Q.pop();
	printf("\n");
	return 0;
}
