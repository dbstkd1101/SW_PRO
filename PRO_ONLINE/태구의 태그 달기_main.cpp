// *** main.cpp ***
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

static int mySeed;
static int myRand(void) {
    mySeed = mySeed * 0x343FD + 0x269EC3;
    return (mySeed >> 16) & 32767;
}

extern void init();
extern void incoming(int pid, int price, int tagCnt, char tagString[][11]);
extern int search(int tagCnt, char tagString[][11], int maxCnt, bool flag, int idList[]);
extern int sell(int pid);

#define INIT        1
#define INCOMING    2
#define SEARCH      3
#define SELL        4

static char Tag[5][11];
static int result[20];

static int genId(int seed) {
    mySeed = seed;
    return ((myRand() << 15) + myRand()) % 1000000000;
}

static int genPrice(int seed) {
    mySeed = seed;
    return (myRand() + (myRand() << 15)) % 100000000 + 1;
}

static int genTag(int seed) {
    static int mod[5] = { 1, 10, 100, 1000, 10000 };
    int cnt = 0;
    for (int i = 0; i < 5; ++i) {
        mySeed = (seed >> 5) / mod[i];
        int len = myRand() % 10 + 1;
        if (seed & (1 << i)) {
            for (int j = 0; j < len; ++j) {
                Tag[cnt][j] = 'a' + myRand() % 26;
            }
            Tag[cnt][len] = 0;
            cnt++;
        }
    }
    return cnt;
}

static bool run() {
    int n;
    scanf("%d", &n);
    int processType, pidSeed, tagSeed;
    int pid, price, tagCnt, k;
    int ret, ans, ans2;
    bool flag;
    bool correct = false;

    for (int i = 0; i < n; ++i) {
        int cmd;
        scanf("%d", &cmd);
        switch (cmd) {
        case INIT:
            scanf("%d", &processType);
            init();
            correct = true;
            break;
        case INCOMING:
            if (processType) {
                scanf("%d", &pidSeed);
                pid = genId(pidSeed);
                price = genPrice(pidSeed);
                scanf("%d", &tagSeed);
                tagCnt = genTag(tagSeed);
            }
            else {
                scanf("%d %d %d", &pid, &price, &tagCnt);
                for (int j = 0; j < tagCnt; ++j) {
                    scanf("%s", Tag[j]);
                }
            }
            if (correct) {
                incoming(pid, price, tagCnt, Tag);
            }
            break;
        case SEARCH:
            if (processType) {
                scanf("%d", &tagSeed);
                tagCnt = genTag(tagSeed);
                k = myRand() % 10 + 1;
                flag = myRand() % 2;
            }
            else {
                scanf("%d", &tagCnt);
                for (int j = 0; j < tagCnt; ++j) {
                    scanf("%s", Tag[j]);
                }
                int tmp;
                scanf("%d %d", &k, &tmp);
                flag = (tmp == 1);
            }
            if (correct) {
                ret = search(tagCnt, Tag, k, flag, result);
            }
            scanf("%d", &ans);
            if (ret != ans)
                correct = false;

            for (int j = 0; j < ans; ++j) {
                scanf("%d", &ans2);
                if (processType) {
                    ans2 = genId(ans2);
                }
                if (ans2 != result[j]) {
                    correct = false;
                }
            }
            break;
        case SELL:
            if (processType) {
                scanf("%d", &pidSeed);
                pid = genId(pidSeed);
            }
            else {
                scanf("%d", &pid);
            }
            if (correct) {
                ret = sell(pid);
            }
            scanf("%d", &ans);
            if (correct && ans != ret) {
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

int main() {
    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);

    int testCase, success;
    scanf("%d %d", &testCase, &success);

    for (int tc = 1; tc <= testCase; ++tc) {
        int score = run() ? success : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}