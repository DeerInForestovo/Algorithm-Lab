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
const int Mod = 12345678;
inline void Qmod(int &A) {
	if(A >= Mod) A -= Mod;
}
int N, M, K;
int Dp[155][155][25][25];
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M >> K;
	Dp[0][0][0][0] = 1;
	For(i, 0, N) For(j, 0, M) For(m, 0, K) For(n, 0, K)
		Qmod(Dp[i + 1][j][m + 1][max(0, n - 1)] += Dp[i][j][m][n]),
		Qmod(Dp[i][j + 1][max(0, m - 1)][n + 1] += Dp[i][j][m][n]);
	int Ans = 0;
	For(i, 0, K) For(j, 0, K)
		Qmod(Ans += Dp[N][M][i][j]);
	cout << Ans << endl;
	return 0;
}

