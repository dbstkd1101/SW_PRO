#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int Q;
int key, val;
struct node {
	int val,idx;
};
unordered_map<int, node> hTab(200000);

int nodeCnt;

int main() {
	freopen("input.txt", "r", stdin);
	cin >> Q;
	nodeCnt = 0;
	for (; Q; Q--) {
		cin >> key >> val;
		node tmp;
		auto it = hTab.find(key);
		if (it == hTab.end()) {
			tmp = { val, ++nodeCnt };
			it=hTab.insert({ key, tmp }).first;
		}
		else {
			it->second.val = val;
		}
		cout << it->second.idx << " " << it->second.val << endl;
	}

	return 0;
}