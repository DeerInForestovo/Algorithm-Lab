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
const long long Inf = 1ll << 32;
int N, M, S, T;
int Cnt = 1, Head[MaxN], To[MaxN], Next[MaxN];
long long W[MaxN], Ans;
inline void _Add(int u, int v, long long w) {
    To[++Cnt] = v;
    W[Cnt] = w;
    Next[Cnt] = Head[u];
    Head[u] = Cnt;
}
inline void Add(int u, int v, long long w) {
    _Add(u, v, w);
    _Add(v, u, 0);
}
int Now[MaxN];  // Present-arc optimization
int Dis[MaxN];  // Layer graph
bool Bfs() {
    For(i, 1, N) Dis[i] = N, Now[i] = Head[i];
    Dis[S] = 0;
    queue<int> Q; Q.push(S);
    while(!Q.empty()) {
        int Nod = Q.front(); Q.pop();
        for(int i = Head[Nod]; i ; i = Next[i])
            if(W[i] > 0 && Dis[To[i]] == N) {
                Q.push(To[i]);
                Dis[To[i]] = Dis[Nod] + 1;
            }
    }
    return Dis[T] != N;
}
long long Dfs(int Nod, long long Limit) {
    if(Nod == T) return Limit;
    long long Tot = 0;
    for(int i = Now[Nod]; i && Limit ; i = Next[i]) {
        Now[Nod] = i;
        if(W[i] > 0 && Dis[To[i]] == Dis[Nod] + 1) {
            long long Flow = Dfs(To[i], min(Limit, W[i]));
            if(Flow == 0) Dis[To[i]] = N;
            else {
                W[i] -= Flow;
                W[i^1] += Flow;
                Tot += Flow;
                Limit -= Flow;
            }
        }
    }
    return Tot;
}
int n, x[MaxN], a[MaxN], dp[MaxN];
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    cin >> n;
    For(i, 1, n) cin >> a[i];
    For(i, 1, n) cin >> x[i];
    // DP part
    For(i, 1, n)
        For(j, 0, i - 1)
            if(a[j] <= a[i])
                Checkmax(dp[i], dp[j] + 1);
    int k = 0;
    For(i, 1, n)
        Checkmax(k, dp[i]);
    cout << k << endl;
    // Flow part
    N = (n + 1) << 1;
    S = N - 1;
    T = N;
    For(i, 1, n) Add((i << 1) - 1, i << 1, x[i]);
    For(i, 1, n) {
        if(dp[i] == 1) Add(S, (i << 1) - 1, Inf);
        if(dp[i] == k) Add(i << 1, T, Inf);
        For(j, i + 1, n)
            if(a[i] <= a[j] && dp[i] + 1 == dp[j])
                Add(i << 1, (j << 1) - 1, Inf);
    }
    while(Bfs()) Ans += Dfs(S, Inf);
    cout << Ans << endl;
    return 0;
}