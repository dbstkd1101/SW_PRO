#include<stdio.h>
#include<algorithm>
#include<list>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

const int SIZE = 1 << 18;
struct Data {
	int key, id, value;
};
//list<Data> htab[SIZE];
vector<Data> htab[SIZE];
int idcnt;

auto probing(int key, int value) {
	int hidx = (unsigned int)key % SIZE;
	for (auto& d : htab[hidx]) {
		if (d.key == key) {
			d.value = min(d.value, value);
			return d;
		}
	}
	htab[hidx].push_back({ key, ++idcnt, value });
	return htab[hidx].back();
}

int main() {
	freopen("input.txt", "r", stdin);
	int q, key, value;
	scanf("%d", &q);
	while (q--) {
		scanf("%d%d", &key, &value);
		Data d = probing(key, value);
		printf("%d %d\n", d.id, d.value);
	}
	return 0;
}