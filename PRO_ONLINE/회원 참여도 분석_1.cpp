#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern struct maxData;

#define MIN_HEAP_SIZE 100000

struct minData{
	int id, freq;
	maxData * maxAddr;
}minHeap[MIN_HEAP_SIZE];

int minHeapSize = 0;

void minHeapInit(void)
{
	minHeapSize = 0;
}

minData* minHeapPush(minData value)
{
	if (minHeapSize + 1 > MIN_HEAP_SIZE)
	{
		printf("queue is full!");
		return 0;
	}

	minHeap[minHeapSize] = value;

	int current = minHeapSize;
	while (current > 0 && (minHeap[current].freq < minHeap[(current - 1) / 2].freq)||(minHeap[current].freq == minHeap[(current - 1) / 2].freq && minHeap[current].id < minHeap[(current - 1) / 2].id))
	{
		minData temp = minHeap[(current - 1) / 2];
		minHeap[(current - 1) / 2] = minHeap[current];
		minHeap[current] = temp;
		current = (current - 1) / 2;
	}

	return &minHeap[minHeapSize++];
}

int minHeapPop(minData *value)
{
	if (minHeapSize <= 0)
	{
		return -1;
	}

	*value = minHeap[0];
	minHeapSize = minHeapSize - 1;

	minHeap[0] = minHeap[minHeapSize];

	int current = 0;
	while (current * 2 + 1 < minHeapSize)
	{
		int child;
		if (current * 2 + 2 == minHeapSize)
		{
			child = current * 2 + 1;
		}
		else
		{
			if (minHeap[current * 2 + 1].freq < minHeap[current * 2 + 2].freq) {
				child = current * 2 + 1;
			}
			else if((minHeap[current * 2 + 1].freq == minHeap[current * 2 + 2].freq) && (minHeap[current * 2 + 1].id < minHeap[current * 2 + 2].id)) {
				child = current * 2 + 1;
			}
			else{
				child = current * 2 + 2;
			}
		}

		if ((minHeap[current].freq < minHeap[child].freq) || ((minHeap[current].freq == minHeap[child].freq) && (minHeap[current].id < minHeap[child].id)))
		{
			break;
		}

		minData temp = minHeap[current];
		minHeap[current] = minHeap[child];
		minHeap[child] = temp;

		current = child;
	}
	return 1;
}


#define MAX_HEAP_SIZE 100000

struct maxData {
	int id, freq;
	minData * maxAddr;
}maxHeap[MAX_HEAP_SIZE];

int maxHeapSize = 0;

void maxHeapInit(void)
{
	maxHeapSize = 0;
}

maxData* maxHeapPush(maxData value)
{
	if (maxHeapSize + 1 > MAX_HEAP_SIZE)
	{
		printf("queue is full!");
		return 0;
	}

	maxHeap[maxHeapSize] = value;

	int current = maxHeapSize;
	while (current > 0 && (maxHeap[current].freq > maxHeap[(current - 1) / 2].freq) || (maxHeap[current].freq == maxHeap[(current - 1) / 2].freq && maxHeap[current].id > maxHeap[(current - 1) / 2].id))
	{
		maxData temp = maxHeap[(current - 1) / 2];
		maxHeap[(current - 1) / 2] = maxHeap[current];
		maxHeap[current] = temp;
		current = (current - 1) / 2;
	}

	return &maxHeap[maxHeapSize++];
}

int maxHeapPop(maxData *value, maxData* pos)
{
	if (maxHeapSize <= 0)
	{
		return -1;
	}

	*value = maxHeap[0];
	maxHeapSize = maxHeapSize - 1;

	if (pos) {
		*pos = maxHeap[maxHeapSize];
	}
	maxHeap[0] = maxHeap[maxHeapSize];

	int current = 0;
	while (current * 2 + 1 < maxHeapSize)
	{
		int child;
		if (current * 2 + 2 == maxHeapSize)
		{
			child = current * 2 + 1;
		}
		else
		{
			if (maxHeap[current * 2 + 1].freq > maxHeap[current * 2 + 2].freq) {
				child = current * 2 + 1;
			}
			else if ((maxHeap[current * 2 + 1].freq == maxHeap[current * 2 + 2].freq) && (maxHeap[current * 2 + 1].id > maxHeap[current * 2 + 2].id)) {
				child = current * 2 + 1;
			}
			else {
				child = current * 2 + 2;
			}
		}

		if ((maxHeap[current].freq > maxHeap[child].freq) || ((maxHeap[current].freq == maxHeap[child].freq) && (maxHeap[current].id > maxHeap[child].id)))
		{
			break;
		}

		maxData temp = maxHeap[current];
		maxHeap[current] = maxHeap[child];
		maxHeap[child] = temp;

		current = child;
	}
	return 1;
}

int N, M;
int mCnt, freSum;

int main() {
	minHeapInit();
	minHeapInit();

	freopen("input.txt", "r", stdin);
	scanf("%d %d", &N, &M);
	



	return 0;
}