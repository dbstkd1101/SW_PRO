#ifndef NULL
#define NULL 0
#endif

#define MAX_N 1000
#define MAX_M 20

#define SIZE_HASH 5

#define SIZE 100000

int N, M;

int data[MAX_N][MAX_N];

struct node {
	int r, c;
	node * next;
	node * alloc(int _r, int _c, node * _next) {
		r = _r, c = _c, next = _next;
		return this;
	}
}*bucket[SIZE], buf[MAX_N * MAX_N + 100];

int bCnt;

int getHash(int r, int c) {
	int sum = 0;
	for (int i = 0; i < SIZE_HASH; i++) {
		if(i==0) sum |= data[r][c+i];
		else sum = ((sum << SIZE_HASH) | data[r][c + i]);
	}
	return sum;
}

void init(int n, int ap[][1000], int m) {
	N = n, M=m, bCnt=0;
	int tR, tC;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if(j==0) data[i][j] = ap[i][j]; 
			else data[i][j] = (((data[i][j - 1] << 1) | ap[i][j]));

			tR = i;
			tC = j - SIZE_HASH + 1;
			if ( (0 <= tR && tR <= (N - SIZE_HASH)) && (0 <= tC && tC <= (N - SIZE_HASH))) {
				int hash = getHash(tR, tC);
				bucket[hash] = buf[bCnt++].alloc(tR, tC, bucket[hash]);
			}
		}
	}
}

int check(node * p, int tBp[][20], int * row, int * col) {


	return 1;
}

int query(int bp[][20]) {
	int row = 0, col = 0;
	
	int tBData[MAX_M][MAX_M];
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			if (j == 0) tBData[i][j] = bp[i][j];
			else tBData[i][j] = (((tBData[i][j - 1] << 1) | bp[i][j]));
		}
	}

	int tHash = 0;
	for (int i = 0; i < SIZE_HASH; i++) {
		if (i == 0) tHash |= tBData[i][SIZE_HASH-1];
		else tHash = ((tHash << SIZE_HASH) | tBData[i][SIZE_HASH - 1]);
	}
	
	for (node * p = bucket[tHash]; p; p = p->next) {
		if (check(p, tBData, &row, &col)) break;
	}

	return row * N + col;
}