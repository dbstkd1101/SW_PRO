#include <stdio.h>
#include <list>
#include <iostream>
#include <string>

using namespace std;

int T;

list<char> li;
string str;
//char str[1000001];

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		li.clear();
		// auto는 생성과 동시에 초기화 필수
		auto it = li.begin(); // list<char>::iterator
		//scanf("%s", str);
		cin >> str;
		//for (int j = 0; str[j]; j++) {
		for (int j = 0; j<str.size(); j++) {
			char back = str[j];
			switch (back) {
			case '<':
				if (it != li.begin()) {
					it--;
				}
				break;
			case '>':
				if (it != li.end()) {
					it++;
				}
				break;
			case '-':
				if(it!=li.begin())it=li.erase(--it);
				// == li.erase(prev(it, 1));
				break;
			default : 
				li.push_back(str[j]);
				break;
			}
		}
		for (char c : li) cout << c;
		cout << endl;
	}

}