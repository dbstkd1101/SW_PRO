#include<iostream>
#include<set>
#include<stdio.h>

const int LM = 1e5+1;

using namespace std;

struct member {
	int id, freq;
	bool operator<(const member& r) const {
		return freq != r.freq ? freq < r.freq : id < r.id;
	}
};

set<member> memSet;
set<member>::iterator iter[LM];

int N, M;
int cmd;
int id, freq;

int freqSum;
int main() {
	freopen("input.txt", "r", stdin);
	for (auto& d : iter) d = memSet.end();
	freqSum = 0;
	cin >> N >> M;
	for (; M; M--) {
		cin >> cmd;
		if (cmd == 0) {
			cin >> id >> freq;
			iter[id] = (memSet.insert({ id, freq })).first;
			freqSum += iter[id]->freq;
		}
		else if(cmd == 1) {
			auto it = memSet.begin();
			memSet.erase(it);
			freqSum -= it->freq;
		}
		else if (cmd == 2) {
			auto it = memSet.end();
			memSet.erase(it);
			freqSum -= it->freq;
		}
		else if (cmd == 3) {
			int rst = freqSum;
			if (memSet.size() >= 2) {
				auto beginIt = memSet.begin();
				auto endIt = (memSet.end());
				rst - beginIt->freq - (--endIt)->freq;
			}
			else if (memSet.size() == 1) {
				auto beginIt = memSet.begin();
				rst - beginIt->freq;
			}
			printf("%d\n", rst);
		}
	}

	return 0;
}