#include <bits/stdc++.h>
#define For(_, L, R) for(int _ = L; _ <= R; ++_)
#define SQU(x) ((x)*(x))
using namespace std;
const int MaxN = 1000 + 10;
int N, K, M;
long long X[MaxN], Y[MaxN];
int Find[MaxN];
int F(int N) {
	return N == Find[N] ? N : Find[N] = F(Find[N]);
}
vector<pair<long long, pair<int, int>>> Edge;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> N >> K;
	For(i, 1, N) cin >> X[i] >> Y[i];
	M = N;
	For(i, 1, N) Find[i] = i;
	For(i, 1, N) For(j, i + 1, N)
		Edge.push_back(make_pair(SQU(X[i] - X[j]) + SQU(Y[i] - Y[j]), make_pair(i, j)));
	sort(Edge.begin(), Edge.end());
	for(auto e : Edge) {
		long long w = e.first;
		int u = e.second.first, v = e.second.second;
		if(F(u) == F(v)) continue;
		if(M == K) return not printf("%.2lf\n", sqrt(w));
		--M;
		Find[Find[u]] = Find[v];
	}
}
