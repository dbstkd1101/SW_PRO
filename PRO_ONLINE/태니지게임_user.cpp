#ifndef NULL
#define NULL 0
#endif
#include <vector>
#include <set>
#include <list>
#include <unordered_map>

using namespace std;

#define MAXLEN (5)
#define MAX_CNT_SERVER 20+3
#define MAX_CNT_CREATE 30000+3

enum {
    GIVE=0, RECV
};

struct character {
    int userIdx, serverIdx, tick, point;
    int recentAction;
};

//vector<character> hist[MAX_CNT_CREATE][MAX_CNT_SERVER];
list<character>hist[MAX_CNT_CREATE][MAX_CNT_SERVER];

unordered_map<int, int> charHTab;
unordered_map<string, int> userHTab;
unordered_map<string, int> serverHTab;

int characCnt;
int userCnt;
int serverCnt;

list<character>::iterator charItArr[MAX_CNT_CREATE];

set<pair<int, int>> pq;

void userInit() {
    serverCnt = userCnt = characCnt = 0;
    for (int i = 0; i < MAX_CNT_CREATE; i++) {
        for (int j = 0; j < MAX_CNT_SERVER; j++) {
            hist[i][j].clear();
        }
    }

    charHTab.clear();
    userHTab.clear();
    serverHTab.clear();
}

void create(int tick, char userName[MAXLEN], char serverName[MAXLEN], int charID, int point) {
    if (userHTab.find(userName) == userHTab.end()) userHTab[userName] = userCnt++;
    int userIdx = userHTab[userName];
    int charIdx = charHTab[charID];
    if (serverHTab.find(serverName) == serverHTab.end()) serverHTab[serverName] = serverCnt++;
    int serverIdx = serverHTab[serverName];

    charItArr[charIdx] = hist[charIdx][serverIdx].insert(hist[charIdx][serverIdx].begin(), { userIdx, serverIdx, tick, point, -1 });
}

int destroy(int tick, int charID) {
    int charIdx = charHTab[charID];
    //charItArr[charIdx]->tick = tick;
    int rst = (charItArr[charIdx]->point);
    
    int userIdx = charItArr[charIdx]->userIdx;
    int serverIdx = charItArr[charIdx]->serverIdx;

    hist[userIdx][serverIdx].erase(charItArr[charIdx]);

    return rst;
}

int numToNum(int tick, int giverID, int recieverID, int point) {
    int giverIdx = charHTab[giverID];
    int recieverIdx = charHTab[recieverID];
    if ((charHTab.find(giverID) == charHTab.end()) || (charHTab.find(recieverID) == charHTab.end())) return -1;
    if (charItArr[giverIdx]->point < point) return -1;
    
    character giverTmp = *charItArr[giverIdx]; giverTmp.tick = tick; giverTmp.point -= point;

    int giverUserIdx = charItArr[giverIdx]->userIdx;
    int giverServerIdx = charItArr[giverIdx]->serverIdx;
    hist[giverUserIdx][giverServerIdx].erase(charItArr[giverIdx]);
    hist[giverUserIdx][giverServerIdx].insert(hist[giverUserIdx][giverServerIdx].begin(), giverTmp);
    
    character recieverTmp = *charItArr[recieverIdx]; recieverTmp.tick = tick; recieverTmp.point += point;

    int recieverUserIdx = charItArr[recieverIdx]->userIdx;
    int recieverServerIdx = charItArr[recieverIdx]->serverIdx;
    hist[recieverUserIdx][recieverServerIdx].erase(charItArr[recieverIdx]);
    hist[recieverUserIdx][recieverServerIdx].insert(hist[recieverUserIdx][recieverServerIdx].begin(), recieverTmp);

    return hist[recieverUserIdx][recieverServerIdx].begin()->point;
}

int numToName(int tick, int giverID, char recieverName[MAXLEN], int point) {
    int giverIdx = charHTab[giverID];
    int recieverIdx = userHTab[recieverName];
    if ((charHTab.find(giverID) == charHTab.end()) || (userHTab.find(recieverName) == userHTab.end())) return -1;
    if (charItArr[giverIdx]->point < point) return -1;

    pq.clear();

    for (int i = 0; i < MAX_CNT_SERVER; i++) {
        if (hist[recieverIdx][i].size()) {
            auto it = hist[recieverIdx][i].begin();
            pq.insert({ it->tick, it->recentAction });
        }
    }

    auto it = pq.begin();

    
    charItArr[giverIdx]->tick = tick;
    charItArr[recieverIdx]->tick = tick;

    charItArr[giverIdx]->point -= point;
    charItArr[recieverIdx]->point += point;


    return charItArr[recieverIdx]->point;
}

void payBonusPoint(int tick, char serverName[MAXLEN], int point) {
    pq.clear();
    int serverIdx = serverHTab[serverName];
    for (int i = 0; i < userCnt; i++) {
        if (hist[i][serverIdx].size()) {
            auto it = hist[i][serverIdx].begin();
            it->point += point;
            it->recentAction = RECV;
            it->tick = tick;
        }
    }
}