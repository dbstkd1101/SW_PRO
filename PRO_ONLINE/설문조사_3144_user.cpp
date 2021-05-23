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
int bcnt, ccnt, qcnt;// 버퍼, 해시, 질의
int qchk[MAX_CNT_STD + 10], blind[MAX_CNT_CELE + 10];

struct sNode {
	int sId;
	sNode *prev, *next;
	sNode* mAlloc(int _sId, sNode* _prev, sNode* _next) {
		sId = _sId, prev = _prev, next = _next;
		// dummy Node를 초기화 (initUser())하는 것까지 감안해서, if(prev) 조건 추가
		if (prev) prev->next = this;
		if (next) next->prev = this;
		return this;
	}
	void pop() {
		// 앞에 dummy node가 반드시 존재하므로, prev는 생략 가능
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
	// 이게 나랑 생각이 다르네. Stack을 별도 구축 ← hash에 동일 cID node가 중복 들어갈 일이 없겟네
	int  cId;
	char name[MAX_LEN_CELEB_NAME+1];
	cNODE* next;
	cNODE* mAlloc(int _cId, char _name[], cNODE* _next) {
		cId = _cId, strcpy(name, _name), next = _next;
		return this;
	}
}*cBucket[SIZE+10], cBuf[MAX_CNT_CELE+10];
// *hash , hbuf
// 골고루 잘 분산만 되면 돼. 심지어 겹쳐도 괜찮아.
int getHash(char * s) {
	int sum = 5381;
	for (char c = *s; c;  c = *s++) {
		sum = ((sum << 5) + sum + c) % SIZE;
	}
	return sum;
}

// celeb stack ID 단번에 찾기, 없으면 push
int search(char * name) {
	int hash = getHash(name);
	for (cNODE * p = cBucket[hash]; p; p = p->next) {
		if (strcmp(p->name, name) == 0) return p->cId;
	}
	cBucket[hash] = cBuf[ccnt].mAlloc(ccnt, name, cBucket[hash]);
	return ccnt++;
}

// 새로운 설문조사 시작을 위한 초기화
void initUser()
{
	int i;
	bcnt = ccnt = 0;
	for (i = 0; i < MAX_CNT_STD; i++) stu[i].cnt = 0;
	for (i = 0; i < SIZE; i++) cBucket[i] = 0;
	for (i = 0; i < MAX_CNT_CELE; i++) {
		blind[i] = 0;
		// dummy node를 만들어준다? 
		sBucket[i] = sBuf[bcnt++].mAlloc(0, 0, 0);
	}
}

// 설문조사 결과를 저장
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

// 설문조사 결과 등록을 취소
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

// 특정 유명 인물을 선택한 학생들에 대한 모든 선호도 기록을 제외시키기
// 예를 들어 7번 학생이 A, B, C를 선호하는데 A인물을 blind한다면
// 7번 학생이 선호하는 B, C에 대한 기록도 제외된다.
void blindCelebID(char celebID[])
{
	blind[search(celebID)] = 1;
}

/// 특정 유명 인물에 대한 모든 선호도 기록이 제외되어 있다면 다시 복원
void recoverCelebID(char celebID[])
{
	blind[search(celebID)] = 0;
}

// 특정인물을 선호하는 학생수를 리턴한다.
// 단, blind 처리된 인물을 선정하지 않은 학생이 대상이 된다.
// mode == 0 : 단일 인물을 선호하는 학생 수
// mode == 1 : 두 인물 모두를 선호하는 학생 수
// mode == 2 : 둘 중 하나 이상을 선호하는 학생 수
int query(int mode, char celebID[][11])
{
	//query() 호출 때마다 qchk 초기화할 필요 없도록
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