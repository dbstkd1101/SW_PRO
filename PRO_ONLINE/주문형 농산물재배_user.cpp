#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef NULL
#define NULL 0
#endif

#define MAX_REQ 10000

struct pos {
	int row, col;
};

struct emptyNode {
	pos posHead;
	int size;
	emptyNode * prev, * next;
	emptyNode * alloc(pos _posHead, int _size, emptyNode * _prev, emptyNode * _next) {
		posHead = _posHead, size = _size, prev=_prev, next = _next;
		prev->next = this;
		if(prev) next->prev = this;
		return this;
	}
	emptyNode * pop() {
		if (prev) prev->next = next;
		if (next) next->prev = prev;
		return this;
	}
}emptyBuf[MAX_REQ];

struct realNode {
	pos posHead;
	int size;
	realNode * next;
	realNode * alloc(pos _posHead, int _size, realNode * _next) {
		posHead = _posHead, size = _size, next = _next;
		return this;
	}
}realBuf[MAX_REQ], *memberArr[10000];

emptyNode * emptyBufHead;
int emptyBufCnt;
int realBufCnt;

int lotCnt;

extern int add_lot();
extern void assign(int lot_num, int s, int size, int member_id);
extern void back(int lot_num, int s, int size);
extern void grow(int lot_num, int s, int size, int crop);

void init_member()
{
	emptyBufCnt = lotCnt = realBufCnt = 0;
	emptyBufHead = NULL;
	for (int i = 0; i < 10000; i++) {
		memberArr[i] = NULL;
	}
}

void assign_member(int member_id, int size)
{
	int popedSizeSum=0;
	
	while(emptyBufCnt > 0 && popedSizeSum < size){
		emptyNode * temp = emptyBufHead->pop();
		if (size < (popedSizeSum + temp->size)) {
			int diff = popedSizeSum + temp->size - size;
			emptyBuf[emptyBufCnt++].alloc({ temp->posHead.row, temp->posHead.col + temp->size - diff }, diff, temp->prev, temp->next);
			popedSizeSum += temp->size - diff;
			assign(lotCnt, temp->posHead.col, temp->size - diff, member_id);
			memberArr[member_id] = realBuf[realBufCnt++].alloc(temp->posHead, temp->size-diff, memberArr[member_id]);
		}
		else {
			popedSizeSum += temp->size;
			assign(lotCnt, temp->posHead.col, temp->size, member_id);
			memberArr[member_id] = realBuf[realBufCnt++].alloc(temp->posHead, temp->size, memberArr[member_id]);
		}
	}

	if(emptyBufCnt < 0 && popedSizeSum < size ) {
		add_lot(); lotCnt++;
		//���� ���� �� �κ��� ��� emptyNode�� �߰�
		assign(lotCnt, 0, size-popedSizeSum, member_id);
		memberArr[member_id] = realBuf[realBufCnt++].alloc({lotCnt, 0}, size - popedSizeSum, memberArr[member_id]);
		popedSizeSum += (size - popedSizeSum);
	}
}

void back_member(int member_id)
{
	for (realNode * p = memberArr[member_id]; p; p = p->next) {
		back(p->posHead.row, p->posHead.col, p->size);
		//��.. �̰� �� �Ҿ��ϳ�
		emptyBuf[emptyBufCnt].alloc(p->posHead, p->size, &emptyBuf[emptyBufCnt], NULL);
		emptyBufCnt++;
	}
	memberArr[member_id] = NULL;
}

void grow_member(int member_id, int crop)
{
	for (realNode * p = memberArr[member_id]; p; p = p->next) {
		grow(p->posHead.row, p->posHead.col, p->size, crop);
	}
}