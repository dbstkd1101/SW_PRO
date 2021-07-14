#include<stdio.h>
#include<set>
using namespace std;

struct Data {
	int id, value;
	bool operator<(const Data& r) const {
		return value != r.value ? value < r.value : id < r.id;
	}
};
set<Data> s;
set<Data>::iterator iter[100003];

int main() {
	freopen("input.txt", "r", stdin);
	int q, cmd, id, value;
	scanf("%d", &q);
	//for (int i = 1; i <= 100000; i++) iter[i] = s.end();
	for (auto& d : iter) d = s.end();
	while (q--) {
		scanf("%d", &cmd);
		if (cmd == 1) {
			scanf("%d%d", &id, &value);
			if (iter[id] != s.end()) s.erase(iter[id]);
			iter[id] = s.insert({ id, value }).first;
		}
		if (cmd == 2) {
			scanf("%d", &id);
			if (iter[id] != s.end()) s.erase(iter[id]);
			iter[id] = s.end();
		}
		if (cmd == 3) {
			printf("%d\n", s.empty() ? -1 : s.begin()->id);	// (*s.begin()).id
		}
		if (cmd == 4) {
			printf("%d\n", s.empty() ? -1 : s.rbegin()->id);
		}
	}

	return 0;
}