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
int N, Mod;
inline void Qmod(int &Ans) {
    if(Ans >= Mod) Ans -= Mod;
}
int Dp[3][256][256];
const int sp[8] = {2, 3, 5, 7, 11, 13, 17, 19};  // small primes
vector<int> Num[505];
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    cin >> N >> Mod;
    For(i, 2, N) {
        int lp = -1, j = i;  // largest prime factor
        for(int k = 2; k * k <= j; ++k) {
            if(j % k == 0) Checkmax(lp, k);
            while(j % k == 0) j /= k;
        }
        Checkmax(lp, j);
        Num[lp].push_back(i);
    }
    Dp[0][0][0] = 1;
    For(i, 2, 500) if(Num[i].size()) {
        memcpy(Dp[1], Dp[0], sizeof Dp[1]);
        memcpy(Dp[2], Dp[0], sizeof Dp[2]);
        for(auto p : Num[i]) {
            int s = 0;
            For(i, 0, 7) if(p % sp[i] == 0) s |= 1 << i;
            _For(i, 255, 0) _For(j, 255, 0) if(!(i & j)) {
                if(!(j & s)) Qmod(Dp[1][i | s][j] += Dp[1][i][j]);
                if(!(i & s)) Qmod(Dp[2][i][j | s] += Dp[2][i][j]);
            }
        }
        _For(i, 255, 0) _For(j, 255, 0)
            Dp[0][i][j] = (1ll * Mod + Dp[1][i][j] + Dp[2][i][j] - Dp[0][i][j]) % Mod;
    }
    int Ans = 0;
    _For(i, 255, 0) _For(j, 255, 0) Qmod(Ans += Dp[0][i][j]);
    cout << Ans << endl;
    return 0;
}