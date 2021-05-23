#include <stdio.h>
#define MAX_KEY 5
#define MAX_DATA 5
#define MAX_TABLE 1000000

void strcpy(char* dest, const char* origin) {
	while (*origin) *dest++ = *origin++;
	*dest = 0;
}


int strcmp(const char* s1, const char* s2) {
	while (*s1 && *s1 == *s2) {
		++s1; ++s2;
	}
	return *s1 - *s2;
}

typedef struct
{
	char key[MAX_KEY + 1];
	char data[MAX_DATA + 1];
}Hash;

Hash tb[MAX_TABLE+100];

Hash* exist[MAX_TABLE + 1];
int existRear = -1;

// 추가적인 공간이 필요
char sorted[MAX_TABLE + 1][MAX_KEY + 1];

char existWorking[MAX_TABLE + 1][MAX_KEY + 1];

// 2 <= N < 10^6
int N;

unsigned long hash(const char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}

	return hash % MAX_TABLE;
}

int find(const char *key, char *data)
{
	unsigned long h = hash(key);
	int cnt = MAX_TABLE;

	while (tb[h].key[0] != 0 && cnt--)
	{
		if (strcmp(tb[h].key, key) == 0)
		{
			strcpy(data, tb[h].data);
			return 1;
		}
		h = (h + 1) % MAX_TABLE;
	}
	return 0;
}

int add(const char *key, char *data)
{	
	unsigned long h = hash(key);

	if (data[0] == 'e') {
		while (tb[h].key[0] != 0)
		{
			if (strcmp(tb[h].key, key) == 0)
			{
				strcpy(tb[h].data, data);
				return 0;
			}

			h = (h + 1) % MAX_TABLE;
		}
		// newNode
		strcpy(tb[h].key, key);
		strcpy(tb[h].data, data);

		exist[++existRear] = &tb[h];
	}
	if (data[0] == 'l') {
		while (tb[h].key[0] != 0)
		{
			if (strcmp(tb[h].key, key) == 0)
			{
				strcpy(tb[h].data, data);
				return 0;
			}

			h = (h + 1) % MAX_TABLE;
		}
	}

	return 1;
}

void merge(char list[][MAX_DATA + 1], int left, int mid, int right) {
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;

	while (i <= mid && j <= right) {
		if (strcmp(list[i], list[j]) > 0)
			strcpy(sorted[k++], list[i++]);
		else
			strcpy(sorted[k++], list[j++]);
	}

	if (i>mid) {
		for (l = j; l <= right; l++)
			strcpy(sorted[k++], list[l]);
	}
	else {
		for (l = i; l <= mid; l++)
			strcpy(sorted[k++], list[l]);
	}

	for (l = left; l <= right; l++) {
		strcpy(list[l], sorted[l]);
	}
}

void merge_sort(char list[][MAX_KEY + 1], int left, int right) {
	int mid;

	if (left<right) {
		mid = (left + right) / 2; // 중간 위치를 계산하여 리스트를 균등 분할 -분할(Divide)
		merge_sort(list, left, mid); // 앞쪽 부분 리스트 정렬 -정복(Conquer)
		merge_sort(list, mid + 1, right); // 뒤쪽 부분 리스트 정렬 -정복(Conquer)
		merge(list, left, mid, right); // 정렬된 2개의 부분 배열을 합병하는 과정 -결합(Combine)
	}
}

int main() {
	freopen("input.txt", "r", stdin);

	scanf("%d", &N);
	char k[MAX_KEY + 1];
	char d[MAX_DATA + 1];

	for (int i = 1; i <= N; i++) {
		scanf("%s %s", &k, &d);
		add(k, d);
	}

	int workingCnt = -1;
	char tmpData[MAX_DATA + 1];
	for (int i = 0; i <= existRear; i++) {
		find(exist[i]->key, tmpData);
		if (tmpData[0] == 'e') {
			strcpy(existWorking[++workingCnt], exist[i]->key);
		}
	}

	merge_sort(existWorking, 0, workingCnt);

	for (int j = 0; j <= workingCnt; j++) {
		printf("%s\n", existWorking[j]);
	}

}