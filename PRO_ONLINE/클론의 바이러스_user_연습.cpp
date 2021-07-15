#ifndef NULL
#define NULL 0
#endif

#include <list>
#include <unordered_map>
using namespace std;

const int LN = 1e4 + 3;

struct node {
	int idx, pIdx, fearIndex, delta;
	int fearSum;
	list<node> children;
};

list<node>::iterator itArr[LN];

list<node> map;
unordered_map<int, int> nodeAdrr(LN);
int nCnt, solCnt;

void init() {
	nCnt = solCnt = 0;
	map.clear();
	nodeAdrr.clear();

	nodeAdrr[10000] = nCnt++;
	itArr[nodeAdrr[10000]] = map.insert(map.begin(), { nodeAdrr[10000], -1, 0, 0, 0 });
}

void updateFear(list<node>::iterator _it, int _fearIndex) {
	_it->delta += _fearIndex;
	_it->fearSum += _fearIndex;
	if (_it->pIdx!=-1) {
		updateFear(itArr[nodeAdrr[_it->pIdx]], _fearIndex);
	}
}

int enlist(int id, int teamID, int fearIndex) {
	nodeAdrr[id] = nCnt++;
	list<node> childTmp = itArr[nodeAdrr[teamID]]->children;
	
	list<node>::iterator it;
	if (childTmp.size() == 0) {
		it = childTmp.begin();
	}
	else {
		it = childTmp.end();
		it--;
	}
	node tmp = { nodeAdrr[id], nodeAdrr[teamID], fearIndex, 0, 0 };

	//itArr[nodeAdrr[id]]=itArr[nodeAdrr[teamID]]->children.insert(it, tmp);
	childTmp.insert(it, tmp);

	updateFear(itArr[nodeAdrr[teamID]], fearIndex);

	return itArr[nodeAdrr[teamID]]->fearSum;
}
int move(int id, int teamID) {
	return 0;
}
int infect(int id) {
	return 0;
}
int cure(int id) {
	return 0;
}
int discharge(int id) {
	return 0;
}