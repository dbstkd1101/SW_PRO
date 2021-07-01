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
	while (src[i] != 0) { dest[i] = src[i]; i++; }
	dest[i] = src[i];
}

int mstrlen(const char a[])
{
	int i;
	for (i = 0; a[i] != '\0'; ++i);
	return i;
}

#define SIZE 1000000
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
	char name[MAX_LEN_NAME + 1];
	word *prev, *next;
	word* alloc(int _idx, char _name[MAX_LEN_NAME + 1], word *_prev, word *_next) {
		idx = _idx, prev = _prev, next = _next;
		mstrcpy(name, _name);
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
	wBCnt = nSCnt = 0;
	searchRemoveCnt = 0;
	// dummy node add
	char tmp[MAX_LEN_NAME + 1] = "";
	for (int i = 0; i < SIZE; i++) {
		front[i] = wBuf[wBCnt++].alloc(-1, tmp, NULL, NULL);
		back[i] = wBuf[wBCnt++].alloc(-1, tmp, NULL, NULL);
		origin[i] = wBuf[wBCnt++].alloc(-1, tmp, NULL, NULL);
	}

	for (int j = 0; j < MAX_CNT_ADD; j++) nameCnt[j] = 0;
}

int getSearch(char str[]) {
	int hash = getHash(str);

	for (word* p = origin[hash]->next; p; p = p->next) {
		if (!mstrcmp(str, p->name)) {
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

int astericCheck(char * front, char *back, char * str, int len) {
	int rst = 0;

	for (int i = 0; i < len; i++) {
		if (str[i] == '*') {
			for (int j = 0; j < i; j++) {
				front[j] = str[j];
			}
			int c = 0;
			for (int j = i+1; str[j] && j < len; j++, c++) {
				back[c] = str[j];
			}
			return (rst = 1);
		}
	}
	return rst;
}

// 같은 단어 여러 번 나올 수 있음
void addWord(char str[])
{
	if (!mstrcmp("lpp", str)) {
		int a = 1;
	}
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
			nStk[idx].addr[nStk[idx].addrCnt++]=wBuf[wBCnt++].alloc(idx, tmpStr, front[hash], front[hash]->next);
		}
		//back Add
		for (int i = 0; i < len; i++) {
			char tmpStr[MAX_LEN_NAME + 1] = { 0, };
			for (int j = 0; j <= i; j++) {
				tmpStr[j] = str[len-1-i+j];
			}
			int hash = getHash(tmpStr);
			nStk[idx].addr[nStk[idx].addrCnt++]=wBuf[wBCnt++].alloc(idx, tmpStr, back[hash], back[hash]->next);
		}
		//origin Add
		int hash = getHash(str);
		nStk[idx].addr[nStk[idx].addrCnt++]=wBuf[wBCnt++].alloc(idx, str, origin[hash], origin[hash]->next);
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
	searchRemoveCnt++;

	int len = mstrlen(str);
	// '*'가 있다면
	if (astericCheck(frontStr, backStr, str, len)) {
		if (frontStr[0]) {
			int fHash = getHash(frontStr);
			for (word* p = front[fHash]->next; p; p = p->next) {
				if (!mstrcmp(p->name, frontStr)) {
					nameCnt[p->idx] = searchRemoveCnt*2;
				}
			}
		}

		if (backStr[0]) {
			int fHash = getHash(backStr);
			for (word* p = back[fHash]->next; p; p = p->next) {
				if (!mstrcmp(p->name, backStr)) {
					if (nameCnt[p->idx] == searchRemoveCnt * 2) nameCnt[p->idx] = (searchRemoveCnt * 2 + 1);
					else nameCnt[p->idx] = searchRemoveCnt * 2;
				}
			}
		}

		if (frontStr[0] && backStr[0]) {
			for (int i = 0; i < nSCnt; i++) {
				if (nameCnt[i] == (searchRemoveCnt * 2 + 1)&& mstrlen(nStk[i].name) >= (mstrlen(frontStr) + mstrlen(backStr))) {
					rstCnt += nStk[i].cnt;
					nStk[i].cnt = 0;
					for (int j = 0; j < nStk[i].addrCnt; j++) {
						nStk[i].addr[j]->pop();
					}
					nStk[i].addrCnt = 0;
				}
			}
		}
		else if(frontStr[0] || backStr[0]){
			// front or back 만 있을 경우
			for (int i = 0; i < nSCnt; i++) {
				if (nameCnt[i] == (searchRemoveCnt * 2)) {
					rstCnt += nStk[i].cnt;
					nStk[i].cnt = 0;
					for (int j = 0; j < nStk[i].addrCnt; j++) {
						nStk[i].addr[j]->pop();
					}
					nStk[i].addrCnt = 0;
				}
			}
		}
		// '*' 일때 = frontStr, backStr 모두 null
		else {
			for (int i = 0; i < nSCnt; i++) {
				rstCnt += nStk[i].cnt;
				nStk[i].cnt = 0;
				for (int j = 0; j < nStk[i].addrCnt; j++) {
					nStk[i].addr[j]->pop();
				}
				nStk[i].addrCnt = 0;
			}
		}
	}
	else {
		int hash = getHash(str);
		for (word* p = origin[hash]->next; p; p = p->next) {
			if (!mstrcmp(p->name, str)) {
				rstCnt = nStk[p->idx].cnt;
				nStk[p->idx].cnt = 0;
				for (int i = 0; i < nStk[p->idx].addrCnt; i++) {
					nStk[p->idx].addr[i]->pop();
				}
				//아니 왜 이거 때문에 오류가 나지? 
				nStk[p->idx].addrCnt = 0;
			}
		}
	}
	return rstCnt;
}

int searchWord(char str[])
{
	int rstCnt = 0;
	
	char frontStr[MAX_LEN_NAME + 1] = { 0, };
	char backStr[MAX_LEN_NAME + 1] = { 0, };
	
	searchRemoveCnt++;
	int len = mstrlen(str);
	// '*'가 있다면
	if (astericCheck(frontStr, backStr, str, len)) {
		if (frontStr[0]) {
			int fHash = getHash(frontStr);
			for (word* p = front[fHash]->next; p; p = p->next) {
				if (!mstrcmp(p->name, frontStr)) {
					nameCnt[p->idx] = searchRemoveCnt * 2;
				}
			}
		}
		
		if (backStr[0]) {
			int fHash = getHash(backStr);
			for (word* p = back[fHash]->next; p; p = p->next) {
				if (!mstrcmp(p->name, backStr)) {
					if (nameCnt[p->idx] == searchRemoveCnt * 2) nameCnt[p->idx] = (searchRemoveCnt * 2 + 1);
					else nameCnt[p->idx] = searchRemoveCnt * 2;
				}
			}
		}

		if (frontStr[0] && backStr[0]) {
			for (int i = 0; i < nSCnt; i++) {
				if (nameCnt[i] == (searchRemoveCnt * 2 + 1) && mstrlen(nStk[i].name) >= (mstrlen(frontStr)+mstrlen(backStr))) {
					rstCnt += nStk[i].cnt;
				}
			}
		}
		
		else if (frontStr[0] || backStr[0]) {
			// front만 있을 경우
			for (int i = 0; i < nSCnt; i++) {
				if (nameCnt[i] == (searchRemoveCnt * 2)) {
					rstCnt += nStk[i].cnt;
				}
			}
		}
		// '*' 일때 = frontStr, backStr 모두 null
		else {
			for (int i = 0; i < nSCnt; i++) {
				rstCnt += nStk[i].cnt;
			}
		}
	}
	else {
		int hash = getHash(str);
		for (word* p = origin[hash]->next; p; p = p->next) {
			if (!mstrcmp(p->name, str)) {
				rstCnt = nStk[p->idx].cnt;
			}
		}
	}
	return rstCnt;
}
