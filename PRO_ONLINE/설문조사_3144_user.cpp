#ifndef NULL
#define NULL 0
#endif

#define MAX_CNT_STD 50000
#define MAX_CNT_CELE 10000
#define MAX_BUCKET_SIZE 100000
#define MAX_LEN_CELEB_NAME 10

void strcpy(char*dest, char*src) {
	while ((*dest++ = *src++));
}

int strcmp(char*s, char*t) {
	while (*s && *s == *t) ++s, ++t;
	return *s - *t;
}

const int SIZE = 1 << 12;
int bcnt, ccnt, qcnt;// ����, �ؽ�, ����
int qchk[MAX_CNT_STD + 10], blind[MAX_CNT_CELE + 10];

struct sNode {
	int sId;
	sNode *prev, *next;
	sNode* mAlloc(int _sId, sNode* _prev, sNode* _next) {
		sId = _sId, prev = _prev, next = _next;
		// dummy Node�� �ʱ�ȭ (initUser())�ϴ� �ͱ��� �����ؼ�, if(prev) ���� �߰�
		if (prev) prev->next = this;
		if (next) next->prev = this;
		return this;
	}
	void pop() {
		// �տ� dummy node�� �ݵ�� �����ϹǷ�, prev�� ���� ����
		prev->next = next;
		if (next) next->prev = prev;
	}
} sBuf[MAX_CNT_STD*4+ MAX_CNT_CELE*2], *sBucket[MAX_CNT_CELE+10];
//buf

struct STU {
	int cnt, celeb[4];
	sNode * adr[4];
}stu[MAX_CNT_STD+10];

struct cNODE {
	// �̰� ���� ������ �ٸ���. Stack�� ���� ���� �� hash�� ���� cID node�� �ߺ� �� ���� ���ٳ�
	int  cId;
	char name[MAX_LEN_CELEB_NAME+1];
	cNODE* next;
	cNODE* mAlloc(int _cId, char _name[], cNODE* _next) {
		cId = _cId, strcpy(name, _name), next = _next;
		return this;
	}
}*cBucket[SIZE+10], cBuf[MAX_CNT_CELE+10];
// *hash , hbuf
// ���� �� �л길 �Ǹ� ��. ������ ���ĵ� ������.
int getHash(char * s) {
	int sum = 5381;
	for (char c = *s; c;  c = *s++) {
		sum = ((sum << 5) + sum + c) % SIZE;
	}
	return sum;
}

// celeb stack ID �ܹ��� ã��, ������ push
int search(char * name) {
	int hash = getHash(name);
	for (cNODE * p = cBucket[hash]; p; p = p->next) {
		if (strcmp(p->name, name) == 0) return p->cId;
	}
	cBucket[hash] = cBuf[ccnt].mAlloc(ccnt, name, cBucket[hash]);
	return ccnt++;
}

// ���ο� �������� ������ ���� �ʱ�ȭ
void initUser()
{
	int i;
	bcnt = ccnt = 0;
	for (i = 0; i < MAX_CNT_STD; i++) stu[i].cnt = 0;
	for (i = 0; i < SIZE; i++) cBucket[i] = 0;
	for (i = 0; i < MAX_CNT_CELE; i++) {
		blind[i] = 0;
		// dummy node�� ������ش�? 
		sBucket[i] = sBuf[bcnt++].mAlloc(0, 0, 0);
	}
}

// �������� ����� ����
void addSurveyResult(int stdID, int cnt, char celebID[][11])
{
	stu[stdID].cnt = cnt;
	for (int i = 0; i < cnt; i++) {
		int cid = search(celebID[i]);
		stu[stdID].celeb[i] = cid;
		stu[stdID].adr[i] = sBuf[bcnt].mAlloc(stdID, sBucket[cid], sBucket[cid]->next);
		bcnt++;
	}
}

// �������� ��� ����� ���
void cancelSurveyResult(int stdID)
{
	for (int i = 0; i < stu[stdID].cnt; i++) {
		stu[stdID].adr[i]->pop();
	}
	stu[stdID].cnt = 0;
}

int blind_chk(int sid) {
	for (int i = 0; i < stu[sid].cnt; i++) {
		if (blind[stu[sid].celeb[i]] == 1)return 1;
	 }
	return 0;
}

// Ư�� ���� �ι��� ������ �л��鿡 ���� ��� ��ȣ�� ����� ���ܽ�Ű��
// ���� ��� 7�� �л��� A, B, C�� ��ȣ�ϴµ� A�ι��� blind�Ѵٸ�
// 7�� �л��� ��ȣ�ϴ� B, C�� ���� ��ϵ� ���ܵȴ�.
void blindCelebID(char celebID[])
{
	blind[search(celebID)] = 1;
}

/// Ư�� ���� �ι��� ���� ��� ��ȣ�� ����� ���ܵǾ� �ִٸ� �ٽ� ����
void recoverCelebID(char celebID[])
{
	blind[search(celebID)] = 0;
}

// Ư���ι��� ��ȣ�ϴ� �л����� �����Ѵ�.
// ��, blind ó���� �ι��� �������� ���� �л��� ����� �ȴ�.
// mode == 0 : ���� �ι��� ��ȣ�ϴ� �л� ��
// mode == 1 : �� �ι� ��θ� ��ȣ�ϴ� �л� ��
// mode == 2 : �� �� �ϳ� �̻��� ��ȣ�ϴ� �л� ��
int query(int mode, char celebID[][11])
{
	//query() ȣ�� ������ qchk �ʱ�ȭ�� �ʿ� ������
	qcnt++;
	int cnt1 = 0, cnt2 = 0;
	int cId = search(celebID[0]);
	if (blind[cId] == 0) {
		for (sNode* p = sBucket[cId]->next; p; p = p->next) {
			if (blind_chk(p->sId)) continue;
			cnt1++;
			qchk[p->sId] = qcnt;
		}
	}
	if (mode == 0)return cnt1;

	cId = search(celebID[1]);
	if (blind[cId] == 0) {
		for (sNode* p = sBucket[cId]->next; p; p = p->next) {
			if (blind_chk(p->sId)) continue;
			cnt1++;
			if (qchk[p->sId] == qcnt) cnt2++;
		}
	}

	if (mode == 1) return cnt2;
	if (mode == 2) return cnt1 - cnt2;

	return 0;
}