#include <stdio.h>

struct Node
{
	int id;
	int freq;
};

int validID[110000];
Node minHeap[110000];
Node maxHeap[110000];
int minHn;
int maxHn;

int sum;

void minPush(Node value)
{
	minHeap[++minHn] = value;

	int now = minHn;
	int parent;

	while (1)
	{
		parent = now / 2;
		if (now == 1) break;
		if (minHeap[now].freq > minHeap[parent].freq) break;
		if (minHeap[now].freq == minHeap[parent].freq && minHeap[now].id > minHeap[parent].id) break;

		Node temp = minHeap[now];
		minHeap[now] = minHeap[parent];
		minHeap[parent] = temp;

		now = parent;
	}
}

Node minPop()
{
	Node ret = minHeap[1];
	minHeap[1] = minHeap[minHn];
	minHeap[minHn].id = 0;
	minHeap[minHn].freq = 0;
	minHn--;

	int now = 1;
	int son;

	while (1)
	{
		son = now * 2;
		if (son + 1 <= minHn && minHeap[son].freq > minHeap[son + 1].freq) son++;
		else if (son + 1 <= minHn && minHeap[son].freq == minHeap[son + 1].freq && minHeap[son].id > minHeap[son + 1].id) son++;

		if (son > minHn) break;
		if (minHeap[son].freq > minHeap[now].freq) break;
		if (minHeap[son].freq == minHeap[now].freq && minHeap[son].id > minHeap[now].id) break;

		Node temp = minHeap[now];
		minHeap[now] = minHeap[son];
		minHeap[son] = temp;

		now = son;
	}

	return ret;
}

void maxPush(Node value)
{
	maxHeap[++maxHn] = value;

	int now = maxHn;
	int parent;

	while (1)
	{
		parent = now / 2;
		if (now == 1) break;
		if (maxHeap[now].freq < maxHeap[parent].freq) break;
		if (maxHeap[now].freq == maxHeap[parent].freq && maxHeap[now].id < maxHeap[parent].id) break;

		Node temp = maxHeap[now];
		maxHeap[now] = maxHeap[parent];
		maxHeap[parent] = temp;

		now = parent;
	}
}

Node maxPop()
{
	Node ret = maxHeap[1];
	maxHeap[1] = maxHeap[maxHn];
	maxHeap[maxHn].id = 0;
	maxHeap[maxHn].freq = 0;
	maxHn--;

	int now = 1;
	int son;

	while (1)
	{
		son = now * 2;
		if (son + 1 <= maxHn && maxHeap[son].freq < maxHeap[son + 1].freq) son++;
		else if (son + 1 <= maxHn && maxHeap[son].freq == maxHeap[son + 1].freq && maxHeap[son].id < maxHeap[son + 1].id) son++;

		if (son > maxHn) break;
		if (maxHeap[son].freq < maxHeap[now].freq) break;
		if (maxHeap[son].freq == maxHeap[now].freq && maxHeap[son].id < maxHeap[now].id) break;

		Node temp = maxHeap[now];
		maxHeap[now] = maxHeap[son];
		maxHeap[son] = temp;

		now = son;
	}

	return ret;
}

Node minTop()
{
	Node t = { 0 };
	Node blank = { 0 };

	while (1)
	{
		if (minHn == 0) return blank;

		t = minPop();
		if (validID[t.id] == 1)
		{
			minPush(t);
			break;
		}
	}

	return t;
}


Node maxTop()
{
	Node t = { 0 };
	Node blank = { 0 };

	while (1)
	{
		if (maxHn == 0) return blank;

		t = maxPop();
		if (validID[t.id] == 1)
		{
			maxPush(t);
			break;
		}
	}

	return t;
}

int main()
{
	int n, m;
	int mode;
	//freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &m);
	Node t;

	for (int i = 0; i < m; i++)
	{
		scanf("%d", &mode);

		if (mode == 0)
		{
			scanf("%d %d", &t.id, &t.freq);
			minPush(t);
			maxPush(t);
			validID[t.id] = 1;
			sum += t.freq;
		}
		else if (mode == 1)
		{
			t = minTop();
			if (minHn > 0)
			{
				printf("%d\n", t.id);
				minPop();
				validID[t.id] = 0; //ID제거
				sum -= t.freq;
			}
		}
		else if (mode == 2)
		{
			t = maxTop();
			if (maxHn > 0)
			{
				printf("%d\n", t.id);
				maxPop();
				validID[t.id] = 0;//ID제거
				sum -= t.freq;
			}
		}
		else if (mode == 3)
		{
			Node h = maxTop();
			Node l = minTop();

			if (minHn > 0 && h.id == l.id)
			{
				printf("%d\n", sum - h.freq);
			}
			else
			{
				printf("%d\n", sum - h.freq - l.freq);
			}
		}
	}

	return 0;
}