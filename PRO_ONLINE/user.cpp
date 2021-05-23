#ifndef NULL
#define NULL 0
#endif

#define MAX_LENT_SECTION		100
#define MAX_CNT_ONE_BOOK_TYPE	5
#define MAX_TYPE 500
#define MAX_NAME_LEN	(6+1)
#define MAX_TYPE_LEN		(3+1)
#define MAX_CNT_ADD 50000
#define MAX_CNT_COUNT 100
#define SIZE 5000000

//TC 4, q=18, Add에서 오류

void mstrcpy(char dst[], const char src[]) {
	int c = 0;
	while ((dst[c] = src[c]) != '\0') ++c;
}

int mstrcmp(const char str1[], const char str2[]) {
	int c = 0;
	while (str1[c] != '\0' && str1[c] == str2[c]) ++c;
	return str1[c] - str2[c];
}

struct book {
	int bStkIdx;
	int tStkIdx;
	book * prev;
	book * next;

	book* push(int _bStkIdx, int _tStkIdx, book * _prev, book * _next) {
		bStkIdx=_bStkIdx, tStkIdx = _tStkIdx, prev = _prev, next = _next;
		if(prev) prev->next = this;
		if(next) next->prev = this;
		return this;
	}
	void pop() {
		prev->next = next;
		if (next) next->prev = prev;
	}
}* sections[MAX_LENT_SECTION +1][MAX_TYPE+1], bookBuf[MAX_TYPE * MAX_LENT_SECTION + MAX_CNT_ADD * MAX_CNT_ONE_BOOK_TYPE +100];

char typeStk[MAX_TYPE + 1][MAX_TYPE_LEN];
struct tNode {
	char tName[MAX_TYPE_LEN];
	int tIdx;
	tNode * next;
	tNode* alloc(char _tName[], int _tIdx, tNode * _next) {
		mstrcpy(tName, _tName);
		tIdx = _tIdx;
		next = _next;
		return this;
	}
}* tBucket[SIZE], tNodeBuf[MAX_TYPE];

int getHash(char * bName) {
	int sum = 5831;
	for (int i = 0; bName[i]; i++) {
		sum = ((sum << 6) + bName[i]) % SIZE;
	}
	return sum;
}

char bStk[MAX_CNT_ADD + 1][MAX_NAME_LEN];
struct bNode{
	char bName[MAX_NAME_LEN];
	int bStkIdx;
	int typeCnt;
	book* addr[MAX_CNT_ONE_BOOK_TYPE];
	bNode * next;
	bNode * alloc(char * _bName, int _bStkIdx, bNode * _next, int _typeCnt, book* _addr[MAX_TYPE_LEN]) {
		mstrcpy(bName, _bName);
		bStkIdx=_bStkIdx, next = _next, typeCnt = _typeCnt;
		for (int i = 0; i < typeCnt; i++) {
			addr[i] = _addr[i];
		}
		return this;
	}
}* bBucket[SIZE], bNodeBuf[MAX_CNT_ADD + 1];

int bCnt;
int tCnt;
int bNodeCnt;

int bStkCntArr[MAX_CNT_COUNT + 1];
int cntBCnt;

void init(int M)
{
	cntBCnt= bCnt = tCnt = bNodeCnt = 0;
	// dummy Node를 초기화
	for (int i = 0; i < MAX_LENT_SECTION; i++) {
		for (int j = 0; j < MAX_TYPE; j++) {
			sections[i][j] = bookBuf[bCnt++].push(-1, -1, NULL, NULL);
		}
	}
	 
	for (int j = 0; j < MAX_TYPE; j++) {
		tBucket[j] = NULL;
		typeStk[j][0] = NULL;
	}

	for (int k = 0; k < SIZE; k++) {
		bBucket[k] = NULL;
	}
	
	for (int l = 0; l < MAX_CNT_ADD; l++) {
		bStk[l][0] = NULL;
	}

	for (int m = 0; m < MAX_CNT_COUNT+1; m++) {
		bStkCntArr[m] = 0;
	}
}

