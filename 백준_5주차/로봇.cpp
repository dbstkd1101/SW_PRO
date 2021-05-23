#include <stdio.h>
#define MAX_LEN_MAP 101
#define MAX_LEN_QUEUE 3500000
#define MAX_LEN_K 3


// 100이하의 자연수
int N, M;
int answer;

int front = 0;
int rear = 0;

int map[MAX_LEN_MAP][MAX_LEN_MAP];
int mapBEST[MAX_LEN_MAP][MAX_LEN_MAP][5];

typedef enum direction {
	EAST = 1, WEST, SOUTH, NORTH
}DIR;

typedef struct node {
	int mx, my;
	DIR dir;
	int first;
	int cmdCnt;
	int pX, pY;
	DIR pDir;
}NODE;

NODE end;
NODE queue[MAX_LEN_QUEUE];


int getDistanceBetweenChildAndParent(int cx, int cy, DIR cDir, int px, int py, DIR pDir) {
	int rst = -1;
	if (cDir != pDir) {
		return rst;
	}

	switch (cDir) {
	case EAST:
		rst = cy - py;
		break;
	case WEST:
		rst = py - cy;
		break;
	case SOUTH:
		rst = cx - px;
		break;
	case NORTH:
		rst = px - cx;
		break;

	}
	return rst;
}

