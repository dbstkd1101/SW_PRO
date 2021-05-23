#include <stdio.h>

#define MAX_LEN_MAP 100

enum direction {
	UP=0, DOWN, LEFT, RIGHT
};

typedef struct {
	int row, col;
}POS;

int Graph[MAX_LEN_MAP+1][MAX_LEN_MAP+1][4] = { 0 };

int BFSvisit[MAX_LEN_MAP+1][MAX_LEN_MAP+1] = { 0 };
POS queue[1001];
int Data[MAX_LEN_MAP + 1][MAX_LEN_MAP + 1];

int liveCnt;
int sec;

void BFS(int col, int row, int N) {
	int front = 0, rear = 0;

	sec++;
	POS start; start.row = row; start.col = col;
	queue[0] = start;
	rear++;

	BFSvisit[row][col] = 1;

	while (front < rear) {
		POS Pop = queue[front];
		front++;

		for (int i = UP; i <= RIGHT; i++) {
			if (Graph[Pop.row][Pop.col][i] == 1 && BFSvisit[i] == 0) {
				POS node;
				if (i == UP) {
					node = { Pop.row - 1, Pop.col };
				}
				if (i == DOWN) {
					node = { Pop.row + 1, Pop.col };
				}
				if (i == LEFT) {
					node = { Pop.row, Pop.col - 1 };
				}
				if (i == RIGHT) {
					node = { Pop.row, Pop.col + 1};
				}
				queue[rear] = node;
				rear++;

				BFSvisit[i] = 1;
			}
		}
	}

	return;
}


int main() {
	int N, M, Start;
	int col, row;
	int x, y;

	//scanf("%d%d%d", &N, &M, &Start);

	/*
	for (int i = 0; i < M; i++) {
		scanf("%d%d", &x, &y);
		Graph[x][y] = 1;
		Graph[y][x] = 1;
	}

	puts("");
	BFS(Start, N);
	*/

	scanf("%d %d", &col, &row);
	int input_temp;
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= col; j++) {
			scanf("%d", &Data[i][j]);
			
			if (Data[i][j] == 1) {
				liveCnt++;

				if (i > 1) {
					if (Data[i - 1][j] == 1)
						Graph[i][j][UP] = 1;
				}
				if (i < row) {
					if (Data[i + 1][j] == 1)
						Graph[i][j][DOWN] = 1;
				}
				if (j > 1) {
					if (Data[i][j - 1] == 1)
						Graph[i][j][LEFT] = 1;
				}
				if (i < col) {
					if (Data[i][j + 1] == 1)
						Graph[i][j][RIGHT] = 1;
				}
			}
		}
	}
	scanf("%d %d", &x, &y);

	BFS(x, y, N);

	return 0;
}