#include <bits/stdc++.h>
#define For(_, L, R) for(int _ = L; _ <= R; ++_)
using namespace std;
int main() {
	int N, K;
	cin >> N >> K;
    if (K > N / 2) K = N - K + 1;
    printf("%d\n", N == 1 ? 1 : 2 * K);
    return 0;
}

