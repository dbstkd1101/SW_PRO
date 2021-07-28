#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define INIT            1
#define CREATE          2
#define DESTROY         3
#define NUMTONUM        4
#define NUMTONAME       5
#define BONUSPOINT      6

#define MAX_LEN 5


extern void userInit();
extern void create(int tick, char userName[MAX_LEN], char serverName[MAX_LEN], int charID, int point);
extern int destroy(int tick, int charID);
extern int numToNum(int tick, int giverID, int recieverID, int point);
extern int numToName(int tick, int giverID, char recieverName[MAX_LEN], int point);
extern void payBonusPoint(int tick, char serverName[MAX_LEN], int point);

static bool run()
{
    int commandCount;
    int order, charID, giverID, recieverID, point;
    char userName[MAX_LEN], recieverName[MAX_LEN], serverName[MAX_LEN];

    int ret = 0;
    int ans = 0;
    scanf("%d", &commandCount);
    bool correct = false;

    for (int tick = 0; tick < commandCount; ++tick)
    {
        scanf("%d", &order);
        if (tick == 11) {
            int a = 1;
        }
        switch (order)
        {
        case INIT:
            userInit();
            correct = true;
            break;
        case CREATE:
            scanf("%s %s %d %d", userName, serverName, &charID, &point);
            if (correct)
                create(tick, userName, serverName, charID, point);
            break;
        case DESTROY:
            scanf("%d", &charID);
            if (correct)
                ret = destroy(tick, charID);
            scanf("%d", &ans);
            if (ret != ans)
                correct = false;
            break;
        case NUMTONUM:
            scanf("%d %d %d", &giverID, &recieverID, &point);
            if (correct)
                ret = numToNum(tick, giverID, recieverID, point);
            scanf("%d", &ans);
            if (ret != ans)
                correct = false;
            break;
        case NUMTONAME:
            scanf("%d %s %d", &giverID, recieverName, &point);
            if (correct)
                ret = numToName(tick, giverID, recieverName, point);
            scanf("%d", &ans);
            if (ret != ans)
                correct = false;
            break;
        case BONUSPOINT:
            scanf("%s %d", serverName, &point);
            if (correct)
                payBonusPoint(tick, serverName, point);
            break;
        }
    }
    return correct;
}

int main()
{
    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);

    int testCase, perfectScore;
    scanf("%d %d", &testCase, &perfectScore);

    for (int nc = 1; nc <= testCase; nc++)
    {
        int ncScore = run() ? perfectScore : 0;
        printf("#%d %d\n", nc, ncScore);
    }
    return 0;
}