NODE turnPossibleAndTurn(NODE currNode, int dir) {
	NODE rstNODE = { -1 };

	DIR turnedDir;
	int cmdCnt = 0;

	int possible = 0;

	switch (currNode.dir) {
	case EAST:
		// EAST
		if (dir == 0) {
			turnedDir = EAST;
			// 정답이면 무조건 queue 담도록 진행
			if (currNode.mx == end.mx && currNode.my == end.my && end.dir == EAST) {
				possible = 1;
				break;
			}
			if (currNode.my + 1 <= M && map[currNode.mx][currNode.my + 1] == 0) {
				possible = 1;
			}
		}
		// SOUTH
		if (dir == 1) {
			turnedDir = SOUTH;
			// 정답이면 무조건 queue 담도록 진행
			if (currNode.mx  == end.mx && currNode.my == end.my && end.dir == SOUTH) {
				possible = 1;
				break;
			}
			if (currNode.mx + 1 <= N && map[currNode.mx + 1][currNode.my] == 0) {
				possible = 1;
			}
		}
		// WEST
		if (dir == 2) {
			turnedDir = WEST;
			// 정답이면 무조건 queue 담도록 진행
			if (currNode.mx == end.mx && currNode.my == end.my && end.dir == WEST) {
				possible = 1;
				break;
			}
			if (currNode.my - 1 >= 1 && map[currNode.mx][currNode.my - 1] == 0 && !(currNode.dir == currNode.pDir)) {
				int dist = getDistanceBetweenChildAndParent(currNode.mx, currNode.my, currNode.dir, currNode.pX, currNode.pY, currNode.pDir);
				if (dist == 0) {
					return rstNODE;
				}
				possible = 1;
				
			}
		}
		// NORTH
		if (dir == 3) {
			turnedDir = NORTH;
			// 정답이면 무조건 queue 담도록 진행
			if (currNode.mx  == end.mx && currNode.my == end.my && end.dir == NORTH) {
				possible = 1;
				break;
			}
			if (currNode.mx - 1 >= 1 && map[currNode.mx - 1][currNode.my] == 0) {
				possible = 1;
			}
		}
		break;
	case WEST:
		// WEST
		if (dir == 0) {
			turnedDir = WEST;
			// 정답이면 무조건 queue 담도록 진행
			if (currNode.mx == end.mx && currNode.my == end.my && end.dir == WEST) {
				possible = 1;
				break;
			}
			if (currNode.my - 1 >= 1 && map[currNode.mx][currNode.my - 1] == 0) {
				possible = 1;
			}
		}
		// SOUTH
		if (dir == 1) {
			turnedDir = SOUTH;
			// 정답이면 무조건 queue 담도록 진행
			if (currNode.mx == end.mx && currNode.my == end.my && end.dir == SOUTH) {
				possible = 1;
				break;
			}
			if (currNode.mx + 1 <= N && map[currNode.mx + 1][currNode.my] == 0) {
				possible = 1;
			}
		}
		// EAST
		if (dir == 2) {
			turnedDir = EAST;
			// 정답이면 무조건 queue 담도록 진행
			if (currNode.mx == end.mx && currNode.my == end.my && end.dir == EAST) {
				possible = 1;
				break;
			}
			if (currNode.my + 1 <= M && map[currNode.mx][currNode.my + 1] == 0 && !(currNode.dir == currNode.pDir)) {
				int dist = getDistanceBetweenChildAndParent(currNode.mx, currNode.my, currNode.dir, currNode.pX, currNode.pY, currNode.pDir);
				if (dist == 0) {
					return rstNODE;
				}
				possible = 1;
			}
		}
		// NORTH
		if (dir == 3) {
			turnedDir = NORTH;
			// 정답이면 무조건 queue 담도록 진행
			if (currNode.mx == end.mx && currNode.my == end.my && end.dir == NORTH) {
				possible = 1;
				break;
			}
			if (currNode.mx - 1 >= 1 && map[currNode.mx - 1][currNode.my] == 0) {
				possible = 1;
			}
		}
		break;
	case SOUTH:
		// SOUTH
		if (dir == 0) {
			turnedDir = SOUTH;
			// 정답이면 무조건 queue 담도록 진행
			if (currNode.mx == end.mx && currNode.my == end.my && end.dir == SOUTH) {
				possible = 1;
				break;
			}
			if (currNode.mx + 1 <= N && map[currNode.mx + 1][currNode.my] == 0) {
				possible = 1;
			}
		}
		// WEST
		if (dir == 1) {
			turnedDir = WEST;
			// 정답이면 무조건 queue 담도록 진행
			if (currNode.mx == end.mx && currNode.my == end.my && end.dir == WEST) {
				possible = 1;
				break;
			}
			if (currNode.my - 1 >= 1 && map[currNode.mx][currNode.my - 1] == 0) {
				possible = 1;
			}
		}
		// NORTH
		if (dir == 2) {
			turnedDir = NORTH;
			// 정답이면 무조건 queue 담도록 진행
			if (currNode.mx == end.mx && currNode.my == end.my && end.dir == NORTH) {
				possible = 1;
				break;
			}
			if (currNode.mx - 1 >= 1 && map[currNode.mx - 1][currNode.my] == 0 && !(currNode.dir == currNode.pDir)) {
				int dist = getDistanceBetweenChildAndParent(currNode.mx, currNode.my, currNode.dir, currNode.pX, currNode.pY, currNode.pDir);
				if (dist == 0) {
					return rstNODE;
				}
				possible = 1;
			}
		}
		// EAST
		if (dir == 3) {
			turnedDir = EAST;
			// 정답이면 무조건 queue 담도록 진행
			if (currNode.mx == end.mx && currNode.my == end.my && end.dir == EAST) {
				possible = 1;
				break;
			}
			if (currNode.my + 1 <= M && map[currNode.mx][currNode.my + 1] == 0) {
				possible = 1;
			}
		}
		break;
	case NORTH:
		// NORTH
		if (dir == 0) {
			turnedDir = NORTH;
			// 정답이면 무조건 queue 담도록 진행
			if (currNode.mx == end.mx && currNode.my == end.my && end.dir == NORTH) {
				possible = 1;
				break;
			}
			if (currNode.mx - 1 >= 1 && map[currNode.mx - 1][currNode.my] == 0) {
				possible = 1;
			}
		}
		// EAST
		if (dir == 1) {
			turnedDir = EAST;
			// 정답이면 무조건 queue 담도록 진행
			if (currNode.mx == end.mx && currNode.my == end.my && end.dir == EAST) {
				possible = 1;
				break;
			}
			if (currNode.my + 1 <= M && map[currNode.mx][currNode.my + 1] == 0 ) {
				possible = 1;
			}
		}
		// SOUTH
		if (dir == 2) {
			turnedDir = SOUTH;
			// 정답이면 무조건 queue 담도록 진행
			if (currNode.mx == end.mx && currNode.my == end.my && end.dir == SOUTH) {
				possible = 1;
				break;
			}
			if (currNode.mx + 1 <= N && map[currNode.mx + 1][currNode.my] == 0 && !(currNode.dir == currNode.pDir)) {
				int dist = getDistanceBetweenChildAndParent(currNode.mx, currNode.my, currNode.dir, currNode.pX, currNode.pY, currNode.pDir);
				if (dist == 0) {
					return rstNODE;
				}
				possible = 1;
			}
		}
		// WEST
		if (dir == 3) {
			turnedDir = WEST;
			// 정답이면 무조건 queue 담도록 진행
			if (currNode.mx == end.mx && currNode.my == end.my && end.dir == WEST) {
				possible = 1;
				break;
			}
			if (currNode.my - 1 >= 1 && map[currNode.mx][currNode.my - 1] == 0) {
				possible = 1;
			}
		}
		break;
	}


	if (possible) {
		// 최단 cmdCnt가 아니면 굳이 더 진행할 필요가 없음
		/*
		if (dir == 3) {
			if (!(mapBEST[currNode.mx][currNode.my][turnedDir]==0 || mapBEST[currNode.mx][currNode.my][turnedDir]>(currNode.cmdCnt + 1)))
				return rstNODE;
		}
		else {
			if(!(mapBEST[currNode.mx][currNode.my][turnedDir] == 0 || mapBEST[currNode.mx][currNode.my][turnedDir]>(currNode.cmdCnt + dir)))
				return rstNODE;
		}*/
		rstNODE = currNode;
		rstNODE.dir = turnedDir;
		rstNODE.first = 0;
		rstNODE.pX = currNode.mx;
		rstNODE.pY = currNode.my;
		rstNODE.pDir = currNode.dir;
		if (dir == 3) {
			rstNODE.cmdCnt += 1;
		}
		else {
			rstNODE.cmdCnt += dir;
		}
	}
	

	return rstNODE;
}



