#include <stdio.h>
#include <list>
#include <vector>
#include <string.h>

using namespace std;

const int LM = 1e5 + 1;
vector<int> highEdge[LM];
vector<int> lowEdge[LM];

bool visited[LM];

template<typename T>

int dfs(int x, T edge[]) {
	if (visited[x]) return 0;
	//방문 표시
	visited[x] = true;
	
	//방문 logic
	int cnt = 1;
	for (auto y : edge[x]) cnt += dfs(y, edge);
	return cnt;	
}

int main() {
	freopen("input.txt", "r", stdin);
	int N, M, X, a, b;
	scanf("%d %d %d", &N, &M, &X);
	for (; M; M--) {
		scanf("%d %d", &a, &b);
		highEdge[b].push_back(a);
		lowEdge[a].push_back(b);
	}
	int highCnt = dfs(X, highEdge) - 1;
	memset(visited, 0, sizeof(visited));
	int lowCnt = dfs(X, lowEdge) - 1;
	printf("%d %d\n", highCnt + 1, N - lowCnt);
	return 0;
}