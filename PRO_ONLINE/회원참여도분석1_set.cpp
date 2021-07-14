#include<stdio.h>
#include<set>
using namespace std;
using pii = pair<int, int>;	// operator <, <=, >, >=, ==, !=

int n, m, total;
set<pii> s;	// first: freq  , second: id

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	int cmd, id, freq;
	while (m--) {
		scanf("%d", &cmd);
		if (cmd == 0) {
			scanf("%d%d", &id, &freq);
			s.insert({ freq, id });
			total += freq;
		}
		if (cmd == 1) {
			if (s.size()) {
				printf("%d\n", s.begin()->second);
				total -= s.begin()->first;
				s.erase(s.begin());
			}
		}
		if (cmd == 2) {
			if (s.size()) {
				printf("%d\n", s.rbegin()->second);
				total -= s.rbegin()->first;
				s.erase(--s.end());
			}
		}
		if (cmd == 3) {
			if (s.size() <= 2) printf("0\n");
			else printf("%d\n", total - s.begin()->first - s.rbegin()->first);
		}
	}
	return 0;
}