#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define NEW_CLASS 1
#define NEW_RECORD 2
#define CHANGE_RECORD 3
#define CHECK_ATTENDANCE 4
#define CHECK_CHEATING 5

extern void init();
extern void destroy();
extern void newClass(int mClassId, char mClassBegin[], char mClassEnd[], int mRatio);
extern void newRecord(int mRecordId, int mClassId, char mRecordBegin[], char mRecordEnd[]);
extern void changeRecord(int mRecordId, char mNewBegin[], char mNewEnd[]);
extern int checkAttendance(int mClassId, char mDate[]);
extern int checkCheating();

static int run(int Result)
{
    int N;
    scanf("%d", &N);
    init();
    for (int i = 0; i < N; ++i) {
        int cmd = 0;
        int mClassId, mRatio, mRecordId;
        char mClassBegin[64], mClassEnd[64], mRecordBegin[64], mRecordEnd[64];
        char mNewBegin[64], mNewEnd[64], mDate[64];
        int res, ans;
        scanf("%d", &cmd);
        switch (cmd) {
        case NEW_CLASS:
            scanf("%d %s %s %d", &mClassId, mClassBegin, mClassEnd, &mRatio);
            newClass(mClassId, mClassBegin, mClassEnd, mRatio);
            break;
        case NEW_RECORD:
            scanf("%d %d %s %s", &mRecordId, &mClassId, mRecordBegin, mRecordEnd);
            newRecord(mRecordId, mClassId, mRecordBegin, mRecordEnd);
            break;
        case CHANGE_RECORD:
            scanf("%d %s %s", &mRecordId, mNewBegin, mNewEnd);
            changeRecord(mRecordId, mNewBegin, mNewEnd);
            break;
        case CHECK_ATTENDANCE:
            scanf("%d %s", &mClassId, mDate);
            res = checkAttendance(mClassId, mDate);
            scanf("%d", &ans);
            if (res != ans) {
                Result = 0;
            }
            break;
        case CHECK_CHEATING:
            res = checkCheating();
            scanf("%d", &ans);
            if (res != ans) {
                Result = 0;
            }
            break;
        }
    }
    destroy();
    return Result;
}

int main()
{
    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);

    int T, Result;
    scanf("%d %d", &T, &Result);
    for (int tc = 1; tc <= T; tc++) {
        printf("#%d %d\n", tc, run(Result));
    }
    return 0;
}
