#include<unordered_map>
#include<unordered_set>
#include<string>
#include<vector>
#include<set>
using namespace std;
using pii = pair<int, int>;

unordered_set<int> prod;			// valid product list
unordered_map<string, int> htab;	// tag hash table
set<pii> s[1003];					// tag별 poduct list ( first:가격, second: id )
int tcnt;							// tag 개수

void init() {
	prod.clear();
	htab.clear(), htab.reserve(1000);
	for (int i = 1; i <= tcnt; i++) s[i].clear();
	tcnt = 0;
}

void incoming(int pid, int cost, int tagCnt, char tagString[][11]) {
	prod.insert(pid);
	for (int i = 0; i < tagCnt; i++) {
		int tid = htab[tagString[i]];
		if (!tid) htab[tagString[i]] = tid = ++tcnt;
		s[tid].insert({ cost, pid });
	}
}

int search(int tagCnt, char tagString[][11], int maxCnt, bool flag, int idList[]) {
	int c = 0;
	vector<int> tid;
	for (int i = 0; i < tagCnt; i++) {
		auto it = htab.find(tagString[i]);
		if (it != htab.end()) tid.push_back(it->second);
	}
	if (flag) {
		set<pii, greater<pii>> prior;
		for (int x : tid) {
			for (auto it = s[x].end(); it != s[x].begin();) {
				--it;
				if (!prod.count(it->second)) it = s[x].erase(it);
				else {
					prior.insert(*it);
					if (prior.size() > maxCnt) prior.erase(--prior.end());
				}
			}
		}
		for (auto p : prior) idList[c++] = p.second;
	}
	else {
		set<pii> prior;
		for (int x : tid) {
			for (auto it = s[x].begin(); it != s[x].end();) {
				if (!prod.count(it->second)) it = s[x].erase(it);
				else {
					prior.insert(*it);
					if (prior.size() > maxCnt) prior.erase(--prior.end());
					++it;
				}
			}
		}
		for (auto p : prior) idList[c++] = p.second;
	}
	return c;
}

int sell(int pid) {
	return prod.erase(pid);
}