int goPossible(NODE currNode, DIR dir, int K) {
	int rst = 0;

	switch (dir) {
	case EAST:
		// map에서 갈 수 있는 곳인지
		if (currNode.my + K <= M) {
			for (int i = 1; i <= K; i++) {
				if (!(map[currNode.mx][currNode.my + i] == 0)) {
					return rst = 0;
				}
			}
			if (K == 1) {
				int dist = getDistanceBetweenChildAndParent(currNode.mx, currNode.my, currNode.dir, currNode.pX, currNode.pY, currNode.pDir);
				if (dist == 0 || dist == -1 || dist >= 3) {
					rst = 1;
				}
				else {
					rst = 0;
				}
			}
			if (K == 2) {
				int dist = getDistanceBetweenChildAndParent(currNode.mx, currNode.my, currNode.dir, currNode.pX, currNode.pY, currNode.pDir);
				if (dist == 0 || dist == -1 || dist >= 2) {
					rst = 1;
				}
				else {
					rst = 0;
				}
			}
			if (K == 3) {
				rst = 1;
			}	
		}
		break;
	case WEST:
		if (currNode.my - K >= 1) {
			for (int i = 1; i <= K; i++) {
				if (!(map[currNode.mx][currNode.my - i] == 0)) {
					return rst = 0;
				}
			}
			if (K == 1) {
				int dist = getDistanceBetweenChildAndParent(currNode.mx, currNode.my, currNode.dir, currNode.pX, currNode.pY, currNode.pDir);
				if (dist == 0 || dist == -1 || dist >= 3) {
					rst = 1;
				}
				else {
					rst = 0;
				}
			}
			if (K == 2) {
				int dist = getDistanceBetweenChildAndParent(currNode.mx, currNode.my, currNode.dir, currNode.pX, currNode.pY, currNode.pDir);
				if (dist == 0 || dist == -1 || dist >= 2) {
					rst = 1;
				}
				else {
					rst = 0;
				}
			}
			if (K == 3) {
				rst = 1;
			}
		}
		break;
	case SOUTH:
		if (currNode.mx + K <= N) {
			for (int i = 1; i <= K; i++) {
				if (!(map[currNode.mx + i][currNode.my] == 0)) {
					return rst = 0;
				}
			}
			if (K == 1) {
				int dist = getDistanceBetweenChildAndParent(currNode.mx, currNode.my, currNode.dir, currNode.pX, currNode.pY, currNode.pDir);
				if (dist == 0 || dist == -1 || dist >= 3) {
					rst = 1;
				}
				else {
					rst = 0;
				}
			}
			if (K == 2) {
				int dist = getDistanceBetweenChildAndParent(currNode.mx, currNode.my, currNode.dir, currNode.pX, currNode.pY, currNode.pDir);
				if (dist == 0 || dist == -1 || dist >= 2) {
					rst = 1;
				}
				else {
					rst = 0;
				}
			}
			if (K == 3) {
				rst = 1;
			}
		}
		break;
	case NORTH:
		if (currNode.mx - K >= 1) {
			for (int i = 1; i <= K; i++) {
				if (!(map[currNode.mx - i][currNode.my] == 0)) {
					return rst = 0;
				}
			}
			if (K == 1) {
				int dist = getDistanceBetweenChildAndParent(currNode.mx, currNode.my, currNode.dir, currNode.pX, currNode.pY, currNode.pDir);
				if (dist == 0 || dist == -1 || dist >= 3) {
					rst = 1;
				}
				else {
					rst = 0;
				}
			}
			if (K == 2) {
				int dist = getDistanceBetweenChildAndParent(currNode.mx, currNode.my, currNode.dir, currNode.pX, currNode.pY, currNode.pDir);
				if (dist == 0 || dist == -1 || dist >= 2) {
					rst = 1;
				}
				else {
					rst = 0;
				}
			}
			if (K == 3) {
				rst = 1;
			}
		}
		break;
	}

	return rst;
}

