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
const int MaxN = 2100000 + 10;
struct cp {
	double x, y;
	cp (double X = 0, double Y = 0) { x = X, y = Y; }
};
cp operator + (cp a,cp b) { return cp(a.x + b.x, a.y + b.y); }
cp operator - (cp a,cp b) { return cp(a.x - b.x, a.y - b.y); }
cp operator * (cp a,cp b) { return cp(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
cp A[MaxN], B[MaxN], C[MaxN];
const double pi = acos(-1.0);
int N, M, Lim = 1, L;
int R[MaxN];
void FFT(cp *A, int type) {
	For(i, 0, Lim - 1)
		if(i < R[i]) swap(A[i], A[R[i]]);
	for(int i = 1; i < Lim; i <<= 1) {
		cp wn = cp(cos(pi / i), type * sin(pi / i));
		for(int R = i << 1, j = 0; j < Lim; j += R) {
			cp w = cp(1, 0);
			for(int k = 0; k < i; ++k, w = w * wn) {
				cp x = A[j + k], y = w * A[j + k + i];
				A[j + k] = x + y;
				A[j + k + i] = x - y;
			}
		}
	}
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	For(i, 1, N) {
		cin >> A[i].x;
		B[i].x = 1.0 / i / i;
		C[N - i].x = A[i].x;
	}
	while(Lim <= (N << 1)) Lim <<= 1, ++L;
	For(i, 0, Lim - 1) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
	FFT(A, 1); FFT(B, 1); FFT(C, 1);
	For(i, 0, Lim - 1) A[i] = A[i] * B[i], C[i] = C[i] * B[i];
	FFT(A, -1); FFT(C, -1);
	For(i, 1, N) printf("%.5lf\n", (A[i].x - C[N - i].x) / Lim);
	return 0;
}

