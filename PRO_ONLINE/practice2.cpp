#include <iostream>
#include <set>
#include <map>

using namespace std;

struct Data {
	int a, b, c, d, e;
	bool operator<(const Data& r) const {
		return a < r.a;
	}
};

int main() {
	set<int, greater<int>> s{ 4, 4, 4, 2, 3, 4, 5, 12, 33, 65 };
	for (int x : s) cout << x << " ";
	cout << endl;

	set<Data> s2; // set<Data, less<Data>>s2

	return 0;
}
