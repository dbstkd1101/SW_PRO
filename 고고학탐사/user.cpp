// 채점시에는 아래 구조체 부분을 주석처리하고 제출해 주세요.
struct Position {
	int y, x, dir;
};

// *** user.cpp ***
#define MAXN 200
#define GOFORWARD 0
#define TURNRIGHT 1

#define NULL 0
#define MAX_BUF_SIZE 40000
#define MAX_BUCKET_SIZE 100000

#define UP     0
#define RIGHT  1
#define DOWN   2
#define LEFT   3


typedef unsigned int UI;

UI copy_map[MAXN][MAXN];

extern void identify(int minimap[4][4]);
extern bool moving(int method);


typedef struct node {
	Position pos;
	node * next;
}NODE;

NODE buf[MAX_BUF_SIZE];
int bufN;
NODE * bucket[MAX_BUCKET_SIZE];
UI value[MAXN][MAXN][4];

UI getHashCode(UI value) {
	return value % MAX_BUCKET_SIZE;
}

UI getValue(int x, int y, int dir) {
	UI sum = 0;

	switch (dir) {
	case UP:
		for (int i = 0; i <= 3; ++i) {
			for (int j = 0; j <= 3; ++j) {
				sum = sum * 4 + copy_map[y + i - 1][x + j - 1];
			}
		}
		break;

	case RIGHT:
		for (int i = 0; i <= 3; ++i) {
			for (int j = 0; j <= 3; ++j) {
				sum = sum * 4 + copy_map[y + j - 1][x - i + 2];
			}
		}
		break;

	case DOWN:
		for (int i = 0; i <= 3; ++i) {
			for (int j = 0; j <= 3; ++j) {
				sum = sum * 4 + copy_map[y - i + 2][x - j + 2];
			}
		}
		break;

	case LEFT:
		for (int i = 0; i <= 3; ++i) {
			for (int j = 0; j <= 3; ++j) {
				sum = sum * 4 + copy_map[y - j + 2][x + i - 1];
			}
		}
		break;

	}

	return sum;
}

UI getValueIdentify(int area[][4]) {
	UI sum = 0;

	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			sum = sum * 4 + (area[i][j]+2);
		}
	}
	return sum;
}

NODE * mAlloc(int hash_code, int row, int col, int dir) {
	(buf[bufN].pos.x) = col; (buf[bufN].pos.y) = row; (buf[bufN].pos.dir) = dir;
	buf[bufN].next = bucket[hash_code];
	return &buf[bufN++];
}

void makeValueAllDir(int row, int col) {
	for (int i = 0; i <= 3; ++i) {
		for (int j = 0; j <= 3; ++j) {
			value[row][col][0] = value[row][col][0] * 4 + copy_map[row + i - 1][col + j - 1];
			value[row][col][1] = value[row][col][1] * 4 + copy_map[row + j - 1][col - i + 2];
			value[row][col][2] = value[row][col][2] * 4 + copy_map[row - i + 2][col - j + 2];
			value[row][col][3] = value[row][col][3] * 4 + copy_map[row - j + 2][col + i - 1];
		}
	}
}

void addNode(int row, int col) {
	makeValueAllDir(row, col);
	for (int i = 0; i < 4; i++) {
		int hash_code = getHashCode(value[row][col][i]);
		bucket[hash_code] = mAlloc(hash_code, row, col, i);
	}
}

void userInit(int n, int Map[MAXN][MAXN]) {
	bufN = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			copy_map[i][j] =( Map[i][j] + 2);
		}
	}

	for (int k = 0; k < MAX_BUCKET_SIZE; k++) {
		bucket[k] = NULL;
	}

	for (int i = 1; i < n - 2; i++) {
		for (int j = 1; j < n - 2; j++) {
			value[i][j][0] = NULL;
			value[i][j][1] = NULL;
			value[i][j][2] = NULL;
			value[i][j][3] = NULL;
		}
	}

	for (int row = 1; row < n - 2; row++) {
		for (int col = 1; col < n - 2; col++) {
			if (row == 55 && col == 60) {
				int debug = 1;
			}
			addNode(row, col);
		}
	}
}

Position pos_search() {
	int curArea[4][4];

	identify(curArea);
	UI valueArea = getValueIdentify(curArea);
	int hash_code = getHashCode(valueArea);

	NODE * p = bucket[hash_code];

	int cnt = 0;

	Position candi[MAX_BUF_SIZE];

	int debugCnt = 0;

	for (; (p != NULL); p = (p->next)) {
		debugCnt++;
		if (debugCnt == 5000) {
			int a = 2;
		}
		if (debugCnt == 10000) {
			int a = 2;
		}
		if (debugCnt == 20000) {
			int a = 2;
		}
		int row = p->pos.y;
		int col = p->pos.x;
		int dir = p->pos.dir;

		if (value[row][col][dir] == valueArea) {
			Position temp;
			temp.x = col; temp.y = row; temp.dir = dir;
			candi[cnt++] = temp;
		}

		if (p->next == NULL) {
			break;
		}
		
	}

	while (cnt > 1) {
		int Ncnt = 0;
		int dirChangeCnt = 0;
		int changedCurArea[4][4];
		for (int i = 0; i < 4; i++) {
			if (!moving(GOFORWARD)) {
				moving(TURNRIGHT);
				dirChangeCnt++;
			}
			else {

				
				break;
			}
		}

		identify(changedCurArea);

		UI valueChangedCurArea = getValueIdentify(changedCurArea);
		for (int j = 0; j<cnt; j++) {

			int nX = candi[j].x; int nY = candi[j].y; int nDir = candi[j].dir;

			for (int i = 0; i < dirChangeCnt; i++) {
				nDir =(nDir +1) % 4;
			}

			switch (nDir) {
			case UP : 
				nY -= 1;
				break;
			case RIGHT : 
				nX += 1;
				break;
			case DOWN:
				nY += 1;
				break;
			case LEFT:
				nX -= 1;
				break;
			}

			if (value[nY][nX][nDir] == valueChangedCurArea) {
				Position temp = { nY, nX, nDir };
				candi[Ncnt++]=temp;
			}
		}
		cnt = Ncnt;
	}

	return  candi[0];
}