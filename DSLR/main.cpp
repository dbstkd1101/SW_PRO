#include <stdio.h>

#define MAX_QUEUE 25000
#define MAX_COMMAND_HIST 10000

int N;
int A, B;

typedef struct node {
	int v;
	char command[MAX_COMMAND_HIST];
}NODE;
 
NODE queue[MAX_QUEUE];


int valD(int input) {
	int rst = input * 2;
	if (rst > 9999) {
		return rst % 10000;
	}
	else {
		return rst;
	}
}

int valS(int input) {
	if (input == 0) {
		return 9999;
	}
	else {
		return input - 1;
	}
}

int valL(int input) {
	int mok = input / 1000;
	int temp = input % 1000 * 10;
	int rst = temp + mok;
	return rst;
}

int valR(int input) {
	int remain = input % 10;
	int temp = input / 10;
	int rst = temp + remain * 1000;
	return rst;
}

int DSLR(int A, int B) {

	int front = 0, rear = 0;

	// 1¹øÂ° enqueue
	NODE temp;
	temp.v = valD(A); temp.command[1] = 'D';
	queue[++rear] = temp;

	temp.v = valS(A); temp.command[1] = 'S';
	queue[++rear] = temp;

	temp.v = valL(A); temp.command[1] = 'L';
	queue[++rear] = temp;

	temp.v = valR(A); temp.command[1] = 'R';
	queue[++rear] = temp;
	
	int tier = 1;
	int tierCnt = rear;
	int tierCntIdx = 0;
	int nextTierCnt = 0;
	while (front < rear) {
		NODE temp = queue[++front];
		tierCntIdx++;

		if (temp.v == B) {
			for (int i = 1; i <= tier; i++) {
				printf("%c", temp.command[i]);
			}
			puts("");
			return tier;
		}
		else {
			NODE insertTmp;
			for (int i = 1; i <= tier; i++) {
				insertTmp.command[i] = temp.command[i];
			}
			insertTmp.v = valD(temp.v); insertTmp.command[tier + 1] = 'D';
			queue[++rear] = insertTmp; nextTierCnt++;
			insertTmp.v = valS(temp.v); insertTmp.command[tier + 1] = 'S';
			queue[++rear] = insertTmp; nextTierCnt++;
			insertTmp.v = valL(temp.v); insertTmp.command[tier + 1] = 'L';
			queue[++rear] = insertTmp; nextTierCnt++;
			insertTmp.v = valR(temp.v); insertTmp.command[tier + 1] = 'R';
			queue[++rear] = insertTmp; nextTierCnt++;
		}
		if (tierCntIdx == tierCnt) {
			tier++;
			tierCntIdx = 0;
			tierCnt = nextTierCnt;
			nextTierCnt = 0;
		}
	}

	return 0;
}

int main() {

	//freopen("input.txt", "r", stdin);

	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d %d", &A, &B);
		DSLR(A, B);
	}


	return 0;
}