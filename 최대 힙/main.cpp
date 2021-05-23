#include <stdio.h>
#define MAX_INPUT 1000000

int N;
int input[MAX_INPUT+10];
int rear = 0;

void ascending(int idx) {
	
	//end point
	if (idx == 1) {
		return;
	}
	if (input[idx] > input[idx / 2]) {
		int temp = input[idx / 2];
		input[idx / 2] = input[idx];
		input[idx] = temp;
		ascending(idx / 2);
	}
	else {
		return;
	}
}

void descending(int idx) {
	//end point
	if (idx*2 > rear) {
		return;
	}
	
	// 왼쪽 자식보다 작을 때
	if (input[idx] < input[idx * 2]) {
		// 오른쪽 자식이 제일 큼
		if (input[idx * 2] < input[idx * 2 + 1]) {
			int temp = input[idx * 2 + 1];
			input[idx * 2 + 1] = input[idx];
			input[idx] = temp;
			descending(idx * 2+1);
		}
		// 왼쪽 자식이 제일 큼
		else {
			int temp = input[idx * 2];
			input[idx * 2] = input[idx];
			input[idx] = temp;
			descending(idx * 2);
		}
	}
	// 왼쪽자식보다 작지 않으면서, 오른쪽 자식보다 작을 때
	else if(input[idx] < input[idx * 2+1]){
		int temp = input[idx * 2 + 1];
		input[idx * 2 + 1] = input[idx];
		input[idx] = temp;
		descending(idx * 2 + 1);
	}
	else {
		return;
	}
}


int MaxHeap(int command) {

	int rst = -1;

	if (command == 0) {
		if (rear == 0) {
			return 0;
		}
		rst = input[1];
		input[1] = input[rear];
		rear--;
		descending(1);
	}
	else {
		input[++rear] = command;
		ascending(rear);
	}

	return rst;
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &N);

	int command;
	int inputCnt = 0;
	for (int i = 1; i <= N; i++) {
		scanf("%d", &command);
		if (command == 0) {
			printf("%d\n", MaxHeap(command));
		}
		else {
			MaxHeap(command);
		}
	}
	return 0;
}