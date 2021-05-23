#include <stdio.h>

#define MAX_ARR_LENGTH 100

#ifndef NULL
#define NULL 0
#endif

int N;

typedef struct node {
	int value;
}NODE;


NODE maxArr[MAX_ARR_LENGTH];
int maxCnt;

void maxPush(NODE node) {

	maxArr[++maxCnt] = node;

	int now = maxCnt;

	while (1) {
		int parent = now / 2;

		//exit
		if (now == 1) break;
		if (maxArr[parent].value >= maxArr[now].value) break;

		NODE temp = maxArr[parent];
		maxArr[parent] = maxArr[now];
		maxArr[now] = temp;

		now = parent;
	}
}

NODE maxPop() {
	NODE ret = maxArr[1];
	maxArr[1] = maxArr[maxCnt--];

	int now = 1;
	
	while (1) {
		int son = now * 2;
		if ((son + 1) <= maxCnt && maxArr[son + 1].value > maxArr[son].value)son++;

		if (son > maxCnt)break;
		if (maxArr[son].value < maxArr[now].value)break;
		
		NODE temp = maxArr[son];
		maxArr[son] = maxArr[now];
		maxArr[now] = temp;

		now = son;
	}
	
	return ret;
}


int main()
{
	maxCnt = 0;

	freopen("input.txt", "r", stdin);

	scanf("%d", &N);
	
	for (int i = 0; i < N; i++) {
		int input_value;
		scanf("%d", &input_value);
		NODE input = { input_value };
		maxPush(input);
	}

	for (int i = 1; i <= maxCnt; i++) {
		printf("%d ", maxArr[i]);
	}
	puts("");
	for (int i = 1; i <= 6; i++) {
		printf("%d ", maxPop());
	}


    return 0;
}