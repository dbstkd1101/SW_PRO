#include <stdio.h>

#define MAX_LEN_N 500000

// �߰����� ������ �ʿ�
int sorted[MAX_LEN_N+10];

int arr[MAX_LEN_N + 10];

int N;
long long swapCnt;

// i: ���ĵ� ���� ����Ʈ�� ���� �ε���
// j: ���ĵ� ������ ����Ʈ�� ���� �ε���
// k: ���ĵ� ����Ʈ�� ���� �ε���
/* 2���� ������ �迭 list[left...mid]�� list[mid+1...right]�� �պ� ���� */
/* (������ ���ڵ��� ���ĵǴ� ����) */
void merge(int list[], int left, int mid, int right) {
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;

	/* ���� ���ĵ� list�� �պ� */
	while (i <= mid && j <= right) {
		if (list[i] <= list[j])
			sorted[k++] = list[i++];
		else {
			swapCnt += (mid - i + 1) * 1LL;
			sorted[k++] = list[j++];
		}
	}

	// ���� �ִ� ������ �ϰ� ����
	if (i>mid) {
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	}
	// ���� �ִ� ������ �ϰ� ����
	else {
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];
	}

	// �迭 sorted[](�ӽ� �迭)�� ����Ʈ�� �迭 list[]�� �纹��
	for (l = left; l <= right; l++) {
		list[l] = sorted[l];
	}
}

// �պ� ����
void merge_sort(int list[], int left, int right) {
	int mid;

	if (left<right) {
		mid = (left + right) / 2; // �߰� ��ġ�� ����Ͽ� ����Ʈ�� �յ� ���� -����(Divide)
		merge_sort(list, left, mid); // ���� �κ� ����Ʈ ���� -����(Conquer)
		merge_sort(list, mid + 1, right); // ���� �κ� ����Ʈ ���� -����(Conquer)
		merge(list, left, mid, right); // ���ĵ� 2���� �κ� �迭�� �պ��ϴ� ���� -����(Combine)
	}
}


void swap(int *a, int *b) {
	int	temp = *b;
	*b = *a;
	*a = temp;
	
	return ;
}

int main() {

	freopen("input.txt", "r", stdin);

	scanf("%d", &N);
	
	for (int i = 1; i <= N; i++) {
		scanf("%d", &arr[i]);
	}
	
	merge_sort(arr, 1, N);
	printf("%lld\n", swapCnt);


	return 0;
}