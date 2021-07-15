#include <stdio.h>
#include <list>
#include <string.h>
#include <iostream>

using namespace std;

const int LN = 1e6 + 3;
int T;

char input[LN];

list<char> li;

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &T);

	while (T--) {
		memset(input, 0, sizeof(input));
		li.clear();
		scanf("%s", input);
		auto it = li.begin();
		for (int i = 0; input[i]; i++) {
			if (input[i] == '-') {
				if (it != li.begin()) li.erase(--it);
			}
			else if (input[i] == '<') {
				if(it!=li.begin()) it--;
			}
			else if (input[i] == '>') {
				if(it!=li.end()) it++;
			}
			else {
				li.insert(it, input[i]);
			}
		}
		for (it = li.begin(); it != li.end(); it++) {
			printf("%c", *it);
		}
		puts("");
	}

	return 0;
}