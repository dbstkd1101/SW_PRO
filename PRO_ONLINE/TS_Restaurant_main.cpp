#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>

const int MAXN = 10000;
const int MAXM = 10;

const int ORDER = 200;
const int RECENTLY = 300;
const int OLDEST = 400;
const int MOSTORDERD = 500;
const int MOSTALL = 600;

extern void init(int N, int M, int K, int idList[]);
extern void order(int uid, int mid);
extern int getRecentlyMenu(int uid, int retList[]);
extern int getOldestMenu(int uid, int retList[]);
extern void getMostOrdered(int uid, int retList[]);
extern void getMostOrderedAll(int retList[]);

static int uid_list[MAXN + 5];

static int run(int score)
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", uid_list + i);
    }
    init(n, m, k, uid_list);

    int QN, q;
    scanf("%d", &QN);

    for (q = 0; q < QN; q++)
    {
        int cmd, uid, mid;
        int userAns, userAnsList[MAXM];
        int ans, ansList[MAXM];

        scanf("%d", &cmd);

        if (cmd == ORDER) {
            scanf("%d%d", &uid, &mid);
            order(uid, mid);
            continue;
        }
        else if (cmd == RECENTLY || cmd == OLDEST || cmd == MOSTORDERD) {
            scanf("%d", &uid);
            if (cmd == RECENTLY) {
                userAns = getRecentlyMenu(uid, userAnsList);
                scanf("%d", &ans);
            }
            else if (cmd == OLDEST) {
                userAns = getOldestMenu(uid, userAnsList);
                scanf("%d", &ans);
            }
            else if (cmd == MOSTORDERD) {
                ans = userAns = m;
                getMostOrdered(uid, userAnsList);
            }
        }
        else {
            ans = userAns = m;
            getMostOrderedAll(userAnsList);
        }

        if (userAns != ans)
            score = 0;

        for (int i = 0; i < ans; i++) {
            scanf("%d", ansList + i);

            if (ansList[i] != userAnsList[i]) {
                score = 0;
            }
        }
    }

    return score;
}

int main() {
    setbuf(stdout, NULL);

    freopen("input.txt", "r", stdin);

    int TC, success;
    scanf("%d%d", &TC, &success);

    for (int tc = 1; tc <= TC; tc++) {
        int score = run(success);
        printf("#%d %d\n", tc, score);
    }

    return 0;
}
