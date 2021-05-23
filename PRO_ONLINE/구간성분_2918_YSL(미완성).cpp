#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define NULL 0
#define MAX_BUCKET_SIZE 15000
#define MAX_BUF_SIZE 15000

typedef unsigned long long ULL;

char sA[MAX_BUF_SIZE];
char sB[MAX_BUF_SIZE];

int lenSA;
int lenSB;

int sumA[MAX_BUF_SIZE];
int sumB[MAX_BUF_SIZE];

int strLen(const char* str) {
	int cnt = 0;
	while (*str) {
		cnt++;
		str += 1;
	}
	return cnt;
}

int minStr(const char* sA, const char* sB) {
	int rst = 0;
	if (strLen(&sA[1]) <= strLen(&sB[1])) {
		rst = -1;
	}
	else {
		rst = 1;
	}
	return rst;
}

int getHash(const int * sumArr, int startIdx, int len) {
	ULL sum = 5831;
	sum += (sumArr[startIdx + len - 1] - sumArr[startIdx - 1]) % MAX_BUCKET_SIZE;
	return sum % MAX_BUCKET_SIZE;
}

int bufCnt = 0;

struct node {
	int pos;
	node * next;
	node * mAlloc(int _pos, int hash) {
		buf[bufCnt].pos = _pos;
		buf[bufCnt].next = bucket[hash];
		return bucket[hash] = this;
	}
}*bucket[MAX_BUCKET_SIZE], buf[MAX_BUF_SIZE];

void addNode(const int * sumArr, int startIdx, int len) {
	ULL hash = getHash(sumArr, startIdx, len);
	bucket[hash] = buf[bufCnt++].mAlloc(startIdx, hash);
}

int isSame(const char* shortStr, int shortStrStartIdx, const char * longStr, int longStrStartIdx, int len) {
	int rst = 1;
	int alphaForShortStr[27] = { 0 };
	int alphaForLongStr[27] = { 0 };

	for (int i = 1; i <= len; i++) {
		alphaForShortStr[shortStr[shortStrStartIdx] - 96]++;
	}
	for (int i = 1; i <= len; i++) {
		if (--alphaForShortStr[longStr[longStrStartIdx] - 96] < 0) {
			return rst = 0;
		};
	}	
	return rst;
}
// 6634
int checkVal(const char* shortStr, int startIdx, const char* longStr, int len) {
	//sB, j-len+1 ,sA, len
	int rst = 0;
	int hash;
	if (minStr(sA, sB) == 1) {
		 hash= getHash(sumB, startIdx, len);
	}
	else {
		hash = getHash(sumA, startIdx, len);
	}
	

	for (node* p = bucket[hash]; p && p->pos; p = p->next) {
		if (isSame(shortStr, startIdx, longStr, p->pos, len)) {
			return rst = len;
		}
	}
	return rst;
}

void init() {
	for (int i = 0; i < MAX_BUCKET_SIZE; i++) {
		bucket[i] = NULL;
	}
	bufCnt = 0;
}

int main() {
	freopen("input.txt", "r", stdin);

	scanf("%s", &sA[1]);
	scanf("%s", &sB[1]);

	for (int i = 1; sA[i] != NULL; i++) {
		lenSA++;
		sumA[i] = sumA[i - 1] + (sA[i] - 96) * (sA[i] - 96);
	}

	for (int i = 1; sB[i] != NULL; i++) {
		lenSB++;
		sumB[i] = sumB[i - 1] + (sB[i] - 96) * (sB[i] - 96);
	}

	int answer = 0;
	if (minStr(sA, sB) == 1) {
		for (int i = lenSB; i > 0; i--) {
			if (answer) break;
			int len = i;
			init();

			for (int k = 1; k <= lenSA; k++) {
				if (k >= len) {
					addNode(sumA, k - len + 1, len);
				}
			}

			for (int j = 1; j <= lenSB; j++) {
				if (j >= len) {
					if (answer=checkVal(sB, j - len + 1, sA, len)) {
						break;
					}
				}
			}
		}
	}

	printf("%d\n", answer);

	return 0;
}