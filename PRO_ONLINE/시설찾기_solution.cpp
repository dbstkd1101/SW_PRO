#define MAX_N 10000
#define MAX_M_TYPE 10
#define MAX_M_ID 5000
#define SIZE 10000
#define MAX_ADD_CNT (int)(50000*0.45)

#ifndef NULL
#define NULL 0
#endif

int xDir[4] = { 0, 1, 0, -1 };
int yDir[4] = { -1, 0, 1, 0 };

struct Pos {
	int x, y;
	int dist;
};

int gethash(Pos _pos) {
	int sum = 0;
	sum = ((_pos.x) * (_pos.x) + (_pos.y) * (_pos.y)) % SIZE;
	return sum;
}

struct facility {
	Pos pos;
	int mId, mType;
	facility* prev, * next;
	facility* alloc(Pos _pos, int _mId, int _mType, facility* _prev, facility* _next) {
		pos = _pos, mId = _mId, mType = _mType, prev = _prev, next = _next;
		if (prev) prev->next = this;
		if (next) next->prev = this;
		return this;
	}
	void pop() {
		prev->next = next;
		if (next) next->prev = prev;
	}
}fBuf[MAX_ADD_CNT + SIZE], * bucket[SIZE];

int fBCnt;
int tN;

facility* mIdArr[MAX_M_ID];

int getRootDistance(int ax, int bx, int ay, int by) {
	int distX = (ax >= bx) ? ax - bx : bx - ax;
	int distY = (ay >= by) ? ay - by : by - ay;

	return distX * distX + distY * distY;
}

void init(int N)
{
	fBCnt = 0;
	tN = N;

	//dummy node
	for (int i = 0; i < SIZE; i++) {
		bucket[i] = fBuf[fBCnt++].alloc({ -1, -1, -1 }, -1, -1, NULL, NULL);
	}
	// 0 부터 시작
	for (int j = 0; j < MAX_M_ID; j++) {
		mIdArr[j] = NULL;
	}
}

void add(int mId, int mType, int mX, int mY)
{
	Pos _pos = { mX, mY, -1 };
	int hash = gethash(_pos);
	mIdArr[mId] = fBuf[fBCnt++].alloc(_pos, mId, mType, bucket[hash], bucket[hash]->next);
}

void removeId(int mId)
{
	if (mIdArr[mId]) mIdArr[mId]->pop();
	mIdArr[mId] = NULL;
}

bool isThere(int mType, Pos _pos) {
	int hash = gethash(_pos);
	for (facility* p = bucket[hash]->next; p; p = p->next) {
		if (mType == 0) {
			if (p->pos.x == _pos.x && p->pos.y == _pos.y) {
				return true;
			}
		}
		else {
			if (p->pos.x == _pos.x && p->pos.y == _pos.y && p->mType == mType) {
				return true;
			}
		}
	}
	return false;
}

int isThereAndFindMId(int mType, Pos _pos) {
	int rst = -1;
	int hash = gethash(_pos);
	for (facility* p = bucket[hash]->next; p; p = p->next) {
		if (p->pos.x == _pos.x && p->pos.y == _pos.y && p->mType == mType) {
			return rst = p->mId;
		}
	}
	return rst;
}

int visited[MAX_N][MAX_N];
Pos queue[MAX_N * MAX_N];

void initErase() {
	for (int i = 0; i < tN; i++) {
		for (int j = 0; j < tN; j++) {
			visited[i][j] = NULL;
		}
	}
}

int search1(int mType, int mX, int mY, int radius)
{
	initErase();
	int rstCnt = 0, front = -1, rear = -1;
	Pos first = { mX, mY };
	visited[first.y][first.x] = true;
	if (isThere(mType, first)) {
		rstCnt++;
	}
	if (radius * radius > getRootDistance(mX, first.x, mY, first.y)) queue[++rear] = first;

	while (front < rear) {
		Pos popNode = queue[++front];
		for (int i = 0; i < 4; i++) {
			Pos tmp = { popNode.x + xDir[i], popNode.y + yDir[i] };
			if (!visited[tmp.y][tmp.x]) {
				visited[tmp.y][tmp.x] = true;
				if (radius * radius > getRootDistance(mX, tmp.x, mY, tmp.y)) {
					queue[++rear] = tmp;
					if (isThere(mType, tmp)) {
						rstCnt++;
					}
				}
			}
		}
	}
	return rstCnt;
}

