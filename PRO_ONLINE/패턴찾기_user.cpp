#ifndef NULL
#define NULL 0
#endif

#define MAX_LEN_A 1000
#define BUCKET_SIZE 1000000
#define BUF_SIZE (MAX_LEN_A * MAX_LEN_A) + 1000

struct node {
	int r, c;
	node * next;
	node * alloc(int _r, int _c, node * _next) {
		r = _r, c = _c;
		next = _next;
		return this;
	}
}*bucket[BUCKET_SIZE], buf[BUF_SIZE];

int N, M;
int data[MAX_LEN_A][MAX_LEN_A];
int bCnt;

int getHash(int r, int c) {
	int sum = 0;
	for (int i = 0; i < 5; i++) {
		if(i!=0) sum <<= 5;
		sum |= (data[r + i][c + 5 - 1] & (32-1)) % BUCKET_SIZE;
	}
	return sum % BUCKET_SIZE;;
}

void init(int n, int ap[][1000], int m) {
	N = n, M = m, bCnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (j == 0) {
				data[i][j] = ap[i][j];
			}
			else {
				data[i][j] = (data[i][j - 1] << 1) | ap[i][j];
			}
		}
	}
	for (int k = 0; k < BUCKET_SIZE; k++) {
		bucket[k] = NULL;
	}

	int hash;
	for (int i = 0; i < N - M + 1; i++) {
		for (int j = 0; j < N - M + 1; j++) {
			hash=getHash(i, j);
			bucket[hash] = buf[bCnt++].alloc(i, j, bucket[hash]);
		}
	}
}

int comp(int r, int c, int bArrTmp[][20]) {
	for (int i = 0; i < M; i++) {
		if (!((data[r + i][c + M - 1] & ((1 << M) - 1)) == bArrTmp[i][M - 1])) {
			return 0;
		}
			
	}
	return 1;
}

int query(int bp[][20]) {
	int row = 0, col = 0;

	int bArr[20][20];
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			if (j == 0) bArr[i][j] = bp[i][j];
			else bArr[i][j] = ((bArr[i][j - 1] << 1) | bp[i][j]);
		}
	}

	int sum = 0;
	for (int i = 0; i < 5; i++) {
		if (i != 0) sum <<= 5;
		sum |= (bArr[i][5 - 1]&(32-1)) % BUCKET_SIZE;
	}
	sum %= BUCKET_SIZE;
	
	for (node * p = bucket[sum]; p; p = p->next) {
		if (comp(p->r, p->c, bArr)) {
			row = p->r, col = p->c;
			break;
		}
	}

	return row * N + col;
}