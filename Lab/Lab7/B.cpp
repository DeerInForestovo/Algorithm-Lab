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
const int MaxN = 1100000 + 10;
const int Mod = 998244353;
inline int Pow(int A, int B) {
	int Ans = 1;
	while(B) {
		if(B & 1) Ans = 1ll * Ans * A % Mod;
		A = 1ll * A * A % Mod;
		B >>= 1;
	}
	return Ans;
}
const int G = 3;
const int iG = Pow(G, Mod - 2);
int N, M, Lim = 1, L, R[MaxN];
void NTT(int *A, int type) {
	For(i, 0, Lim - 1)
		if(i < R[i]) swap(A[i], A[R[i]]);
	for(int i = 1; i < Lim; i <<= 1) {
		int wn = Pow(type == 1 ? G : iG, (Mod - 1) / (i << 1));
		for(int R = i << 1, j = 0; j < Lim; j += R) {
			int w = 1;
			for(int k = 0; k < i; ++k, w = 1ll * w * wn % Mod) {
				int x = A[j + k], y = 1ll * w * A[j + k + i] % Mod;
				A[j + k] = (x + y) % Mod;
				A[j + k + i] = (x - y + Mod) % Mod;
			}
		}
	}
	if(type == -1) {
		int inv = Pow(Lim, Mod - 2);
		For(i, 0, Lim - 1)
			A[i] = 1ll * A[i] * inv % Mod;
	}
}
int A[MaxN], B[MaxN], A2[MaxN], B2[MaxN], A3[MaxN], B3[MaxN], C[MaxN];
char S[MaxN];
int Charmap[300];
int main() {
	Charmap['?'] = 0, Charmap['0'] = 1, Charmap['1'] = 2;
	cin >> S;
	N = strlen(S); 
	For(i, 0, N - 1) {
		A[i] = Charmap[S[i]];
		A2[i] = A[i] * A[i];
		A3[i] = A2[i] * A[i];
		B[i] = Charmap[S[N - 1 - i]];
		B2[i] = B[i] * B[i];
		B3[i] = B2[i] * B[i];
	}
	while(Lim <= N + N + 2) Lim <<= 1, ++L;
	For(i, 0, Lim - 1) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
	NTT(A, 1); NTT(B, 1); NTT(A2, 1); NTT(B2, 1); NTT(A3, 1); NTT(B3, 1);
	For(i, 0, Lim - 1)
		C[i] = ((1ll * A[i] * B3[i] + 1ll * B[i] * A3[i] - 2ll * A2[i] * B2[i]) % Mod + Mod) % Mod;
	NTT(C, -1);
	long long Ans = 0;
	For(i, 1, N / 2)
		if(C[i - 1] == 0)
			Ans ^= 1ll * i * i;
	printf("%lld\n", Ans);
	return 0;
}
