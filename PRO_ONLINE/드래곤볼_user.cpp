#ifndef NULL
#define NULL 0
#endif

#define SIZE 500000

extern struct queue;

struct node {
	int r, c;
	node * prev, *next;
	queue * qAddr;
	node * alloc(int _r, int _c, node * _prev, node * _next, queue* _qAddr) {
		r = _r, c = _r, prev = _prev, next = _next, qAddr = _qAddr;
		if (prev) prev->next = this;
		if (next) next->prev = this;
		return this;
	}
	void pop() {
		prev->next = next;
		if (next) next->prev = prev;
	}
}*bucket[SIZE], nBuf[SIZE * 2];

struct queue {
	int r, c;
	node * nAddr;
	queue* next;
	queue * alloc(int _r, int _c, node * _nAddr, queue * _next) {
		r = _r, c = _c, nAddr = _nAddr, next = _next;
		return this;
	}
}qBuf[SIZE];

typedef enum dir {
	N = 0,
	E,
	S,
	W
}DIR;

queue * head, *tail;
int dir;
int nBCnt, qBCnt, qLen;

// 북, 동, 남, 서
int rowDir[4] = { -1, 0, 1, 0 };
int colDir[4] = { 0, 1, 0, -1 };

// 갱신 필요
int getHash(int r, int c) {
	int sum = 0;
	return (r * 20000 + c) % SIZE;
}

void init(int N) {
	nBCnt = qBCnt = qLen = 0;
	for (int i = 0; i < SIZE; i++) {
		bucket[i] = NULL;
		// dummy Node
		bucket[i] = nBuf[nBCnt++].alloc(-1, -1, NULL, NULL, NULL);
	}
	head = tail = NULL;
	int initR = (N + 1)/ 2, initC = (N +1) / 2;

	int hash = getHash(initR, initC);
	node * tmp = nBuf[nBCnt++].alloc(initR, initC, bucket[hash], bucket[hash]->next, &qBuf[qBCnt]);
	head = tail = qBuf[qBCnt++].alloc(initR, initC, tmp, NULL);
	qLen++;
	dir = S;
}

int overlapChk(queue ** overlapPos) {
	int rst = 0;
	int r = head->r + rowDir[dir];
	int c = head->c + colDir[dir];

	int hash = getHash(r, c);
	for (node * p = bucket[hash]; p; p = p->next) {
		if (p->r == r && p->c == c) {
			*overlapPos = p->qAddr;
			return rst = 1;
		}
	}
	return rst;
}

void goAhead() {
	queue ** overlapPosTmp = NULL;
	if (overlapChk(overlapPosTmp)) {
		// Tail 부터 해당 queue 직전까지 다 날림
		queue * p;
		for (p = tail; p && *overlapPosTmp!=p; p = p->next) {
			int hash = getHash(p->r, p->c);
			for (node * q = bucket[hash]; q; q = q->next) {
				if (q->r == p->r && q->c == p->c) {
					q->pop();
					qLen--;
					break;
				}
			}
		}
		tail = p;
	}

	for (queue * p = tail; p; p = p->next) {
		int hash = getHash(p->r, p->c);
		for (node * q = bucket[hash]; q; q = q->next) {
			if (q->r == p->r && q->c == p->c) {
				q->pop();
				break;
			}
		}
		if (p == head) {
			p->r += rowDir[dir];
			p->c += colDir[dir];
		}
		else {
			p->r = (p->next->r), p->c = (p->next->c);
		}
		int hashNew = getHash(p->r, p->c);
		p->nAddr = nBuf[nBCnt++].alloc(p->r, p->c, bucket[hashNew], bucket[hashNew]->next, p);
	}
}

void turn(int right) {
	if (right) {
		dir = (dir + 1) % 4;
	}
	else {
		if (dir == 0) {
			dir = 3;
		}
		else {
			dir = (dir - 1) % 4;
		}
	}
}

int move(int r, int c, int len) {
	int rst = 0;
	bool sameRow, sameCol;

	if ((r > head->r && (rowDir[dir] == 1)) || (r < head->r && (rowDir[dir] == -1))) sameRow = true;
	else sameRow = false;

	if (c > head->c && (colDir[dir] == 1) || (c < head->c && (colDir[dir] == -1))) sameCol = true;
	else sameCol = false;

	int goCntFirst = 0;
	int goCntSecond = 0;
	int turnDirFirst = 0;
	int turnDirSecond = 0;
	if (sameRow || sameCol) {
		if (sameRow) {
			goCntFirst = ((r > head->r) ? r - head->r : head->r - r);
			if (head->c > c) turnDirFirst = 1; else turnDirFirst = 0;
			goCntSecond = ((c > head->c) ? c - head->c : head->c - c);
		}
		else {
			goCntFirst = ((c > head->c) ? c - head->c : head->c - c);
			if (head->r > r) turnDirFirst = 0; else turnDirFirst = 1;
			goCntSecond = ((r > head->r) ? r - head->r : head->r - r);
		}
		while (goCntFirst--) {
			goAhead();
		}
		turn(turnDirFirst);
		while (goCntSecond--) {
			goAhead();
		}
	}
	else {
		// 북/남 방향
		if (dir % 2 == 0) {
			// 동/서 먼저
			if (head->c > c) turnDirFirst = 1; else turnDirFirst = 0;
			goCntFirst = ((c > head->c) ? c - head->c : head->c - c);
			if (turnDirFirst) turnDirSecond = 1; else turnDirSecond = 0;
			goCntSecond = ((r > head->r) ? r - head->r : head->r - r);
		}
		// 동/서 방향
		else {
			// 북/남 먼저
			if (head->r > r) {
				dir == E ? turnDirFirst = 0 : turnDirFirst = 1;
			}
			else {
				dir == E ? turnDirFirst = 1 : turnDirFirst = 0;
			}
			goCntFirst = ((r > head->r) ? r - head->r : head->r - r);
			// 동/서 다음
			if (turnDirFirst) turnDirSecond = 1; else turnDirSecond = 0;
			goCntSecond = ((c > head->c) ? c - head->c : head->c - c);
		}

		turn(turnDirFirst);
		while (goCntFirst--) {
			goAhead();
		}
		turn(turnDirSecond);
		while (goCntSecond--) {
			goAhead();
		}
	}

	for (int i = len; i > 0; i--) {
		queue ** overlapPosTmp = NULL;
		if (overlapChk(overlapPosTmp)) {
			// Tail 부터 해당 queue 직전까지 다 날림
			queue * p;
			for (p = tail; p && *overlapPosTmp != p; p = p->next) {
				int hash = getHash(p->r, p->c);
				for (node * q = bucket[hash]; q; q = q->next) {
					if (q->r == p->r && q->c == p->c) {
						q->pop();
						qLen--;
						break;
					}
				}
			}
			tail = p;
		}
		int newR = head->r + rowDir[dir], newC = head->c + colDir[dir];
		int hash = getHash(newR, newC);
		node * tmp = nBuf[nBCnt++].alloc(newR, newC, bucket[hash], bucket[hash]->next, &qBuf[qBCnt]);
		head = qBuf[qBCnt-1].next = qBuf[qBCnt].alloc(newR, newC, tmp, NULL);
		qLen++;
		qBCnt++;
	}

	return qLen;
}