typedef facility data;

void swap(data& a, data& b) {
	data t = a; a = b; b = t;
}

bool Min(data a, data b, Pos center) {
	return getRootDistance(a.pos.x, center.x, a.pos.y, center.y) < getRootDistance(b.pos.x, center.x, b.pos.y, center.y) ? true : ((getRootDistance(a.pos.x, center.x, a.pos.y, center.y) == getRootDistance(b.pos.x, center.x, b.pos.y, center.y)) && (a.mId < b.mId)) ? true : false;
}

struct PriorityQueue {
	data heap[800];
	int hn;
	Pos center;
	bool(*comp) (data, data, Pos);
	void init(Pos _center, bool(*_comp)(data, data, Pos)) {
		hn = 0, center = _center;
		comp = _comp;
	}
	data top() {
		while (hn > 1) pop();
		return heap[1];
	}
	int size() {
		return hn;
	}
	void push(data memId) {
		// 1부터 시작
		heap[++hn] = memId;
		for (int cur = hn; cur > 1 && comp(heap[cur], heap[cur / 2], center); cur /= 2) {
			swap(heap[cur], heap[cur / 2]);
		}
	}
	data pop() {
		data ret = heap[1];
		swap(heap[1], heap[hn--]);

		int p = 1, cur = 2;
		for (; cur <= hn; p = cur, cur *= 2) {
			// 최적의 자식(cur) 선택 (우자식이 가능하며, 우자식이 더 좋을 때)
			if (cur < hn && comp(heap[cur + 1], heap[cur], center)) cur++;
			if (comp(heap[p], heap[cur], center)) break;
			else swap(heap[p], heap[cur]);
		}
		return ret;
	}
}minpq;


void search2(int mType, int mX, int mY, int mIdList[5])
{
	initErase();

	int rstIdx = 0, front = -1, rear = -1;
	int beforeDist = 0;
	Pos first = { mX, mY, 0 };
	visited[first.y][first.x] = true;
	int mId;
	if ((mId = isThereAndFindMId(mType, { first.x, first.y })) >= 0) mIdList[rstIdx++] = mId;
	queue[++rear] = first;

	Pos tempPos = { mX, mY, -1 };
	minpq.init(tempPos, Min);
	while (front < rear) {	
		Pos popNode = queue[++front];

		// queue에 있는 node의 dist가 1이 추가 되었다는 것은, 최고 5개 이하만 추리는 작업이 필요.
		if (beforeDist != popNode.dist) {
			while (rstIdx < 5 && minpq.size() > 0) {
				mIdList[rstIdx++] = (minpq.pop()).mId;
			}
		}

		for (int i = 0; i < 4; i++) {
			Pos tmp = { popNode.x + xDir[i], popNode.y + yDir[i], popNode.dist + 1 };
			if (0<=tmp.x && tmp.x<tN && 0<=tmp.y && tmp.y<tN && !visited[tmp.y][tmp.x]) {
				if (tmp.x == 5 && tmp.y == 1) {
					int a = 1;
				}
				visited[tmp.y][tmp.x] = true;
				if ((mId = isThereAndFindMId(mType, { tmp.x, tmp.y, -1 })) >= 0) {
					facility tempFacility;
					tempFacility.pos = { tmp.x, tmp.y, -1 };
					tempFacility.mId = mId;
					minpq.push(tempFacility);
				}
				queue[++rear] = tmp;
			}
			beforeDist = popNode.dist;
		}
	}
	while (rstIdx < 5 && minpq.size() > 0) {
		mIdList[rstIdx++] = (minpq.pop()).mId;
	}
}

