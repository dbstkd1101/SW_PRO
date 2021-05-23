

/// *** main.cpp ***
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <malloc.h>

extern void init(int N);
extern int move(int r, int c, int len);

static bool run()
{
	int N, Q;
	bool correct = true;
	scanf("%d", &N);
	init(N);
	scanf("%d", &Q);
	for (int i = 0; i < Q; i++)
	{
		int r, c, len;
		scanf("%d %d %d", &r, &c, &len);
		int userResult = 0;
		if (correct)
		{
			if (i == 3) {
				int a = 1;
			}
			userResult = move(r, c, len);
		}

		int ans;
		scanf("%d", &ans);
		if (ans != userResult)
		{
			correct = false;
		}
	}
	return correct;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("input.txt", "r", stdin);

	int T, success;
	scanf("%d %d", &T, &success);

	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? success : 0;
		printf("#%d %d\n", tc, score);
	}
	return 0;
}