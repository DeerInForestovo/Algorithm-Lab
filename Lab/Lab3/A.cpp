#include <bits/stdc++.h>
#define For(_, L, R) for(int _ = L; _ <= R; ++_)
using namespace std;
const int MaxN = 1000 + 10;
int N, Sum, T[MaxN], W[MaxN];
vector<int> Time[MaxN];
priority_queue<int> Q;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> N;
	For(i, 1, N) cin >> T[i];
	For(i, 1, N) cin >> W[i];
	For(i, 1, N) Time[T[i]].push_back(W[i]);
	For(i, 1, N) {
		int sz = (int)Time[i].size();
		For(j, 1, sz) {
			int Game = Time[i][j - 1];
			Q.push(-Game);
			if((int)Q.size() > i) {
				Sum -= Q.top();
				Q.pop();
			}
		}
	}
	cout << Sum << endl;
	return 0;
	// Time Complexity: O(NlogN)
}

