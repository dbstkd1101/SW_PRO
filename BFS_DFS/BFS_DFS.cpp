#include <stdio.h>
#include  <stdlib.h>

#define MAX 1000

int visited[MAX+1];
int graph[MAX][MAX];
int queue[MAX*MAX] = { 0 };

void DFS(int N, int start) {

	visited[start] = 1;
	printf("%d, ", start);

	for (int i = 1; i <= N; i++) {
		if (!visited[i]&&graph[start][i]) {
			DFS(N, i);
		}
	}

	return;
}


void BFS(int N, int start) {


	int front = -1; int  rear = -1;


	visited[start] = 1;
	printf("%d, ", start);
	
	rear++;
	queue[rear] = start;
	
	while (front < rear) {
		front++;
		int nextV = queue[front];

		for (int i = 1; i <= N; i++) {
			if (!visited[i] && graph[nextV][i]) {
				rear++;
				visited[i] = 1;
				printf("%d, ", i);

				queue[rear] = i;
			}
		}
	}

	return;
}

void init() {
	for (int i = 0; i <= MAX; i++) {
		visited[i] = 0;
	}
}

int main() {
	
	int N, M, start;

	freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);
	scanf("%d %d %d", &N, &M, &start);
	
	for (int i = 1; i <= M; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		graph[a][b] = 1;
		graph[b][a] = 1;
	}

	puts("DFS Start!!!");
	DFS(N, start);
	init();
	puts("");
	puts("BFS Start!!!");
	BFS(N, start);

	return 0;
}