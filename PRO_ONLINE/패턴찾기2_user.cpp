#ifndef NULL
#define NULL 0
#endif

const int LM = 1005;
const int SIZE = 1 << 16;
int N, M, A[LM][LM], B[22][22], bcnt;

struct Node {
	int r, c;
	Node * next;
	Node * alloc(int _r, int _c, Node * _next) {
		r = _r, c = _c, next = _next;
		return this;
	}
}buf[LM*LM], *hash[SIZE];

int hashkey(int r, int c) {
	int key = 0;
	for (int i = 0; i < 4; i++) {
		key = (key << 4) + (A[r + i][c + 3] & (16 - 1));
	}
	return key;
}

void init(int n, int ap[][1000], int m) {
	N = n, M = m, bcnt = 0;
	for (int i = 0; i < SIZE; i++) hash[i] = NULL;
	for (int i = 0; i < N; i++) for (int j = 0, k=0; j < N; j++) {
		A[i][j] = k = ((k << 1) + ap[i][j]);
	}
	for (int i = 0; i <= N - M; i++) for (int j = 0; j <= N - M; j++) {
		int key = hashkey(i, j);
		hash[key] = buf[bcnt++].alloc(i, j, hash[key]);
	}
}

int check(int r, int c) {
	// for 조건이 4가 아니라 M이어야 한다.
	for (int i = 0; i < M; i++) {
		// B는 M-1열이 M기준 맨 마지막인게 확실하지만, A는 앞에서부터 누적된 값이므로 filter해줘야 함
		if ((A[r + i][c + M - 1] & ((1<<M)-1))!= B[i][M - 1]) return 0;
	}
	return 1;
}

void rotate(int b[][20]) {
	int t[20][20];
	for (int i = 0; i < M; i++) for (int j = 0; j < M; j++) {
		// 원래꺼에서 왼쪽으로 90도 돌려야 함. (이건 문제 잘 읽었어야 했네)
		t[i][j] = b[j][M-1-i];
	}
	for (int i = 0; i < M; i++)for (int j = 0; j < M; j++) b[i][j] = t[i][j];
}

int query(int bp[][20], int userAns[]) {
	int r, c, key, b[20][20];

	for (int i = 0; i < M; i++)for (int j = 0; j < M; j++) b[i][j] = bp[i][j];

	for (int t = 0; t < 4; t++) {
		for (int i = 0; i < M; i++) for (int j = 0, k = 0; j < M; j++) {
			if (b[i][j] == 9) r = i, c = j, b[i][j] = 1;
			B[i][j] = k = ((k << 1) + b[i][j]);
		}
		key = 0;
		for (int i = 0; i < 4; i++) key = (key << 4) + B[i][3];
		for (Node * p = hash[key]; p; p = p->next) {
			if (check(p->r, p->c)) {
				userAns[0] = p->r, userAns[1] = p->c;
				userAns[2] = p->r + r, userAns[3] = p->c + c;
				return t;
			}
		}
		b[r][c] = 9;
		rotate(b);
	}

	return 0;
}