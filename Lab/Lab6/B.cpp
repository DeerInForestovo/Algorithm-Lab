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
struct Point { long long X, Y; };
bool Cmp(Point &A, Point &B) { return A.X == B.X ? A.Y < B.Y : A.X < B.X; }
const int MaxN = 3000000 + 10;
long long Mindist = (long long)9e16;
double mindist = 3e8;
int N, Q[MaxN];
Point P[MaxN], Reg[MaxN];
inline long long Squ(long long X) { return X * X; }
inline void Update(int i, int j) {
	long long Newdist = Squ(P[i].X - P[j].X) + Squ(P[i].Y - P[j].Y);
	if(Mindist > Newdist) mindist = sqrt(Mindist = Newdist);
}
void Merge(int L, int Mid, int R) {
	int l = L, r = Mid + 1, reg = L;
	while(l <= Mid && r <= R)
		if(P[l].Y < P[r].Y) Reg[reg++] = P[l++];
			else Reg[reg++] = P[r++];
	while(l <= Mid) Reg[reg++] = P[l++];
	while(r <= R) Reg[reg++] = P[r++];
	For(i, L, R) P[i] = Reg[i];
}
void Solve(int L, int R) {
	if(L == R) return;
	int Mid = (L + R) >> 1, Midx = P[Mid].X, Qtop = 0;
	Solve(L, Mid); Solve(Mid + 1, R); Merge(L, Mid, R);
	For(i, L, R)
		if(Midx - mindist < P[i].X && P[i].X < Midx + mindist) {
			for(int j = Qtop; j && P[i].Y - P[Q[j]].Y < mindist; --j) Update(i, Q[j]);
			Q[++Qtop] = i;
		}
}
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N; For(i, 1, N) cin >> P[i].X >> P[i].Y;
	sort(P + 1, P + 1 + N, Cmp);
	Solve(1, N);
	printf("%lld\n", Mindist);
	return 0;
}
