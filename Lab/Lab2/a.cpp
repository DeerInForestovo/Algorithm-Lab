#include <bits/stdc++.h>
#define For(_, L, R) for(int _ = L; _ <= R; ++_)
using namespace std;
int main() {
	int t;
	cin >> t;
	while(t--) {
		int n;
		cin >> n;
		if(n % 6) printf("Alice\n");
			else printf("Bob\n");
	}
	return 0;
}

