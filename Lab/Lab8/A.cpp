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
const int MaxN = 100 + 10;
const int MaxM = 40000 + 10;
int N, C, V[MaxN], W[MaxN], S[MaxN];
struct Queue {
	int Lim, Bias, T[MaxM], W[MaxM], Head, Tail;
	void Push(int t, int w) {
		w -= Bias;
		while(Head < Tail && W[Tail] <= w) --Tail;
		W[++Tail] = w;
		T[Tail] = t;
	}
	void Init(int lim, int w) {
		Bias = Head = T[1] = 0;
		Tail = 1;
		W[1] = w;
		Lim = lim;
	}
	int Pop(int t) {
		while(Head < Tail && T[Head + 1] + Lim < t) ++Head;
		return Head == Tail ? -(1 << 30) : W[Head + 1] + Bias;
	}
} q[MaxN];
int Dp[MaxM], Reg[MaxM];
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> C;
	For(i, 1, N) cin >> W[i] >> V[i] >> S[i];
	For(i, 1, N) {
		For(j, 0, C)
			if(j < V[i]) q[j].Init(S[i], Reg[j] = Dp[j]);
				else {
					int id = j % V[i], t = j / V[i];
					q[id].Bias += W[i];
					Reg[j] = max(Dp[j], q[id].Pop(t));
					q[id].Push(t, Dp[j]);
				}
		memcpy(Dp, Reg, sizeof Dp);
	}
	int Ans = 0;
	For(i, 0, C)
		Checkmax(Ans, Dp[i]);
	cout << Ans << endl;
	return 0;
}

