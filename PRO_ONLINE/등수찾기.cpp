#include <stdio.h>
#include <list>
#include <vector>
#include <string.h>
using namespace std;

vector<int> muchThan[100001];
vector<int> lessThan[100001];

int visited[100001];

template<typename T>
int DFS(T edge[]) {
	int rst = 0;
	// exit
	if (T.size() == 0) {
		return 1;
	}
	
	for (int i = 0; i < edge.size(); i++) {
		if (!visited[edge[i]]) {
			visited[edge[i]] = 1;
			rst += DFS(muchThan[edge[i]]);
		}
	}
	rst += 1;

	return rst;
}

int N, M, X;
int U, V;
int main() {
	freopen("input.txt", "r", stdin);
	int muchCnt, lessCnt;
	int best, worst;
	scanf("%d %d %d", &N, &M, &X);
	for (; M; M--) {
		scanf("%d %d", &U, &V);
		muchThan[U].push_back(V);
		lessThan[V].push_back(U);
	}
	
	if (muchThan[X].size() > 0) {
		visited[X]=1;
		muchCnt = DFS(muchThan);
		muchCnt--;
	}
	else {
		muchCnt = 0;
	}
	memset(visited, 0, sizeof(visited));

	if (lessThan[X].size() > 0) {
		visited[X] = 1;
		lessCnt = DFS(lessThan);
		lessCnt--;
	}
	else {
		lessCnt = 0;
	}
	
	best = lessCnt + 1;
	worst = N - muchCnt;
	printf("%d %d\n", best, worst);
	return 0;
}