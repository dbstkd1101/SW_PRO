//	 The below commented functions are for your reference. If you want 
//	 to use it, uncomment these functions.
#ifndef NULL
#define NULL 0
#endif

int mstrcmp(const char a[], const char b[])
{
	int i;
	for (i = 0; a[i] != '\0'; ++i) if (a[i] != b[i]) return a[i] - b[i];
	return a[i] - b[i];
}

void mstrcpy(char dest[], const char src[])
{
	int i = 0;
	while (src[i] != '\0') { dest[i] = src[i]; i++; }
	dest[i] = src[i];
}

int mstrlen(const char a[])
{
	int i;
	for (i = 0; a[i] != '\0'; ++i);
	return i;
}

#define SIZE 10000
#define MAX_LEN_NAME 6
#define MAX_CNT_ADD 50000

int getHash(char name[MAX_LEN_NAME+1]) {
	int sum = 0;
	for (int i = 0; name[i] && i < MAX_LEN_NAME; i++) {
		sum = ((sum << 5 | name[i])%SIZE);
	}
	return sum;
}

struct word {
	int idx;
	word *prev, *next;
	word* alloc(int _idx, word *_prev, word *_next) {
		idx = _idx, prev = _prev, next = _next;
		if (prev) prev->next = this;
		if (next) next->prev = this;
		return this;
	}
	void pop() {
		prev->next = next;
		if (next) next->prev = prev;
	}
}wBuf[MAX_CNT_ADD*12+ MAX_CNT_ADD+SIZE*3+1000], *front[SIZE], *back[SIZE], *origin[SIZE];

int wBCnt;

struct name {
	char name[MAX_LEN_NAME + 1];
	int cnt, addrCnt;
	word* addr[13];
}nStk[MAX_CNT_ADD];

int nSCnt;

int nameCnt[MAX_CNT_ADD];
int searchRemoveCnt;

void init(void)
{
	searchRemoveCnt = wBCnt = nSCnt = 0;
	// dummy node add
	for (int i = 0; i < SIZE; i++) {
		front[i] = wBuf[wBCnt++].alloc(-1, NULL, NULL);
		back[i] = wBuf[wBCnt++].alloc(-1, NULL, NULL);
		origin[i] = wBuf[wBCnt++].alloc(-1, NULL, NULL);
	}

	for (int j = 0; j < MAX_CNT_ADD; j++) nameCnt[j] = 0;
}

int getSearch(char str[]) {
	int hash = getHash(str);

	for (word* p = origin[hash]->next; p; p = p->next) {
		if (!mstrcmp(str, nStk[p->idx].name)) {
			return p->idx;
		}
	}
	mstrcpy(nStk[nSCnt].name, str);
	nStk[nSCnt].cnt = 1, nStk[nSCnt].addrCnt = 0;
	for (int i = 0; i < 13; i++) {
		nStk[nSCnt].addr[i] = NULL;
	}
	return nSCnt++;
}

bool astericCheck(char * front, char *back, char * str) {
	bool rst = false;

	for (int i = 0; i < MAX_LEN_NAME + 1; i++) {
		if (str[i] == '*') {
			for (int j = 0; j < i; j++) {
				front[j] = str[j];
			}
			for (int j = i+1; j < MAX_LEN_NAME; j++) {
				back[j] = str[j];
			}
			return (rst = true);
		}
	}
	return rst;
}

// 같은 단어 여러 번 나올 수 있음
void addWord(char str[])
{
	int nSCntTmp = nSCnt;
	int idx = getSearch(str);
	//신규추가
	if (nSCntTmp != nSCnt) {
		int len = mstrlen(str);
		//front Add
		for (int i = 0; i < len; i++) {
			char tmpStr[MAX_LEN_NAME + 1] = { 0, };
			for (int j = 0; j <= i; j++) {
				tmpStr[j] = str[j];
			}
			int hash = getHash(tmpStr);
			nStk[idx].addr[nStk[idx].addrCnt++]=wBuf[wBCnt++].alloc(idx, front[hash], front[hash]->next);
		}
		//back Add
		for (int i = 0; i < len; i++) {
			char tmpStr[MAX_LEN_NAME + 1] = { 0, };
			for (int j = 0; j <= i; j++) {
				tmpStr[j] = str[len-1-i+j];
			}
			int hash = getHash(tmpStr);
			nStk[idx].addr[nStk[idx].addrCnt++]=wBuf[wBCnt++].alloc(idx, back[hash], back[hash]->next);
		}
		//origin Add
		int hash = getHash(str);
		nStk[idx].addr[nStk[idx].addrCnt++]=wBuf[wBCnt++].alloc(idx, origin[hash], origin[hash]->next);
	}
	else {
		nStk[idx].cnt++;
	}
}

