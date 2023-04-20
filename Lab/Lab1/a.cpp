#include <bits/stdc++.h>
#define For(_, L, R) for(int _ = L; _ <= R; ++_)
using namespace std;
const int MaxN = 1000 + 10;
int N;
int Map[MaxN][MaxN], Point[MaxN][MaxN], Lastpro[MaxN], Ans1[MaxN];
int Map2[MaxN][MaxN], Point2[MaxN][MaxN], Nowpro[MaxN], Ans2[MaxN];
char Name[MaxN][13], Name2[MaxN][13], str[13];
queue<int> Q;
const int MaxM = 20000 + 10;
int Id[MaxM], To[MaxM][52], Cnt;
inline int toInt(char c) {
	if(c <= 'Z') return c - 'A';
	return c - 'a' + 26;
}
void Insert(int id, char *strs, int len) {
	int Nod = 0;
	For(i, 0, len - 1) {
		int toint = toInt(strs[i]);
		if(To[Nod][toint] == 0) To[Nod][toint] = ++Cnt;
		Nod = To[Nod][toint];
	}
	Id[Nod] = id;
}
int getId(char *strs, int len) {
	int Nod = 0;
	For(i, 0, len - 1) Nod = To[Nod][toInt(strs[i])];
	return Id[Nod];
}
int main() {
	scanf("%d", &N);
	For(i, 1, N) {
		scanf("%s", Name[i]);
		Insert(i, Name[i], strlen(Name[i]));
	}
	For(i, 1, N) {
		scanf("%s", Name2[i]);
		Insert(i, Name2[i], strlen(Name2[i]));
	}
	For(i, 1, N)
		Q.push(i);
	For(i, 1, N)
		For(j, 1, N) {
			memset(str, 0, sizeof str);
			scanf("%s", str);
			Map[i][j] = getId(str, strlen(str));
			Point[i][Map[i][j]] = N - j;
		}
	For(i, 1, N)
		For(j, 1, N) {
			memset(str, 0, sizeof str);
			scanf("%s", str);
			Map2[i][j] = getId(str, strlen(str));
			Point2[i][Map2[i][j]] = N - j;
		}
	while(!Q.empty()) {
		int Man = Q.front(); Q.pop();
		int Woman = Map[Man][++Lastpro[Man]];
		if(Nowpro[Woman] == 0) Nowpro[Woman] = Man;
		else if(Point2[Woman][Man] > Point2[Woman][Nowpro[Woman]]) {
			Q.push(Nowpro[Woman]);
			Nowpro[Woman] = Man;
		} else Q.push(Man);
	}
	For(i, 1, N) {
		Ans1[Nowpro[i]] = i;
		Ans2[i] = Nowpro[i];
	}
	For(i, 1, N)
		For(j, 1, N)
			if(Point[i][j] > Point[i][Ans1[i]] && Point2[j][i] > Point2[j][Ans2[j]])
				return !printf("Wrong Answer\n");
	For(i, 1, N) {
		printf("%s %s", Name[i], Name2[Ans1[i]]);
		if(i != N) printf("\n");
	}
	return 0;
} 
/*
3
aaa bbbb c
a bb cc
cc a bb
a bb cc
bb cc a
aaa bbbb cc
aaa bbbb cc
aaa bbbb cc

*/
