#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
// cake, bunny, belt

#define MAX_MEM	100000
#define MAX_ID	100000
#define MAX_FREQ	20000

struct member {
	int id, freq;
	bool status;
}memArr[MAX_ID+1];

bool Max(member a, member b) { return (a.freq > b.freq) ? true : (a.freq == b.freq && a.id > b.id) ? true : false; }
bool Min(member  a, member b) { return (a.freq < b.freq) ? true : (a.freq == b.freq && a.id < b.id) ? true : false; }

void swap(int&a, int&b) {
	int t = a; a = b; b = t;
}

struct PriorityQueue {
	int heap[MAX_ID+1];
	int hn;
	bool(*comp)(member a, member b);
	void init(bool(*_comp)(member a, member b)) {
		hn = 0;
		comp = _comp;
	}
	int top() { return hn < 1 ? -1 : heap[1]; }
	int size() { return hn; }
	bool empty() { return hn == 0; }
	void push(int num) {
		// 1부터 시작
		heap[++hn] = num;
		// 자식이 더 낫다면(=비정상) swap
		for (int cur=hn; cur > 1 && comp(memArr[heap[cur]], memArr[heap[cur / 2]]); cur /= 2) {
			swap(heap[cur], heap[cur / 2]);
		}
	}

	int pop() {
		int p = 1, cur = 2, ret = heap[1];
		swap(heap[1], heap[hn--]);
		for (; cur <= hn; p=cur, cur *= 2) {
			// 최적의 비교 자식 선정
			if (cur < hn && comp(memArr[heap[cur + 1]], memArr[heap[cur]])) cur++;
			if (comp(memArr[heap[p]], memArr[heap[cur]])) break;
			else swap(heap[p], heap[cur]);
		}
		return ret;
	}
}maxpq, minpq;

int N, M, cmd;
int memCnt;
int memInputCnt;
int freqSum;
int main() {

	freopen("input.txt", "r", stdin);

	maxpq.init(Max);
	minpq.init(Min);

	scanf("%d %d", &N, &M);
	int id, freq;
	for (int i = 0; i < M; i++) {
		scanf("%d", &cmd);
		switch (cmd) {
		case 0:
			scanf("%d %d", &id, &freq);
			memArr[memInputCnt].id = id, memArr[memInputCnt].freq = freq, memArr[memInputCnt].status = true;
			maxpq.push(memInputCnt);
			minpq.push(memInputCnt);
			freqSum += freq;
			memInputCnt++;
			memCnt++;
			break;
		case 1:
			while (minpq.top()!=-1 && memArr[minpq.top()].status ==false) minpq.pop();
			if (minpq.top()!=-1) {
				int memIdx = minpq.pop();
				freqSum -= memArr[memIdx].freq;
				memCnt--;
				memArr[memIdx].status = false;
				printf("%d\n", memArr[memIdx].id);
			}
			break;
		case 2:
			while (maxpq.top() != -1 && memArr[maxpq.top()].status == false) maxpq.pop();
			if (maxpq.top() != -1) {
				int memIdx = maxpq.pop();
				freqSum -= memArr[memIdx].freq;
				memCnt--;
				memArr[memIdx].status = false;
				printf("%d\n", memArr[memIdx].id);
			}
			break;
		case 3:
			if (memCnt > 2) {
				while (minpq.top() != -1 && memArr[minpq.top()].status == false) minpq.pop();
				int memMinIdx = minpq.top();

				while (maxpq.top() != -1 && memArr[maxpq.top()].status == false) maxpq.pop();
				int memMaxIdx = maxpq.top();

				printf("%d\n", freqSum - memArr[memMinIdx].freq - memArr[memMaxIdx].freq);
			}
			else {
				printf("%d\n", 0);
			}
			break;
		}
	}

	return 0;
}