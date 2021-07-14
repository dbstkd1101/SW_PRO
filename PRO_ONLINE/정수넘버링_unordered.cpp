#include<stdio.h>
#include<algorithm>
#include<list>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

int idcnt;
struct Value { int id, value; };
unordered_map<int, Value> htab(200000);

int main() {
	freopen("input.txt", "r", stdin);
	int q, key, value;
	scanf("%d", &q);
	while (q--) {
		scanf("%d%d", &key, &value);
		if (htab.count(key)) htab[key].value = min(htab[key].value, value);
		else htab[key] = { ++idcnt, value };
		printf("%d %d\n", htab[key].id, htab[key].value);
		//auto it = htab.find(key);
		//if (it == htab.end()) 
		//	it = htab.insert({ key, {++idcnt, value} }).first;
		//	//htab[key] = { ++idcnt, value };
		//	//printf("%d %d\n", idcnt, value);
		//else it->second.value = min(it->second.value, value);
		//printf("%d %d\n", it->second.id, it->second.value);
	}
	return 0;
}