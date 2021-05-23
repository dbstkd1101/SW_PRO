#include <stdio.h>
#include "heap_sort.h"

int main(int argc, char* argv[])
{
	int T, N;

	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++)
	{
		scanf("%d", &N);

		heapInit();

		for (int i = 0; i < N; i++)
		{
			int value;
			scanf("%d", &value);
			heapPush(value);
		}

		printf("#%d ", test_case);

		for (int i = 0; i < N; i++)
		{
			int value;
			heapPop(&value);
			printf("%d ", value);
		}
		printf("\n");
	}
	return 0;
}