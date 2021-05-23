#include <stdio.h>

#define MAX_LEN_MAP 100

int N;

enum direction {
	UP = 0, DOWN, LEFT, RIGHT
};

typedef struct node{
	int r, c, v, m;
}NODE;

int map[MAX_LEN_MAP + 10][MAX_LEN_MAP + 10];
NODE queue[(MAX_LEN_MAP+1)*(MAX_LEN_MAP + 1)];

int BFS() {
	int front = 0, rear = 0;

	rear++;

	return 0;
}

int main() {
	
	freopen("input.txt", "r", stdin);
	scanf("%d", &N);
	int temp=-1;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
					
			scanf("%d", &temp);
			NODE tempNode = { i, j, temp, MAX_LEN_MAP + 1 };
			map[i][j]
			
		}
	}

	map[1][1]

	printf("%d\n", BFS());

	return 0;
}