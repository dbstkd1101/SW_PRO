#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

enum COMMAND {
    ENLIST = 1,
    MOVE,
    INFECT,
    CURE,
    DISCHARGE
};

extern void init();
extern int enlist(int id, int teamID, int fearIndex);
extern int move(int id, int teamID);
extern int infect(int id);
extern int cure(int id);
extern int discharge(int id);

static int run(int correct) {
    int N, order, userResult;
    int id, teamID, fearIndex;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        userResult = 0;
        scanf("%d", &order);
        if (i == 6) {
            int a = 6;
        }
        switch (order) {
        case ENLIST: {
            scanf("%d%d%d", &id, &teamID, &fearIndex);
            userResult = enlist(id, teamID, fearIndex);
            break;
        }
        case MOVE: {
            scanf("%d%d", &id, &teamID);
            userResult = move(id, teamID);
            break;
        }
        case INFECT: {
            scanf("%d", &id);
            userResult = infect(id);
            break;
        }
        case CURE: {
            scanf("%d", &id);
            userResult = cure(id);
            break;
        }
        case DISCHARGE: {
            scanf("%d", &id);
            userResult = discharge(id);
            break;
        }
        }

        int ans;
        scanf("%d", &ans);
        if (userResult != ans)
            correct = 0;
    }
    return correct;
}


int main() {
    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);

    int TC, score;
    scanf("%d%d", &TC, &score);
    for (int t = 1; t <= TC; t++) {
        init();
        int userResult = run(score);
        printf("#%d %d\n", t, userResult);
    }
    return 0;
}