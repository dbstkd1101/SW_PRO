#ifndef NULL
#define NULL 0
#endif

#include <list>
#include <unordered_map>
using namespace std;

const int LN = (int)1e4 + 3;

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
	(_it->delta) += _fearIndex;
	(_it->fearSum) += _fearIndex;
	if ((_it->pIdx)!=-1) {
		updateFear(itArr[_it->pIdx], _fearIndex);
	}
}

//자기 자신부터
int downUpdateFear(list<node>::iterator _it, int _iAmount) {
	if (_it->children.size() == 0) {
		(_it->delta) += _iAmount;
		(_it->fearSum) += _iAmount;
		return _iAmount;
	}
	
	int sum = 0;
	for (auto it = _it->children.begin(); it!= _it->children.end(); it++) {
		sum+=downUpdateFear(it, _iAmount);
	}
	(_it->delta) += sum;
	(_it->fearSum) += sum;
	return sum;
}

int enlist(int id, int teamID, int fearIndex) {
	nodeAdrr[id] = nCnt++;
	if (fearIndex) solCnt++;

	list<node>::iterator it = itArr[nodeAdrr[teamID]]->children.end();
		
	itArr[nodeAdrr[id]] = (itArr[nodeAdrr[teamID]]->children).insert(it, { nodeAdrr[id], nodeAdrr[teamID], fearIndex, 0, 0 });
	updateFear(itArr[nodeAdrr[teamID]], fearIndex);
	
	return itArr[nodeAdrr[teamID]]->fearSum;
}
int move(int id, int teamID) {
	int idx = nodeAdrr[id];
	int tIdx = nodeAdrr[teamID];
	
	updateFear(itArr[itArr[idx]->pIdx], (-1)*((itArr[idx]->delta)+ (itArr[idx]->fearIndex)));
	

	list<node>::iterator toIt;
	if (itArr[tIdx]->children.size() == 0) {
		toIt= itArr[tIdx]->children.begin();
	}
	else {
		toIt = itArr[tIdx]->children.end();
		toIt--;
	}
	// 음..insert가 아닌 splice는 from it가 옮길 직전 element이여야 하나봐.
	itArr[tIdx]->children.splice(toIt, itArr[itArr[idx]->pIdx]->children, itArr[idx]);
	itArr[idx]->pIdx = tIdx;
	updateFear(itArr[itArr[idx]->pIdx], (itArr[idx]->delta)+(itArr[idx]->fearIndex));

	return itArr[tIdx]->fearSum;
}
int infect(int id) {
	if (!solCnt) return 0;

	int idx = nodeAdrr[id];
	int iAmount=((itArr[0]->fearSum) / solCnt);

	downUpdateFear(itArr[idx], iAmount);

	return 0;
}
int cure(int id) {
	return 0;
}
int discharge(int id) {
	return 0;
}