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
int Map[1005][1005];
long long Val[1005][1005];
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    cin >> N >> M;
    int cnt = 0;
    long long Sum = 0;
    For(i, 1, N)
        For(j, 1, M) {
            cin >> Val[i][j];
            Sum += Val[i][j];
            Map[i][j] = ++cnt;
        }
    S = N * M + 1;
    T = S + 1;
    For(i, 1, N)
        For(j, 1, M)
            if((i ^ j) & 1) {
                Add(S, Map[i][j], Val[i][j]);
                if(i != 1) Add(Map[i][j], Map[i-1][j], Inf);
                if(i != N) Add(Map[i][j], Map[i+1][j], Inf);
                if(j != 1) Add(Map[i][j], Map[i][j-1], Inf);
                if(j != M) Add(Map[i][j], Map[i][j+1], Inf);
            } else
                Add(Map[i][j], T, Val[i][j]);
    N = T;
    while(Bfs()) Ans += Dfs(S, Inf);
    cout << Sum - Ans << endl;
    return 0;
}