void go(NODE* currNode, int K) {

	switch (currNode->dir) {
	case EAST:
		currNode->my += K;
		break;
	case WEST:
		currNode->my -= K;
		break;
	case SOUTH:
		currNode->mx += K;
		break;
	case NORTH:
		currNode->mx -= K;
		break;
	}
}

int BFS(NODE start) {

	queue[++rear] = start;

	while (front < rear) {

		NODE temp = queue[++front];
		
		if (front == 16) {
			int c = 2;
		}

		if (temp.mx == end.mx && temp.my == end.my && temp.dir == end.dir) {
			answer = temp.cmdCnt;
			return answer;
		}

		// 최초 고려되는 노드면 방향 돌기
		if (temp.first) {
			for (int i = 0; i <= 3; i++) {
				int c;
				// 제자리 1번, 오른쪽 2번, 왼쪽 1번
				NODE insrtedNode = turnPossibleAndTurn(temp, i);
				if (insrtedNode.mx != -1) {
					queue[++rear] = insrtedNode;
				}

			}
		}
		// 이전 고려되는 노드가 아니면, 직진 하기
		else {
			for (int i = 1; i <= MAX_LEN_K; i++) {
				if (goPossible(temp, temp.dir, i)) {
					// first=1
					NODE instNode = { temp.mx, temp.my, temp.dir, 1, temp.cmdCnt + 1, temp.mx, temp.my, temp.dir};
					go(&instNode, i);
					if (mapBEST[instNode.mx][instNode.my][instNode.dir] != 0 && mapBEST[instNode.mx][instNode.my][instNode.dir] <= instNode.cmdCnt) {
						continue;
					}
					queue[++rear] = instNode;
				}
			}
		}
	}

	return answer;
}

int main() {

	freopen("input.txt", "r", stdin);

	scanf("%d %d\n", &N, &M);

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	NODE start;
	scanf("%d %d %d", &start.mx, &start.my, &start.dir);
	mapBEST[start.mx][start.my][start.dir] = 0;

	start.cmdCnt = 0; start.pX = -1; start.pY = -1; start.first = 1;

	scanf("%d %d %d", &end.mx, &end.my, &end.dir);
	end.cmdCnt = 0;   end.pX = -1; end.pY = -1; end.first = 1;

	answer = BFS(start);
	printf("%d\n", answer);

	return 0;
}