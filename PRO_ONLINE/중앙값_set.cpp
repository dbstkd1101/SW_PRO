#include<iostream>
#include<set>
#include<stdio.h>
using namespace std;

multiset<int> left_s, right_s;	// ��������

int main() {
	freopen("input.txt", "r", stdin);
	int n, mid, a, b;
	cin >> n >> mid;
	cout << mid << endl;
	for (int i = 1; i <= n / 2; i++) {
		cin >> a >> b;
		mid < a ? right_s.insert(a) : left_s.insert(a);
		mid < b ? right_s.insert(b) : left_s.insert(b);

		// ���� > ������
		if (left_s.size() > right_s.size()) {
			right_s.insert(mid);
			mid = *left_s.rbegin();
			//mid = *(--left_s.end());
			//left_s.erase(mid); // �ߺ��Ǵ� �� ��������
			left_s.erase(--left_s.end());
		}

		// ���� < ������
		else if (left_s.size() < right_s.size()) {
			left_s.insert(mid);
			mid = *right_s.begin();
			right_s.erase(right_s.begin());
		}

		// ���� == ������
		// �Ұž���

		cout << mid << endl;
	}
	return 0;
}