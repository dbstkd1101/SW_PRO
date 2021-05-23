#ifndef NULL
#define NULL 0
#endif 

// MEM : 256 MB
#define MAX_CNT_ID 10000
#define MAX_LEN_RECORD 100
//#define MAX_BUCKET_SIZE 30000000
#define MAX_BUCKET_SIZE 100000
#define MAX_BUF_SIZE (MAX_CNT_ID * MAX_LEN_RECORD)
#define EXTRACT_LENGTH 8

typedef unsigned long long ULL;

int record[MAX_CNT_ID + 1][MAX_LEN_RECORD + 1];
int bufCnt;

int hashArr[100][100];

struct node {
	int id;
	int startIdx;
	node * next;
	node * mAlloc(int _id, int _startIdx, int hash) {
		buf[bufCnt].id = _id;
		buf[bufCnt].startIdx = _startIdx;
		buf[bufCnt].next = bucket[hash];
		return this;
	}
}*bucket[MAX_BUCKET_SIZE], buf[MAX_BUF_SIZE];


int getHash(int * str, int startIdx) {
	ULL sum = 5831;
	for (int i = startIdx; i < EXTRACT_LENGTH; i++) {
		sum = ((sum << 8) + (str[i]))% MAX_BUCKET_SIZE;
	}
	return sum;
}

void initUser(int dataN) {
	for (int i = 1; i <= dataN; i++) {
		for (int j = 1; j <= MAX_LEN_RECORD; j++) {
			record[i][j] = NULL;
		}
	}
	for (int k = 0; k < MAX_BUCKET_SIZE; k++) {
		bucket[k] = NULL;
	}
	bufCnt = 0;
}

void registerData(int dataID, int dataLen, int dataArr[MAX_LEN_RECORD]) {

	for (int i = 0; i < dataLen; i++) {
		record[dataID][i] = dataArr[i];
		if (i >= EXTRACT_LENGTH-1) {
			if (dataID == 1) {
				int a = 1;
			}
			int startIdx = i - EXTRACT_LENGTH+1;
			int hash = getHash(dataArr, startIdx);
			bucket[hash]=buf[bufCnt].mAlloc(dataID, startIdx, hash);
			bufCnt++;
		}
	}
}

int idComp(int * origin, int * dest, int len) {
	int rst = 1;
	for (int i = 0; i < len; i++) {
		if (origin[i] != dest[i]) {
			return rst = 0;
		}
	}
	return rst;
}

int findID(int args[8]) {
	int id = 0;

	int hash = getHash(args, 0);
	node * p = bucket[hash];
	for ( ; p; p = p->next) {
		if (idComp(args, &record[p->id][p->startIdx], EXTRACT_LENGTH)) {
			return p->id;
		}
	}
	return id;
}