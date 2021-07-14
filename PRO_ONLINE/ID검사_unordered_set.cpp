#include<stdio.h>
#include<unordered_set>
#include<set>
using namespace std;

char str[13];
unordered_set<string> member, active;	// O(1+a)
//set<string> member, active;			// O(log n)

int validate() {
	return member.count(str);
}

int activate() {
	return active.count(str);
}
int signup() {
	member.insert(str);
	return member.size();
}
int close() {
	member.erase(str);
	active.erase(str);
	return member.size();
}
int login() {
	if (member.count(str)) active.insert(str);
	return active.size();
}
int logout() {
	active.erase(str);
	return active.size();
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