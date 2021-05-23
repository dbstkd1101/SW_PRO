#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_CNT_N 100 // 2<=N<=100
#define MAX_LEN_K 1000 // 4<=K<=1000
#define MAX_LEN_MI 1000 // 4<=Mi<=1000
#define NULL 0

const int SIZE = 1 << 10; //1024
const int MOD = SIZE - 1; //1023

int N, K;
int M;

int virusExist;

struct node{
	int pos;
	int same_cnt;
	node * next;
}*bucket[SIZE], buf[MAX_LEN_MI + 10];

int bufCnt;

int sum[MAX_LEN_MI + 10];
int sum2[MAX_LEN_MI + 10];
int firstArr[MAX_LEN_MI + 10];
int otherArr[MAX_LEN_MI + 10];

int getHash(int idx) {
	return (sum[idx] - sum[idx - K]+100000000)&MOD;
}

int getHash2(int idx) {
	return (sum2[idx] - sum2[idx - K] + 100000000)&MOD;
}

struct node* mAlloc(int pos, int hashKey) {
	bufCnt++;
	buf[bufCnt].pos = pos; buf[bufCnt].same_cnt = 1;
	buf[bufCnt].next= bucket[hashKey];
	return (bucket[hashKey] = &buf[bufCnt]);
}

int compare(int oIdx, int dIdx) {
	int same = 0;
	
	int cnt=1;
	// goAhead
	for (int i = oIdx-K+1, j = dIdx-K+1; cnt<=K; i++, j++, cnt++) {
		if (firstArr[i] != otherArr[j]) {
			break;
		}
	}
	if (cnt == (K + 1)) {
		return (same = 1);
	}

	cnt = 1;
	// contrary
	for (int i = oIdx - K + 1, j = dIdx; cnt <= K; i++, j--, cnt++) {
		if (firstArr[i] != otherArr[j]) {
			break;
		}
	}

	if (cnt == (K + 1)) {
		return (same = 1);
	}

	return same;
}

int check(int idx, int N) {
	int exist = 0;
	int hashKey = getHash2(idx);
	struct node* p = bucket[hashKey];
	for (; p && (p->same_cnt==N-1); p = p->next) {
		if (compare(p->pos, idx)) {
			exist = 1;
			p->same_cnt = N;
		}
	}

	return exist;
}

int main() {

	freopen("input.txt", "r", stdin);
	scanf("%d %d", &N, &K);
	scanf("%d", &M);
	
	for (int i = 1; i<=M ; i++) {
		scanf("%d", &firstArr[i]);
		sum[i] = sum[i - 1] + firstArr[i] * firstArr[i];
		if (i >= K) {
			if (i == 8) {
				int deg = 1;
			}
			mAlloc(i, getHash(i));
		}
	}

	for (int i = 2; i <= N; i++) {
		scanf("%d", &M);
		for (int j = 1; j <= M; j++) {
			scanf("%d", &otherArr[j]);
			sum2[j] = sum2[j - 1] + (otherArr[j] * otherArr[j]);
			if (j >= K) {
				if (check(j, i)) {
					virusExist = 1;
				}
			}
		}
		if (!virusExist) {
			puts("NO");
			break;
		}		
	}

	if (virusExist) {
		puts("YES");
	}

	return 0;
}