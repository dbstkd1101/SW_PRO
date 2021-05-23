#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#ifndef NULL
#define NULL 0
#endif 

#define MAX_DATA_NUM (1000010)
#define MAX_BUCKET_NUM 29000000

int T, N, M;

typedef unsigned int UI;

typedef struct node {
	int num;
	node * next;
}NODE;

NODE buf[MAX_DATA_NUM];
int bufN;

NODE * bucket[MAX_BUCKET_NUM];

int getHashCode(int num) {
	UI sum = 5831;
	return ((num + sum)%MAX_BUCKET_NUM);
}

NODE * mAlloc(int num, int hash_code) {
	buf[bufN].num = num;
	buf[bufN].next = bucket[hash_code];
	return &buf[bufN++];
}

void addNode(int num, int hash_code) {
	bucket[hash_code] = mAlloc(num, hash_code);
}

void registerData(int num) {	
	int hashCode = getHashCode(num);
	addNode(num, hashCode);
}

int findNum(int num) {
	int rst = 0;

	int hash_code = getHashCode(num);

	for (NODE * pos = bucket[hash_code]; pos != NULL; pos = pos->next) {
		if ((pos->num) == num) {
			rst = 1;
			break;
		}
	}

	return rst;
}

void initBucket() {
	for (int i = 0; i < MAX_BUCKET_NUM; i++) {
		bucket[i] = NULL;
	}
}

int main() {
	freopen("input.txt", "r", stdin);

	scanf("%d\n", &T);
	for (int t = 0; t < T; t++) {
		if (t != 0) {
			initBucket();
			bufN = 0;
		}
		scanf("%d\n", &N);
		int numTmp;
		for (int i = 1; i <= N; i++) {
			scanf("%d", &numTmp);
			registerData(numTmp);
		}
		scanf("%d\n", &M);
		int numQnATmp;
		for (int j = 1; j <= M; j++) {
			scanf("%d", &numQnATmp);
			if (findNum(numQnATmp)) {
				printf("%d\n", 1);
			}
			else {
				printf("%d\n", 0);
			}
		}
	}
	
	return 0;
}