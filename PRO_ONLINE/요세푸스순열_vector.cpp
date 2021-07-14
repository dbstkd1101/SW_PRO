#include<iostream>
#include<vector>
using namespace std;

int n, k;
vector<int> v;

int main() {
	freopen("input.txt", "r", stdin);
	cin >> n >> k;
	v.reserve(n);
	for (int i = 1; i <= n; i++) {
		v.push_back(i);
		//cout << v.size() << " " << v.capacity() << endl;
	}
	int idx = 0;
	for (int i = 1; i <= n; i++) {
		idx = (idx + k - 1) % v.size();
		cout << v[idx] << " ";
		v.erase(v.begin() + idx);
	}
	return 0;
}