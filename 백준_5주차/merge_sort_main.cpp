# include <stdio.h>
# include "merge_sort.h"



void main() {
	int i;
	int list[9] = { 21, 10, 12, 20, 25, 13, 15, 22 };

	// �պ� ���� ����(left: �迭�� ���� = 0, right: �迭�� �� = 7)
	mergeSort(list, 0, 9-1);

	// ���� ��� ���
	for (i = 0; i< (9-1); i++) {
		printf("%d\n", list[i]);
	} 
}