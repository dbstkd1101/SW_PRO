/*
* ÀÚ·á ÀúÀå _ stl set
*/
#include<algorithm>
#include<set>
#include<unordered_map>
#include<string.h>
using namespace std;
#define MAXLEN (5)

int ucnt, scnt;
unordered_map<string, int> utab, stab;

struct Data {
    int id, tick, recieved;
    bool operator<(const Data& r) const {
        return tick != r.tick ? tick > r.tick : recieved > r.recieved;
    }
};

struct Character {
    int sid, uid, point;
    set<Data>::iterator it;
}cha[100003];

set<Data> user[30003];

void userInit() {
    for (int i = 1; i <= ucnt; i++) user[i].clear();
    ucnt = scnt = 0;
    memset(cha, 0, sizeof(cha));
    utab.clear(), stab.clear();
}

void create(int tick, char userName[MAXLEN], char serverName[MAXLEN], int charID, int point) {
    int uid = utab[userName];
    if (!uid) utab[userName] = uid = ++ucnt;

    int sid = stab[serverName];
    if (!sid) stab[serverName] = sid = ++scnt;

    cha[charID] = { sid, uid, point };
    cha[charID].it = user[uid].insert({ charID, tick, 0 }).first;
}

int destroy(int tick, int charID) {
    auto& p = cha[charID].it;
    user[cha[charID].uid].erase(p);
    cha[charID].uid = 0;
    return cha[charID].point;
}

int exchange(int src, int dest, int point, int tick) {
    if (!cha[src].uid || !cha[dest].uid || cha[src].point < point) return -1;

    cha[src].point -= point;
    cha[dest].point += point;

    user[cha[src].uid].erase(cha[src].it);
    user[cha[dest].uid].erase(cha[dest].it);

    cha[src].it = user[cha[src].uid].insert({ src, tick, 0 }).first;
    cha[dest].it = user[cha[dest].uid].insert({ dest, tick, 1 }).first;

    return cha[dest].point;
}

int numToNum(int tick, int giverID, int recieverID, int point) {
    return exchange(giverID, recieverID, point, tick);
}

int numToName(int tick, int giverID, char recieverName[MAXLEN], int point) {
    int uid = utab[recieverName];
    if (!uid || user[uid].empty()) return -1;
    return exchange(giverID, user[uid].begin()->id, point, tick);
}

void payBonusPoint(int tick, char serverName[MAXLEN], int point) {
    int sid = stab[serverName];
    for (int i = 1; i <= ucnt; i++) {
        for (auto& c : user[i]) {
            int cid = c.id;
            if (cha[cid].sid == sid) {
                cha[cid].point += point;
                user[i].erase(cha[cid].it);
                cha[cid].it = user[i].insert({ cid, tick, 0 }).first;
                break;
            }
        }
    }
}