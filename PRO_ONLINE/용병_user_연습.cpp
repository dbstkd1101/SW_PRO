#include <stdio.h>
#include <string.h>
#include <list>
#include <set>

#ifndef NULL
#define NULL 0
#endif

using namespace std;

const int LS = 1e5 + 3;

struct soldier {
    int id, team, score;
}* sIdMap[LS], *sTMap[6];

list<soldier> li[6][11];
list<soldier> tLi[6];

list<soldier>::const_iterator it[6][11];
list<soldier>::const_iterator tIt[6];

void init() {
    for (int i = 1; i < LS; i++) {
        sIdMap[i] = NULL;
    }


    for (int i = 1; i <= 5; i++) {
        tIt[i] = tLi[i].begin();
        sTMap[i] = NULL;
        for (int j = 1; j <= 10; j++) {
            li[i][j].clear();
            it[i][j] = li[i][j].begin();
        }
    }
}
void hireMercenary(int id, int team, int score) {
    soldier tmp = { id, team, score };
    auto tmpIt1 = li[team][score + 4].insert(it[team][score + 4], tmp);
    auto tmpIt2 = tLi[team].insert(tIt[team], tmp);

    sIdMap[id] = &*tmpIt1;
    sTMap[team]= &*tmpIt2;
}
void fireMercenary(int id) {

}
void updateMercenaryScore(int id, int score) {


}
void updateTeamScore(int team, int newScore) {

}
int bestMercenary(int team) {
    return 0;
}