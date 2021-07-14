#include<iostream>
#include<queue>
#include<stdio.h>
using namespace std;

priority_queue<int> left_pq;	// max_pq
priority_queue<int, vector<int>, greater<int>> right_pq; // min_pq

int main() {
	freopen("input.txt", "r", stdin);
	int n, mid, a, b;
	cin >> n >> mid;
	cout << mid << endl;
	for (int i = 1; i <= n / 2; i++) {
		cin >> a >> b;
		mid < a ? right_pq.push(a) : left_pq.push(a);	// 조건 ? 참 : 거짓
		mid < b ? right_pq.push(b) : left_pq.push(b);

		// 왼쪽 > 오른쪽
		if (left_pq.size() > right_pq.size()) {
			right_pq.push(mid);
			mid = left_pq.top();
			left_pq.pop();
		}

		// 왼쪽 < 오른쪽
		else if (left_pq.size() < right_pq.size()) {
			left_pq.push(mid);
			mid = right_pq.top();
			right_pq.pop();
		}

		// 왼쪽 == 오른쪽
		// 할거없음

		cout << mid << endl;
	}
	return 0;
}