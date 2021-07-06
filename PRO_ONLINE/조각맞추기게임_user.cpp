
#ifndef NULL
#define NULL 0
#endif

#define MAX_LEN_PIECE 5
#define MAX_CNT_CALL 20000
#define MAX_LEN_WALL (MAX_LEN_PIECE)*(MAX_CNT_CALL)
#define SIZE 100000

extern struct piece;

int map[MAX_LEN_WALL + 100];
piece * pieceMap[MAX_LEN_WALL + 100];

int mapIdx, mapHP;

int getHash(int * p) {

	int sum = 0;
	for (int i = 0; i < MAX_LEN_PIECE; i++) {
		if (i != 0) {
			sum = ((sum << 4) | (*(p + i)))%SIZE;
		}
		else {
			sum |= (*(p + i))%SIZE;
		}
	}
	return sum%SIZE;
}

struct piece {
	int pMap[MAX_LEN_PIECE];
	int idx;
	piece* prev, * next;
	piece* alloc(int* _pMap, int _idx, piece* _prev, piece* _next) {
		for (int i = 0; i < MAX_LEN_PIECE; i++) {
			pMap[i] = _pMap[i];
		}
		idx = _idx;
		prev = _prev, next = _next;
		if (prev) prev->next = this;
		if (next) next->prev = this;
		return this;
	}
	void pop() {
		prev->next = next;
		if(next) next->prev = prev;
	}
}* pBucket[SIZE], pBuf[SIZE + MAX_LEN_WALL + 100];

int pBCnt;

void init()
{
	mapHP = mapIdx = pBCnt = 0;
	for (int i = 0; i < SIZE; i++) {
		pBucket[i]=pBuf[pBCnt++].alloc(NULL, -1, NULL, NULL);
	}
}

void makeWall(int mHeights[5])
{
	for (int i = 0; i < MAX_LEN_PIECE; i++) {
		map[mapIdx++] = mHeights[i];
	}

	for (; (mapHP+ MAX_LEN_PIECE-1) < mapIdx; mapHP++) {
		int hash = getHash(&map[mapHP]);
		pieceMap[mapHP]=pBuf[pBCnt++].alloc(&map[mapHP], mapHP, pBucket[hash], pBucket[hash]->next);
	}
}

void rotate(int _mHeights[]) {
	int rotatedHeights[MAX_LEN_PIECE];
	for (int i = 0; i < MAX_LEN_PIECE; i++) {
		rotatedHeights[MAX_LEN_PIECE - i - 1] = _mHeights[i];
	}

	for (int j = 0; j < MAX_LEN_PIECE; j++) {
		_mHeights[j] = rotatedHeights[j];
	}
}

int findMaxHeight(int _mHeights[]) {
	int max = -1;
	for (int i = 0; i < MAX_LEN_PIECE; i++) {
		if (_mHeights[i] > max) max = _mHeights[i];
	}
	return max;
}

bool isSame(int a[], int b[]) {
	bool rst = true;
	for (int i = 0; i < MAX_LEN_PIECE; i++) {
		if (a[i] != b[i]) return (rst = false);
	}
	return rst;
}

void updateMap(int _maxMatchIdx) {

	for (int i = _maxMatchIdx+MAX_LEN_PIECE; i< mapIdx; i++) {
		map[i - MAX_LEN_PIECE] = map[i];
	}
	//제외되는 buf pop 시켜야하고, mapHP 구간 내/외 구분하여 처리
	mapHP -= 5;
	mapIdx -= 5;
}

int matchPiece(int mHeights[5])
{
	rotate(mHeights);
	int maxHeight= findMaxHeight(mHeights);
	int maxMatchIdx = -1;

	for (int i = 0; i+ maxHeight <= 10 ; i++) {
		int temp[5];
		for (int j = 0; j < 5; j++) {
			temp[j] = i + mHeights[j];
		}
		int hash = getHash(temp);
		for (piece* p = pBucket[hash]->next; p; p = p->next) {
			if (isSame(p->pMap, temp)) {
				if (p->idx > maxMatchIdx) maxMatchIdx = p->idx;
			}
		}
	}

	updateMap(maxMatchIdx);

	return maxMatchIdx ;
}