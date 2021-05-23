#define _CRT_SECURE_NO_WARNINGS

#ifndef NULL
#define NULL  0

struct Member {
	int id, frequency;
};
#endif

/// === submit area start ===
#define MAX_MEMBER	50000
#define MAX_ID	100000
#define MAX_FREQ	100000

typedef int data;

bool active[MAX_ID];
int frr[MAX_ID];

bool Max(data a, data b) { return (frr[a] > frr[b]) ? true : (frr[a] == frr[b] && a > b) ? true : false; }
bool Min(data a, data b) { return (frr[a] < frr[b]) ? true : (frr[a] == frr[b] && a < b) ? true : false; }

void swap(data &a, data &b) {
	data t = a; a = b; b = t;
}

struct PriorityQueue {
	data heap[MAX_MEMBER + 5];
	int hn;
	bool(*comp) (data, data);
	void init(bool(*_comp)(data, data)) {
		hn = 0;
		comp = _comp;
	}
	data top() {
		while (hn > 1 && active[heap[1]] == false) pop();
		return hn > 0 ? heap[1] : -1;
	}
	int size() {
		return hn;
	}
	void push(data memId) {
		// 1부터 시작
		heap[++hn] = memId;
		for (int cur = hn; cur > 1 &&  comp(heap[cur], heap[cur/2]); cur /= 2) {
			swap(heap[cur], heap[cur / 2]);
		}
	}
	data pop() {
		if (hn < 1) return -1;
		
		data ret = heap[1];
		swap(heap[1], heap[hn--]);
		
		int p = 1, cur = 2;
		for (; cur <= hn; p = cur, cur *= 2) {
			// 최적의 자식(cur) 선택 (우자식이 가능하며, 우자식이 더 좋을 때)
			if(cur < hn && comp(heap[cur + 1], heap[cur])) cur++;
			if(comp(heap[p], heap[cur])) break;
			else swap(heap[p], heap[cur]);
		}
		return ret;
	}
}maxpq, minpq, front, back;

int fCnt, bCnt, fSum, bSum;

void addMember(Member obj) {
	frr[obj.id] = obj.frequency;
	active[obj.id] = true;
	maxpq.push(obj.id);
	minpq.push(obj.id);

	if (fCnt == 0) {
		front.push(obj.id);
		fCnt++; fSum += obj.frequency;
	}
	else {
		data fTopTmp = front.top();
		data bTopTmp = back.top();

		// back node가 없다면
		if (bTopTmp == -1) {
			if (Max(obj.id, fTopTmp)) {
				back.push(obj.id);
				bCnt++; bSum += obj.frequency;
			}
			else {
				front.push(obj.id);
				fCnt++; fSum += obj.frequency;
			}
		}
		else {
			//back.top보다 작을 경우
			if (Min(obj.id, bTopTmp)) {
				front.push(obj.id);
				fCnt++; fSum += obj.frequency;
			}
			// 클 경우
			else {
				back.push(obj.id);
				bCnt++; bSum += obj.frequency;
			}
		}
	}

	//rebalancing
	while (!(fCnt == bCnt || fCnt == bCnt + 1)) {
		if (fCnt > bCnt + 1) {
			data fTopTmp = front.pop();
			back.push(fTopTmp);
			fCnt--; fSum-= frr[fTopTmp];
			bCnt++; bSum+= frr[fTopTmp];
		}
		if (fCnt < bCnt) {
			data bTopTmp = back.pop();
			front.push(bTopTmp);
			bCnt--; bSum -= frr[bTopTmp];
			fCnt++; fSum += frr[bTopTmp];
		}
	}
}

int removeMembers(int mode) {
	int rst = 0;
	switch (mode) {
	case 0:
	{
		minpq.top();
		data minPopTmp = minpq.pop();
		active[minPopTmp] = false;
		rst = minPopTmp;
		fCnt--; fSum -= frr[minPopTmp];
	}
	break;
	case 1:
	{
		if ((fCnt + bCnt) % 2 == 0) {
			back.top();
			data backPopTmp = back.pop();
			active[backPopTmp] = false;
			bCnt--; bSum -= frr[backPopTmp];
			rst += backPopTmp;
		}
		front.top(); data frontPopTmp = front.pop();
		active[frontPopTmp] = false;
		fCnt--; fSum -= frr[frontPopTmp];
		rst += frontPopTmp;
	}
		break;
	case 2:
	{
		maxpq.top();
		data maxPopTmp = maxpq.pop();
		active[maxPopTmp] = false;
		rst = maxPopTmp;
		bCnt--; bSum -= frr[maxPopTmp];
	}
		break;
	}
	return rst;
}

void getSum(int sum[]) {
	sum[1] = bSum;
	if ((fCnt + bCnt) % 2 == 0) {
		sum[0] = fSum;
	}
	else {
		data frontPopTmp = front.top();
		sum[0] = (fSum - frr[frontPopTmp]);
	}
}

void userInit(int memberCount, Member members[]) {
	fCnt = bCnt = fSum = bSum = 0;
	maxpq.init(Max); front.init(Max);
	minpq.init(Min); back.init(Min);
	for (int i = 0; i < MAX_ID; i++) {
		frr[i] = false;
	}
	for (int i = 0; i < memberCount; i++) {
		addMember(members[i]);
	}
}



/// === submit area end ===