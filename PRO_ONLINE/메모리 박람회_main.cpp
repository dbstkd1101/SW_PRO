#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int N, int bidArr[], int duration[], int capacity[]);
extern int add(int tick, int bid, int guestNum, int priority);
extern void search(int tick, int findCnt, int bidArr[], int numResult[]);

/////////////////////////////////////////////////////////////////////////

#define INIT   1
#define ADD    2
#define SEARCH 3

#define MAX_N 100

static int boothID[MAX_N];
static int boothDuration[MAX_N];
static int boothCapa[MAX_N];

static bool run() {
    int n, num, pri, tick, idx, cnt;
    int cmd, ans, ret = 0;
    int bidArr[10];
    int numResult[10];
    bool correct = false;
    int queryCnt;

    scanf("%d", &queryCnt);

    for (int i = 0; i < queryCnt; ++i) {
        scanf("%d", &cmd);
        switch (cmd) {
        case INIT:
            scanf("%d", &n);
            for (int j = 0; j < n; ++j) {
                scanf("%d %d %d", &boothID[j], &boothDuration[j], &boothCapa[j]);
            }
            init(n, boothID, boothDuration, boothCapa);
            correct = true;
            break;
        case ADD:
            scanf("%d %d %d %d %d", &tick, &idx, &num, &pri, &ans);
            if (correct) {
                ret = add(tick, boothID[idx], num, pri);
            }
            if (ret != ans)
                correct = false;
            break;
        case SEARCH:
            scanf("%d %d", &tick, &cnt);
            if (correct) {
                search(tick, cnt, bidArr, numResult);
            }
            for (int j = 0; j < cnt; ++j) {
                scanf("%d %d", &idx, &num);
                if (num != numResult[j] || boothID[idx] != bidArr[j]) {
                    correct = false;
                }
            }
            break;
        default:
            correct = false;
            break;
        }
    }

    return correct;
}

int main() {
    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);
    int T, success;
    scanf("%d %d", &T, &success);

    for (int tc = 1; tc <= T; tc++) {
        int score = run() ? success : 0;
        printf("#%d %d\n", tc, score);
    }
    return 0;
}
