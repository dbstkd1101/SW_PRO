#include<stdio.h>
#include<unordered_map>
#include<algorithm>
#include<string>
#include<set>
using namespace std;

const int LM = 2e5 + 3;
int value[LM], idcnt;
unordered_map<string, int> htab(LM);	// ¹®ÀÚ¿­¿¡ ´ëÇÑ id

int main() {
	int q, val;
	char str[23];
	scanf("%d", &q);
	while (q--) {
		scanf("%s%d", str, &val);
		for (int i = 0; str[i]; i++) str[i] = tolower(str[i]);
		//for (int i = 0; str[i]; i++)
		//	if (str[i] < 'a') str[i] = str[i] - 'A' + 'a';

		int id = htab[str];
		if (!id) htab[str] = id = ++idcnt;
		value[id] = max(value[id], val);
		printf("%d %d\n", id, value[id]);
	}
	return 0;
}