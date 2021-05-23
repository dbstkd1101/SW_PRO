#include <stdio.h>

#define MAX_LEN_INPUT 1000001


typedef struct node {
	char data;
	node * next;
}NODE;

NODE input_str[MAX_LEN_INPUT];

int bufCnt;
int headIdx;
int tailIdx;
int curIdx;


NODE* mAlloc(char inputChar) {
	input_str[bufCnt]

}


int empty() {

	int rst = -1;
	if (info->head == NULL) {
		rst = 1;
	}
	else {
		rst = 0;
	}

	return rst;
}

int size(INFO * info) {
	return info->cnt;
}

NODE * begin(INFO * info) {
	return info->head;
}

NODE * end(INFO * info) {
	return info->tail;
}

void insert(NODE data) {
	if (info->cur != NULL) {
		NODE temp = *(info->cur);
		*(info->cur) = data;
		*(info->cur->next) = temp;
		info->cnt++;
		if (info->cur == info->tail) {
			info->tail = info->cur->next;
		}
		info->cur = info->cur->next;
	}
	else {
		info->tail=info->cur=info->head = &data;
		info->cnt++;
	}
}

void erase() {

}

void decode(char * input) {


	printf("hello world!\n");
}

void init() {
	info->cnt = 0;
	info->cur = NULL;
	info->head = NULL;
	info->tail = NULL;

	input_str[0] = { 0, };
}

int main() {
	
	int N;

	freopen("input.txt", "r", stdin);
	setbuf(stdout, NULL);
	scanf("%d\n", &N);

	for (int i = 0; i < N; i++) {
		init();
		scanf("%s", input_str);
		decode(input_str);



	}



	return 0;
}