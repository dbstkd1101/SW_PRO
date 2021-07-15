#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif // _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

static int AN, A[1000][1000], BM, B[20][20];

static unsigned int seed;
static unsigned int myRand() {
    seed = 22695477 * seed + 1;
    return seed >> 16;
}

extern void init(int, int[][1000], int);
extern int query(int[][20]);

static void makeArr() {
    int i, j;
    for (i = 0; i < AN; ++i)for (j = 0; j < AN; ++j) {
        A[i][j] = myRand() & 1;
    }
}

static int makeBrr(int limit) {
    int r = myRand() % (limit + 1);
    int c = myRand() % (limit + 1);
    int i, j, zero = 1;
    for (i = 0; i < BM; ++i)for (j = 0; j < BM; ++j) {
        B[i][j] = A[r + i][c + j];
        if (B[i][j]) zero = 0;
    }
    return zero;
}

static int run() {
    int limit = AN - BM;
    int i, j, ret;
    while (makeBrr(limit));
    ret = query(B);
    int userR = ret / AN, userC = ret % AN;
    if (userR < 0 || userR > limit || userC < 0 || userC > limit)
        return 0;

    for (i = 0; i < BM; ++i)for (j = 0; j < BM; ++j) {
        if (B[i][j] != A[userR + i][userC + j]) return 0;
    }
    return 100;
}

int main() {
    freopen("input.txt", "r", stdin);
    int TC, i, j, Q;
    scanf("%d", &TC);
    for (i = 1; i <= TC; ++i) {
        scanf("%d %d %u %d", &AN, &BM, &seed, &Q);
        int total = 0;
        makeArr();
        init(AN, A, BM);
        for (j = 1; j <= Q; ++j) {
            int sc = run();
            total += sc;
        }
        printf("#case %d : %d\n", i, total / Q);
    }
    return 0;
}