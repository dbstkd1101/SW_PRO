#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define INIT 1
#define HIRE 2
#define FIRE 3
#define UPDATE_MERCENARY 4 
#define UPDATE_TEAM 5
#define BEST_MERCENARY 6 

extern void init();
extern void hireMercenary(int id, int team, int score);
extern void fireMercenary(int id);
extern void updateMercenaryScore(int id, int score);
extern void updateTeamScore(int team, int newScore);
extern int bestMercenary(int team);

static bool run()
{
    int queryCnt;
    int id, team, score, newScore;
    int userAns, ans;

    bool correct = false;

    scanf("%d", &queryCnt);

    for (int i = 0; i < queryCnt; ++i)
    {
        int cmd;
        scanf("%d", &cmd);
        switch (cmd)
        {
        case INIT:
            init();
            correct = true;
            break;
        case HIRE:
            scanf("%d %d %d", &id, &team, &score);
            hireMercenary(id, team, score);
            break;
        case FIRE:
            scanf("%d", &id);
            fireMercenary(id);
            break;
        case UPDATE_MERCENARY:
            scanf("%d %d", &id, &score);
            updateMercenaryScore(id, score);
            break;
        case UPDATE_TEAM:
            scanf("%d %d", &team, &newScore);
            updateTeamScore(team, newScore);
            break;
        case BEST_MERCENARY:
            scanf("%d", &team);
            userAns = bestMercenary(team);
            scanf("%d", &ans);
            if (userAns != ans)
            {
                correct = false;
            }
            break;
        default:
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

    int T, success;
    scanf("%d %d", &T, &success);

    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? success : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}