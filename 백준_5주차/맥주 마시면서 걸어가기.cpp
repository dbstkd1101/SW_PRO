#include <stdio.h>
#define MAX_LEN_HISTORY 103
#define MAX_LEN_QUEUE 100000

int t;
int store;
int find = 0;

typedef struct object {
	int x, y;
}OBJECT;

typedef struct node {
	OBJECT pos;
	int hist[MAX_LEN_HISTORY];
	int histCnt;
}NODE;


typedef struct list {
	int cnt;
	int listArr[MAX_LEN_HISTORY];
}LIST;

OBJECT map[MAX_LEN_HISTORY];
NODE queue[MAX_LEN_QUEUE];

int distance(OBJECT from, OBJECT to) {
	int distX, distY;
	if (from.x - to.x > 0) {
		distX = from.x - to.x;
	}
	else {
		distX = to.x - from.x;
	}

	if (from.y - to.y > 0) {
		distY = from.y - to.y;
	}
	else {
		distY = to.y - from.y;
	}

	return  distX + distY;
}

LIST getPossibleStoreList(NODE target, int havingBeer) {
	LIST list = { 0, 0 };
	int i = 1;
	for (int i = 1; i < store + 2; i++) {
		// 다녀온 편의점 skip
		int alreadyVisited = 0;
		for (int j = 0; j < target.histCnt; j++) {
			if (target.hist[j] == i) {
				alreadyVisited = 1;
			}
		}
		if (alreadyVisited)
			continue;

		if (distance(target.pos, map[store+1]) <= havingBeer * 50) {
			find = 1;
		}

		//listArr[0]에는 자기 자신의 map 번호
		if (target.pos.x == map[i].x && target.pos.y == map[i].y) {
			list.listArr[0] = i;
			continue;
		}

		if (distance(target.pos, map[i]) <= havingBeer * 50) {
			list.listArr[++list.cnt] = i;
		}		
	}

	return list;
}

int BFS() {

	int front = -1; int rear = -1;	
	
	// 집 꺼네요
	NODE first = { map[0], 0, 0 };
	queue[++rear]= first;
	
	while (front < rear) {
		NODE temp = queue[++front];
		LIST listTmp = getPossibleStoreList(temp, 20);
		if (find == 1) {
			return 1;
		}
		for (int i = 1; i <= listTmp.cnt; i++) {
			OBJECT insertedPos = map[listTmp.listArr[i]];
			NODE insertedNode = { insertedPos, 0, 0 };
			int j = 1;
			for (  ; j <= temp.histCnt; j++) {
				insertedNode.hist[j] = temp.hist[j];
				insertedNode.histCnt++;
			}
			insertedNode.hist[insertedNode.histCnt++] = listTmp.listArr[0];
			queue[++rear] = insertedNode;
		}
	}

	return 0;
}

int main() {
	freopen("input.txt", "r", stdin);
	
	scanf("%d\n", &t);

	for (int i = 1; i <= t; i++) {
		if (i == 2) {
			int c = 0;
		}
		find = 0;
		scanf("%d\n", &store);
		int x, y;
		for (int j = 0; j < store + 2; j++) {
			scanf("%d %d", &x, &y);
			OBJECT tempObj = { x, y };
			map[j] = tempObj;
		}

		if (BFS()) {
			printf("happy\n");
		}
		else {
			printf("sad\n");
		}
	}
	
	return 0;
}