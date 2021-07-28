#ifndef NULL
#define NULL 0
#endif 

#include <list>
#include <unordered_map>

const int LN = 1e4 + 3000 + 3;

using namespace std;

struct node {
	int idx, cnt;
	list<node> children;
};

int nameCnt;
list<node> nLi;
list<node>::iterator itArr[LN];
unordered_map<string, int> nameHash;

int delCnt;

void init()
{
	nameCnt = 0;
	nLi.clear();
	for (int i = 0; i < LN; i++) {
		itArr[i] = nLi.end();
	}
	nameHash.clear();
}

void addSub(char mNode[], int mCnt, char mSubNode[][7])
{
	if(nameHash.count(mNode)==0) nameHash[mNode] = nameCnt++;
	int idx = nameHash[mNode];

	// 신규이면
	if (itArr[idx] == nLi.end()) {
		itArr[idx]=nLi.insert(nLi.end(), { idx, 0 });
	}

	for (int i = 0; i < mCnt; i++) {
		bool isExistSubNode = false;
		if (nameHash.count(mSubNode[i]) == 0) nameHash[mSubNode[i]] = nameCnt++;
		int subIdx = nameHash[mSubNode[i]];
		// sub node가 있을 경우
		for (auto it = itArr[idx]->children.begin(); it != itArr[idx]->children.end(); it++) {
			if (it->idx == nameHash[mSubNode[i]]) {
				it->cnt++;
				isExistSubNode = true;
				break;
			}
		}
		// sub node가 없을 경우 신규 insert
		if(isExistSubNode==false) itArr[subIdx] = itArr[idx]->children.insert(itArr[idx]->children.end(), { subIdx, 1 });
	}
}

void eraseSub(char mNode[], char mSubNode[])
{
	int idx = nameHash[mNode];
	int subIdx = nameHash[mSubNode];
	for (auto it = itArr[idx]->children.begin(); it != itArr[idx]->children.end(); it++) {
		if (it->idx == subIdx) {
			delCnt = it->cnt;
			if ((it->cnt) > 0) (it->cnt)--;
			if ((it->cnt) == 0) {
				itArr[idx]->children.erase(it);
				itArr[subIdx] = nLi.end();
			}
			return;
		}
	}
}

int changeSub(char mNode[], char mSubA[], char mSubB[])
{
	int idx = nameHash[mNode];
	int subIdxA = nameHash[mSubA];

	eraseSub(mNode, mSubA);
	int rst = delCnt;
	char mSubNode[1][7];
	strcpy(mSubNode[0], mSubB);
	addSub(mNode, 1, mSubNode);

	return rst;
}

int BFS(int idx) {
	//base condition
	if (itArr[idx]->children.size() == 0) return itArr[idx]->cnt;

	int sum = 0;
	for (auto it = itArr[idx]->children.begin(); it != itArr[idx]->children.end(); it++) {
		sum += BFS(it->idx);
	}

	return sum;
}

int countLeaf(char mNode[])
{
	int idx = nameHash[mNode];

	return BFS(idx);
}