#include <stdio.h>

#define MAX_CNT_N 102
#define MAX_LEN_MAP 102

int A, B, N, M;

typedef enum crash {
	WALL = 1, ROBOT
}CRASH;

typedef enum direction {
	EAST, SOUTH, WEST, NORTH
}DIRECTION;

typedef struct node {
	int x, y;
	int dir;
}NODE;


// 로봇별 현재 위치
NODE currPos[MAX_CNT_N];

int who; char command; int cnt;
int whom;

// 현재 어디에 누가 있는지
int map[MAX_LEN_MAP][MAX_LEN_MAP];

int turn(int who_dir, char command) {
	int rst = -1;
	switch (command) {
	case 'R':
		rst = (who_dir + 1) % 4;
		break;
	case 'L':
		rst = (who_dir - 1) % 4;
		if (rst == -1) {
			rst = NORTH;
		}
		break;
	default:
		rst = who_dir;
		break;
	}
	return rst;
}

int move(int who, char command) {
	int who_x = currPos[who].x;
	int who_y = currPos[who].y;
	int who_dir = currPos[who].dir;
	int determined_dir = turn(who_dir, command);
	currPos[who].dir = determined_dir;

	if (command == 'F') {
		switch (determined_dir)
		{
		case EAST:
			if (map[who_x][who_y + 1] > 0) {
				whom = map[who_x][who_y + 1];
				return ROBOT;
			}
			else if (map[who_x][who_y + 1] == -1) {
				return WALL;
			}
			else {
				map[who_x][who_y + 1] = who;
				map[who_x][who_y] = 0;
				currPos[who].y++;
			}
			break;
		case WEST:
			if (map[who_x][who_y - 1] > 0) {
				whom = map[who_x][who_y - 1];
				return ROBOT;
			}
			else if (map[who_x][who_y - 1] == -1) {
				return WALL;
			}
			else {
				map[who_x][who_y - 1] = who;
				map[who_x][who_y] = 0;
				currPos[who].y--;
			}
			break;
		case SOUTH:
			if (map[who_x + 1][who_y] > 0) {
				whom = map[who_x + 1][who_y];
				return ROBOT;
			}
			else if (map[who_x + 1][who_y] == -1) {
				return WALL;
			}
			else {
				map[who_x + 1][who_y] = who;
				map[who_x][who_y] = 0;
				currPos[who].x++;
			}
			break;
		case NORTH:
			if (map[who_x - 1][who_y] > 0) {
				whom = map[who_x - 1][who_y];
				return ROBOT;
			}
			else if (map[who_x - 1][who_y] == -1) {
				return WALL;
			}
			else {
				map[who_x - 1][who_y] = who;
				map[who_x][who_y] = 0;
				currPos[who].x--;
			}
			break;
		}
	}


	return 0;
}

int main() {
	freopen("input.txt", "r", stdin);

	scanf("%d %d\n", &A, &B);


	// map 둘레 -1로 초기화
	for (int i = 0; i <= B + 1; i++) {
		for (int j = 0; j <= A + 1; j++) {
			if ((i == 0 || i == B + 1)) {
				map[i][j] = -1;
			}
			else {
				if (j == 0 || j == A + 1) {
					map[i][j] = -1;
				}
			}
		}
	}

	scanf("%d %d\n", &N, &M);

	for (int i = 1; i <= N; i++) {
		int first_pos_x, first_pos_y;
		char pos;
		int deter_pos;
		scanf("%d %d %c\n", &first_pos_y, &first_pos_x, &pos);

		// 방위 값 문자에서 숫자로 변환
		switch (pos) {
		case 'E':
			deter_pos = EAST;
			break;
		case 'W':
			deter_pos = WEST;
			break;
		case 'S':
			deter_pos = SOUTH;
			break;
		case 'N':
			deter_pos = NORTH;
			break;
		}

		NODE temp = { B-first_pos_x+1, first_pos_y, deter_pos };
		currPos[i] = temp;
		map[temp.x][temp.y] = i;
	}

	int i = 1;
	for ( ; i <= M; i++) {
		scanf("%d %c %d", &who, &command, &cnt);
		if (i == 13) {
			int l = 1;
		}
		for (int k = 1; k <= cnt; k++) {
			int rst = move(who, command);
			if (rst == WALL) {
				printf("Robot %d crashes into the wall\n", who);
				return 0;
			}
			if (rst == ROBOT) {
				printf("Robot %d crashes into robot %d\n", who, whom);
				return 0;
			}
		}
	}

	if ((i-1) == M) {
		printf("OK");
		return 0;
	}

	return 0;
}