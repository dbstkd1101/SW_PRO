#include <stdio.h>
// vector는 FILO에 안좋지.
//#include <vector>
#include <list>

#include <stack>

using namespace std;

list<int> li;
int main() {
	//freopen("input.txt", "r", stdin);
	int n, value;
	char cmd;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		// blak character(공백, 엔터) 무시를 위해 앞에 공백
		scanf(" %c", &cmd);
		if (cmd == 'i') {
			scanf("%d", &value);
			//v.push_back(value);
			li.push_back(value);
		}
		if (cmd == 'c') {
			//printf("%d\n", v.size());
			printf("%d\n", li.size());
		}
		if (cmd == 'o') {
			if (li.empty()) printf("empty\n");
			else {
				//printf("%d\n", v.back());
				//v.pop_back();
				printf("%d\n", li.front());
				li.pop_front();
			}
		}
	}


	return 0;
}