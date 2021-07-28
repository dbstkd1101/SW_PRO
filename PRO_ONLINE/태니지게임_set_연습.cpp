#ifndef NULL
#define NULL 0
#endif

#include <set>
#include <unordered_map>
#include <string>

using namespace std;

#define MAXLEN (5)
#define MAX_ID 100+3
#define MAX_CNT_SERVER 20
#define MAX_CNT_CREATE 30000+3

struct Data {
    int cId, tick, recentAction;
    bool operator<(const Data &a)const {
        return tick == a.tick ? recentAction > a.recentAction : tick > a.tick;
    }
};

set<Data> userArr[MAX_CNT_CREATE];
set<Data> findServerSet;

unordered_map<string, int> uHTab, sHTab;
int userCnt, serverCnt;

struct charac{
    int uIdx, sIdx, point;
    set<Data>::iterator pos;
}characArr[MAX_ID];

void userInit() {
    for (int i = 0; i < MAX_CNT_CREATE; i++) {
        userArr[i].clear();
    }
    uHTab.clear(); sHTab.clear();
    userCnt = serverCnt = 0;
    for (int j = 0; j < MAX_ID; j++) {
        characArr[j] = { 0, };
        //characArr[j].pos 초기화??
    }
}

void create(int tick, char userName[MAXLEN], char serverName[MAXLEN], int charID, int point) {
    if (uHTab.find(userName) == uHTab.end()) uHTab[userName] = ++userCnt;
    if (sHTab.find(serverName) == sHTab.end()) sHTab[serverName] = ++serverCnt;
    int uIdx = uHTab[userName], sIdx = sHTab[serverName];

    characArr[charID] = { uIdx, sIdx, point };
    characArr[charID].pos = userArr[uIdx].insert({ charID, tick, 0 }).first;
}

int destroy(int tick, int charID) {
    int rstPoint = characArr[charID].point;
    //삭제여부 기록

    userArr[characArr[charID].uIdx].erase((characArr[charID].pos));
    characArr[charID].uIdx = 0;
    characArr[charID].sIdx = 0;
    characArr[charID].point = 0;

    return rstPoint;
}

int updateData(int giverID, int recieverID, int point, int tick) {
    int rst = -1;
    characArr[giverID].point -= point;
    Data giverDataTmp = *characArr[giverID].pos;
    giverDataTmp.tick = tick;
    giverDataTmp.recentAction = 0;
    userArr[characArr[giverID].uIdx].erase(characArr[giverID].pos);
    characArr[giverID].pos = userArr[characArr[giverID].uIdx].insert(giverDataTmp).first;

    characArr[recieverID].point += point;
    Data recieverDataTmp = *characArr[recieverID].pos;
    recieverDataTmp.tick = tick;
    recieverDataTmp.recentAction = 1;
    userArr[characArr[recieverID].uIdx].erase(characArr[recieverID].pos);
    characArr[recieverID].pos = userArr[characArr[recieverID].uIdx].insert(recieverDataTmp).first;

    return characArr[recieverID].point;
}

int numToNum(int tick, int giverID, int recieverID, int point) {
    if (!characArr[giverID].uIdx) return -1;
    if (!characArr[recieverID].uIdx) return -1;
    if (!characArr[giverID].point<point) return -1;

    return updateData(giverID, recieverID, point, tick);
}

int numToName(int tick, int giverID, char recieverName[MAXLEN], int point) {
    if (!characArr[giverID].uIdx) return -1;
    if (uHTab.find(recieverName) == uHTab.end()) return -1;
    if (characArr[giverID].point < point) return -1;

    int recieverID = userArr[uHTab[recieverName]].begin()->cId;

    return updateData(giverID, recieverID, point, tick);;
}

void payBonusPoint(int tick, char serverName[MAXLEN], int point) {
    findServerSet.clear();
    int sIdx = sHTab[serverName];
    
    for (int i = 0; ; i++) {
        for (int j = 1; j <= userCnt; j++) {
            if (i < userArr[j].size()) {
                if (characArr[next(userArr[j].begin(), i)->cId].sIdx == sIdx) {
                    Data temp = *next(userArr[j].begin(), i);
                    findServerSet.insert(temp);
                }
            }
            if (findServerSet.size() > 0) {
                characArr[findServerSet.begin()->cId].point += point;
                auto it5=characArr[findServerSet.begin()->cId].pos;
                //(*it).tick = 1;
                //(*it5).tick = tick;
                
                return;
            }
        }
    }
}
