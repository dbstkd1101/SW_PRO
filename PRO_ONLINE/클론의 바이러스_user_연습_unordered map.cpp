#include <unordered_set>
#include <unordered_map>
using namespace std;

const int LN = (int)1e4 + 3;

enum CMD{
	DOWN_SUM = 0, 
	DOWN_INFECT,
	DOWN_CURE, 
	DOWN_CNT,
};

struct node{
	int idx, pIdx;
	int initFear, infectedFear;
	unordered_set<int> chlidren;
}nodeArr[LN];

int nCnt;
int solCnt;

unordered_map<int, int> hTab;

int dfs(node & _Node, CMD cmd, int param) {
	int sum = 0;
	if (cmd == DOWN_SUM) {
		if (_Node.chlidren.size() == 0) {
			if (_Node.initFear) {
				return (_Node.initFear + _Node.infectedFear);
			}
		}
		else {
			for (auto x : _Node.chlidren) {
				sum += dfs(nodeArr[x], DOWN_SUM, 0);
			}
		}
	}
	if (cmd == DOWN_INFECT) {
		if (_Node.chlidren.size() == 0) {
			if (_Node.initFear) {
				_Node.infectedFear += param;
				return 0;
			}
		}
		else {
			for (auto x : _Node.chlidren) dfs(nodeArr[x], DOWN_INFECT, param);
		}
	}
	if (cmd == DOWN_CURE) {
		if (_Node.chlidren.size() == 0) {
			if (_Node.initFear) {
				_Node.infectedFear =0;
				return 0;
			}
		}
		else {
			for (auto x : _Node.chlidren) dfs(nodeArr[x], DOWN_CURE, 0);
		}
	}
	if (cmd == DOWN_CNT) {
		if (_Node.chlidren.size() == 0) {
			if (_Node.initFear) {
				return ++sum;
			}
		}
		else {
			for (auto x : _Node.chlidren) sum += dfs(nodeArr[x], DOWN_CNT, 0);
		}
	}
	return sum;
}

void init() {
	nCnt = solCnt = 0;

	for (int i = 0; i < LN; i++) {
		nodeArr[i] = {0};
		nodeArr[i].chlidren.clear();
	}
	hTab.clear();
	hTab[10000] = nCnt;

	nodeArr[hTab[10000]] = { nCnt++, -1, 0, 0 };
}

int cmdAdd(int newID, int pID, int fileSize) {
	int idx = hTab[newID] = nCnt++;
	int pIdx = hTab[pID];

	nodeArr[pIdx].chlidren.insert(idx);
	nodeArr[idx] = { idx, pIdx, fileSize, 0 };
	if (fileSize) solCnt++;
	int sum = dfs(nodeArr[pIdx], DOWN_SUM, 0);

	return sum;
}

int cmdMove(int tID, int pID) {
	int idx = hTab[tID];
	int pIdx = hTab[pID];

	nodeArr[nodeArr[idx].pIdx].chlidren.erase(idx);
	nodeArr[pIdx].chlidren.insert(idx);
	//아래 부분 놓치는 실수
	nodeArr[idx].pIdx = pIdx;

	int sum = dfs(nodeArr[pIdx], DOWN_SUM, 0);

	return sum;
}

int cmdInfect(int tID) {
	if (solCnt == 0) return 0;
	int idx = hTab[tID];
	int pIdx = nodeArr[idx].pIdx;
	
	int sum = dfs(nodeArr[0], DOWN_SUM, 0);
	int infectAmt = (sum) / solCnt;

	dfs(nodeArr[idx], DOWN_INFECT, infectAmt);

	int rst=dfs(nodeArr[idx], DOWN_SUM, 0);

	return rst;
}

int cmdRecover(int tID) {
	int idx = hTab[tID];
	int pIdx = nodeArr[idx].pIdx;

	dfs(nodeArr[idx], DOWN_CURE, 0);

	int rst= dfs(nodeArr[idx], DOWN_SUM, 0);

	return rst;
}

int cmdRemove(int tID) {
	int idx = hTab[tID];
	int pIdx = nodeArr[idx].pIdx;

	int rst = dfs(nodeArr[idx], DOWN_SUM, 0);
	int changedSolCnt = dfs(nodeArr[idx], DOWN_CNT, 0);
	solCnt -= changedSolCnt;

	if(idx!=0) nodeArr[pIdx].chlidren.erase(idx);
	else {
		for (auto x : nodeArr[0].chlidren) { 
			nodeArr[0].chlidren.erase(x);
		}
	}
	return rst;
}
