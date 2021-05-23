#include <stdio.h>

# include <stdio.h>
# define MAX_N_SIZE 32010
# define MAX_M_SIZE 100010

int sorted[MAX_N_SIZE];
int inputOrigin[MAX_M_SIZE];
int inputComparand[3];

// �߰����� ������ �ʿ�

// i: ���ĵ� ���� ����Ʈ�� ���� �ε���s
// j: ���ĵ� ������ ����Ʈ�� ���� �ε���
// k: ���ĵ� ����Ʈ�� ���� �ε���
/* 2���� ������ �迭 list[left...mid]�� list[mid+1...right]�� �պ� ���� */
/* (������ ���ڵ��� ���ĵǴ� ����) */
void merge(int list[], int left, int mid, int right) {
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;

	int firstComparand = 0;
	int secondComparand = 0;

	for (int i = 1; i <= mid; i++) {
		if (list[i] == list[right - 1]) {
			firstComparand = 1;
		}
		if (list[i] == list[right]) {
			secondComparand = 1;
		}
	}

	/* ���� ���ĵ� list�� �պ� */
	while (i <= mid && j <= right) {
		if (list[i] < list[j]) {
			sorted[k++] = list[i++];
		}
		else if (list[i] == list[j]) {
			sorted[k++] = list[i++];
			j++;
		}
		else {
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
/*
void merge_sort(int list[], int left, int right) {
	int mid;

	if (left<right) {
		mid = (left + right) / 2; // �߰� ��ġ�� ����Ͽ� ����Ʈ�� �յ� ���� -����(Divide)
		merge_sort(list, left, mid); // ���� �κ� ����Ʈ ���� -����(Conquer)
		merge_sort(list, mid + 1, right); // ���� �κ� ����Ʈ ���� -����(Conquer)
		merge(list, left, mid, right); // ���ĵ� 2���� �κ� �迭�� �պ��ϴ� ���� -����(Combine)
	}
}
*/
int main() {
	int N, M;

	freopen("input.txt", "r", stdin);

	scanf("%d %d", &N, &M);

	int left = 1;
	int right = 2;
	int mid;
	for (int i = 1; i <= M; i++) {
		if (i == 1) {
			scanf("%d %d", &inputOrigin[1], &inputOrigin[2]);
		}
		else {
			right = i * 2;
			mid = (left + right) / 2;
			scanf("%d %d", &inputOrigin[right-1], &inputOrigin[right]);
			merge(inputOrigin, left, mid, right);
		}
	}
	
	int i;
	int n = MAX_SIZE;
	int list[n] = { 21, 10, 12, 20, 25, 13, 15, 22 };

	// �պ� ���� ����(left: �迭�� ���� = 0, right: �迭�� �� = 7)
	merge_sort(list, 0, n - 1);

	// ���� ��� ���
	for (i = 0; i<n; i++) {
		printf("%d\n", list[i]);
	}

	return 0;

}