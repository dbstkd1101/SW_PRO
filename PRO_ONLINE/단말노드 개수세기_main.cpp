// *** main.cpp ***
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>

#define MAX_NODE  10000
#define MAX_SUB  3000
#define MAX_LEN  7
#define MAX_CNT  10

extern void init();
extern void addSub(char mNode[], int mCnt, char mSubNode[][7]);
extern void eraseSub(char mNode[], char mSubNode[]);
extern int changeSub(char mNode[], char mSubA[], char mSubB[]);
extern int countLeaf(char mNode[]);

#define CMD_INIT                1
#define CMD_ADD                    2
#define CMD_ERASE                3
#define CMD_CHANGE                4
#define CMD_COUNT                5

static bool run()
{
    int  Q, cmd, mCnt;
    char mNode[MAX_LEN], mSubNode[MAX_CNT][MAX_LEN], mSub[MAX_LEN];
    char mSubA[MAX_LEN], mSubB[MAX_LEN];

    int  ans, res;

    scanf("%d", &Q);

    bool correct = false;

    for (int q = 0; q < Q; ++q)
    {
        if (q == 6) {
            int a = 1;
        }
        scanf("%d", &cmd);
        switch (cmd)
        {
        case CMD_INIT:
            init();
            correct = true;
            break;
        case CMD_ADD:
            scanf("%s %d", mNode, &mCnt);
            for (int i = 0; i < mCnt; ++i)
                scanf("%s", mSubNode[i]);
            if (correct)
                addSub(mNode, mCnt, mSubNode);
            break;
        case CMD_ERASE:
            scanf("%s %s", mNode, mSub);
            if (correct)
                eraseSub(mNode, mSub);
            break;
        case CMD_CHANGE:
            scanf("%s %s %s", mNode, mSubA, mSubB);
            if (correct)
                res = changeSub(mNode, mSubA, mSubB);
            scanf("%d", &ans);
            if (res != ans)
                correct = false;
            break;
        case CMD_COUNT:
            scanf("%s", mNode);
            if (correct)
                res = countLeaf(mNode);
            scanf("%d", &ans);
            if (res != ans)
                correct = false;
            break;
        }
    }

    return correct;
}

int main()
{
    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);

    int T, SCORE;
    scanf("%d %d", &T, &SCORE);

    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? SCORE : 0;
        printf("#%d %d\n", tc, score);
    }
    return 0;
}
