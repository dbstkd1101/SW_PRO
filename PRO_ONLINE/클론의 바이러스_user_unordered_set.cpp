#include<unordered_set>
#include<unordered_map>
using namespace std;

const int LM = 10003;
unordered_set<int> chart[LM];
unordered_map<int, int> htab;
int fear[LM], curFear[LM], parent[LM], idcnt;
int total, cnt;

int getId(int x) {
	if (!htab[x]) return htab[x] = ++idcnt;
	return htab[x];
}

void init() {
	htab.clear();
	for (int i = 1; i <= idcnt; i++) chart[i].clear();
	htab[10000] = idcnt = 1;
	total = cnt = 0;
}

int delta;
int dfs(int x, int cmd = 0) {
	if (cmd == 1 && fear[x]) curFear[x] += delta, total += delta;
	if (cmd == 2 && fear[x]) total += (fear[x] - curFear[x]), curFear[x] = fear[x];
	if (cmd == 3 && fear[x]) total -= curFear[x], cnt--;
	int sum = curFear[x];
	for (auto y : chart[x]) sum += dfs(y, cmd);
	return sum;
}

int enlist(int id, int teamID, int fearIndex) {
	id = getId(id), teamID = getId(teamID);
	chart[teamID].insert(id);
	curFear[id] = fear[id] = fearIndex;
	parent[id] = teamID;
	total += fearIndex;
	if (fearIndex) cnt++;
	return dfs(teamID);
}

int move(int id, int teamID) {
	id = getId(id), teamID = getId(teamID);
	chart[teamID].insert(id);
	chart[parent[id]].erase(id);
	parent[id] = teamID;
	return dfs(teamID);
}

int infect(int id) {
	if (cnt) delta = total / cnt;
	return dfs(getId(id), 1);
}
int cure(int id) {
	return dfs(getId(id), 2);
}
int discharge(int id) {
	id = getId(id);
	chart[parent[id]].erase(id);
	return dfs(id, 3);
}