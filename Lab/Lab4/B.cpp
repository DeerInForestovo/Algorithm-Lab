#include <bits/stdc++.h>
#define For(_, L, R) for(int _ = L; _ <= R; ++_)
using namespace std;
const int MaxN = 100000 + 10;
int N, Fa[MaxN], R, Find[MaxN];
vector<int> To[MaxN];
long long Cost[MaxN], Sum[MaxN], C[MaxN], Siz[MaxN];
int F(int N) {
	return N == Find[N] ? N : Find[N] = F(Find[N]);
}
priority_queue<pair<double, int>> Q;
bool Vis[MaxN];
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> N >> R;
	For(i, 1, N) cin >> C[i];
	For(i, 1, N - 1) {
		int U, V;
		cin >> U >> V;
		To[U].push_back(V);
		Fa[V] = U;
	}
	For(i, 1, N) {
		Q.push(make_pair((double)C[i], i));
		Siz[i] = 1;
		Sum[i] = Cost[i] = C[i];
		Find[i] = i;
	}
	Vis[R] = true;
	while(!Q.empty()) {
		int Nod = Q.top().second; Q.pop();
		if(Vis[Nod]) continue;
		Vis[Nod] = true;
		int fa = F(Fa[Nod]);
		Find[Nod] = fa;
		Cost[fa] += Cost[Nod] + Siz[fa] * Sum[Nod];
		Siz[fa] += Siz[Nod];
		Sum[fa] += Sum[Nod];
		Q.push(make_pair((double)Sum[fa] / Siz[fa], fa));
	}
	cout << Cost[R] << endl;
	return 0;
}
/*
5 1
1 2 1 2 4
1 2
1 3
2 4
3 5

5 1
1 1 1 2 1
1 2
2 3
3 5
1 4

*/
