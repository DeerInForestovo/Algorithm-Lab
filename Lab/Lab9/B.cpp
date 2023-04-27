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
const int MaxN = 27000 + 10;
int N, M;
int Head[MaxN], To[MaxN], Next[MaxN], V[MaxN], P[MaxN], Cnt;
double W[MaxN], Dis[MaxN];
inline void Add(int S, int T) {
	To[++Cnt] = T;
	Next[Cnt] = Head[S];
	Head[S] = Cnt;
}
bool Vis[MaxN];
bool Spfa(int Nod) {
	Vis[Nod] = true;
	for(int i = Head[Nod]; i ; i = Next[i]) {
		if(Dis[To[i]] > Dis[Nod] + W[i]) {
			if(Vis[To[i]]) return false;
				else {
					Dis[To[i]] = Dis[Nod] + W[i];
					if(!Spfa(To[i])) return false;
				}
		}
	}
	Vis[Nod] = false;
	return true;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M;
	For(i, 1, M) {
		int S, T;
		cin >> S >> T >> V[i];
		Add(S, T);
	}
	For(i, 1, M) cin >> P[i];
	For(i, 1, N) Add(0, i);
	double L = 0.0, R = 256.0, Mid;
	For(_, 1, 15) {
		Mid = (L + R) / 2;
		For(i, 1, M) W[i] = Mid * P[i] - V[i];
		memset(Dis, 127, sizeof Dis);
		memset(Vis, 0, sizeof Vis);
		Dis[0] = 0.0;
		if(Spfa(0)) R = Mid;
			else L = Mid;
	}
	if(fabs(L) < 1e-3) printf("-1\n");
		else printf("%.1f\n", L);
	return 0;
}