#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int strcmp(const int* s1, const int* s2, int k) {
	int rst = 1;
	// 순방향
	for (int i = 0; i < k; i++) {
		if (*(s1+i) != *(s2+i)) {
			rst = 0;
			break;
		}
	}

	// 역방향
	if (!rst) {
		int tmpRst = 1;
		for (int i = 0; i < k; i++) {
			if (*(s1+i) != *(s2+k-1-i)) {
				tmpRst = 0;
				break;
			}
		}
		if (tmpRst) {
			rst = 1;
		}
	}
	return rst;
}

#ifndef NULL
#define NULL 0
#endif 

#define MAX_PROG_CNT 100
#define MAX_K_LEN 1000
#define MAX_EXTRACT_NUM 8
#define MAX_DATA_NUM ((MAX_K_LEN)*(MAX_PROG_CNT))
#define MAX_BUCKET_NUM 15000000

int program[MAX_PROG_CNT + 1][MAX_K_LEN + 1];

typedef unsigned int UI;

typedef struct node {
	int progId;
	int progStartIdx;
	node * next;
}NODE;

NODE buf[MAX_DATA_NUM+10]; int bufN;
NODE * bucket[MAX_BUCKET_NUM];

UI getHash(int * arr, int k) {
	UI sum = 5831;
	for (int i = 0; i<k; i++) {
		// 너무 유일할 필요 없다.
		//sum = ((sum << 10) + arr[i])% MAX_BUCKET_NUM;
		sum += (arr[i] * arr[i]) % MAX_BUCKET_NUM;
	}
	return (sum%MAX_BUCKET_NUM);
}

NODE * mAlloc(int progId, int progStartIdx, int hash) {	
	buf[bufN].progId = progId;
	buf[bufN].progStartIdx= progStartIdx;
	buf[bufN].next = bucket[hash];
	return &buf[bufN++];
}

void addNode(int progId, int progStartIdx, int hash) {
	bucket[hash] = mAlloc(progId, progStartIdx, hash);
}

int findNode(int progId, int progStartIdx, int k, int hash) {
	int rst = 0;
	int sameCnt = 0;
	for (NODE* p = bucket[hash]; p != NULL; p = p->next) {
		if (strcmp(&program[progId][progStartIdx], &program[p->progId][p->progStartIdx], k)) {
			sameCnt++;
			if (sameCnt == (progId - 1)) {
				return rst = 1;
			}
		}
	}
	return rst;
}

int N, K;
int Mi;
int answer;
int main() {

	freopen("input.txt", "r", stdin);
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &Mi);
		answer = 0;
		for (int j = 1; j <= Mi; j++) {
			scanf("%d", &program[i][j]);
			if (i ==1 && j >= K ) {
				int hash = getHash(&program[i][j - K + 1], K);
				addNode(i, (j - K + 1), hash);
			}
			if (i != 1 && j >= K) {
				int hash = getHash(&program[i][j - K + 1], K);
				if (findNode(i, (j - K + 1), K, hash)) {
					addNode(i, (j - K + 1), hash);
					answer = 1;
				}
			}
		}
		if (i!=1 && !answer) {
			break;
		}
	}
	
	if (answer) {
		printf("%s\n", "YES");
	}
	else {
		printf("%s\n", "NO");
	}

	return 0;
}