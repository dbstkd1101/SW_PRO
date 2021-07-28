/* ´Ü¸»³ëµå °³¼ö¼¼±â _ vector */
#include<string.h>
#include<algorithm>
#include<unordered_map>
#include<list>
using namespace std;
using pii = pair<int, int>;

const int LM = 10003;

int idcnt;
unordered_map<string, int> htab(LM);
list<pii> edge[LM];   // subid, cnt

void init()
{
    for (int i = 0; i <= idcnt; i++) edge[i].clear();
    idcnt = 0;
    htab.clear();
}

int getId(char str[]) {
    if (!htab[str]) htab[str] = ++idcnt;
    return htab[str];
}

auto findId(int id, int subid) {    // iterator ¹ÝÈ¯
    for (auto it = edge[id].begin(); it != edge[id].end(); ++it)
        if (it->first == subid) return it;
    return edge[id].end();
    //return find_if(edge[id].begin(), edge[id].end(), [&](auto x) { return x.first == subid; });
}

void addSub(char mNode[], int mCnt, char mSubNode[][7])
{
    int id = getId(mNode);
    for (int i = 0; i < mCnt; i++) {
        int subid = getId(mSubNode[i]);
        auto it = findId(id, subid);
        if (it == edge[id].end()) edge[id].push_back({ subid, 1 });
        else it->second++;
    }
}

void eraseSub(char mNode[], char mSubNode[])
{
    int id = getId(mNode);
    int subid = getId(mSubNode);
    auto it = findId(id, subid);
    it->second--;
    if (!it->second) edge[id].erase(it); // edge[id].erase(it) : O(n)
}

int changeSub(char mNode[], char mSubA[], char mSubB[])
{
    int id = getId(mNode);
    int ida = getId(mSubA);
    int idb = getId(mSubB);
    auto ita = findId(id, ida);
    auto itb = findId(id, idb);
    int ret = ita->second;
    if (itb != edge[id].end()) {
        itb->second += ita->second;
        edge[id].erase(ita);
    }
    else ita->first = idb;
    return ret;
}

int leaf[LM];
int dfs(int id) {
    if (leaf[id]) return leaf[id];
    if (edge[id].empty()) return leaf[id] = 1;
    int cnt = 0;
    for (auto& x : edge[id]) cnt += dfs(x.first) * x.second;
    return leaf[id] = cnt;
}

int countLeaf(char mNode[])
{
    memset(leaf, 0, sizeof(leaf));
    return dfs(getId(mNode));
}