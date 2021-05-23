#ifndef NULL
#define NULL 0
#endif

#define MAX_LEN_RC 150
#define MAX_LEN_NAME 10
#define SIZE 150*150
#define BUF_SIZE 100000

void strcpy(char* dest, char* origin) {
	while (*origin && ('a'<=*origin && *origin <='z')) *dest++ = *origin++;
	*dest = 0;
}

int strcmp(char* s1, char* s2) {
	while (('a'<=*s1 && *s1<='z')&& ('a' <= *s2 && *s2 <= 'z') && *s1 && (*s1 == *s2)) {
		++s1; ++s2;
	}
	return *s1 - *s2;
}

// rR, rC ���� (-1, -1) ���� ����. �� �θ� ����Ű�ų�, �ڽ��� �θ��̰ų�.
struct {
	bool root;
	int mR, mC, sIdx, areaCnt;
}data[MAX_LEN_RC + 1][MAX_LEN_RC + 1];

struct cStack {
	char name[MAX_LEN_NAME + 1];
	int cellCnt, areaCnt;
}stkArr[MAX_LEN_RC * MAX_LEN_RC+10];

struct node {
	char name[MAX_LEN_NAME+1];
	int sIdx;
	node * next;
	node* alloc(char * _name, int _sIdx, node* _next) {
		strcpy(name, _name);
		sIdx = _sIdx, next = _next;
		return this;
	}
}*bucket[SIZE], buf[BUF_SIZE];

int bCnt, sCnt;

void init(int Row, int Col) {
	bCnt = 0, sCnt = 1;
	for (int i = 1; i<= Row; i++) {
		for (int j = 1; j <= Col; j++) {
			data[i][j] = { true, 0, 0, 0, 1 };
		}
	}
	for (int i = 0; i < SIZE; i++) {
		bucket[i] = NULL;
	}
}

int getHash(char * name) {
	int sum = 5831;
	for (int i = 0; ('a' <= name[i] && name[i] <= 'z'); i++) {
		sum = (((sum << 5) | name[i])%SIZE);
	}
	return sum;
}

int search(char * name) {
	int hash = getHash(name);
	for (node * p = bucket[hash]; p; p = p->next) {
		if (!strcmp(name, p->name)) return p->sIdx;
	}
	bucket[hash] = buf[bCnt].alloc(name, sCnt, bucket[hash]);
	bCnt++;
	strcpy(stkArr[sCnt].name, name);
	return sCnt++;
}

int findRootCrop(int row, int col, int* rootR, int* rootC) {
	int isExist = false;
	// ���� �� ���� �θ� ��ǥ NULL
	if (data[row][col].mR && data[row][col].mC) {
		int nR = row, nC = col;
		// root���� �ź� �����, root key �� NULL ��ġ �ʿ�
		while (!data[nR][nC].root) {
			int tmpR = data[nR][nC].mR;
			int tmpC= data[nR][nC].mC;
			nR = tmpR, nC = tmpC;
		}
		*rootR = nR, *rootC = nC;
		isExist = true;
	}
	else if(data[row][col].sIdx){
		// �ڱⰡ ���۹��� �����ϴ� ���� root
		*rootR = row, *rootC = col;
		isExist = true;
	}
	else {
		*rootR = row, *rootC = col;
	}
	return isExist;
}

void setFarm(int row, int col, char crop[]) {
	int rootR, rootC;
	int sIdx = search(crop);

	if (findRootCrop(row, col, &rootR, &rootC)) {
		stkArr[data[rootR][rootC].sIdx].areaCnt -= data[rootR][rootC].areaCnt;
		stkArr[data[rootR][rootC].sIdx].cellCnt--;
	}
	// root�� ���� X (�ڱ� �ڽŸ�?)
	else {
		data[rootR][rootC].root = true;
	}
	stkArr[sIdx].areaCnt += data[rootR][rootC].areaCnt;
	data[rootR][rootC].sIdx = sIdx;
	stkArr[sIdx].cellCnt++;
}

void getCrop(int row, int col, char crop[]) {
	int rootR, rootC;
	findRootCrop(row, col, &rootR, &rootC);
	int sIdx = data[rootR][rootC].sIdx;
	strcpy(crop, stkArr[sIdx].name);
}


void mergeCell(int row1, int col1, int row2, int col2, int sw) {
	int destRR, destRC, srcRR, srcRC;
	if (sw == 1) {
		findRootCrop(row1, col1, &destRR, &destRC);
		findRootCrop(row2, col2, &srcRR, &srcRC);
	}
	else {
		findRootCrop(row2, col2, &destRR, &destRC);
		findRootCrop(row1, col1, &srcRR, &srcRC);
	}

	data[srcRR][srcRC].root = false;
	data[srcRR][srcRC].mR = destRR;
	data[srcRR][srcRC].mC = destRC;
	int srcSIdx = data[srcRR][srcRC].sIdx;
	stkArr[srcSIdx].cellCnt--;
	stkArr[srcSIdx].areaCnt -= data[srcRR][srcRC].areaCnt;

	int destSIdx = data[destRR][destRC].sIdx;
	stkArr[destSIdx].areaCnt += data[srcRR][srcRC].areaCnt;
	data[destRR][destRC].areaCnt += data[srcRR][srcRC].areaCnt;
	data[srcRR][srcRC].areaCnt = 0;
}

int cntCell(char crop[]) {
	int sIdx = search(crop);
	return stkArr[sIdx].cellCnt;
}

int cntArea(char crop[]) {
	int sIdx = search(crop);
	return stkArr[sIdx].areaCnt;
}