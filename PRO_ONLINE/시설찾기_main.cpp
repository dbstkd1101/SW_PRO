#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <time.h>


extern void init(int N);
extern void add(int mId, int mType, int mX, int mY);
extern void removeId(int mId);
extern int  search1(int mType, int mX, int mY, int radius);
extern void search2(int mType, int mX, int mY, int mIdList[5]);

typedef enum { ADD, DEL, SR1, SR2 } CMD;

static int N;
static int seed;
static int cmd_cnt;
static int Score, TotalScore;
static int mId;


static int pseudo_rand()
{
	seed = seed * 201633 + 4123011;
	return (seed >> 16) & 0x7FFFFFFF;
}

void _add()
{
	int mType = pseudo_rand() % 10 + 1;
	int mX = pseudo_rand() % N;
	int mY = pseudo_rand() % N;

	add(mId++, mType, mX, mY);
}

void _removeId()
{
	int r_mId = pseudo_rand() % mId;

	removeId(r_mId);
}

void _search1()
{
	int mType = pseudo_rand() % 11;
	int mX = pseudo_rand() % N;
	int mY = pseudo_rand() % N;
	int radius = pseudo_rand() % (N / 2) + 1;
	int result;

	scanf("%d", &result);
	int ret = search1(mType, mX, mY, radius);

	if (result != ret) Score = 0;

}

void _search2()
{
	int mType = pseudo_rand() % 10 + 1;
	int mX = pseudo_rand() % N;
	int mY = pseudo_rand() % N;
	int mIdList[5] = { 0, };
	int result[5] = { 0, };

	for (int i = 0; i < 5; i++) scanf("%d", &result[i]);

	search2(mType, mX, mY, mIdList);

	for (int i = 0; i < 5; i++)
	{
		if (result[i] != mIdList[i])
		{
			Score = 0;
			break;
		}
	}
}

int main()
{
	time_t start_time = clock();
	int T;
	int cmd;

	freopen("input.txt", "rt", stdin);

	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%d %d %d", &N, &cmd_cnt, &seed);
		Score = 100;
		mId = 0;
		init(N);


		for (int i = 0; i < cmd_cnt; i++)
		{
			if (i < cmd_cnt / 10) cmd = ADD;
			else
			{

				int rate = pseudo_rand() % 100;
				if (rate < 45) cmd = ADD;
				else if (rate < 55) cmd = DEL;
				else if (rate < 90) cmd = SR1;
				else cmd = SR2;
			}

			switch (cmd)
			{
			case ADD: _add(); break;
			case DEL: _removeId(); break;
			case  SR1: _search1(); break;
			case SR2: _search2(); break;
			}

		}

		printf("#%d %d\n", tc, Score);
		TotalScore += Score;

	}

	printf("Total Score :%d\n", TotalScore);
	printf("Program running time:%0.4f\n", (double)(clock() - start_time) / CLOCKS_PER_SEC);

	return 0;
}