int removeWord(char str[])
{
	int rstCnt = 0;
	char frontStr[MAX_LEN_NAME + 1] = { 0, };
	char backStr[MAX_LEN_NAME + 1] = { 0, };

	// '*'가 있다면
	if (astericCheck(frontStr, backStr, str)) {
		if (front[0]) {
			int fHash = getHash(frontStr);
			for (word* p = front[fHash]; p; p = p->next) {
				if (nameCnt[p->idx] == searchRemoveCnt) nameCnt[p->idx] = (searchRemoveCnt + 1);
				else nameCnt[p->idx] = searchRemoveCnt;
			}
		}

		if (back[0]) {
			int fHash = getHash(backStr);
			for (word* p = back[fHash]; p; p = p->next) {
				if (nameCnt[p->idx] == searchRemoveCnt) nameCnt[p->idx] = (searchRemoveCnt + 1);
				else nameCnt[p->idx] = searchRemoveCnt;
			}
		}

		if (front[0] && back[0]) {
			for (int i = 0; i < nSCnt; i++) {
				if (nameCnt[i] == (searchRemoveCnt + 1)) {
					rstCnt += nStk[i].cnt;
					for (int j = 0; j < nStk[i].addrCnt; j++) {
						nStk[i].addr[j]->pop();
					}
				}
			}
		}
		else {
			// front만 있을 경우
			for (int i = 0; i < nSCnt; i++) {
				if (nameCnt[i] == (searchRemoveCnt)) {
					rstCnt += nStk[i].cnt;
					for (int j = 0; j < nStk[i].addrCnt; j++) {
						nStk[i].addr[j]->pop();
					}
				}
			}
		}
	}
	else {
		int hash = getHash(str);
		for (word* p = origin[hash]; p; p = p->next) {
			rstCnt = nStk[p->idx].cnt;
			for (int i = 0; i < nStk[p->idx].addrCnt; i++) {
				nStk[p->idx].addr[i]->pop();
			}
		}
	}
	searchRemoveCnt *= 2;

	return rstCnt;
}

int searchWord(char str[])
{
	int rstCnt = 0;
	
	char frontStr[MAX_LEN_NAME + 1] = { 0, };
	char backStr[MAX_LEN_NAME + 1] = { 0, };

	// '*'가 있다면
	if (astericCheck(frontStr, backStr, str)) {
		if (front[0]) {
			int fHash = getHash(frontStr);
			for (word* p = front[fHash]; p; p = p->next) {
				if (nameCnt[p->idx] == searchRemoveCnt) nameCnt[p->idx] = (searchRemoveCnt + 1);
				else nameCnt[p->idx] = searchRemoveCnt;
			}
		}
		
		if (back[0]) {
			int fHash = getHash(backStr);
			for (word* p = back[fHash]; p; p = p->next) {
				if (nameCnt[p->idx] == searchRemoveCnt) nameCnt[p->idx] = (searchRemoveCnt + 1);
				else nameCnt[p->idx] = searchRemoveCnt;
			}
		}

		if (front[0] && back[0]) {
			for (int i = 0; i < nSCnt; i++) {
				if (nameCnt[i] == (searchRemoveCnt + 1)) {
					rstCnt++;
				}
			}
		}
		else {
			// front만 있을 경우
			for (int i = 0; i < nSCnt; i++) {
				if (nameCnt[i] == (searchRemoveCnt)) {
					rstCnt++;
				}
			}
		}
	}
	else {
		int hash = getHash(str);
		for (word* p = origin[hash]; p; p = p->next) {
			rstCnt=nStk[p->idx].cnt;
		}
	}
	searchRemoveCnt*=2;
	return rstCnt;
}
