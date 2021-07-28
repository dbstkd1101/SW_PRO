#include<set>
#include<algorithm>
#include<string.h>
#include<unordered_map>
using namespace std;
using pii = pair<int, int>;
using ull = unsigned long long;

const int LM = 1e4 + 3;

struct Member {
    int id;
    bool state;
}member[LM];

struct Chat {
    int aidx, bidx;
    int cnt;
    char msg[6][21];
    void sendTalk(char talk[]) {
        strcpy(msg[cnt % 5], talk);
        cnt++;
    }
}chat[LM * 2];

int ccnt, mcnt;
unordered_map<ull, int> ctab, mtab; // chat table, member table
unordered_map<int, int> plist[LM];  // key: partner id, second: chat id

void init() {
    for (int i = 1; i <= mcnt; i++) plist[i].clear();
    ccnt = mcnt = 0;
    ctab.clear(), mtab.clear();
}

int getMemberIdx(int aid) {
    if (mtab[aid]) return mtab[aid];
    mtab[aid] = ++mcnt;
    member[mcnt] = { aid, 0 };
    return mcnt;
}

ull getKey(int aid, int bid) {
    if (aid > bid) swap(aid, bid);
    return aid * (ull)1e10 + bid;
}

void makeOnOff(int aid, int state) {
    int idx = getMemberIdx(aid);
    member[idx].state = state;
}

void meetBreak(int aid, int bid, int state) {
    ull key = getKey(aid, bid);
    int aidx = getMemberIdx(aid);
    int bidx = getMemberIdx(bid);
    if (state) {
        chat[++ccnt] = { aidx, bidx, 0 };
        ctab[key] = ccnt;
        plist[aidx].insert({ bidx, ccnt });
        plist[bidx].insert({ aidx, ccnt });
    }
    else {
        plist[aidx].erase(bidx);
        plist[bidx].erase(aidx);
        ctab.erase(key);
    }
}

void sendTalk(int aid, int bid, char talk[21]) {
    int idx = ctab[getKey(aid, bid)];
    chat[idx].sendTalk(talk);
}

int getTalkList(int aid, int bid, char userTalkList[5][21]) {
    int chatIdx = ctab[getKey(aid, bid)];
    int msgIdx = chat[chatIdx].cnt % 5;
    int n = min(chat[chatIdx].cnt, 5);
    for (int i = 0; i < n; i++) {
        msgIdx = (msgIdx + 4) % 5;
        strcpy(userTalkList[i], chat[chatIdx].msg[msgIdx]);
    }
    return n;
}

struct Partner {
    int state, cnt, id;
    bool operator<(const Partner& r) const {
        if (state != r.state) return state > r.state;
        if (cnt != r.cnt) return cnt > r.cnt;
        return id < r.id;
    }
};

int getTalkPartnerList(int aid, int userPartnerList[5]) {
    int aidx = getMemberIdx(aid);
    set<Partner> partner;
    for (auto& x : plist[aidx]) {
        partner.insert({ member[x.first].state, chat[x.second].cnt, member[x.first].id });
        if (partner.size() > 5) partner.erase(--partner.end());
    }

    int n = 0;
    for (auto p : partner) userPartnerList[n++] = p.id;
    return n;
}