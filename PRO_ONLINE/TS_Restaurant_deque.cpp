#include<unordered_map>
#include<deque>
#include<algorithm>
#include<string.h>
using namespace std;

const int LM = 10003;       // ��� ��
const int MLM = 13;         // �޴� ��

int n, m, capa;             // ��� ��, �޴� ��, ���� �뷮
int tick;                   // �ֹ� ����. order�ø��� 1�� ����
int orderCnt[LM][MLM];      // ȸ���� �޴��� �ֹ� Ƚ��(1~n), 0�� total

unordered_map<int, int> htab;
deque<int> member[LM][MLM];

struct Order {      // order ������ ������� ����
    int uid, mid;   // 1���� �ο��� ����� ��ȣ , mid
}orderInfo[LM * MLM];

void init(int N, int M, int K, int idList[]) {
    n = N, m = M, capa = K;
    tick = 0;
    memset(orderCnt, 0, sizeof(orderCnt));
    htab.clear(), htab.reserve(N);
    for (int i = 1; i <= n; i++) htab[idList[i - 1]] = i;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) member[i][j].clear();
}

void order(int uid, int mid) {
    uid = htab[uid];
    orderInfo[++tick] = { uid, mid };
    member[uid][mid].push_back(tick);
    orderCnt[0][mid]++;
    orderCnt[uid][mid]++;

    if (tick - capa > 0) {
        uid = orderInfo[tick - capa].uid, mid = orderInfo[tick - capa].mid;
        member[uid][mid].pop_front();
        orderCnt[0][mid]--;
        orderCnt[uid][mid]--;
    }
}

struct Data {
    int mid, prior;
    bool operator<(const Data& r) const {
        return prior != r.prior ? prior > r.prior : mid < r.mid;
    }
}d[MLM];

int getRecentlyMenu(int uid, int retList[]) {
    uid = htab[uid];
    int cnt = 0;
    for (int i = 1; i <= m; i++)
        if (member[uid][i].size()) d[cnt++] = { i, member[uid][i].back() };
    sort(d, d + cnt);
    for (int i = 0; i < cnt; i++) retList[i] = d[i].mid;
    return cnt;
}

int getOldestMenu(int uid, int retList[]) {
    uid = htab[uid];
    int cnt = 0;
    for (int i = 1; i <= m; i++)
        if (member[uid][i].size()) d[cnt++] = { i, -member[uid][i].front() };
    sort(d, d + cnt);
    for (int i = 0; i < cnt; i++) retList[i] = d[i].mid;
    return cnt;
}

void getMostOrdered(int uid, int retList[]) {
    uid = htab[uid];
    for (int i = 1; i <= m; i++) d[i - 1] = { i, orderCnt[uid][i] };
    sort(d, d + m);
    for (int i = 0; i < m; i++) retList[i] = d[i].mid;
}

void getMostOrderedAll(int retList[]) {
    for (int i = 1; i <= m; i++) d[i - 1] = { i, orderCnt[0][i] };
    sort(d, d + m);
    for (int i = 0; i < m; i++) retList[i] = d[i].mid;
}