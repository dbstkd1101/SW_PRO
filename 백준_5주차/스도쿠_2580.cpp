#include <stdio.h>

#define MAX_MAP_ROW 9
#define MAX_MAP_COL 9

#define MAX_ZONE_ROW 3
#define MAX_ZONE_COL 3

#define POSSI_NUM_CNT 9
#define NULL 0

int map[9][9];
int isEnd = 0;
typedef struct pos {
	int r, c;
}POS;

int* findZonePos(int row, int col) {
	int rstPos[2] = { 0, };
	rstPos[0] = (row / 3)*3;
	rstPos[1] = (col / 3)*3;
	return rstPos;
}

// map row, col insert from 0
int possNumList(int rstList[], int map[][MAX_MAP_COL], int row, int col) {
	int rst = 0;

	for (int c = 0; c < MAX_MAP_COL; c++) {
		if (map[row][c] && rstList[map[row][c]]) {
			rstList[map[row][c]] = 0;
		}
	}

	for (int i = 1; i <= POSSI_NUM_CNT; i++) {
		if (rstList[i]) {
			rst = 1;
		}
	}

	for (int r = 0; rst&& r <  MAX_MAP_ROW; r++) {
		if (map[r][col] && rstList[map[r][col]]) {
			rstList[map[r][col]] = 0;
		}
	}

	rst = 0;
	for (int i = 1; i <= POSSI_NUM_CNT; i++) {
		if (rstList[i]) {
			rst = 1;
		}
	}

	if (rst) {
		int* zonePos = findZonePos(row, col);

		for (int r = 0; r < MAX_ZONE_ROW; r++) {
			for (int c = 0; c < MAX_ZONE_COL; c++) {
				if (map[zonePos[0] + r][zonePos[1] + c] && rstList[map[zonePos[0] + r][zonePos[1] + c]]) {
					rstList[map[zonePos[0] + r][zonePos[1] + c]] = 0;
				}
			}
		}
	}

	rst = 0;
	for (int i = 1; i <= POSSI_NUM_CNT; i++) {
		if (rstList[i]) {
			rst = 1;
		}
	}

	return rst;
}

POS findNextZero(int map[][MAX_MAP_COL], int row, int col) {

	POS rstPos = {-1,};

	for (int r = row; r < MAX_MAP_ROW; r++) {
		for (int c = 0; c < MAX_MAP_COL; c++) {
			if(!map[r][c]){
				return rstPos = { r, c };
			}
		}
	}

	return rstPos;
}

void DFS(int row, int col) {
	int rstList[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	if (possNumList(rstList, map, row, col)) {
		for (int i = 1; i <= POSSI_NUM_CNT; i++) {
			if (isEnd) {
				return;
			}
			if (rstList[i]) {
				map[row][col] = rstList[i];
				POS nextPos = findNextZero(map, row, col);

				// exit
				if (nextPos.r == -1 || nextPos.c == -1) {
					isEnd = 1;
					return;
				}

				if (nextPos.r!=-1 && nextPos.c!=-1) {
					DFS(nextPos.r, nextPos.c);
				}
			}

		}
	}
}

int main() {
	
	freopen("input.txt", "r", stdin);
	
	int sRow, sCol;
	int isFirst = 1;
	
	for (int i = 0; i < MAX_MAP_ROW; i++) {
		for (int j = 0; j < MAX_MAP_COL; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 0) {
				if (isFirst) {
					sRow = i;
					sCol = j;
					isFirst = 0;
				}
			}
		}
	}
	
	DFS(sRow, sCol);

	for (int i = 0; i < MAX_MAP_ROW; i++) {
		for (int j = 0; j < MAX_MAP_COL; j++) {
			printf("%d ", map[i][j]);
		}
		puts("");
	}


	return 0;
}