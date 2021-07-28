/* stl map */
#include<algorithm>
#include<map>
#include<string.h>
#include<string>
#include<unordered_map>
using namespace std;
#define MAXLEN (5)

struct Character {
    int sid, uid, point;
    map<int, int>::iterator pos;
}cha[100003];

int ucnt, scnt;
unordered_map<string, int> utab, stab;

map<int, int> user[30003]; // first: priority , second: character id
                           // priority는 default tick*2, reciever의 경우 tick*2+1
                           // reciever와 giver의 차이를 두기 위해
void userInit() {
    for (int i = 1; i <= ucnt; i++) user[i].clear();
    ucnt = 0;
    memset(cha, 0, sizeof(cha));
    utab.clear(), stab.clear();
}

void create(int tick, char userName[MAXLEN], char serverName[MAXLEN], int charID, int point) {
    int uid = utab[userName];
    if (!uid) utab[userName] = uid = ++ucnt;

    int sid = stab[serverName];
    if (!sid) stab[serverName] = sid = ++scnt;

    cha[charID] = { sid, uid, point };
    cha[charID].pos = user[uid].insert({ tick * 2, charID }).first;
}

int destroy(int tick, int charID) {
    auto& p = cha[charID].pos;
    user[cha[charID].uid].erase(p);
    cha[charID].uid = 0;
    return cha[charID].point;
}

int exchange(int src, int dest, int point, int tick) {
    if (!cha[src].uid || !cha[dest].uid || cha[src].point < point) return -1;

    cha[src].point -= point;
    cha[dest].point += point;

    user[cha[src].uid].erase(cha[src].pos);
    user[cha[dest].uid].erase(cha[dest].pos);

    cha[src].pos = user[cha[src].uid].insert({ tick * 2, src }).first;
    cha[dest].pos = user[cha[dest].uid].insert({ tick * 2 + 1, dest }).first;

    return cha[dest].point;
}

int numToNum(int tick, int giverID, int recieverID, int point) {
    return exchange(giverID, recieverID, point, tick);
}

int numToName(int tick, int giverID, char recieverName[MAXLEN], int point) {
    int uid = utab[recieverName];
    if (!uid || user[uid].empty()) return -1;
    return exchange(giverID, user[uid].rbegin()->second, point, tick);
}

void payBonusPoint(int tick, char serverName[MAXLEN], int point) {
    int sid = stab[serverName];
    for (int i = 1; i <= ucnt; i++) {
        for (auto it = user[i].rbegin(); it != user[i].rend(); ++it) {
            int cid = it->second;
            if (cha[cid].sid == sid) {
                cha[cid].point += point;
                user[i].erase(cha[cid].pos);
                cha[cid].pos = user[i].insert({ tick * 2, cid }).first;
                break;
            }
        }
    }
}