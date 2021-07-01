#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

// API Command
#define CMD_INIT        100
#define CMD_ADDWORD     200
#define CMD_REMOVEWORD  300
#define CMD_SEARCHWORD  400

// User Implement API
extern void init(void);
extern void addWord(char str[]);
extern int  removeWord(char str[]);
extern int  searchWord(char str[]);

#define STRLEN_MAX 6

static int run(int score)
{
	int queryCnt;
	scanf("%d", &queryCnt);

	for (int q = 0; q < queryCnt; ++q)
	{
		if (q == 366) {
			int a = 1;
		}
		int cmd;
		scanf("%d", &cmd);

		if (cmd == CMD_INIT)
		{
			init();
		}
		else if (cmd == CMD_ADDWORD)
		{
			char str[STRLEN_MAX + 1];
			scanf("%s", str);

			addWord(str);
		}
		else if (cmd == CMD_REMOVEWORD)
		{
			char str[STRLEN_MAX + 1];
			scanf("%s", str);

			int userAns = removeWord(str);

			int ans;
			scanf("%d", &ans);

			if (userAns != ans)
			{
				score = 0;
			}
		}
		else if (cmd == CMD_SEARCHWORD)
		{
			char str[STRLEN_MAX + 1];
			scanf("%s", str);

			int userAns = searchWord(str);

			int ans;
			scanf("%d", &ans);

			if (userAns != ans)
			{
				score = 0;
			}
		}
	}
	return score;
}

int main(void)
{
	setbuf(stdout, NULL);

	freopen("input.txt", "r", stdin);

	int TC;
	int targetScore;
	scanf("%d %d", &TC, &targetScore);

	for (int testcase = 1; testcase <= TC; ++testcase)
	{
		int score = run(targetScore);
		printf("#%d %d\n", testcase, score);
	}

	return 0;
}
 