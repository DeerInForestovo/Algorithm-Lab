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
const int MaxN = 500 + 10;
int N, M;
char S[MaxN];
int Dp[MaxN][MaxN];
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    cin >> M;
    cin >> (S + 1);
    For(i, 1, M)
        if(S[i] != S[i - 1])
            S[++N] = S[i];
    For(i, 1, N) {
        Dp[i][i] = 1;
        For(j, i + 1, N)
            Dp[i][j] = 1000;
    }
    For(l, 2, N)
        For(i, 1, N - l + 1) {
            int j = i + l - 1;
            For(k, i, j - 1)
                Checkmin(Dp[i][j], Dp[i][k] + Dp[k + 1][j]);
            if(S[i] == S[j]) {
                For(k, i + 1, j - 1)
                    Checkmin(Dp[i][j], Dp[i + 1][k] + Dp[k + 1][j]);
                For(k, i, j - 2)
                    Checkmin(Dp[i][j], Dp[i][k] + Dp[k + 1][j - 1]);
            }
        }
    cout << Dp[1][N] << endl;
    return 0;
}