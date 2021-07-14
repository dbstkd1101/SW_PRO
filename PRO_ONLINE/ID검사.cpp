#include<stdio.h>
#include<algorithm>
#include<list>
#include<vector>
#include<unordered_map>
#include<algorithm>

using namespace std;

struct member {
	string id;
	int login;
}members[500003];

unordered_map<string, int> hTab(500003);

int N, cmd;
int memCnt;
int loginCnt;

int validate(char* ID) {
	string tmp(ID);
	auto it = hTab.find(tmp);
	if (it == hTab.end()) return 0;
	else return 1;
}

int activate(char* ID) {
	string tmp(ID);
	return members[hTab[tmp]].login;
}

int signup(char* ID) {
	if (!validate(ID)) {
		string tmp(ID);
		//hTab.insert({ id, ++memCnt });
		hTab[tmp] = { ++memCnt };
		members[memCnt].id = tmp;
		members[memCnt].login = 0;
	}
	return hTab.size();
}

int close(char* ID) {
	if (validate(ID)) {
		if (activate(ID)) {
			loginCnt--;
		}
		string tmp(ID);
		hTab.erase(tmp);
		memCnt--;
	}
	return memCnt;
}

int login(char* ID) {
	if (validate(ID) && !activate(ID)) {
		string tmp(ID);
		members[hTab[tmp]].login = 1;
		loginCnt++;
	}
	return loginCnt;
}

int logout(char* ID) {
	if (validate(ID) && activate(ID)) {
		string tmp(ID);
		members[hTab[tmp]].login = 0;
		loginCnt--;
	}
	return loginCnt;
}

int main() {
	freopen("input.txt", "r", stdin);
	hTab.clear();
	memCnt = 0;
	scanf("%d", &N);
	while (N--) {
		char id[13];
		scanf("%d", &cmd);
		scanf("%s", &id);
		if (cmd == 1) {
			return validate(id);
		}
		if (cmd == 2) {
			return activate(id);
		}
		if (cmd == 3) {
			return signup(id);
		}
		if (cmd == 4) {
			return close(id);
		}
		if (cmd == 5) {
			return login(id);
		}
		if (cmd == 6) {

		}
	}

	return 0;
}