#include <bits/stdc++.h>
#define For(_, L, R) for(int _ = L; _ <= R; ++_)
using namespace std;
const int Ans[5][5] = {
	{1, 1, 1, 1, 1},
	{0, 1, 1, 1, 1},
	{0, 0, 2, 1, 1},
	{0, 0, 0, 0, 1},
	{0, 0, 0, 0, 0}},
dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2},
dy[8] = {1, -1, 2, -2, 2, -2, 1, -1};
int Map[5][5], x, y;
int v() {
	int V = 0;
	For(i, 0, 4)
		For(j, 0, 4)
			V += (Map[i][j] != Ans[i][j]);
	return V == 2 ? 1 : V;
}
bool IDAx(int dep, int lim) {
	if(dep == lim) return !(bool)v();
	For(i, 0, 7) {
		int xx = x, yy = y;
		x += dx[i], y += dy[i];
		if(x >= 0 && y >= 0 && x <= 4 && y <= 4) {
			swap(Map[x][y], Map[xx][yy]);
			if(v() + dep <= lim)
				if(IDAx(dep + 1, lim))
					return true;
			swap(Map[x][y], Map[xx][yy]);
		}
		x = xx, y = yy;
	}
	return false;
}
int main() {
	int T; cin >> T; while(T--) {
		For(i, 0, 4)
			For(j, 0, 4) {
				char C = getchar();
				while(C != '0' && C != '1' && C != '*') C = getchar();
				if((Map[i][j] = (C == '1' ? 1 : (C == '0' ? 0 : 2))) == 2) x = i, y = j;
			}
		bool notfound = true;
		For(i, 0, 15)
			if(IDAx(0, i)) {
				cout << i << endl;
				notfound = false;
				break;
			}
		if(notfound) cout << -1 << endl;
	}
	return 0;
}
/*
1
11111
01111
00111
0000*
00000

*/
