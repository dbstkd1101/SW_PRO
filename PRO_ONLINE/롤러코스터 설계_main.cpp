#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

static const int CMD_INIT = 100;
static const int CMD_ADDRAIL = 200;
static const int CMD_DELRAIL = 300;

extern void init(int);
extern void addRail(int, int);
extern int delRail(int, int);

static int run(void)
{
	int ret = 0;
	int query_cnt, cmd;
	int usr, ans;
	int N, mRow, mCol, mFront, mDirection;

	scanf("%d", &query_cnt);

	for (int q = 0; q < query_cnt; q++)
	{
		scanf("%d", &cmd);
		switch (cmd) {
		case CMD_INIT:
			scanf("%d", &N);
			init(N);
			ret = 1;
			break;
		case CMD_ADDRAIL:
			scanf("%d %d", &mFront, &mDirection);
			addRail(mFront, mDirection);
			break;
		case CMD_DELRAIL:
			scanf("%d %d", &mRow, &mCol);
			usr = delRail(mRow, mCol);
			scanf("%d", &ans);
			if (usr != ans)
				ret = 0;
			break;
		default:
			ret = 0;
			break;
		}
	}

	return ret;
}

int main()
{
	setbuf(stdout, NULL);
	//freopen("sample_input.txt", "r", stdin);
	int tc, MARK;

	scanf("%d %d", &tc, &MARK);

	for (int t = 1; t <= tc; t++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", t, score);
	}

	return 0;
}