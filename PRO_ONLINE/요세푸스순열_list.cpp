#include<iostream>
#include<list>
using namespace std;

int n, k;
list<int> li;

int main() {
	freopen("input.txt", "r", stdin);
	cin >> n >> k;
	for (int i = 1; i <= n; i++) li.push_back(i);
	//auto it = li.begin();
	list<int>::iterator it = li.begin();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < k; j++) {
			++it;	// it++ : ���ʿ��� ��ü ����/�ı��� ����
			if (it == li.end()) it = li.begin();
		}
		cout << *it << " ";
		it = li.erase(it);
		if (it == li.end()) it = li.begin();
	}
	return 0;
}