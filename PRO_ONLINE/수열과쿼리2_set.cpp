#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<set>
#include<stdio.h>
#include<algorithm>
using namespace std;

set<int> s;


// 알아서 정렬→it 찾을 필요 없음.
void insert(int x) {
	auto ret = s.insert(x);
	// ret.first : 입력된 iterator
	// ret.second : 1 or 0 넣었는지 안넣었는지
}

void erase(int x) {
	auto ret = s.erase(x);
	// ret : 1 or 0
}

void update(int x, int y) {
	// list처럼 순회하면서 찾을 필요 없음
	if (!s.count(x) || s.count(y)) return;
	s.erase(x);
	s.insert(y);
}

void front(int c) {
	if (s.empty()) {
		cout << "empty" << endl;
		return;
	}
	c = min(c, (int)s.size());	// size_t : unsgined long long 
	// -1 여부 조심
	cout << *next(s.begin(), c - 1) << endl;
}

void back(int c) {
	if (s.empty()) {
		cout << "empty" << endl;
		return;
	}
	c = min(c, (int)s.size());	// size_t : unsgined long long 

	// -0 여부 조심
	cout << *prev(s.end(), c) << endl;
}

int main() {
	freopen("input.txt", "r", stdin);
	int t, q, x, y;
	string cmd;
	cin >> t;
	while (t--) {
		cin >> q;
		s.clear();
		while (q--) {
			cin >> cmd >> x;
			if (cmd == "insert") insert(x);
			if (cmd == "erase") erase(x);
			if (cmd == "update") {
				cin >> y;
				update(x, y);
			}
			if (cmd == "front") front(x);
			if (cmd == "back") back(x);
		}
	}
	return 0;
}