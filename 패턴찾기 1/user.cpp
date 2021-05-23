#define MAX_ARR_LENGTH 1000
#define MAX_BUF_LENGTH (1000-4)*(1000-4)
#define MAX_BUCKET_LENGTH 1000
#define MAX_M_LENGTH 8

#ifndef NULL
#define NULL 0
#endif

typedef unsigned long long  ULL;

int N, M;

int arr[MAX_ARR_LENGTH][MAX_ARR_LENGTH];


typedef struct node {
	int row, col;
	ULL value;
	node * next;
}NODE;

NODE buf[MAX_BUF_LENGTH];
int bufN;

NODE * bucket[MAX_BUCKET_LENGTH];

ULL getValue(int row, int col, int maxMSize) {
	ULL sum = 0;
	
	for (int i = 0; i < maxMSize; i++) {
		for (int j = 0; j < maxMSize; j++) {
			sum = sum * 2 + arr[row + i][col + j];
		}
	}
	return sum;
}

int getHashCode(ULL value) {
	return value % MAX_BUCKET_LENGTH;
}

NODE * mAlloc(ULL value, int row, int col, int hash_code) {
	buf[bufN].row = row; buf[bufN].col = col; buf[bufN].value = value;
	buf[bufN].next = bucket[hash_code];
	return &buf[bufN++];
}

void addNode(ULL value, int row, int col, int hash_code) {
	bucket[hash_code] = mAlloc(value, row, col, hash_code);
}

void init(int n, int ap[][1000], int m) {
	N = n; M = m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			arr[i][j] = ap[i][j];
		}
	}
	
	bufN = 0;
	
	for (int i = 0; i < MAX_BUCKET_LENGTH; i++) {
		bucket[i] = NULL;
	}
	
	//make hash
	int maxM = 0; int limit = 0;
	if (m <= MAX_M_LENGTH) {
		maxM = m;
	}
	else {
		maxM = MAX_M_LENGTH;
	}

	limit = N - M;

	for (int i = 0; i < limit; i++) {
		for (int j = 0; j < limit; j++) {
			ULL value = getValue(i, j, maxM);
			int hash_code = getHashCode(value);
			addNode(value, i, j, hash_code);
		}
	}
}

int query(int bp[][20]) {
	int row = 0, col = 0;
	ULL value = 0;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			value = value * 2 + bp[i][j];
		}
	}

	int hash_code = getHashCode(value);

	NODE * cursor = bucket[hash_code];

	for (; cursor!=NULL; cursor=(cursor->next)) {

		if (value == cursor->value)
		{
			row = cursor->row;
			col = cursor->col;
			break;
		}

		if (cursor->next == NULL)
			break;
	}

	return row * N + col;
}
