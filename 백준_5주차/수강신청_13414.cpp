#include <stdio.h>

#define MAX_BUF_SIZE 500000
#define MAX_BUCUKE_SIZE 1000000
#define MAX_LEN_STDNUM 8

#define NULL 0
typedef unsigned long long ULL;

int K, L;
int answerCnt;

typedef struct inputNode {
	char stdNum[MAX_LEN_STDNUM + 1];
	int inputOrder;
}INPUTNODE;

//24Byte
typedef struct node {
	char stdNum[MAX_LEN_STDNUM+1];
	int inputOrder;
	struct node* next;
}NODE;

NODE buf[MAX_BUF_SIZE]; int bufCnt;
NODE * bucket[MAX_BUCUKE_SIZE+10];
INPUTNODE input[MAX_BUCUKE_SIZE+10];

ULL getHashcode(char* stdNum) {
	ULL h = 5831;
	
	for (int i = 0; i < MAX_LEN_STDNUM; i++) {
		h = h * 10 + stdNum[i] - '0';
	}
	return h % MAX_BUCUKE_SIZE;
}

char* strcpy(char* dest, const char* origin) {
	int i = 0;
	while (origin[i] != '\0') {
		dest[i] = origin[i++];
	}
	// bug fix
	dest[i] = '\0';
	return dest;
}

int strcmp(const char* s1, const char* s2) {
	unsigned char c1, c2;

	while (1) {
		/* s1, s2 문자열에서 순서대로 한글자씩 가져옵니다. */
		c1 = *s1++;
		c2 = *s2++;
		/* 한글자씩 비교하고 다르면 -1 또는 1 리턴합니다. */
		if (c1 != c2)
			return c1 < c2 ? -1 : 1;
		if (!c1)
			break;
	}
	/* 루프를 빠져나오면 두 문자열이 같다는 의미이므로 0을 리턴합니다. */
	return 0;
}

NODE* mAlloc(char*  stdNum, int hashCode, int inputOrder) {
	strcpy(buf[bufCnt].stdNum, stdNum);
	buf[bufCnt].inputOrder = inputOrder;
	return &buf[bufCnt++];
}

void registerData(char* stdNum, int inputOrder) {
	int hashCode = getHashcode(stdNum);
	NODE* newNode=mAlloc(stdNum, hashCode, inputOrder);
	newNode->next = bucket[hashCode];
	bucket[hashCode] = newNode;
	
	INPUTNODE tmp;	strcpy(tmp.stdNum, stdNum);	tmp.inputOrder = inputOrder;
	input[inputOrder] = tmp;
}

int main() {	
	
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &K, &L);
	char stdNumTmp[MAX_LEN_STDNUM+1];
	for (int i = 1; i <= L; i++) {
		scanf("%s", stdNumTmp);
		registerData(stdNumTmp, i);
 	}

	for (int j = 1; j <= L && answerCnt<K; j++) {
		INPUTNODE tmpNode = input[j];
		int hashCode = getHashcode(tmpNode.stdNum);

		for (NODE* pos = bucket[hashCode]; pos ; pos = pos->next) {
			if (strcmp(pos->stdNum, tmpNode.stdNum) == 0) {
				// descending sorting
				if (pos->inputOrder != tmpNode.inputOrder) {
					break;;
				}
				else {
					printf("%s\n", tmpNode.stdNum);
					answerCnt++;
					break;
				}
			}
		}
	}

	return 0;
}
