#include<iostream>
#include<unordered_map>
#include<string>
using namespace std;

unordered_map<int, int> htab;

int update(char c) {
	if (c == 'A') return 1e8;
	if (c == 'C') return 1e4;
	if (c == 'G') return 1;
	return 0;
}

int main() {
	freopen("input.txt", "r", stdin);
	string str;
	int K, ret = 0, key = 0;
	cin >> K >> str;
	for (int i = 0; i < str.size(); i++) {
		key += update(str[i]);
		if (i >= K) key -= update(str[i - K]);
		if (i + 1 >= K) ret = max(ret, ++htab[key]);
	}
	cout << ret << endl;
	return 0;
}