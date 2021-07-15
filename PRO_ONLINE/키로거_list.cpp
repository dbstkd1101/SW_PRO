#include<stdio.h>
#include<iostream>
#include<list>
#include<string>
using namespace std;

const int LM = 1e6 + 3;	// 1e6 : double 1,000,000
//char str[LM];
string str;
list<char> li;

int main() {
	freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	for (; t; t--) {
		li.clear();
		auto it = li.begin();	// list<char>::iterator
		//scanf("%s", str);
		cin >> str;
		for (int i = 0; i < str.size(); i++) {
			if (str[i] == '-') {
				if (it != li.begin()) it = li.erase(--it);
				//li.erase(prev(it, 1));
			}
			else if (str[i] == '<') {
				if (it != li.begin()) --it;
			}
			else if (str[i] == '>') {
				if (it != li.end()) ++it;
			}
			else {	// insert
				li.insert(it, str[i]);
			}
		}
		for (char c : li) cout << c;
		cout << endl;
	}
	return 0;
}