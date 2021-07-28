/*
단말노드개수세기 _ int unordered_map
노드별로 1부터 id부여
*/
#include<string.h>
#include<algorithm>
#include<unordered_map>
using namespace std;

const int LM = 10003;

int idcnt;
unordered_map<string, int> htab;
unordered_map<int, int> edge[LM];  // map<int,int> edge[LM]으로 구성하여도 문제없이 돌아간다(map header추가)

void init()
{
    htab.clear(), htab.reserve(LM);
    for (int i = 1; i <= idcnt; i++) edge[i].clear();
    idcnt = 0;
}

int getId(char str[]) {
    if (!htab[str]) htab[str] = ++idcnt;
    return htab[str];
}

void addSub(char mNode[], int mCnt, char mSubNode[][7])
{
    int id = getId(mNode);
    for (int i = 0; i < mCnt; i++) {
        int subid = getId(mSubNode[i]);
        edge[id][subid]++;
    }
}

void eraseSub(char mNode[], char mSubNode[])
{
    int id = getId(mNode);
    int subid = getId(mSubNode);
    int cnt = --edge[id][subid];
    if (!cnt) edge[id].erase(subid);
}

int changeSub(char mNode[], char mSubA[], char mSubB[])
{
    int id = getId(mNode);
    int ida = getId(mSubA);
    int idb = getId(mSubB);
    int ret = edge[id][ida];
    edge[id][idb] += ret;
    edge[id].erase(ida);
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