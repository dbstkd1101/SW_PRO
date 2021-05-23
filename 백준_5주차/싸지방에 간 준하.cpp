#include <stdio.h>

//  1<= N <= 100000
//  0<= P, Q <=1000000

int N;
#define MAX_LEN_N 100010

typedef struct node {
	int P, Q;
	int comIdx;
}NODE;

NODE input[MAX_LEN_N];
NODE sorted[MAX_LEN_N];

int com[MAX_LEN_N];

NODE heap_Q[MAX_LEN_N];
int rear = 0;

int answer;

void merge(NODE list[], int left, int mid, int right) {
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;

	/* ���� ���ĵ� list�� �պ� */
	while (i <= mid && j <= right) {
		if (list[i].P <= list[j].P) {
			sorted[k++] = list[i++];
		}
		else {
			sorted[k++] = list[j++];
		}
	}

	// ���� �ִ� ������ �ϰ� ����
	if (i>mid) {
		for (l = j; l <= right; l++) {
			sorted[k++] = list[l];
		}
	}// ���� �ִ� ������ �ϰ� ����
	else {
		for (l = i; l <= mid; l++) {
			sorted[k++] = list[l];	
		}
	}

	// �迭 sorted[](�ӽ� �迭)�� ����Ʈ�� �迭 list[]�� �纹��
	for (l = left; l <= right; l++) {
		list[l] = sorted[l];
	}
}

// �պ� ����
void merge_sort(NODE list[], int left, int right) {
	int mid;

	if (left<right) {
		mid = (left + right) / 2; // �߰� ��ġ�� ����Ͽ� ����Ʈ�� �յ� ���� -����(Divide)
		merge_sort(list, left, mid); // ���� �κ� ����Ʈ ���� -����(Conquer)
		merge_sort(list, mid + 1, right); // ���� �κ� ����Ʈ ���� -����(Conquer)
		merge(list, left, mid, right); // ���ĵ� 2���� �κ� �迭�� �պ��ϴ� ���� -����(Combine)
	}
}

void ascending(int idx) {

	//end point
	if (idx == 1) {
		return;
	}
	if (heap_Q[idx].Q < heap_Q[idx / 2].Q) {
		NODE temp = heap_Q[idx / 2];
		heap_Q[idx / 2] = heap_Q[idx];
		heap_Q[idx] = temp;
		ascending(idx / 2);
	}
	else {
		return;
	}
}

void descending(int idx) {
	//end point
	if (idx * 2 > rear) {
		return;
	}

	if (heap_Q[idx].Q > heap_Q[idx * 2].Q) {
		if (heap_Q[idx * 2].Q > heap_Q[idx * 2 + 1].Q) {
			NODE temp = heap_Q[idx * 2 + 1];
			heap_Q[idx * 2 + 1] = heap_Q[idx];
			heap_Q[idx] = temp;
			descending(idx * 2 + 1);
		}	
		else {
			NODE temp = heap_Q[idx * 2];
			heap_Q[idx * 2] = heap_Q[idx];
			heap_Q[idx] = temp;
			descending(idx * 2);
		}
	}
	else if (heap_Q[idx].Q > heap_Q[idx * 2 + 1].Q) {
		NODE temp = heap_Q[idx * 2 + 1];
		heap_Q[idx * 2 + 1] = heap_Q[idx];
		heap_Q[idx] = temp;
		descending(idx * 2 + 1);
	}
	else {

		return;
	}
}

// �Ű����� number : -1 �̸� pop
NODE minHeap(NODE number, int command) {
	NODE rst = { -1, -1, -1 };

	// pop
	if (command == -1) {
		if (rear == 0) {
			return rst;
		}
		rst = heap_Q[1];
		heap_Q[1] = heap_Q[rear--];
		descending(1);
	}
	// top
	else if (command == -2) {
		if (rear == 0) {
			return rst;
		}
		rst = heap_Q[1];
	}
	// push
	else {
		heap_Q[++rear] = number;
		ascending(rear);
	}

	return rst;
}

int existAleadyEndCom(NODE number) {
	int rst = 0;
	NODE topRst = minHeap(number , -2);

	// �̹� ���� Com�� ���� ��
	if (topRst.Q != -1 && topRst.Q <= number.P) {
		rst = 1;
	}
	
	return rst;
}

void minComputer() {

	for (int i = 1; i <= N; i++) {
		// �̹� ���� Com�� ����.
		if (!existAleadyEndCom(input[i])){
			input[i].comIdx = (++answer);
			// minHeap�� �ش� Q�ð� Push
			minHeap(input[i], 3);
			com[answer]++;
		}

		// �̹� ���� Com�� �����Ѵ�.
		else if (existAleadyEndCom(input[i])) {
			NODE pop=minHeap(input[i], -1);
			input[i].comIdx = pop.comIdx;
			minHeap(input[i], 3);
			com[pop.comIdx]++;
		}
		else {

		}
	}

	return ;
}

int main() {
	freopen("input.txt", "r", stdin);

	scanf("%d", &N);
	int P, Q;
	for (int i = 1; i <= N; i++) {
		scanf("%d %d", &P, &Q);
		input[i].P = P; input[i].Q = Q;
	}

	merge_sort(input, 1, N);

	minComputer();

	printf("%d\n", answer);
	for (int i = 1; i <= answer; i++) {
		printf("%d ", com[i]);
	}

	return 0;
}