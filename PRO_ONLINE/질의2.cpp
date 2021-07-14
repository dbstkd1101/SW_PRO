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
int val[100003];

int main() {
	freopen("input.txt", "r", stdin);
	int q, cmd, id, value;
	scanf("%d", &q);
	while (q--) {
		scanf("%d", &cmd);
		if (cmd == 1) {
			scanf("%d%d", &id, &value);
			if (val[id]) s.erase({ id, val[id] });
			s.insert({ id, value });
			val[id] = value;
		}
		if (cmd == 2) {
			scanf("%d", &id);
			s.erase({ id, val[id] });
			val[id] = 0;
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