int bSearch(char _bName[]) {
	int hash = getHash(_bName);
	for (bNode * p = bBucket[hash]; p; p = p->next) {
		if (mstrcmp(p->bName, _bName) == 0) return p->bStkIdx;
	}
	// 없다면 idx만 return, 추가는 add 마지막에서
	return bNodeCnt;
}

int tSearch(char _tName[]) {
	int hash = getHash(_tName);
	for (tNode * p = tBucket[hash]; p; p = p->next) {
		if (mstrcmp(p->tName, _tName) == 0) return p->tIdx;
	}
	// 없다면 return, 추가는 add 마지막에서	
	return tCnt;
}


void add(char mName[MAX_NAME_LEN], int mTypeNum, char mTypes[MAX_CNT_ONE_BOOK_TYPE][MAX_TYPE_LEN], int mSection)
{
	book* addrTmp[MAX_CNT_ONE_BOOK_TYPE];
	int bIdx, tIdx;
	for (int i = 0; i < mTypeNum; i++) {
		bIdx = bSearch(mName);
		tIdx = tSearch(mTypes[i]);
		
		addrTmp[i]=bookBuf[bCnt++].push(bIdx, tIdx, sections[mSection][tIdx], sections[mSection][tIdx]->next);
		
		// 해당 type이 존재하지 않을 경우 추가
		if (tIdx == tCnt) {
			int tHash = getHash(mTypes[i]);
			tBucket[tHash] = tNodeBuf[tCnt].alloc(mTypes[i], tCnt, tBucket[tHash]);
			mstrcpy(typeStk[tCnt++], mTypes[i]);
		}
	}
	// bNode 추가
	int hash = getHash(mName);
	if (hash == 20775) {
		int c = 1;
	}
	// bIdx === bNodeCnt
	bBucket[hash]=bNodeBuf[bNodeCnt].alloc(mName, bNodeCnt, bBucket[hash], mTypeNum, addrTmp);
	mstrcpy(bStk[bNodeCnt++], mName);
}


void moveName(char mName[MAX_NAME_LEN], int mSection)
{
	int hash = getHash(mName);
	if (hash == 20775) {
		int c = 1;
	}
	for (bNode * p = bBucket[hash]; p; p = p->next) {
		if (mstrcmp(p->bName, mName) == 0) {
			for (int i = 0; i < p->typeCnt; i++) {
				book *tmp = (p->addr[i]);
				tmp->pop();
				tmp->push(tmp->bStkIdx, tmp->tStkIdx, sections[mSection][tmp->tStkIdx], sections[mSection][tmp->tStkIdx]->next);
			}
		}
	}
}

int moveType(char mType[MAX_TYPE_LEN], int mFrom, int mTo)
{
	int rst = 0;
	int tIdx = tSearch(mType);

	book * dummyP = sections[mFrom][tIdx];
	for (book * p = dummyP->next; p; p = dummyP->next) {
		rst++;
		moveName(bStk[p->bStkIdx], mTo);
	}

	return rst;
}
void deleteName(char mName[MAX_NAME_LEN])
{
	int hash = getHash(mName);
	for (bNode * p = bBucket[hash]; p; p = p->next) {
		if (mstrcmp(p->bName, mName) == 0) {
			for (int i = 0; i < p->typeCnt; i++) {
				book *tmp = (p->addr[i]);
				tmp->pop();
			}
		}
	}
}

int countBook(int mTypeNum, char mTypes[MAX_CNT_ONE_BOOK_TYPE][MAX_TYPE_LEN], int mSection)
{
	int rst = 0;
	cntBCnt++; //1부터 시작하기 위해

	for (int i = 0; i < mTypeNum; i++) {
		//없으면 만들지 않음
		int tIdx = tSearch(mTypes[i]);
		if (tIdx == tCnt) continue;

 		book * dummyTmp = sections[mSection][tIdx];
		for (book * p = dummyTmp->next; p; p = p->next) {
			if(bStkCntArr[p->bStkIdx] != cntBCnt) bStkCntArr[p->bStkIdx] = cntBCnt;
		}
	}

	for (int i = 0; i< bNodeCnt; i++) {
		if (bStkCntArr[i] == cntBCnt) rst++;
	}

	return rst;
}