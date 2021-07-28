#include <stdio.h>
#include <queue>

using namespace std;

const int LN = 100;

enum direction {
	E = 1, W, S, N
};

struct pos {
	int x, y;
	direction dir;
	int c, cycle;
};
pos start, end2;


queue<pos> posQ;

int M, NN;

int map[LN][LN];
int visited[LN][LN];
int startEnd[2][3];

int min2=1<<31-1;
int findCycle = 0;

bool isFind = false;


int dirX[4]{ 0, 0, 1, -1 };
int dirY[4]{ 1, -1, 0, 0 };

int bfs(pos _start) {
	
	posQ.push(_start);

	while (!posQ.empty()) {
		pos p = posQ.front();
		posQ.pop();
		if (isFind && p.cycle > findCycle) return 0;

		if (p.x == end2.x && p.y == end2.y) {
			isFind = true;
			if (min2 > p.c) min2 = p.c;
			findCycle = p.cycle;
			return min2;
		}

		for (int i = 0; i < 4; i++) {
			//현 방향과 이동할 방향 비교해서 C ++하기
			pos tmp = { p.x + dirX[i], p.y + dirY[i], p.c++, p.cycle++ };
			if (!visited[tmp.x][tmp.y] && !map[tmp.x][tmp.y]) posQ.push(tmp);
		}
	}
}

int main() {
	
	scanf("%d %d", &M, &NN);

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < NN; j++) {
			scanf("%d", &map[i][j]);
		}
	}
	
	scanf("%d %d %d", &start.x, &start.y, &start.dir);
	start.c = 1; start.cycle = 1;
	scanf("%d %d %d", &end2.x, &end2.y, &end2.dir);

	int rst = bfs(start);

	printf("%d\n", rst);

	return 0;
}