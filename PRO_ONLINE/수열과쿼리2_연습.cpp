#include <stdio.h>
#include <list>
#include <string>
using namespace std;

list<int> li;

int T, Q;
int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &T);
	while(T--){
		li.clear();
		scanf("%d", &Q);
		while (Q--) {
			char input[10];
			int combination[101];
			scanf("%s", input);
			string tmp(input);
			if (tmp == "insert") {
				int x;
				scanf("%d", &x);
				if (li.size() > 0) {
					auto it = lower_bound(li.begin(), li.end(), x);
					if(it==li.end()) li.insert(it, x);
					else {
						if (*it != x) li.insert(it, x);
					}
				}
				else li.insert(li.begin(), x);
			}
			if (tmp == "erase") {
				int x;
				scanf("%d", &x);
				auto it = lower_bound(li.begin(), li.end(), x);
				if (it != li.end()) {
					if (*it == x) li.erase(it);
				}
			}
			if (tmp == "update") {
				int x, y;
				scanf("%d %d", &x, &y);
				auto it2 = lower_bound(li.begin(), li.end(), y);
				if (it2 == li.end()) {
					auto it1 = lower_bound(li.begin(), li.end(), x);
					if (it1 != li.end()) {
						it1=li.erase(it1);
						auto it3=lower_bound(li.begin(), li.end(), y);
						li.insert(it3, y);
					}
				}
			}
			if (tmp == "front") {
				if (li.size() == 0) {
					printf("empty\n");
					continue;
				}
				int c;
				scanf("%d\n", &c);
				int pos;
				if (c > li.size()) pos = li.size();
				else pos = c;

				auto it = next(li.begin(), (pos-1));
				printf("%d\n", *it);
			}
			if (tmp == "back") {
				if (li.size() == 0) {
					printf("empty\n");
					continue;
				}
				int c;
				scanf("%d\n", &c);
				int pos;
				if (c > li.size()) pos = li.size();
				else pos = c;

				auto it = prev((li.end()), pos);
				printf("%d\n", *it);
			}
		}
	}

	return 0;
}