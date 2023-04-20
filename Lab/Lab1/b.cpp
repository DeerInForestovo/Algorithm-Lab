#include <bits/stdc++.h>
#define For(_, L, R) for(int _ = L; _ <= R; ++_)
using namespace std;
const int MaxN = 1000 + 10;
int N, M;
int Cap[MaxN];
pair<int,int> Point1[MaxN][MaxN];
int lastApply[MaxN];
int Point2[MaxN][MaxN];
queue<int> Q;
priority_queue<pair<int,int>> enrolled[MaxN];

bool Enroll[MaxN][MaxN];
int Point[MaxN][MaxN];
int enrollSchool[MaxN], worstStudent[MaxN], enrollNumber[MaxN];

inline void Check() {
	For(i, 1, N)
		For(j, 1, M)
			if(Enroll[i][j]) {
				if(Point[i][j] < 0) printf("Student %d would prefer not to enroll school %d.\n", i, j);
				if(Point2[j][i] < 0) printf("School %d would prefer not accept student %d.\n", j, i);
			} else {
				if(Point[i][enrollSchool[i]] < Point[i][j] && Point2[j][i] > 0 && (enrollNumber[j] < Cap[j] || worstStudent[j] < Point2[j][i])) printf("Student %d and school %d formed an unstable pair.\n", i, j);
			}
}

int main() {
	
//	freopen("b.in", "r", stdin);
//	freopen("b.out", "w", stdout);
	
	scanf("%d%d", &N, &M);
	For(i, 1, M) scanf("%d", &Cap[i]);
	For(i, 1, N) Q.push(i);
	For(i, 1, N) {
		For(j, 1, M) {
			scanf("%d", &Point1[i][j].first);
			Point[i][j] = Point1[i][j].first;
			Point1[i][j].second = j;
		}
		sort(Point1[i] + 1, Point1[i] + 1 + M);
		reverse(Point1[i] + 1, Point1[i] + 1 + M);
	}
	For(i, 1, M)
		For(j, 1, N)
			scanf("%d", &Point2[i][j]);
	while(!Q.empty()) {
		int Student = Q.front(); Q.pop();
		if(lastApply[Student] == M) continue;
		int School = Point1[Student][++lastApply[Student]].second;
		if(Point1[Student][lastApply[Student]].first < 0 || Point2[School][Student] < 0) Q.push(Student);
		else if((int)enrolled[School].size() < Cap[School]) enrolled[School].push(make_pair(-Point2[School][Student], Student));
		else if(-enrolled[School].top().first < Point2[School][Student]) {
			Q.push(enrolled[School].top().second);
			enrolled[School].pop(); 
			enrolled[School].push(make_pair(-Point2[School][Student], Student));
		}
		else Q.push(Student);
	}
	For(i, 1, M) {
		printf("%d ", (int)enrolled[i].size());
//		enrollNumber[i] = (int)enrolled[i].size();
		while(!enrolled[i].empty()) {
			printf("%d ", enrolled[i].top().second);
//			Enroll[enrolled[i].top().second][i] = true;
//			worstStudent[i] = min(worstStudent[i], -enrolled[i].top().first);
//			if(enrollSchool[enrolled[i].top().second]) printf("Student %d enrolled two schools %d and %d.\n", enrolled[i].top().second, i, enrollSchool[enrolled[i].top().second]);
//			enrollSchool[enrolled[i].top().second] = i;
			enrolled[i].pop();
		}
//		if(i != M) printf("\n");
		printf("\n");
	}
	
//	Check();
	
	return 0;
} 
/*
1 1
1
-1
-1

*/
