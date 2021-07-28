#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

const int INIT = 100;
const int MAKE_ON_OFF = 200;
const int MEETBREAK = 300;
const int SENDTALK = 400;
const int GETTALKLIST = 500;
const int GETTALKPARTNERLIST = 600;
const int MAXN = 5;
const int MAXLEN = 21;

extern void init();
extern void makeOnOff(int aid, int state);
extern void meetBreak(int aid, int bid, int state);
extern void sendTalk(int aid, int bid, char talk[MAXLEN]);
extern int getTalkList(int aid, int bid, char userTalkList[MAXN][MAXLEN]);
extern int getTalkPartnerList(int aid, int userPartnerList[MAXN]);

/////////////////////////////////////////////////////////////////////////

int mystrcmp(const char* s, const char* t) {
    while (*s && *s == *t) ++s, ++t;
    return *s - *t;
}

static bool run() {

    char talk[MAXLEN];
    int ansCnt, userAnsCnt = 0;
    char anstalkList[MAXN][MAXLEN], userTalkList[MAXN][MAXLEN];

    int ansPartnerCnt, userPartnerCnt = 0;
    int ansPartnerList[MAXN], userPartnerList[MAXN];

    int queryCnt, cmd;
    int aid, bid, state;

    scanf("%d", &queryCnt);

    bool correct = false;

    for (int qc = 0; qc <= queryCnt; ++qc)
    {
        if (qc == 34) {
            int a = 1;
        }
        scanf("%d", &cmd);
        switch (cmd)
        {
        case INIT:
            init();
            correct = true;
            break;
        case MAKE_ON_OFF:
            scanf("%d %d", &aid, &state);
            if (correct) {
                makeOnOff(aid, state);
            }
            break;
        case MEETBREAK:
            scanf("%d %d %d", &aid, &bid, &state);
            if (correct) {
                meetBreak(aid, bid, state);
            }
            break;
        case SENDTALK:
            scanf("%d %d %s", &aid, &bid, talk);
            if (correct) {
                sendTalk(aid, bid, talk);
            }
            break;
        case GETTALKLIST:
            scanf("%d %d", &aid, &bid);
            if (correct)
                userAnsCnt = getTalkList(aid, bid, userTalkList);
            scanf("%d", &ansCnt);
            for (int i = 0; i < ansCnt; ++i) {
                scanf("%s", anstalkList[i]);
            }
            if (correct) {
                if (userAnsCnt != ansCnt) {
                    correct = false;
                }
                else
                {
                    for (int i = 0; correct && i < ansCnt; ++i) {
                        if (mystrcmp(anstalkList[i], userTalkList[i]) != 0) {
                            correct = false;
                        }
                    }
                }
            }
            break;
        case GETTALKPARTNERLIST:
            scanf("%d", &aid);
            if (correct)
                userPartnerCnt = getTalkPartnerList(aid, userPartnerList);
            scanf("%d", &ansPartnerCnt);
            for (int i = 0; i < ansPartnerCnt; ++i) {
                scanf("%d", &ansPartnerList[i]);
            }
            if (correct) {
                if (userPartnerCnt != ansPartnerCnt) {
                    correct = false;
                }
                else {
                    for (int i = 0; correct && i < ansPartnerCnt; ++i) {
                        if (ansPartnerList[i] != userPartnerList[i]) {
                            correct = false;
                        }
                    }
                }
            }
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
        int result = run() ? success : 0;
        printf("#%d %d\n", tc, result);
    }

    return 0;
}