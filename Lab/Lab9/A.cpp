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
const int MaxN = 200000 + 10;
int N;
int Head[MaxN], To[MaxN], Next[MaxN], Cnt;
inline void Add(int U, int V) {
	To[++Cnt] = V;
	Next[Cnt] = Head[U];
	Head[U] = Cnt;
}
long long V[MaxN], Plus[MaxN], Minus[MaxN];
void Dfs(int Nod, int Fa) {
	for(int i = Head[Nod]; i ; i = Next[i])
		if(To[i] != Fa) {
			Dfs(To[i], Nod);
			Checkmax(Plus[Nod], Plus[To[i]]);
			Checkmax(Minus[Nod], Minus[To[i]]);
		}
	long long Now = V[Nod] + Plus[Nod] - Minus[Nod];
	if(Now < 0) Plus[Nod] -= Now;
		else Minus[Nod] += Now;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	For(i, 1, N - 1) {
		int U, V;
		cin >> U >> V;
		Add(U, V);
		Add(V, U);
	}
	For(i, 1, N) cin >> V[i];
	Dfs(1, 0);
	cout << Plus[1] + Minus[1] << endl;
	return 0;
}