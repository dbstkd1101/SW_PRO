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

void updateFear(list<node>::iterator _it, int _fearIndex, int _delta, int _passFear) {
	(_it->fearSum) += (_fearIndex+ _delta + _passFear);
	(_it->delta) += (_delta);
	if ((_it->pIdx)!=-1) {
		updateFear(itArr[_it->pIdx], _fearIndex, _delta, _passFear);
	}
}

//자기 자신부터
int downUpdateFear(list<node>::iterator _it, int _iAmount) {
	if (_it->children.size() == 0 && (_it->fearIndex)) {
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

int downResetFear(list<node>::iterator _it) {
	if (_it->children.size() == 0 && (_it->fearIndex)) {
		int deltaTmp = (_it->delta);
		(_it->delta) = 0;;
		(_it->fearSum) = (_it->fearIndex);
		return deltaTmp;
	}

	int sum = 0;
	for (auto it = _it->children.begin(); it != _it->children.end(); it++) {
		sum += downResetFear(it);
	}
	(_it->delta) -= sum;
	(_it->fearSum) -= sum;
	
	int deltaTmp = (_it->delta);
	(_it->delta) = 0;
	return sum + deltaTmp;

}

int countSoldier(list<node>::iterator _it) {
	if ((_it->children.size() == 0) && (_it->fearIndex)){
		return 1;
	}
	int sum = 0;
	for (auto it = _it->children.begin(); it != _it->children.end(); it++) {
		sum += countSoldier(it);
	}
	return sum;
}

int cmdAdd(int id, int teamID, int fearIndex) {
	nodeAdrr[id] = nCnt++;
	if (fearIndex) solCnt++;

	list<node>::iterator it = itArr[nodeAdrr[teamID]]->children.end();
		
	itArr[nodeAdrr[id]] = (itArr[nodeAdrr[teamID]]->children).insert(it, { nodeAdrr[id], nodeAdrr[teamID], fearIndex, 0, fearIndex });
	updateFear(itArr[nodeAdrr[teamID]], fearIndex, 0, 0);
	
	return itArr[nodeAdrr[teamID]]->fearSum;
}
int cmdMove(int id, int teamID) {
	int idx = nodeAdrr[id];
	int tIdx = nodeAdrr[teamID];
	if (itArr[idx]->pIdx != -1)	updateFear(itArr[itArr[idx]->pIdx], (-1)*(itArr[idx]->fearIndex), (-1)* (itArr[idx]->delta), (-1)*((itArr[idx]->fearSum) - (itArr[idx]->delta) - (itArr[idx]->fearIndex)));
	

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
	if (itArr[idx]->pIdx != -1)	updateFear(itArr[itArr[idx]->pIdx], (itArr[idx]->fearIndex), (itArr[idx]->delta), ((itArr[idx]->fearSum) - (itArr[idx]->delta) - (itArr[idx]->fearIndex)));

	return itArr[tIdx]->fearSum;
}
int cmdInfect(int id) {
	if (!solCnt) return 0;

	int idx = nodeAdrr[id];
	int iAmount=((itArr[0]->fearSum) / solCnt);
	int changedAmount = downUpdateFear(itArr[idx], iAmount);
	if(itArr[idx]->pIdx!=-1) updateFear(itArr[itArr[idx]->pIdx], 0, changedAmount, 0);

	return itArr[idx]->fearSum;
}
int cmdRecover(int id) {
	int idx = nodeAdrr[id];
	int changedAmount = downResetFear(itArr[idx]);
	int rst = itArr[idx]->fearSum;
	if (itArr[idx]->pIdx != -1) updateFear(itArr[itArr[idx]->pIdx], 0, ((-1) * changedAmount), 0);

	return rst;
}
int cmdRemove(int id) {
	int rst = 0;
	int idx = nodeAdrr[id];
	rst = itArr[idx]->fearSum;

	if(idx!=0) updateFear(itArr[itArr[idx]->pIdx], (-1) * (itArr[idx]->fearIndex), (-1) * (itArr[idx]->delta), ((itArr[idx]->fearSum) - (itArr[idx]->delta) - (itArr[idx]->fearIndex)));
	int removedSolCnt = countSoldier(itArr[idx]);
	solCnt -= removedSolCnt;

	if (idx != 0) auto it=itArr[itArr[idx]->pIdx]->children.erase(itArr[idx]);
	else {
		for (auto it = itArr[idx]->children.begin(); it != itArr[idx]->children.end(); it++) {
			itArr[idx]->children.erase(it);
		}
	}

	return rst;
}