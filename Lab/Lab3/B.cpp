#include <bits/stdc++.h>
#define For(_, L, R) for(int _ = L; _ <= R; ++_)
using namespace std;
const int MaxN = 1000000 + 10;
int N;
long long A[MaxN], C[MaxN], Avg, Mid, Ans;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> N;
	For(i, 1, N) {
		cin >> A[i];
		Avg += A[i];
	}
	Avg /= N;
	For(i, 1, N - 1) C[i] = C[i - 1] + A[i] - Avg;
	nth_element(C + 1, C + (N + 1) / 2, C + N + 1);
	Mid = C[(N + 1) / 2];
	For(i, 1, N) Ans += abs(C[i] - Mid);
	cout << Ans << endl;
	return 0;
}

