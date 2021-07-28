#include <map>
#include <list>
#include <set>
#include <deque>
#include <unordered_map>
using namespace std;

const int LU = 1e4 + 3;
const int LM = 1e1 + 3;
const int LK = 1e5 + 3;

unordered_map<int, int> htab;

int n, m, capa;
int NCnt;
int tick;

struct oNode {
    int uIdx, mid, t;
};

list<pair<int, int>> userHist[LU][LM];
deque<oNode> allHist;

set<pair<int, int>, less<pair<int, int>>> timeAsc;

struct myGreater {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {
        return (a.first == b.first) ? a.second < b.second : a.first > b.first;
    }
};
set<pair<int, int>, myGreater> timeDsc;

void init(int N, int M, int K, int idList[]) {
    n = N, m = M, capa = K;
    tick = NCnt = 0;
    htab.clear();
    for (int i = 0; i < N; i++) {
        htab[idList[i]] = NCnt++;
    }
    for (int i = 0; i < LU; i++) {
        for (int j = 0; j < LM; j++) {
            userHist[i][j].clear();
        }
    }
    allHist.clear();
}
void order(int uid, int mid) {
    int userIdx = htab[uid];
    tick++;
    //push_back의 size가 capa와 같을 경우 front pop, 
    if (allHist.size() >= capa) {
        oNode front = allHist.front();
        userHist[front.uIdx][front.mid].erase(userHist[front.uIdx][front.mid].begin());
        allHist.pop_front();
    }
    allHist.push_back({ userIdx, mid, tick });
    userHist[userIdx][mid].push_back({ tick, mid });
}

int getRecentlyMenu(int uid, int retList[]) {
    int userIdx = htab[uid];
    timeDsc.clear();

    for (int i = 1; i <= m; i++) {
        if (userHist[userIdx][i].size() > 0) {
            auto it = (--userHist[userIdx][i].end());
            timeDsc.insert(*it);
        }
    }
    int j = 0;
    for (auto it = timeDsc.begin(); it != timeDsc.end(); it++, j++) {
        retList[j] = it->second;
    }

    return j;
}
int getOldestMenu(int uid, int retList[]) {
    int userIdx = htab[uid];

    timeAsc.clear();
    for (int i = 1; i <= m; i++) {
        if (userHist[userIdx][i].size() > 0) {
            auto it = userHist[userIdx][i].begin();
            timeAsc.insert(*it);
        }
    }
    int j = 0;
    for (auto it = timeAsc.begin(); it != timeAsc.end(); it++, j++) {
        retList[j] = it->second;
    }

    return j;
}
void getMostOrdered(int uid, int retList[]) {
    int userIdx = htab[uid];
    timeDsc.clear();

    for (int i = 1; i <= m; i++) {
        int oCnt = userHist[userIdx][i].size();
        if (oCnt > 0) timeDsc.insert({ oCnt, i });
        else timeDsc.insert({ 0, i});
    }
    
    int j = 0;
    for (auto it = timeDsc.begin(); it != timeDsc.end(); it++, j++) {
        retList[j] = (it->second);
    }
}
void getMostOrderedAll(int retList[]) {
    timeDsc.clear();
    int cntArr[LM]{ 0, };
    for (auto it = allHist.begin(); it != allHist.end(); it++) {
        cntArr[it->mid]++;
    }

    for (int i = 1; i <= m; i++) {
        timeDsc.insert({ cntArr[i], i });
    }
    int j = 0;
    for (auto it = timeDsc.begin(); it != timeDsc.end(); it++, j++) {
        retList[j] = it->second;
    }
}