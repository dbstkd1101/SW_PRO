# include <stdio.h>
# include "merge_sort.h"



void main() {
	int i;
	int list[9] = { 21, 10, 12, 20, 25, 13, 15, 22 };

	// 합병 정렬 수행(left: 배열의 시작 = 0, right: 배열의 끝 = 7)
	mergeSort(list, 0, 9-1);

	// 정렬 결과 출력
	for (i = 0; i< (9-1); i++) {
		printf("%d\n", list[i]);
	} 
}