#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <set>

#define MAX_USER_CNT 10000+3

using namespace std;
using ull=unsigned long long;

struct minHash {
    int aId, bId;
};

struct chat{
    minHash abId; 
    int state, cnt;
    deque<string> msgQ;
};

struct MyHash {
    size_t operator()(const minHash &a) const {
        return min(a.aId, a.bId)*(ull)1e10+ max(a.aId, a.bId);
    }
};

struct MyEqual {
    bool operator()(const minHash& a, const minHash& b) const{
        return (min(a.aId, a.bId) == min(b.aId, b.bId)) && (max(a.aId, a.bId) == max(b.aId, b.bId));
    }
};

int userCnt;
unordered_map<int, int> idHash;
unordered_map<minHash, chat, MyHash, MyEqual > chatHash;

unordered_set<int> userHist[MAX_USER_CNT];

struct talkPartner{
    int state, msgCnt, id;
};

struct talkPartnerLess {
    bool operator()(const talkPartner& a, const talkPartner& b) const {
        if (a.state > b.state) return true;
        if (a.state < b.state) return false;
        if (a.state == b.state) {
            if (a.msgCnt > b.msgCnt) return true;
            if (a.msgCnt < b.msgCnt) return false;
            if (a.msgCnt == b.msgCnt) {
                if (a.id < b.id) return true;
                if (a.id > b.id) return false;
            }
        }
    }
};

set<talkPartner, talkPartnerLess > talkPartnerPQ;


struct user {
    int id, state;
}userArr[MAX_USER_CNT];


ull getHash(int _aid, int _bid) {
    ull aid = _aid, bid = _bid;
    return ((_aid << 30) | _bid);
}

void init() {
    userCnt = 0;
    idHash.clear();
    chatHash.clear();

    for (int i = 0; i < MAX_USER_CNT; i++) {
        userHist[i].clear();
        userArr[i] = { 0, };
    }
}
void makeOnOff(int aid, int state) {
    if (idHash.find(aid) == idHash.end()) idHash[aid] = ++userCnt;
    userArr[idHash[aid]] = { aid, state };
}
void meetBreak(int aid, int bid, int state) {
    if (idHash.find(bid) == idHash.end()) makeOnOff(bid, 0);
    
    int aIdx = idHash[aid];
    int bIdx = idHash[bid];

    if (state == 0) {
        chatHash[{ aid, bid }].msgQ.clear();
        chatHash[{ aid, bid }].cnt = 0;

        int eraseRstB=userHist[aIdx].erase(bIdx);
        int eraseRstA=userHist[bIdx].erase(aIdx);
    }
    if (state == 1) {
        userHist[aIdx].insert(bIdx);
        userHist[bIdx].insert(aIdx);
    }

    if (chatHash.find({ aid, bid }) == chatHash.end()) chatHash[{ aid, bid }] = { aid , bid, 0, 0 };
    chatHash[{ aid, bid }].state = state;
    
}
void sendTalk(int aid, int bid, char talk[21]) {
    int aIdx = idHash[aid];
    int bIdx = idHash[bid];

    userHist[aIdx].insert(bIdx);
    userHist[bIdx].insert(aIdx);

    while (chatHash[{ aid, bid }].msgQ.size() >= 5) {
        chatHash[{ aid, bid }].msgQ.pop_front();
    }
    chatHash[{ aid, bid }].msgQ.push_back(string(talk));
    chatHash[{ aid, bid }].cnt++;
}
int getTalkList(int aid, int bid, char userTalkList[5][21]) {
    if (chatHash.find({ aid, bid }) == chatHash.end()) return 0;
    int rst = min(chatHash[{ aid, bid }].cnt, 5);

    int i = 0;
    for (auto it = chatHash[{ aid, bid }].msgQ.rbegin(); i<rst&&it != chatHash[{ aid, bid }].msgQ.rend(); it++, i++) {
        int j;
        for (j = 0; j < it->size(); j++) {
            userTalkList[i][j] = it->at(j);
        }
        userTalkList[i][j] = 0;
    }
    
    return rst;
}
int getTalkPartnerList(int aid, int userPartnerList[5]) {
    talkPartnerPQ.clear();

    int aIdx = idHash[aid];
    for (auto it = userHist[aIdx].begin(); it != userHist[aIdx].end(); it++) {
        if (aid == 333) {
            int a = 1;
        }
        int bid = userArr[*it].id;
        int bIdx = idHash[bid];
        talkPartner tmp = { userArr[bIdx].state, chatHash[{ aid, bid }].cnt, bid };
        bool isInsert=talkPartnerPQ.insert(tmp).second;
        int b = 1;
    }

    int outputCnt = min((int)talkPartnerPQ.size(), 5);
    int i = 0;
    for (auto it = talkPartnerPQ.begin(); i < outputCnt && it != talkPartnerPQ.end(); it++, i++) {
        userPartnerList[i] = it->id;
    }

    return outputCnt;
}
