#include<stdio.h>
#include<unordered_map>
#include<map>
using namespace std;

char str[13];
int loginCnt;
unordered_map<string, bool> htab(500000);	// O(1+a)
//map<string, bool> htab;						// O(log n)

int validate() {
	return htab.count(str);
}

int activate() {
	return htab.count(str) && htab[str];
}
int signup() {
	//if(!htab.count(str)) htab[str] = 0;
	htab.insert({ str, 0 });
	return htab.size();
}
int close() {
	loginCnt -= htab[str];
	htab.erase(str);
	return htab.size();
}
int login() {
	auto it = htab.find(str);
	if (it != htab.end() && !it->second) {
		loginCnt++;
		it->second = 1;
	}
	return loginCnt;
}
int logout() {
	auto it = htab.find(str);
	if (it != htab.end() && it->second) {
		loginCnt--;
		it->second = 0;
	}
	return loginCnt;
}

int main() {
	freopen("input.txt", "r", stdin);
	int q, cmd, ret;
	scanf("%d", &q);
	while (q--) {
		scanf("%d%s", &cmd, str);
		if (cmd == 1) ret = validate();
		if (cmd == 2) ret = activate();
		if (cmd == 3) ret = signup();
		if (cmd == 4) ret = close();
		if (cmd == 5) ret = login();
		if (cmd == 6) ret = logout();
		printf("%d\n", ret);
	}
	return 0;
}