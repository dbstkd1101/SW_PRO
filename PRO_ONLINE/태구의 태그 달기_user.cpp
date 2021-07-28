#include <string>
#include <unordered_map>
#include <set>

using namespace std;

const int PN = 10000+3;


unordered_multimap<string, int> tagHash;
unordered_map<int, int> idHash;
set<pair<int, int>> searchSetAsc;
set<pair<int, int>, greater<pair<int, int>>> searchSetDsc;

int pCnt;

struct product {
    int id, price;
    bool isExist;
}pArr[PN];

void init() {
    pCnt = 0;
    tagHash.clear();

    for (int i = 0; i < PN; i++) {
        pArr[i] = { 0, };
    }
}

void incoming(int pid, int price, int tagCnt, char tagString[][11]) {

    pArr[pCnt] = { pid, price, true };

    for (int i = 0; i < tagCnt; i++) {
        tagHash.insert({ tagString[i], pCnt });
    }
    idHash[pid] = pCnt;

    pCnt++;
}

int search(int tagCnt, char tagString[][11], int maxCnt, bool flag, int idList[]) {
    searchSetAsc.clear();
    searchSetDsc.clear();
    int rst=0;
    for (int i = 0; i < tagCnt; i++) {
        auto range = tagHash.equal_range(tagString[i]);
        for (auto it = range.first; it != range.second; it++) {
            if (pArr[it->second].isExist) {
                if (flag == true) searchSetDsc.insert({ pArr[it->second].price, it->second });
                else searchSetAsc.insert({ pArr[it->second].price, it->second });
            }
        }
    }

    if (flag == true) {
        int j = 0;
        for (auto it = searchSetDsc.begin(); j < maxCnt || it != searchSetDsc.end(); j++, it++) {
            idList[j] = it->second;
            searchSetDsc.erase({ it->first, it->second });
            rst++;
        }
    }

    else {
        int j = 0;
        for (auto it = searchSetAsc.begin(); j < maxCnt || it != searchSetAsc.end(); j++, it++) {
            idList[j] = it->second;
            searchSetAsc.erase({ it->first, it->second });
            rst++;
        }
    }

    return rst;
}

int sell(int pid) {

    auto it = idHash.find(pid);
    int idx;
    if (it == idHash.end()) return 0;
    else {
        idx = idHash[pid];
        idHash.erase(it);
    }

    if (pArr[idx].isExist == false) return 0;
    else pArr[idx].isExist = false;    

    return 0;
}